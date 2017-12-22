#include "Ruby-Fmod.h"

VALUE rb_mFmod = Qnil;
VALUE rb_mFmodSystem = Qnil;
VALUE rb_cFmodSound = Qnil;
VALUE rb_cFmodChannel = Qnil;

extern "C" {
    void Init_RubyFmod()
    {
        rb_mFmod = rb_define_module("Fmod");
        rb_mFmodSystem = rb_define_module_under(rb_mFmod, "System");
        rb_cFmodSound = rb_define_class_under(rb_mFmod, "Sound", rb_cObject);
        rb_cFmodChannel = rb_define_class_under(rb_mFmod, "Channel", rb_cObject);
    }
}