#include <ruby.h>

static VALUE hello_world(VALUE mod){
  return rb_str_new2("hello world");
}

void Init_cowboy(){
  VALUE mCowboy = rb_define_module("Cowboy");
  rb_define_singleton_method(mCowboy, "hello_world", hello_world, 0);
}
