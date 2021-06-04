# ifndef _FFT_
# define _FFT_

# include <ap_int.h>
# include <hls_math.h>

# define M 10
# define SIZE_ 1024
# define PI 3.141592653589

typedef ap_int<32> iter;
typedef ap_uint<10> index_t;

typedef float IN_TYPE; 			// data type for the input signal
typedef float TEMP_TYPE; 		// data type for the temporary variables

index_t reverse_bits(index_t input);
void bit_reverse(IN_TYPE X_R[SIZE_], IN_TYPE X_I[SIZE_]);
void fft(IN_TYPE X_R[SIZE_], IN_TYPE X_I[SIZE_]);

# endif
