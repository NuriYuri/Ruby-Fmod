#include "Ruby-Fmod.h"

#define GET_CHANNEL_SAFE \
    GET_CHANNEL(self, fchannel) \
    if(fchannel == nullptr) \
        rb_raise(rb_eFmodError, "Channel not created by Fmod");


void rb_Channel_Free(void* data)
{
    
}

VALUE rb_Channel_Alloc(VALUE klass)
{
    return Data_Wrap_Struct(klass, NULL, rb_Channel_Free, nullptr);
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
    FMOD_RESULT hr = fchannel->addFadePoint(rb_num2ll(dspclock), rb_num2dbl(volume));
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
    FMOD_RESULT hr = fchannel->getDSPClock(&dspclock, &parentclock);
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
    FMOD_RESULT hr = fchannel->getFrequency(&frequency);
    CHECK_ERROR
    return rb_float_new(frequency);
}

VALUE rb_Channel_getIndex(VALUE self)
{
    GET_CHANNEL_SAFE
    int index;
    FMOD_RESULT hr = fchannel->getIndex(&index);
    CHECK_ERROR
    return rb_int2inum(index);
}

VALUE rb_Channel_getLoopCount(VALUE self)
{
    GET_CHANNEL_SAFE
    int loopcount;
    FMOD_RESULT hr = fchannel->getLoopCount(&loopcount);
    CHECK_ERROR
    return rb_int2inum(loopcount);
}

VALUE rb_Channel_getLoopPoints(VALUE self, VALUE startunit, VALUE stopunit)
{
    GET_CHANNEL_SAFE
    unsigned int start, end;
    FMOD_RESULT hr = fchannel->getLoopPoints(
        &start,
        RB_NUM2INT(startunit),
        &end,
        RB_NUM2INT(stopunit)
    );
    CHECK_ERROR
    VALUE return_value = rb_ary_new();
    rb_ary_push(return_value, RB_UINT2NUM(start));
    rb_ary_push(return_value, RB_UINT2NUM(end));
    return return_value;
}

VALUE rb_Channel_getLowPassGain(VALUE self)
{
    GET_CHANNEL_SAFE
    float gain;
    FMOD_RESULT hr = fchannel->getLowPassGain(&gain);
    CHECK_ERROR
    return rb_float_new(gain);
}

VALUE rb_Channel_getMode(VALUE self)
{
    GET_CHANNEL_SAFE
    FMOD_MODE mode;
    FMOD_RESULT hr = fchannel->getMode(&mode);
    CHECK_ERROR
    return RB_UINT2NUM(mode);
}

VALUE rb_Channel_getMute(VALUE self)
{
    GET_CHANNEL_SAFE
    bool mute;
    FMOD_RESULT hr = fchannel->getMute(&mute);
    CHECK_ERROR
    return (mute ? Qtrue : Qfalse);
}

VALUE rb_Channel_getPaused(VALUE self)
{
    GET_CHANNEL_SAFE
    bool paused;
    FMOD_RESULT hr = fchannel->getPaused(&paused);
    CHECK_ERROR
    return (paused ? Qtrue : Qfalse);
}

VALUE rb_Channel_getPitch(VALUE self)
{
    GET_CHANNEL_SAFE
    float pitch;
    FMOD_RESULT hr = fchannel->getPitch(&pitch);
    CHECK_ERROR
    return rb_float_new(pitch);
}

VALUE rb_Channel_getPosition(VALUE self, VALUE unit)
{
    GET_CHANNEL_SAFE
    unsigned int position;
    FMOD_RESULT hr = fchannel->getPosition(&position, RB_NUM2INT(unit));
    CHECK_ERROR
    return RB_UINT2NUM(position);
}

VALUE rb_Channel_getPriority(VALUE self)
{
    GET_CHANNEL_SAFE
    int priority;
    FMOD_RESULT hr = fchannel->getPriority(&priority);
    CHECK_ERROR
    return rb_int2inum(priority);
}

