#ifndef L_SYSTEM_H
#define L_SYSTEM_H

VALUE rb_System_close(VALUE self);
VALUE rb_System_create_Sound(VALUE self, VALUE filename, VALUE mode, VALUE extinfo);
VALUE rb_System_create_Stream(VALUE self, VALUE filename, VALUE mode, VALUE extinfo);
VALUE rb_System_getCPUUsage(VALUE self);
VALUE rb_System_getChannel(VALUE self, VALUE id);
VALUE rb_System_getChannelsPlaying(VALUE self);
VALUE rb_System_getBufferSize(VALUE self);
VALUE rb_System_getDriver(VALUE self);
VALUE rb_System_getDriverInfo(VALUE self, VALUE id);
VALUE rb_System_getFileUsage(VALUE self);
VALUE rb_System_getNumDrivers(VALUE self);
VALUE rb_System_getOutput(VALUE self);
VALUE rb_System_getRecordDriverInfo(VALUE self, VALUE id);
VALUE rb_System_getRecordNumDriver(VALUE self);
VALUE rb_System_getRecordPosition(VALUE self, VALUE id);
VALUE rb_System_getSoftwareChannels(VALUE self);
VALUE rb_System_getSoftwareFormat(VALUE self);
VALUE rb_System_getSoundRAM(VALUE self);
VALUE rb_System_getSpeakerModeChannels(VALUE self, VALUE mode);
VALUE rb_System_getSpeakerPosition(VALUE self, VALUE speaker);
VALUE rb_System_getStreamBufferSize(VALUE self);
VALUE rb_System_getVersion(VALUE self);
VALUE rb_System_init(VALUE self, VALUE num_channel, VALUE flags);
VALUE rb_System_isRecording(VALUE self, VALUE id);
VALUE rb_System_playSound(int argc, VALUE* argv, VALUE self); // sound, paused = false => Channel
VALUE rb_System_recordStart(VALUE self, VALUE id, VALUE sound, VALUE loop);
VALUE rb_System_recordStop(VALUE self, VALUE id);
VALUE rb_System_release(VALUE self);
VALUE rb_System_setDriver(VALUE self, VALUE driver);
VALUE rb_System_setOutput(VALUE self, VALUE output);
VALUE rb_System_setSoftwareChannels(VALUE self, VALUE max_channels);
VALUE rb_System_setSoftwareFormat(VALUE self, VALUE samplerate, VALUE speakermode, VALUE numrawspeakers);
VALUE rb_System_setStreamBufferSize(VALUE self, VALUE filebuffersize, VALUE filebuffersizetype);
VALUE rb_System_update(VALUE self);

#endif