# ifndef _LAB_2_
# define _LAB_2_

# include <hls_math.h>
# include <ap_fixed.h>

// ap_fixed<W,I>
typedef ap_fixed<32,16> data_t;

void lab_2(data_t A, data_t B, data_t C, data_t &Y);

# endif
