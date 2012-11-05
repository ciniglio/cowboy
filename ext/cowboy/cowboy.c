#include "cowboy.h"

VALUE mCowboy;

VALUE fft_1d(VALUE m, VALUE v) {
  fftw_complex *in, *out;
  fftw_plan fp;
  int n;

  n = (int) size_of_val(v);
  if (n == 0) {
    rb_raise(rb_eException, "Can't use empty set of samples");
  }

  in = allocate_fftw_complex(n);
  out = allocate_fftw_complex(n);
  fp = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

  cast_val_to_complex(in, v);

  fftw_execute(fp);
  free(in);
  fftw_destroy_plan(fp);

  return ca_wrap_struct_class(out, n);
}

void Init_cowboy() {
  mCowboy = rb_define_module("Cowboy");

  Init_cowboy_complex();
  Init_cowboy_array();

  rb_define_module_function(mCowboy, "fft_1d", fft_1d, 1);
}
