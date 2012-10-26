#include "cowboy.h"
#include <ruby.h>

long size_of_ary(VALUE nums){
  Check_Type(nums, T_ARRAY);
  return RARRAY_LEN(nums);
}

fftw_complex * cast_nums_to_complex(VALUE nums){
  long len;
  fftw_complex * fc;
  int i;
  VALUE n;
  Check_Type(nums, T_ARRAY);
  len = RARRAY_LEN(nums);
  fc = ALLOC_N(fftw_complex, len);
  i = 0;

  while((n =rb_ary_shift(nums)) != Qnil){
    fc[i][0] = NUM2DBL(n);
    fc[i][1] = 0;
    i++;
  }
  return fc;
}

VALUE complex_to_real_nums(fftw_complex *fc, long N){
  VALUE ar = rb_ary_new();
  int i;
  for(i = 0; i < N; i++){
    rb_ary_push(ar, DBL2NUM(fc[i][0]));
  }
  return ar;
}

VALUE test_back_and_from_complex(VALUE m, VALUE nums){
  Check_Type(nums, T_ARRAY);
  return complex_to_real_nums(cast_nums_to_complex(nums),
                              size_of_ary(nums));
}

void Init_cowboy_complex(){
  //rb_define_module_function(mCowboy, "test_complex", test_back_and_from_complex, 1);
}
