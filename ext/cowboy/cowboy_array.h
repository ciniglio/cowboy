#ifndef RUBY_COWBOY_ARRAY
#define RUBY_COWBOY_ARRAY

extern VALUE cCowboyArray;
void Init_cowboy_array();
VALUE ca_wrap_struct_class(fftw_complex *fc, long N);
#endif
