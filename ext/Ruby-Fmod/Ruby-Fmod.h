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

#define _rbf (VALUE (*)(...))

extern VALUE rb_mFmod;
extern VALUE rb_mFmodSystem;
extern VALUE rb_cFmodSound;
extern VALUE rb_cFmodChannel;
extern VALUE rb_eFmodError;

extern FMOD::System* FmodSystem;

void Init_System();

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
#endif
