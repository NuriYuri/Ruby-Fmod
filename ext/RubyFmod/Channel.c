#include "Ruby-Fmod.h"

#define GET_CHANNEL_SAFE \
    GET_CHANNEL(self, fchannel) \
    if(fchannel == NULL) \
        rb_raise(rb_eFmodError, "Channel not created by Fmod");


void rb_Channel_Free(void* data)
{
    
}

VALUE rb_Channel_Alloc(VALUE klass)
{
    return Data_Wrap_Struct(klass, NULL, rb_Channel_Free, NULL);
}

void Init_Channel()
{
    rb_define_alloc_func(rb_cFmodChannel, rb_Channel_Alloc);
    rb_define_method(rb_cFmodChannel, "addFadePoint", _rbf rb_Channel_addFadePoint, 2);
    rb_define_method(rb_cFmodChannel, "getCurrentSound", _rbf rb_Channel_getCurrentSound, 0);
    rb_define_method(rb_cFmodChannel, "getDSPClock", _rbf rb_Channel_getDSPClock, 0);
    rb_define_method(rb_cFmodChannel, "getFrequency", _rbf rb_Channel_getFrequency, 0);
    rb_define_method(rb_cFmodChannel, "getIndex", _rbf rb_Channel_getIndex, 0);
    rb_define_method(rb_cFmodChannel, "getLoopCount", _rbf rb_Channel_getLoopCount, 0);
    rb_define_method(rb_cFmodChannel, "getLoopPoints", _rbf rb_Channel_getLoopPoints, 2);
    rb_define_method(rb_cFmodChannel, "getLowPassGain", _rbf rb_Channel_getLowPassGain, 0);
    rb_define_method(rb_cFmodChannel, "getMode", _rbf rb_Channel_getMode, 0);
    rb_define_method(rb_cFmodChannel, "getMute", _rbf rb_Channel_getMute, 0);
    rb_define_method(rb_cFmodChannel, "getPaused", _rbf rb_Channel_getPaused, 0);
    rb_define_method(rb_cFmodChannel, "getPitch", _rbf rb_Channel_getPitch, 0);
    rb_define_method(rb_cFmodChannel, "getPosition", _rbf rb_Channel_getPosition, 1);
    rb_define_method(rb_cFmodChannel, "getPriority", _rbf rb_Channel_getPriority, 0);
    rb_define_method(rb_cFmodChannel, "getReverbProperties", _rbf rb_Channel_getReverbProperties, 1);
    rb_define_method(rb_cFmodChannel, "getVolume", _rbf rb_Channel_getVolume, 0);
    rb_define_method(rb_cFmodChannel, "getVolumeRamp", _rbf rb_Channel_getVolumeRamp, 0);
    rb_define_method(rb_cFmodChannel, "isPlaying", _rbf rb_Channel_isPlaying, 0);
    rb_define_method(rb_cFmodChannel, "isVirtual", _rbf rb_Channel_isVirtual, 0);
    rb_define_method(rb_cFmodChannel, "removeFadePoints", _rbf rb_Channel_removeFadePoints, 2);
    rb_define_method(rb_cFmodChannel, "setDelay", _rbf rb_Channel_setDelay, 3);
    rb_define_method(rb_cFmodChannel, "setFadePointRamp", _rbf rb_Channel_setFadePointRamp, 2);
    rb_define_method(rb_cFmodChannel, "setFrequency", _rbf rb_Channel_setFrequency, 1);
    rb_define_method(rb_cFmodChannel, "setLoopCount", _rbf rb_Channel_setLoopCount, 1);
    rb_define_method(rb_cFmodChannel, "setLoopPoints", _rbf rb_Channel_setLoopPoints, 4);
    rb_define_method(rb_cFmodChannel, "setLowPassGain", _rbf rb_Channel_setLowPassGain, 1);
    rb_define_method(rb_cFmodChannel, "setMode", _rbf rb_Channel_setMode, 1);
    rb_define_method(rb_cFmodChannel, "setMute", _rbf rb_Channel_setMute, 1);
    rb_define_method(rb_cFmodChannel, "setPan", _rbf rb_Channel_setPan, 1);
    rb_define_method(rb_cFmodChannel, "setPaused", _rbf rb_Channel_setPaused, 1);
    rb_define_method(rb_cFmodChannel, "setPitch", _rbf rb_Channel_setPitch, 1);
    rb_define_method(rb_cFmodChannel, "setPosition", _rbf rb_Channel_setPosition, 2);
    rb_define_method(rb_cFmodChannel, "setPriority", _rbf rb_Channel_setPriority, 1);
    rb_define_method(rb_cFmodChannel, "setReverbProperties", _rbf rb_Channel_setReverbProperties, 2);
    rb_define_method(rb_cFmodChannel, "setVolume", _rbf rb_Channel_setVolume, 1);
    rb_define_method(rb_cFmodChannel, "setVolumeRamp", _rbf rb_Channel_setVolumeRamp, 1);
    rb_define_method(rb_cFmodChannel, "stop", _rbf rb_Channel_stop, 0);
}

