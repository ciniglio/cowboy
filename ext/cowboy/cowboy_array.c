#include "cowboy.h"
#include <ruby.h>

VALUE cCowboyArray;

typedef struct cowboy_array {
  long N;
  fftw_complex* fc;
} CowboyArray;

static void ca_free(void * ca){
  free(((CowboyArray *)ca)->fc);
  free(ca);
}

VALUE array_index(VALUE self, VALUE index){
  fftw_complex * fc;
  CowboyArray * ca;
  long i = NUM2LONG(index);
  Data_Get_Struct(self, CowboyArray, ca);
  if (i >= ca->N){
    return Qnil;
  }
  return c_to_rb_complex(ca->fc[i][0],
                         ca->fc[i][1]);
}

VALUE array_size(VALUE self){
  fftw_complex * fc;
  CowboyArray * ca;
  Data_Get_Struct(self, CowboyArray, ca);
  return LONG2NUM(ca->N);
}

VALUE array_each(VALUE self){
  int i;
  fftw_complex * fc;
  CowboyArray * ca;
  Data_Get_Struct(self, CowboyArray, ca);

  if (!rb_block_given_p())
    rb_raise(rb_eArgError, "Expected Block");

  for(i = 0; i < ca->N; i++)
    rb_yield(c_to_rb_complex(ca->fc[i][0],
                             ca->fc[i][1]));
  return self;
}

VALUE ca_wrap_struct_class(fftw_complex *fc, long N){
  CowboyArray * ca;
  ca = ALLOC(CowboyArray);
  ca->N = N;
  ca->fc = fc;
  return Data_Wrap_Struct(cCowboyArray, 0, free, ca);
}

VALUE ca_not_implemented(VALUE self){
  rb_notimplement();
}

void Init_cowboy_array(){
  cCowboyArray = rb_define_class_under(mCowboy, "CowboyArray", rb_cObject);
  rb_define_method(cCowboyArray, "initialize", ca_not_implemented, 0);
  rb_define_method(cCowboyArray, "size", array_size, 0);
  rb_define_method(cCowboyArray, "[]", array_index, 1);
  rb_define_method(cCowboyArray, "each", array_each, 0);
  rb_include_module(cCowboyArray, rb_mEnumerable);
}
