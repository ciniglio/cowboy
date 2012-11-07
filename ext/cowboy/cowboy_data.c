#include "cowboy.h"
#include <ruby.h>

VALUE cCowboyData;

long get_size(VALUE data){
  return NUM2LONG(rb_iv_get(data, "@size"));
}

void get_doubles_from_string_data(double * out, char * str,
                                  long len, long size){
  int i;
  short * s; long * l; double * d;
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
    l = (long *) str;
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
  while (num = rb_each(in)){
    out[i] = NUM2DBL(num);
    i++;
  }
}

void get_doubles_from_data(double * out, VALUE in){
  VALUE data;
  long size;
  int i;
  if (rb_obj_is_instance_of(in, cCowboyData) != Qtrue)
    rb_raise(rb_eTypeError, "Expected a CowboyData instance");
  data = rb_iv_get(in, "@data");
  size = get_size(in);

  if (TYPE(data) == T_STRING)
    get_doubles_from_string_data(out, RSTRING_PTR(RSTRING(data)),
                                 size_of_val(data), size);
  else if (TYPE(data) == T_ARRAY)
    get_doubles_from_array_data(out, data, size_of_val(data));
  else
    rb_raise(rb_eException, "Something went awry");
}

VALUE r_data_size(VALUE self){
  VALUE size = rb_iv_get(self, "@size");
  VALUE data = rb_iv_get(self, "@data");
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
