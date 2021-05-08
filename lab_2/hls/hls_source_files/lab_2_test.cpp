# include "lab_2.h"
# include <iostream>
using namespace std;

int main() {
	data_t A[3] = {190.23, 23.4, 1};
	data_t B[3] = {87.2, 45.7, 29.0};
	data_t C[3] = {905.63, 1.45, 0.72};

	// Calculating the Ground Truth
	data_t gnd_truth[3] = {0.0};
	for(int i=0; i<3; i++) {
		data_t t1 = A[i]/C[i];
		data_t t2 = B[i]/C[i];
		gnd_truth[i] = data_t( hls::log(t1.to_float()) + hls::sqrt(t2.to_float()) );
	}

	// Storing the IP's output in out array
	data_t out[3] = {0.0};
	for(int i=0; i<3; i++) {
		lab_2(A[i], B[i], C[i], out[i]);
	}

	// Comparing Ground Truth and the IP's Output
	int ret_val = 0;
	for(int i=0; i<3; i++) {
		float error_margin = float( (gnd_truth[i] - out[i]) / gnd_truth[i] );
		if(error_margin > 0.00001) {
			ret_val++;
		}
	}

	cout<<"********************************\n";
	cout<<" There were "<<ret_val<<" errors\n";
	cout<<"********************************\n";

	return ret_val;
}

