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

long get_channels(VALUE data){
  return NUM2LONG(rb_iv_get(data, "@channels"));
}

long get_count_of_samples(VALUE self){
  VALUE data = rb_iv_get(self, "@data");
  long len;

  check_type_cowboy_data(self);

  len = size_of_val(data);

  if (TYPE(data) == T_STRING){
    len /= get_size(self);
  }
  return len;
}

long get_count_of_data(VALUE self){
  long channels = NUM2LONG(rb_iv_get(self, "@channels"));
  return get_count_of_samples(self)/channels;
}

void get_doubles_from_string_data(double * out, char * str,
                                  long count, long size, long channels){
  int i,j;
  short * s; float * l; double * d;



  switch (size){
  case 1:
    for(i = 0; i < count; i++){
      for(j = 0; j < channels; j++){
        out[i] += (double) str[(i * channels) + j];
      }
      out[i] /= channels;
    }
    break;
  case 2:
    s = (short *) str;
    for(i = 0; i < count; i++){
      for(j = 0; j < channels; j++){
        out[i] += s[(i * channels) + j];
      }
      out[i] /= channels;
    }
    break;
  case 4:
    l = (float *) str;
    for(i = 0; i < count; i++){
      for(j = 0; j < channels; j++){
        out[i] += l[(i * channels) + j];
      }
      out[i] /= channels;
    }
    break;
  case 8:
    d = (double *) str;
    for(i = 0; i < count; i++){
      for(j = 0; j < channels; j++){
        out[i] += d[(i * channels) + j];
      }
      out[i] /= channels;
    }
    break;
  default:
    rb_raise(rb_eArgError, "Size must be 1,2,4, or 8");
    break;
  }
}

void get_doubles_from_array_data(double * out, VALUE in,
                                 long len, long channels){
  VALUE num;
  int i,j;

  for(i = 0; i < len; i++){
    for(j = 0; j < channels; j++){
      out[i] += NUM2DBL(rb_ary_entry(in, (i * channels) + j));
    }
    out[i] /= channels;
  }
}

void get_doubles_from_data(double * out, VALUE in){
  VALUE data;
  long size, channels, count;
  int i;

  check_type_cowboy_data(in);

  data = rb_iv_get(in, "@data");
  size = get_size(in);
  channels = get_channels(in);
  count = get_count_of_data(in);

  memset(out, 0, sizeof(double) * count);

  if (TYPE(data) == T_STRING){
    get_doubles_from_string_data(out, RSTRING_PTR(RSTRING(data)),
                                 count, size, channels);
  } else if (TYPE(data) == T_ARRAY) {
    get_doubles_from_array_data(out, data, count, channels);
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
  VALUE data, size, channels;
  rb_scan_args(argc, argv, "12", &data, &size, &channels);

  if (channels == Qnil)
    channels = LONG2NUM(1);

  rb_iv_set(self, "@data", data);
  rb_iv_set(self, "@size", size);
  rb_iv_set(self, "@channels", channels);

  if (get_count_of_samples(self) % NUM2LONG(channels) != 0)
    rb_raise(rb_eException,
             "The amount of data must be a multiple of the number of channels");

  return self;
}

void Init_cowboy_data() {
  cCowboyData = rb_define_class_under(mCowboy, "CowboyData", rb_cObject);
  rb_define_method(cCowboyData, "initialize", r_data_init, -1);
  rb_define_method(cCowboyData, "size", r_data_size, 0);
  rb_define_attr(cCowboyData, "data", 1, 0);
}