VALUE rb_Channel_addFadePoint(VALUE self, VALUE dspclock, VALUE volume)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_AddFadePoint(fchannel, NUM2LL(dspclock), NUM2DBL(volume));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_getCurrentSound(VALUE self)
{
    GET_CHANNEL_SAFE
    return rb_ivar_get(self, current_sound);
}

VALUE rb_Channel_getDSPClock(VALUE self)
{
    GET_CHANNEL_SAFE
    unsigned long long dspclock;
    unsigned long long parentclock;
    FMOD_RESULT hr = FMOD_Channel_GetDSPClock(fchannel, &dspclock, &parentclock);
    CHECK_ERROR
    VALUE return_value = rb_ary_new();
    rb_ary_push(return_value, rb_ull2inum(dspclock));
    rb_ary_push(return_value, rb_ull2inum(parentclock));
    return return_value;
}

VALUE rb_Channel_getFrequency(VALUE self)
{
    GET_CHANNEL_SAFE
    float frequency;
    FMOD_RESULT hr = FMOD_Channel_GetFrequency(fchannel, &frequency);
    CHECK_ERROR
    return rb_float_new(frequency);
}

VALUE rb_Channel_getIndex(VALUE self)
{
    GET_CHANNEL_SAFE
    int index;
    FMOD_RESULT hr = FMOD_Channel_GetIndex(fchannel, &index);
    CHECK_ERROR
    return rb_int2inum(index);
}

VALUE rb_Channel_getLoopCount(VALUE self)
{
    GET_CHANNEL_SAFE
    int loopcount;
    FMOD_RESULT hr = FMOD_Channel_GetLoopCount(fchannel, &loopcount);
    CHECK_ERROR
    return rb_int2inum(loopcount);
}

VALUE rb_Channel_getLoopPoints(VALUE self, VALUE startunit, VALUE stopunit)
{
    GET_CHANNEL_SAFE
    unsigned int start, end;
    FMOD_RESULT hr = FMOD_Channel_GetLoopPoints(fchannel,
        &start,
        NUM2INT(startunit),
        &end,
        NUM2INT(stopunit)
    );
    CHECK_ERROR
    VALUE return_value = rb_ary_new();
    rb_ary_push(return_value, UINT2NUM(start));
    rb_ary_push(return_value, UINT2NUM(end));
    return return_value;
}

VALUE rb_Channel_getLowPassGain(VALUE self)
{
    GET_CHANNEL_SAFE
    float gain;
    FMOD_RESULT hr = FMOD_Channel_GetLowPassGain(fchannel, &gain);
    CHECK_ERROR
    return rb_float_new(gain);
}

VALUE rb_Channel_getMode(VALUE self)
{
    GET_CHANNEL_SAFE
    FMOD_MODE mode;
    FMOD_RESULT hr = FMOD_Channel_GetMode(fchannel, &mode);
    CHECK_ERROR
    return UINT2NUM(mode);
}

VALUE rb_Channel_getMute(VALUE self)
{
    GET_CHANNEL_SAFE
    int mute;
    FMOD_RESULT hr = FMOD_Channel_GetMute(fchannel, &mute);
    CHECK_ERROR
    return (mute ? Qtrue : Qfalse);
}

VALUE rb_Channel_getPaused(VALUE self)
{
    GET_CHANNEL_SAFE
    int paused;
    FMOD_RESULT hr = FMOD_Channel_GetPaused(fchannel, &paused);
    CHECK_ERROR
    return (paused ? Qtrue : Qfalse);
}

VALUE rb_Channel_getPitch(VALUE self)
{
    GET_CHANNEL_SAFE
    float pitch;
    FMOD_RESULT hr = FMOD_Channel_GetPitch(fchannel, &pitch);
    CHECK_ERROR
    return rb_float_new(pitch);
}

VALUE rb_Channel_getPosition(VALUE self, VALUE unit)
{
    GET_CHANNEL_SAFE
    unsigned int position;
    FMOD_RESULT hr = FMOD_Channel_GetPosition(fchannel, &position, NUM2INT(unit));
    CHECK_ERROR
    return UINT2NUM(position);
}

