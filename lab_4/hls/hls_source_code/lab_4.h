#ifndef _lab_4_
#define _lab_4_

#include <ap_fixed.h>
#include <ap_int.h>

# define N_TAPS 5

// ap_fixed<W,I>
typedef ap_fixed<32,16> data_t;
typedef ap_fixed<32,16> acc_t;

struct axis_stream {
	data_t data;
	ap_uint<1> last;
};

void lab_4(axis_stream* in_data, axis_stream* out_data, int tmp);
#endif
