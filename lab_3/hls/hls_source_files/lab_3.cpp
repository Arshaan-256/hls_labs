#include "lab_3.h"

void lab_3(axis_stream *in_data, axis_stream *out_data, ap_int<32> tmp) {
#pragma HLS CLOCK domain=default
#pragma HLS INTERFACE s_axilite register port=tmp clock=control
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=in_data
#pragma HLS INTERFACE axis port=out_data

	static data_t shift_reg[N_TAPS];
	acc_t acc = 0;
	int i;

	SR:
	for(i=N_TAPS-1; i>=1; i--) {
	#pragma HLS UNROLL factor=4
		shift_reg[i] = shift_reg[i-1];
	}
	shift_reg[0] = in_data->data;
	
	AC:
	for(i=0; i<N_TAPS; i++) {
	#pragma HLS PIPELINE II=2
	#pragma HLS UNROLL factor=4
		acc += shift_reg[i];
	}

	acc = acc / N_TAPS;
	out_data->data = acc;

	if(in_data->last == 1) {
		for(i=0; i<N_TAPS; i++) {
		# pragma HLS UNROLL
			shift_reg[i] = 0;
		}
	}

	out_data->last = in_data->last;
}