VALUE rb_Channel_getPriority(VALUE self)
{
    GET_CHANNEL_SAFE
    int priority;
    FMOD_RESULT hr = FMOD_Channel_GetPriority(fchannel, &priority);
    CHECK_ERROR
    return rb_int2inum(priority);
}

VALUE rb_Channel_getReverbProperties(VALUE self, VALUE instance)
{
    GET_CHANNEL_SAFE
    float wet;
    FMOD_RESULT hr = FMOD_Channel_GetReverbProperties(fchannel, NUM2INT(instance), &wet);
    CHECK_ERROR
    return rb_float_new(wet);
}

VALUE rb_Channel_getVolume(VALUE self)
{
    GET_CHANNEL_SAFE
    float volume;
    FMOD_RESULT hr = FMOD_Channel_GetVolume(fchannel, &volume);
    CHECK_ERROR
    return rb_float_new(volume);
}

VALUE rb_Channel_getVolumeRamp(VALUE self)
{
    GET_CHANNEL_SAFE
    int ramp;
    FMOD_RESULT hr = FMOD_Channel_GetVolumeRamp(fchannel, &ramp);
    CHECK_ERROR
    return (ramp ? Qtrue : Qfalse);
}

VALUE rb_Channel_isPlaying(VALUE self)
{
    GET_CHANNEL_SAFE
    int playing;
    FMOD_RESULT hr = FMOD_Channel_IsPlaying(fchannel, &playing);
    CHECK_ERROR
    return (playing ? Qtrue : Qfalse);
}

VALUE rb_Channel_isVirtual(VALUE self)
{
    GET_CHANNEL_SAFE
    int isvirtual;
    FMOD_RESULT hr = FMOD_Channel_IsVirtual(fchannel, &isvirtual);
    CHECK_ERROR
    return (isvirtual ? Qtrue : Qfalse);
}

VALUE rb_Channel_removeFadePoints(VALUE self, VALUE dspclock_start, VALUE dspclock_end)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_RemoveFadePoints(fchannel,
        NUM2ULL(dspclock_start),
        NUM2ULL(dspclock_end)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setDelay(VALUE self, VALUE dspclock_start, VALUE dspclock_end, VALUE stopchannels)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetDelay(fchannel,
        NUM2ULL(dspclock_start),
        NUM2ULL(dspclock_end),
        RTEST(stopchannels)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setFadePointRamp(VALUE self, VALUE dspclock, VALUE volume)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetFadePointRamp(fchannel,
        NUM2ULL(dspclock),
        (float)(NUM2DBL(volume))
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setFrequency(VALUE self, VALUE frequency)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetFrequency(fchannel, (float)(NUM2DBL(frequency)));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setLoopCount(VALUE self, VALUE loopcount)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetLoopCount(fchannel, NUM2INT(loopcount));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setLoopPoints(VALUE self, VALUE start, VALUE startunit, VALUE stop, VALUE stopunit)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetLoopPoints(fchannel,
        NUM2UINT(start),
        NUM2INT(startunit),
        NUM2UINT(stop),
        NUM2INT(stopunit)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setLowPassGain(VALUE self, VALUE gain)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetLowPassGain(fchannel, (float)(NUM2DBL(gain)));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setMode(VALUE self, VALUE mode)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetMode(fchannel, NUM2INT(mode));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setMute(VALUE self, VALUE mute)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetMute(fchannel, RTEST(mute));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setPan(VALUE self, VALUE pan)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetPan(fchannel, (float)(NUM2DBL(pan)));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setPaused(VALUE self, VALUE paused)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetPaused(fchannel, RTEST(paused));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setPitch(VALUE self, VALUE pitch)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetPitch(fchannel, (float)(NUM2DBL(pitch)));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setPosition(VALUE self, VALUE position, VALUE unit)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetPosition(fchannel,
        NUM2UINT(position),
        NUM2INT(unit)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setPriority(VALUE self, VALUE priority)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetPriority(fchannel, NUM2INT(priority));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setReverbProperties(VALUE self, VALUE instance, VALUE wet)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetReverbProperties(fchannel,
        NUM2INT(instance),
        (float)(NUM2DBL(wet))
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setVolume(VALUE self, VALUE volume)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetVolume(fchannel, (float)(NUM2DBL(volume)));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setVolumeRamp(VALUE self, VALUE ramp)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_SetVolumeRamp(fchannel, RTEST(ramp));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_stop(VALUE self)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = FMOD_Channel_Stop(fchannel);
    CHECK_ERROR
    rb_ivar_set(self, current_sound, Qnil);
    return Qnil;
}