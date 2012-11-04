#ifndef RUBY_COWBOY_COMPLEX
#define RUBY_COWBOY_COMPLEX

#include <cowboy.h>

void Init_cowboy_complex();

void cast_nums_to_complex(fftw_complex * fc, VALUE nums);
fftw_complex * allocate_fftw_complex(long n);
VALUE complex_to_real_nums(fftw_complex * fc, long N);
long size_of_ary(VALUE nums);
VALUE c_to_rb_complex(double r, double i);

#endif
