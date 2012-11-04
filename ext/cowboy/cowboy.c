#include "cowboy.h"

VALUE mCowboy;

VALUE fft_1d(VALUE m, VALUE nums){
  fftw_complex *in, *out;
  fftw_plan fp;
  int n;

  Check_Type(nums, T_ARRAY);

  n = (int) size_of_ary(nums);
  if (n == 0){
    rb_raise(rb_eException, "Can't use blank array");
  }
  in = allocate_fftw_complex(n);
  out = allocate_fftw_complex(n);
  fp = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

  cast_nums_to_complex(in, nums);

  fftw_execute(fp);
  free(in);
  fftw_destroy_plan(fp);

  return complex_to_real_nums(out, n);
}

void Init_cowboy(){
  mCowboy = rb_define_module("Cowboy");

  Init_cowboy_complex();

  rb_define_module_function(mCowboy, "fft_1d", fft_1d, 1);
}
