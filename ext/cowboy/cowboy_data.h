#ifndef RUBY_COWBOY_DATA
#define RUBY_COWBOY_DATA

extern VALUE cCowboyData;

void Init_cowboy_data();
void get_doubles_from_data(double *, VALUE);
long get_count_of_data(VALUE self);

#endif
