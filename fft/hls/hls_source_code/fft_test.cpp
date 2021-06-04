# include "fft.h"
# include <fstream>
# include <iostream>
using namespace std;

void read_into_array(string filename, IN_TYPE arr[]) {
	iter i=0;
	string srg;
	ifstream filestream(filename);

	if (filestream.is_open()) {
		while ( getline (filestream,srg) ) {
			if(i==SIZE_) {
				cout << "File has more elements than " << SIZE_ << "\n";
			}

			arr[i] = stof(srg);
			i++;
		}
		filestream.close();
	}
	else {
	  cout << "File opening failed." << "\n" ;
	}
}

void display_complex_array(IN_TYPE real[], IN_TYPE img[]) {
	for(iter i=0; i<SIZE_; i++) {
		cout << real[i];
		if(img[i] < 0) {
			cout << " - j" << img[i]*-1 << "\n";
		}
		else {
			cout << " + j" << img[i] << "\n";
		}
	}
}

int main() {
	string filename;

	// Reading inputs
	IN_TYPE real[SIZE_], img[SIZE_];

	filename = "E:\\PYNQ\\xilinx_tutorials\\fft_1024_taps\\hls\\hls_source_files\\real_input.txt";
	read_into_array(filename, real);

	filename = "E:\\PYNQ\\xilinx_tutorials\\fft_1024_taps\\hls\\hls_source_files\\img_input.txt";
	read_into_array(filename, img);

	cout << "\n Displaying input values \n";
	display_complex_array(real, img);

	// Reading Ground Truth Output
	IN_TYPE gnd_real[SIZE_], gnd_img[SIZE_];

	filename = "E:\\PYNQ\\xilinx_tutorials\\fft_1024_taps\\hls\\hls_source_files\\real_output.txt";
	read_into_array(filename, gnd_real);

	filename = "E:\\PYNQ\\xilinx_tutorials\\fft_1024_taps\\hls\\hls_source_files\\img_output.txt";
	read_into_array(filename, gnd_img);

	cout << "\nDisplaying ground truth values \n";
	display_complex_array(gnd_real, gnd_img);

	// Testing IP
	fft(real, img);

	cout << "\nDisplaying IP output values \n";
	display_complex_array(real, img);

	// Comparing Ground Truth and the IP's Output
	int ret_val = 0;
	IN_TYPE real_error_margin, img_error_margin;
	for(int i=0; i<SIZE_; i++) {
		if (gnd_real[i] != 0) {
			real_error_margin = ( gnd_real[i] - real[i] ) / gnd_real[i];
		}
		else {
			real_error_margin = float (( gnd_real[i] - real[i] )) / 0.001;
		}

		if (gnd_img[i] != 0) {
			img_error_margin = ( gnd_img[i] - img[i] ) / gnd_img[i];
		}
		else {
			img_error_margin = float(( gnd_img[i] - img[i] ))  / 0.001;
		}

		if(real_error_margin*100 > 0.009 && img_error_margin*100 > 0.009 ) {
			ret_val++;
			cout << "Error: " << gnd_real[i] << " + j" << gnd_img[i] << " =/= ";
			cout << real[i] << " + j" << img[i] << "\n";
			cout << "Error: " << real_error_margin << " and " << img_error_margin << "\n";
		}
	}

	cout << "\n";

	cout << "********************************\n";
	cout << " There were "<<ret_val<<" errors\n";
	cout << "********************************\n";

	return ret_val;
}
