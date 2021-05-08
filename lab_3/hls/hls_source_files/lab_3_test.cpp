# include "lab_3.h"
# include <iostream>
using namespace std;

# define N_LENGTH 11

int main() {
	data_t input[N_LENGTH] = {
		0, 2, 4, 6, 8, 10, 8, 6, 4, 2, 0
	};

	data_t gnd_truth[N_LENGTH] = {0};
	data_t shift_reg[N_TAPS] = {0};

	// Calculating the Ground Truth
	int i, n;
	acc_t acc;
	for(n=0; n<N_LENGTH; n++) {
		acc = 0;
		for(i=N_TAPS-1; i>=1; i--) {
			shift_reg[i] = shift_reg[i-1];
		}
		shift_reg[0] = input[n];

		for(i=0; i<N_TAPS; i++) {
			acc += shift_reg[i];
		}
		gnd_truth[n] = acc / N_TAPS;
	}

	axis_stream in_stream[N_LENGTH], out_stream[N_LENGTH];

	// Storing the IP's output in out_stream array
	for(i=0; i<N_LENGTH; i++) {
		in_stream[i].data = input[i];
		in_stream[i].last = 0;

		if(i == N_LENGTH-1) {
			in_stream[i].last = 1;
		}

		lab_3(&in_stream[i], &out_stream[i], 32);
	}

	// Comparing Ground Truth and the IP's Output
	int ret_val=0;
	cout<<"gnd_output out_stream\n";
	for(i=0; i<N_LENGTH; i++) {
		cout<<gnd_truth[i]<<" "<<out_stream[i].data<<"\n";
		if(gnd_truth[i] != out_stream[i].data) {
			ret_val++;
		}
	}

	cout<<"********************************\n";
	cout<<" There were "<<ret_val<<" errors\n";
	cout<<"********************************\n";

	return ret_val;
}
