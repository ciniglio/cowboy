#include "cowboy.h"
#include <ruby.h>

VALUE cCowboyData;

void check_type_cowboy_data(VALUE in){
  if (rb_obj_is_instance_of(in, cCowboyData) != Qtrue)
    rb_raise(rb_eTypeError, "Expected a CowboyData instance");
}

long get_size(VALUE data){
  VALUE sz = rb_iv_get(data, "@size");
  if (sz == Qnil)
    return -1;
  return NUM2LONG(sz);
}

long get_count_of_data(VALUE self){
  VALUE data = rb_iv_get(self, "@data");
  long len;

  check_type_cowboy_data(self);

  len = size_of_val(data);

  if (TYPE(data) == T_STRING){
    len /= get_size(self);
  }
  return len;
}

void get_doubles_from_string_data(double * out, char * str,
                                  long len, long size){
  int i;
  short * s; float * l; double * d;
  switch (size){
  case 1:
    for(i = 0; i < len; i++){
      out[i] = (double) str[i];
    }
    break;
  case 2:
    s = (short *) str;
    for(i = 0; i < len/size; i++){
      out[i] = s[i];
    }
    break;
  case 4:
    l = (float *) str;
    for(i = 0; i < len/size; i++){
      out[i] = l[i];
    }
    break;
  case 8:
    d = (double *) str;
    for(i = 0; i < len/size; i++){
      out[i] = d[i];
    }
    break;
  default:
    rb_raise(rb_eArgError, "Size must be 1,2,4, or 8");
    break;
  }
}

void get_doubles_from_array_data(double * out, VALUE in, long len){
  VALUE num;
  int i = 0;
  for(i = 0; i < len; i++){
    out[i] = NUM2DBL(rb_ary_entry(in, i));
  }
}

void get_doubles_from_data(double * out, VALUE in){
  VALUE data;
  long size;
  int i;

  check_type_cowboy_data(in);

  data = rb_iv_get(in, "@data");

  size = get_size(in);

  if (TYPE(data) == T_STRING){
    get_doubles_from_string_data(out, RSTRING_PTR(RSTRING(data)),
                                 size_of_val(data), size);
  } else if (TYPE(data) == T_ARRAY) {
    get_doubles_from_array_data(out, data, size_of_val(data));
  } else {
    rb_raise(rb_eException, "Something went awry");
  }
}

VALUE r_data_size(VALUE self){
  VALUE size = rb_iv_get(self, "@size");
  VALUE data = rb_iv_get(self, "@data");

  check_type_cowboy_data(self);

  if (size == Qnil){
    if (TYPE(data) == T_ARRAY){
      size = LONG2NUM(-1);
    }
  }
  rb_iv_set(self, "@size", size);
  return size;
}

VALUE r_data_init(int argc, VALUE * argv, VALUE self){
  VALUE data, size;
  rb_scan_args(argc, argv, "11", &data, &size);

  rb_iv_set(self, "@data", data);
  rb_iv_set(self, "@size", size);
  return self;
}

void Init_cowboy_data() {
  cCowboyData = rb_define_class_under(mCowboy, "CowboyData", rb_cObject);
  rb_define_method(cCowboyData, "initialize", r_data_init, -1);
  rb_define_method(cCowboyData, "size", r_data_size, 0);
  rb_define_attr(cCowboyData, "data", 1, 0);
}
