#include "cowboy.h"

VALUE mCowboy;

void Init_cowboy(){
  mCowboy = rb_define_module("Cowboy");

  Init_cowboy_complex();
}
