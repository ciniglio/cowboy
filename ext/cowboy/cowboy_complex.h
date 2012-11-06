#ifndef RUBY_COWBOY_COMPLEX
#define RUBY_COWBOY_COMPLEX

#include <cowboy.h>

void Init_cowboy_complex();

long size_of_val(VALUE v);
void cast_val_to_complex(double * fc, VALUE v);

fftw_complex * allocate_fftw_complex(long n);

VALUE c_to_rb_complex(double r, double i);

#endif
