#ifndef RF_RUBY_FMOD_H
#define RF_RUBY_FMOD_H
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "ruby.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#include "System.h"
#include "Sound.h"
#include "Channel.h"
#include "ExInfo.h"

#define _rbf (VALUE (*)(...))

extern VALUE rb_mFmod;
extern VALUE rb_mFmodSystem;
extern VALUE rb_cFmodSound;
extern VALUE rb_cFmodChannel;
extern VALUE rb_eFmodError;
extern VALUE rb_cFmodExInfo;

extern FMOD::System* FmodSystem;
extern ID current_sound;

void Init_System();
void Init_Sound();
void Init_Channel();
void Init_SoundEx();

inline long normalize_long(long value, long min, long max) {
    if(value < min)
        return min;
    if(value > max)
        return max;
    return value;
}
inline double normalize_double(double value, double min, double max) {
    if(value < min)
        return min;
    if(value > max)
        return max;
    return value;
}

inline VALUE rb_FmodRaiseError(FMOD_RESULT hr) {
    VALUE argv = rb_int2inum(hr);
    rb_raise(rb_class_new_instance(1, &argv, rb_eFmodError), "FmodError %d : %s", hr, FMOD_ErrorString(hr));
    return Qnil;
}

#define CHECK_ERROR \
    if(hr != FMOD_RESULT::FMOD_OK) \
        return rb_FmodRaiseError(hr); \

#define GET_SOUND(object, varname) \
    FMOD::Sound* varname; \
    Data_Get_Struct(object, FMOD::Sound, varname);

#define SET_DATA(object, varname) \
    rb_check_type(object, T_DATA); \
    RDATA(object)->data = reinterpret_cast<void*>(varname);

#define GET_CHANNEL(object, varname) \
    FMOD::Channel* varname; \
    Data_Get_Struct(object, FMOD::Channel, varname);

#endif
