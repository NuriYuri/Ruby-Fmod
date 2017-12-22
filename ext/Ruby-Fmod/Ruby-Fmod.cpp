#include "Ruby-Fmod.h"

VALUE rb_mFmod = Qnil;
VALUE rb_mFmodSystem = Qnil;
VALUE rb_cFmodSound = Qnil;
VALUE rb_cFmodChannel = Qnil;
VALUE rb_eFmodError = Qnil;

ID FmodErrorHr = Qnil;

FMOD::System* FmodSystem = NULL;

VALUE rb_FmodError_Init(VALUE self, VALUE hr);
VALUE rb_FmodError_hr(VALUE self);

extern "C" {
    void Init_RubyFmod()
    {
        FMOD_RESULT hr = System_Create(&FmodSystem);
        if(hr != FMOD_RESULT::FMOD_OK)
            rb_raise(rb_eRuntimeError, "Could not create Fmod System Object : %s", FMOD_ErrorString(hr));
        
        rb_mFmod = rb_define_module("Fmod");
        rb_mFmodSystem = rb_define_module_under(rb_mFmod, "System");
        rb_cFmodSound = rb_define_class_under(rb_mFmod, "Sound", rb_cObject);
        rb_cFmodChannel = rb_define_class_under(rb_mFmod, "Channel", rb_cObject);
        rb_eFmodError = rb_define_class_under(rb_mFmod, "Error", rb_eStandardError);

        rb_define_method(rb_eFmodError, "initialize", _rbf rb_FmodError_Init, 1);
        rb_define_method(rb_eFmodError, "hr", _rbf rb_FmodError_hr, 0);

        FmodErrorHr = rb_intern("@hr");

        Init_System();
    }
}


VALUE rb_FmodError_Init(VALUE self, VALUE hr)
{
    rb_ivar_set(self, FmodErrorHr, hr);
    return self;
}

VALUE rb_FmodError_hr(VALUE self)
{
    return rb_ivar_get(self, FmodErrorHr);
}