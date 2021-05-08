#ifndef _LAB_3_
#define _LAB_3_

#define N_TAPS 5

#include <ap_int.h>

typedef ap_int<32> data_t;
typedef ap_int<32> acc_t;

struct axis_stream {
	ap_uint<32> data;
	ap_uint<1> last;
};

void lab_3(axis_stream* in_data, axis_stream* out_data, ap_int<32> tmp);
#endif
