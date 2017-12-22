#ifndef L_SOUND_HEADER
#define L_SOUND_HEADER

VALUE rb_Sound_getDefaults(VALUE self);
VALUE rb_Sound_getFormat(VALUE self);
VALUE rb_Sound_getLength(VALUE self, VALUE timeunit);
VALUE rb_Sound_getLength(VALUE self);
VALUE rb_Sound_getLoopPoints(VALUE self, VALUE startunit, VALUE stopunit);
VALUE rb_Sound_getMode(VALUE self);
VALUE rb_Sound_getMusicChannelVolume(VALUE self, VALUE channelid);
VALUE rb_Sound_getMusicNumChannels(VALUE self);
VALUE rb_Sound_getMusicSpeed(VALUE self);
VALUE rb_Sound_getName(VALUE self);
VALUE rb_Sound_getNumSubSounds(VALUE self);
VALUE rb_Sound_getNumTags(VALUE self);
VALUE rb_Sound_getOpenState(VALUE self);
VALUE rb_Sound_getSubSound(VALUE self, VALUE index);
VALUE rb_Sound_getSubSoundParent(VALUE self);
VALUE rb_Sound_getTag(VALUE self, VALUE name, VALUE index);
VALUE rb_Sound_readData(VALUE self, VALUE buffer); // Returns the number of byte read
VALUE rb_Sound_release(VALUE self);
VALUE rb_Sound_seekData(VALUE self, VALUE pcmoffset);
VALUE rb_Sound_setDefaults(VALUE self, VALUE frequency, VALUE priority);
VALUE rb_Sound_setLoopCount(VALUE self, VALUE count);
VALUE rb_Sound_setLoopPoints(VALUE self, VALUE start, VALUE startunit, VALUE stop, VALUE stopunit);
VALUE rb_Sound_setMode(VALUE self, VALUE mode);
VALUE rb_Sound_setMusicChannelVolume(VALUE self, VALUE channelindex, VALUE volume);
VALUE rb_Sound_setMusicSpeed(VALUE self, VALUE speed);


#endif