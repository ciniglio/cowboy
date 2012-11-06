#include "cowboy.h"
#include <ruby.h>

VALUE cCowboyData;


VALUE data_init(VALUE self, VALUE data, VALUE size){
  rb_iv_set(self, "@data", data);
  rb_iv_set(self, "@size", size);
  return self;
}

void Init_cowboy_data() {
  cCowboyData = rb_define_class_under(mCowboy, "CowboyData", rb_cObject);
  rb_define_method(cCowboyData, "initialize", data_init, 2);
}
