#ifndef RF_RUBY_FMOD_H
#define RF_RUBY_FMOD_H
#include "ruby.h"
#include <fmod.h>
#include <fmod_errors.h>
#include "System.h"
#include "Sound.h"
#include "Channel.h"
#include "ExInfo.h"

#define _rbf //(VALUE (*)(...))

#define C_TRUE 1
#define C_FALSE 0

extern VALUE rb_mFmod;
extern VALUE rb_mFmodSystem;
extern VALUE rb_cFmodSound;
extern VALUE rb_cFmodChannel;
extern VALUE rb_eFmodError;
extern VALUE rb_cFmodExInfo;

extern FMOD_SYSTEM* FmodSystem;
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

VALUE rb_FmodRaiseError(FMOD_RESULT hr);

#define CHECK_ERROR \
    if(hr != FMOD_OK) \
        return rb_FmodRaiseError(hr); \

#define GET_SOUND(object, varname) \
    FMOD_SOUND* varname; \
    Data_Get_Struct(object, FMOD_SOUND, varname);

#define SET_DATA(object, varname) \
    rb_check_type(object, T_DATA); \
    RDATA(object)->data = reinterpret_cast<void*>(varname);

#define GET_CHANNEL(object, varname) \
    FMOD_CHANNEL* varname; \
    Data_Get_Struct(object, FMOD_CHANNEL, varname);

#endif
