#ifndef L_CHANNEL_HEADER
#define L_CHANNEL_HEADER

VALUE rb_Channel_addFadePoint(VALUE self, VALUE dspclock, VALUE volume);
VALUE rb_Channel_getCurrentSound(VALUE self);
VALUE rb_Channel_getDSPClock(VALUE self);
VALUE rb_Channel_getFrequency(VALUE self);
VALUE rb_Channel_getIndex(VALUE self);
VALUE rb_Channel_getLoopCount(VALUE self);
VALUE rb_Channel_getLoopPoints(VALUE self, VALUE startunit, VALUE stopunit);
VALUE rb_Channel_getLowPassGain(VALUE self);
VALUE rb_Channel_getMode(VALUE self);
VALUE rb_Channel_getMute(VALUE self);
VALUE rb_Channel_getPaused(VALUE self);
VALUE rb_Channel_getPitch(VALUE self);
VALUE rb_Channel_getPosition(VALUE self, VALUE unit);
VALUE rb_Channel_getPriority(VALUE self);
VALUE rb_Channel_getReverbProperties(VALUE self, VALUE instance);
VALUE rb_Channel_getVolume(VALUE self);
VALUE rb_Channel_getVolumeRamp(VALUE self);
VALUE rb_Channel_isPlaying(VALUE self);
VALUE rb_Channel_isVirtual(VALUE self);
VALUE rb_Channel_removeFadePoints(VALUE self, VALUE dspclock_start, VALUE dspclock_end);
VALUE rb_Channel_setDelay(VALUE self, VALUE dspclock_start, VALUE dspclock_end, VALUE stopchannels);
VALUE rb_Channel_setFadePointRamp(VALUE self, VALUE dspclock, VALUE volume);
VALUE rb_Channel_setFrequency(VALUE self, VALUE frequency);
VALUE rb_Channel_setLoopCount(VALUE self, VALUE loopcount);
VALUE rb_Channel_setLoopPoints(VALUE self, VALUE start, VALUE startunit, VALUE stop, VALUE stopunit);
VALUE rb_Channel_setLowPassGain(VALUE self, VALUE gain);
VALUE rb_Channel_setMode(VALUE self, VALUE mode);
VALUE rb_Channel_setMute(VALUE self, VALUE mute);
VALUE rb_Channel_setPan(VALUE self, VALUE pan);
VALUE rb_Channel_setPaused(VALUE self, VALUE paused);
VALUE rb_Channel_setPitch(VALUE self, VALUE pitch);
VALUE rb_Channel_setPosition(VALUE self, VALUE position, VALUE unit);
VALUE rb_Channel_setPriority(VALUE self, VALUE priority);
VALUE rb_Channel_setReverbProperties(VALUE self, VALUE instance, VALUE wet);
VALUE rb_Channel_setVolume(VALUE self, VALUE volume);
VALUE rb_Channel_setVolumeRamp(VALUE self, VALUE ramp);
VALUE rb_Channel_stop(VALUE self);

#endif