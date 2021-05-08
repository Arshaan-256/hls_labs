# include "lab_2.h"

void lab_2(data_t A, data_t B, data_t C, data_t &Y) {
	data_t t1 = A/C;
	data_t t2 = B/C;
	Y = data_t( hls::log(t1.to_float()) + hls::sqrt(t2.to_float()) );
}
