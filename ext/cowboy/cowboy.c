#include "cowboy.h"

VALUE mCowboy;

  double *in;
  fftw_complex *out;
  fftw_plan fp;
  int n;

  n = (int) size_of_val(v);
  if (n == 0) {
    rb_raise(rb_eException, "Can't use empty set of samples");
  }

  in = calloc(n, sizeof(double));
  out = allocate_fftw_complex(n/2 + 1);
  fp = fftw_plan_dft_r2c_1d(n, in, out, FFTW_ESTIMATE);

  cast_val_to_complex(in, v);

  fftw_execute(fp);
  free(in);
  fftw_destroy_plan(fp);

  return ca_wrap_struct_class(out, n/2 + 1);
}

void Init_cowboy() {
  mCowboy = rb_define_module("Cowboy");

  Init_cowboy_complex();
  Init_cowboy_array();

  rb_define_module_function(mCowboy, "fft_1d", fft_1d, 1);
}
