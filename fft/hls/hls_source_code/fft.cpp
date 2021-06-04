# include "fft.h"

index_t reverse_bits(index_t input) {
	iter i;
	int rev = 0;

	RB:
	for(i=0; i < M; i++) {
	# pragma HLS unroll factor=5
		rev = (rev << 1) | (input & 1);
		input = input >> 1;
	}
	return rev;
}

void bit_reverse(IN_TYPE X_R[SIZE_], IN_TYPE X_I[SIZE_]) {
	index_t reversed;
	iter i;
	IN_TYPE R_temp, I_temp;

	BR:
	for(i=0; i < SIZE_; i++) {
	# pragma HLS pipeline
		reversed = reverse_bits(i);
		if(i <= reversed) {
			// swap the real values
			R_temp = X_R[i];
			X_R[i] = X_R[reversed];
			X_R[reversed] = R_temp;

			// swap the imaginary values
			I_temp = X_I[i];
			X_I[i] = X_I[reversed];
			X_I[reversed] = I_temp;
		}
	}
}

void fft(IN_TYPE X_R[SIZE_], IN_TYPE X_I[SIZE_]) {
#pragma HLS INTERFACE s_axilite port=return bundle=crtl_bus
#pragma HLS INTERFACE m_axi depth=1024 port=X_R offset=slave
#pragma HLS INTERFACE m_axi depth=1024 port=X_I offset=slave
#pragma HLS INTERFACE s_axilite port=X_R
#pragma HLS INTERFACE s_axilite port=X_I

	TEMP_TYPE temp_R, temp_I;
	iter i, j, k, i_lower, stage;
	iter numBF, step, DFTpts;
	iter N2 = SIZE_ >> 1;

	bit_reverse(X_R, X_I);

	step = N2;
	IN_TYPE a, e, c, s;

	// Do M stages of butterflies
	stages:
	for(stage = 1; stage <= M; stage++) {
		DFTpts = 1 << stage;		// DFT = 2^stage = points in sub DFT
		numBF = DFTpts >> 1; 		// Butterfly WIDTHS in sub-DFT
		k=0;

		e = -2*PI/DFTpts;

		a = 0.0;
		// Perform butterflies for j-th stage
		butterfly:
			for(j = 0; j < numBF; j++) {
			# pragma HLS loop_tripcount min=1 max=512
			c = cos(a);
			s = sin(a);
			a = a + e;

			// Compute butterflies that use same W**k
			DFTpts:
				for(i = j; i <SIZE_; i += DFTpts) {
				# pragma HLS loop_tripcount min=1 max=512
					i_lower = i + numBF;			//index of lower point in butterfly
					temp_R = X_R[i_lower]*c - X_I[i_lower]*s;
					temp_I = X_I[i_lower]*c + X_R[i_lower]*s;

					X_R[i_lower] = X_R[i] - temp_R;
					X_I[i_lower] = X_I[i] - temp_I;
					X_R[i] = X_R[i] + temp_R;
					X_I[i] = X_I[i] + temp_I;
				}
			k += step;
		}
		step = step/2;
	}
}
