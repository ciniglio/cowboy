#include <cowboy.h>

void Init_cowboy(){
  VALUE mCowboy = rb_define_module("Cowboy");

  Init_cowboy_complex();
}
