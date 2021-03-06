#include "cowboy.h"
#include <ruby.h>
#include <stdlib.h>

long size_of_ary(VALUE nums){
  Check_Type(nums, T_ARRAY);
  return RARRAY_LEN(nums);
}

long size_of_str(VALUE str){
  Check_Type(str, T_STRING);
  return RSTRING_LEN(RSTRING(str));
}

long size_of_val(VALUE v){
  if (TYPE(v) == T_STRING) {
    return size_of_str(v);
  } else if (TYPE(v) == T_ARRAY) {
    return size_of_ary(v);
  } else {
    rb_raise(rb_eNotImpError, "Size_of_val Needs a string or array");
    return 0;
  }
}

void cast_string_to_complex(double * fc, VALUE str){
  double * s;
  long len;
  int i, j, a;
  double d;
  void *p;
  double t = 2.3;

  p = &d;

  s = (double *) RSTRING_PTR(RSTRING(str));
  len = RSTRING_LEN(RSTRING(str)) / 8;

  for(i = 0; i < len; i++){
    fc[i] = s[i];
  }
}

void cast_nums_to_complex(double * fc, VALUE nums){
  long len;
  int i;
  VALUE n;
  Check_Type(nums, T_ARRAY);
  i = 0;

  for(len = 0; len < size_of_ary(nums); len++){
    n = rb_ary_entry(nums, len);
    fc[len] = NUM2DBL(n);
  }
}

void cast_val_to_complex(double * fc, VALUE v){
  if (TYPE(v) == T_STRING) {
    cast_string_to_complex(fc, v);
  } else if (TYPE(v) == T_ARRAY) {
    cast_nums_to_complex(fc, v);
  } else {
    rb_raise(rb_eNotImpError, "Needs a string or array");
  }
}

fftw_complex * allocate_fftw_complex(long n){
  fftw_complex * fc;
  fc = ALLOC_N(fftw_complex, n);
  return fc;
}

VALUE c_to_rb_complex(double r, double i){
  VALUE cplx = rb_path2class("Complex");
  return rb_funcall(cplx, rb_intern("rect"), 2,
                    DBL2NUM(r), DBL2NUM(i));
}

void Init_cowboy_complex(){
}