VALUE rb_Channel_getReverbProperties(VALUE self, VALUE instance)
{
    GET_CHANNEL_SAFE
    float wet;
    FMOD_RESULT hr = fchannel->getReverbProperties(RB_NUM2INT(instance), &wet);
    CHECK_ERROR
    return rb_float_new(wet);
}

VALUE rb_Channel_getVolume(VALUE self)
{
    GET_CHANNEL_SAFE
    float volume;
    FMOD_RESULT hr = fchannel->getVolume(&volume);
    CHECK_ERROR
    return rb_float_new(volume);
}

VALUE rb_Channel_getVolumeRamp(VALUE self)
{
    GET_CHANNEL_SAFE
    bool ramp;
    FMOD_RESULT hr = fchannel->getVolumeRamp(&ramp);
    CHECK_ERROR
    return (ramp ? Qtrue : Qfalse);
}

VALUE rb_Channel_isPlaying(VALUE self)
{
    GET_CHANNEL_SAFE
    bool playing;
    FMOD_RESULT hr = fchannel->isPlaying(&playing);
    CHECK_ERROR
    return (playing ? Qtrue : Qfalse);
}

VALUE rb_Channel_isVirtual(VALUE self)
{
    GET_CHANNEL_SAFE
    bool isvirtual;
    FMOD_RESULT hr = fchannel->isVirtual(&isvirtual);
    CHECK_ERROR
    return (isvirtual ? Qtrue : Qfalse);
}

VALUE rb_Channel_removeFadePoints(VALUE self, VALUE dspclock_start, VALUE dspclock_end)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->removeFadePoints(
        rb_num2ull(dspclock_start),
        rb_num2ull(dspclock_end)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setDelay(VALUE self, VALUE dspclock_start, VALUE dspclock_end, VALUE stopchannels)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setDelay(
        rb_num2ull(dspclock_start),
        rb_num2ull(dspclock_end),
        RTEST(stopchannels)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setFadePointRamp(VALUE self, VALUE dspclock, VALUE volume)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setFadePointRamp(
        rb_num2ull(dspclock),
        static_cast<float>(rb_num2dbl(volume))
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setFrequency(VALUE self, VALUE frequency)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setFrequency(static_cast<float>(rb_num2dbl(frequency)));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setLoopCount(VALUE self, VALUE loopcount)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setLoopCount(RB_NUM2INT(loopcount));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setLoopPoints(VALUE self, VALUE start, VALUE startunit, VALUE stop, VALUE stopunit)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setLoopPoints(
        RB_NUM2UINT(start),
        RB_NUM2INT(startunit),
        RB_NUM2UINT(stop),
        RB_NUM2INT(stopunit)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setLowPassGain(VALUE self, VALUE gain)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setLowPassGain(static_cast<float>(rb_num2dbl(gain)));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setMode(VALUE self, VALUE mode)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setMode(RB_NUM2INT(mode));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setMute(VALUE self, VALUE mute)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setMute(RTEST(mute));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setPan(VALUE self, VALUE pan)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setPan(static_cast<float>(rb_num2dbl(pan)));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setPaused(VALUE self, VALUE paused)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setPaused(RTEST(paused));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setPitch(VALUE self, VALUE pitch)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setPitch(static_cast<float>(rb_num2dbl(pitch)));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setPosition(VALUE self, VALUE position, VALUE unit)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setPosition(
        RB_NUM2UINT(position),
        RB_NUM2INT(unit)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setPriority(VALUE self, VALUE priority)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setPriority(RB_NUM2INT(priority));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setReverbProperties(VALUE self, VALUE instance, VALUE wet)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setReverbProperties(
        RB_NUM2INT(instance),
        static_cast<float>(rb_num2dbl(wet))
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setVolume(VALUE self, VALUE volume)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setVolume(static_cast<float>(rb_num2dbl(volume)));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_setVolumeRamp(VALUE self, VALUE ramp)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->setVolumeRamp(RTEST(ramp));
    CHECK_ERROR
    return self;
}

VALUE rb_Channel_stop(VALUE self)
{
    GET_CHANNEL_SAFE
    FMOD_RESULT hr = fchannel->stop();
    CHECK_ERROR
    rb_ivar_set(self, current_sound, Qnil);
    return Qnil;
}