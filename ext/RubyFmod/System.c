#include "Ruby-Fmod.h"

ID Sound_ivData = Qnil;

void Init_System()
{
    Sound_ivData = rb_intern("@data");

    rb_define_module_function(rb_mFmodSystem, "close", _rbf rb_System_close, 0);
    rb_define_module_function(rb_mFmodSystem, "createSound", _rbf rb_System_create_Sound, 3);
    rb_define_module_function(rb_mFmodSystem, "createStream", _rbf rb_System_create_Stream, 3);
    rb_define_module_function(rb_mFmodSystem, "getCPUUsage", _rbf rb_System_getCPUUsage, 0);
    rb_define_module_function(rb_mFmodSystem, "getChannel", _rbf rb_System_getChannel, 1);
    rb_define_module_function(rb_mFmodSystem, "getChannelsPlaying", _rbf rb_System_getChannelsPlaying, 0);
    rb_define_module_function(rb_mFmodSystem, "getDSPBufferSize", _rbf rb_System_getBufferSize, 0);
    rb_define_module_function(rb_mFmodSystem, "getDriver", _rbf rb_System_getDriver, 0);
    rb_define_module_function(rb_mFmodSystem, "getDriverInfo", _rbf rb_System_getDriverInfo, 1);
    rb_define_module_function(rb_mFmodSystem, "getFileUsage", _rbf rb_System_getFileUsage, 0);
    rb_define_module_function(rb_mFmodSystem, "getNumDrivers", _rbf rb_System_getNumDrivers, 0);
    rb_define_module_function(rb_mFmodSystem, "getOutput", _rbf rb_System_getOutput, 0);
    rb_define_module_function(rb_mFmodSystem, "getRecordDriverInfo", _rbf rb_System_getRecordDriverInfo, 1);
    rb_define_module_function(rb_mFmodSystem, "getRecordNumDriver", _rbf rb_System_getRecordNumDriver, 0);
    rb_define_module_function(rb_mFmodSystem, "getRecordPosition", _rbf rb_System_getRecordPosition, 1);
    rb_define_module_function(rb_mFmodSystem, "getSoftwareChannels", _rbf rb_System_getSoftwareChannels, 0);
    rb_define_module_function(rb_mFmodSystem, "getSoftwareFormat", _rbf rb_System_getSoftwareFormat, 0);
    rb_define_module_function(rb_mFmodSystem, "getSpeakerModeChannels", _rbf rb_System_getSpeakerModeChannels, 1);
    rb_define_module_function(rb_mFmodSystem, "getSpeakerPosition", _rbf rb_System_getSpeakerPosition, 1);
    rb_define_module_function(rb_mFmodSystem, "getStreamBufferSize", _rbf rb_System_getStreamBufferSize, 0);
    rb_define_module_function(rb_mFmodSystem, "getVersion", _rbf rb_System_getVersion, 0);
    rb_define_module_function(rb_mFmodSystem, "init", _rbf rb_System_init, 2);
    rb_define_module_function(rb_mFmodSystem, "isRecording", _rbf rb_System_isRecording, 1);
    rb_define_module_function(rb_mFmodSystem, "playSound", _rbf rb_System_playSound, -1); // sound, paused = C_FALSE => Channel
    rb_define_module_function(rb_mFmodSystem, "recordStart", _rbf rb_System_recordStart, 3);
    rb_define_module_function(rb_mFmodSystem, "recordStop", _rbf rb_System_recordStop, 1);
    rb_define_module_function(rb_mFmodSystem, "release", _rbf rb_System_release, 0);
    rb_define_module_function(rb_mFmodSystem, "setDriver", _rbf rb_System_setDriver, 1);
    rb_define_module_function(rb_mFmodSystem, "setOutput", _rbf rb_System_setOutput, 1);
    rb_define_module_function(rb_mFmodSystem, "setSoftwareChannels", _rbf rb_System_setSoftwareChannels, 1);
    rb_define_module_function(rb_mFmodSystem, "setSoftwareFormat", _rbf rb_System_setSoftwareFormat, 3);
    rb_define_module_function(rb_mFmodSystem, "setStreamBufferSize", _rbf rb_System_setStreamBufferSize, 2);
    rb_define_module_function(rb_mFmodSystem, "update", _rbf rb_System_update, 0);
}

VALUE rb_System_close(VALUE self)
{
    FMOD_RESULT hr = FMOD_System_Close(FmodSystem);
    CHECK_ERROR
    return self;
}

VALUE rb_System_create_Sound(VALUE self, VALUE filename, VALUE mode, VALUE extinfo)
{
    rb_check_type(filename, T_STRING);
    FMOD_RESULT hr;
    VALUE sound = rb_class_new_instance(0, NULL, rb_cFmodSound);
    rb_ivar_set(sound, Sound_ivData, filename);
    rb_check_type(sound, T_DATA);
	if (rb_obj_is_kind_of(extinfo, rb_cFmodExInfo) == Qtrue)
	{
		FMOD_CREATESOUNDEXINFO* exinfo2;
		Data_Get_Struct(extinfo, FMOD_CREATESOUNDEXINFO, exinfo2);
        hr = FMOD_System_CreateSound(FmodSystem, RSTRING_PTR(filename), NUM2LONG(mode), exinfo2, (FMOD_SOUND**)(&RDATA(sound)->data));
    }
    else
        hr = FMOD_System_CreateSound(FmodSystem, RSTRING_PTR(filename), NUM2LONG(mode), NULL, (FMOD_SOUND**)(&RDATA(sound)->data));
    CHECK_ERROR
    return sound;
}

VALUE rb_System_create_Stream(VALUE self, VALUE filename, VALUE mode, VALUE extinfo)
{
    rb_check_type(filename, T_STRING);
    FMOD_RESULT hr;
    VALUE sound = rb_class_new_instance(0, NULL, rb_cFmodSound);
    rb_ivar_set(sound, Sound_ivData, filename);
    rb_check_type(sound, T_DATA);
	if (rb_obj_is_kind_of(extinfo, rb_cFmodExInfo) == Qtrue)
	{
		FMOD_CREATESOUNDEXINFO* exinfo2;
		Data_Get_Struct(extinfo, FMOD_CREATESOUNDEXINFO, exinfo2);
        hr = FMOD_System_CreateStream(FmodSystem, RSTRING_PTR(filename), NUM2LONG(mode), exinfo2, (FMOD_SOUND**)(&RDATA(sound)->data));
    }
    else
        hr = FMOD_System_CreateStream(FmodSystem, RSTRING_PTR(filename), NUM2LONG(mode), NULL, (FMOD_SOUND**)(&RDATA(sound)->data));
    CHECK_ERROR
    return sound;
}

VALUE rb_System_getCPUUsage(VALUE self)
{
    float dsp;
    float stream;
    float geometry;
    float update;
    float total;
    FMOD_RESULT hr = FMOD_System_GetCPUUsage(FmodSystem, &dsp, &stream, &geometry, &update, &total);
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_float_new(dsp));
    rb_ary_push(return_data, rb_float_new(stream));
    rb_ary_push(return_data, rb_float_new(geometry));
    rb_ary_push(return_data, rb_float_new(update));
    rb_ary_push(return_data, rb_float_new(total));
    return return_data;
}

VALUE rb_System_getChannel(VALUE self, VALUE id)
{
    VALUE channel = rb_class_new_instance(0, NULL, rb_cFmodChannel);
    rb_check_type(channel, T_DATA);
    FMOD_RESULT hr = FMOD_System_GetChannel(FmodSystem,
        NUM2LONG(id),
        (FMOD_CHANNEL**)(&RDATA(channel)->data)
    );
    CHECK_ERROR
    return channel;
}

VALUE rb_System_getChannelsPlaying(VALUE self)
{
    int channels;
    int realchannels;
    FMOD_RESULT hr = FMOD_System_GetChannelsPlaying(FmodSystem, &channels, &realchannels);
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_int2inum(channels));
    rb_ary_push(return_data, rb_int2inum(realchannels));
    return return_data;
}

VALUE rb_System_getBufferSize(VALUE self)
{
    unsigned int bufferlength;
    int numbuffers;
    FMOD_RESULT hr = FMOD_System_GetDSPBufferSize(FmodSystem, &bufferlength, &numbuffers);
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, UINT2NUM(bufferlength));
    rb_ary_push(return_data, rb_int2inum(numbuffers));
    return return_data;
}

VALUE rb_System_getDriver(VALUE self)
{
    int driver;
    FMOD_RESULT hr = FMOD_System_GetDriver(FmodSystem, &driver);
    CHECK_ERROR
    return rb_int2inum(driver);
}

VALUE rb_System_getDriverInfo(VALUE self, VALUE id)
{
    char name[1024];
    FMOD_GUID guid;
    int systemrate;
    FMOD_SPEAKERMODE speakermode;
    int speakermodechannels;
    FMOD_RESULT hr = FMOD_System_GetDriverInfo(FmodSystem,
        NUM2LONG(id),
        name,
        1024,
        &guid,
        &systemrate,
        &speakermode,
        &speakermodechannels
    );
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_str_new_cstr(name));
    VALUE guid_arr = rb_ary_new();
    rb_ary_push(guid_arr, UINT2NUM(guid.Data1));
    rb_ary_push(guid_arr, UINT2NUM(guid.Data2));
    rb_ary_push(guid_arr, UINT2NUM(guid.Data3));
    rb_ary_push(guid_arr, rb_str_new((const char*)(guid.Data4), 8));
    rb_ary_push(return_data, guid_arr);
    rb_ary_push(return_data, rb_int2inum(systemrate));
    rb_ary_push(return_data, rb_int2inum(speakermode));
    rb_ary_push(return_data, rb_int2inum(speakermodechannels));
    return return_data;
}

VALUE rb_System_getFileUsage(VALUE self)
{
    long long sampleBytesRead;
    long long streamBytesRead;
    long long otherBytesRead;
    FMOD_RESULT hr = FMOD_System_GetFileUsage(FmodSystem, &sampleBytesRead, &streamBytesRead, &otherBytesRead);
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_ll2inum(sampleBytesRead));
    rb_ary_push(return_data, rb_ll2inum(streamBytesRead));
    rb_ary_push(return_data, rb_ll2inum(otherBytesRead));
    return return_data;
}

VALUE rb_System_getNumDrivers(VALUE self)
{
    int numdrivers;
    FMOD_RESULT hr = FMOD_System_GetNumDrivers(FmodSystem, &numdrivers);
    CHECK_ERROR
    return rb_int2inum(numdrivers);
}

VALUE rb_System_getOutput(VALUE self)
{
    FMOD_OUTPUTTYPE output;
    FMOD_RESULT hr = FMOD_System_GetOutput(FmodSystem, &output);
    CHECK_ERROR
    return rb_int2inum(output);
}

VALUE rb_System_getRecordDriverInfo(VALUE self, VALUE id)
{
    char name[1024];
    FMOD_GUID guid;
    int systemrate;
    FMOD_SPEAKERMODE speakermode;
    int speakermodechannels;
    FMOD_DRIVER_STATE driverstate;
    FMOD_RESULT hr = FMOD_System_GetRecordDriverInfo(FmodSystem,
        NUM2LONG(id),
        name,
        1024,
        &guid,
        &systemrate,
        &speakermode,
        &speakermodechannels,
        &driverstate
    );
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_str_new_cstr(name));
    VALUE guid_arr = rb_ary_new();
    rb_ary_push(guid_arr, UINT2NUM(guid.Data1));
    rb_ary_push(guid_arr, UINT2NUM(guid.Data2));
    rb_ary_push(guid_arr, UINT2NUM(guid.Data3));
    rb_ary_push(guid_arr, rb_str_new((const char*)(guid.Data4), 8));
    rb_ary_push(return_data, guid_arr);
    rb_ary_push(return_data, rb_int2inum(systemrate));
    rb_ary_push(return_data, rb_int2inum(speakermode));
    rb_ary_push(return_data, rb_int2inum(speakermodechannels));
    rb_ary_push(return_data, UINT2NUM(driverstate));
    return return_data;
}

VALUE rb_System_getRecordNumDriver(VALUE self)
{
    int numdrivers;
    int numconnected;
    FMOD_RESULT hr = FMOD_System_GetRecordNumDrivers(FmodSystem, &numdrivers, &numconnected);
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_int2inum(numdrivers));
    rb_ary_push(return_data, rb_int2inum(numconnected));
    return return_data;
}

VALUE rb_System_getRecordPosition(VALUE self, VALUE id)
{
    unsigned int position;
    FMOD_RESULT hr = FMOD_System_GetRecordPosition(FmodSystem, NUM2LONG(id), &position);
    CHECK_ERROR
    return UINT2NUM(position);
}

VALUE rb_System_getSoftwareChannels(VALUE self)
{
    int numsoftwarechannels;
    FMOD_RESULT hr = FMOD_System_GetSoftwareChannels(FmodSystem, &numsoftwarechannels);
    CHECK_ERROR
    return rb_int2inum(numsoftwarechannels);
}

VALUE rb_System_getSoftwareFormat(VALUE self)
{
    int samplerate;
    FMOD_SPEAKERMODE speakermode;
    int numrawspeakers;
    FMOD_RESULT hr = FMOD_System_GetSoftwareFormat(FmodSystem, &samplerate, &speakermode, &numrawspeakers);
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_int2inum(samplerate));
    rb_ary_push(return_data, rb_int2inum(speakermode));
    rb_ary_push(return_data, rb_int2inum(numrawspeakers));
    return return_data;
}

VALUE rb_System_getSpeakerModeChannels(VALUE self, VALUE mode)
{
    int channels;
    FMOD_RESULT hr = FMOD_System_GetSpeakerModeChannels(FmodSystem,
        (FMOD_SPEAKERMODE)(NUM2LONG(mode)),
        &channels
    );
    CHECK_ERROR
    return rb_int2inum(channels);
}

VALUE rb_System_getSpeakerPosition(VALUE self, VALUE speaker)
{
    float x;
    float y;
    int active;
    FMOD_RESULT hr = FMOD_System_GetSpeakerPosition(FmodSystem,
        (FMOD_SPEAKER)(NUM2LONG(speaker)),
        &x,
        &y,
        &active
    );
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_float_new(x));
    rb_ary_push(return_data, rb_float_new(y));
    rb_ary_push(return_data, active ? Qtrue : Qfalse);
    return return_data;
}

VALUE rb_System_getStreamBufferSize(VALUE self)
{
    unsigned int filebuffersize;
    FMOD_TIMEUNIT filebuffersizetype;
    FMOD_RESULT hr = FMOD_System_GetStreamBufferSize(FmodSystem, &filebuffersize, &filebuffersizetype);
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, UINT2NUM(filebuffersize));
    rb_ary_push(return_data, UINT2NUM(filebuffersizetype));
    return return_data;
}

VALUE rb_System_getVersion(VALUE self)
{
    unsigned int version;
    FMOD_RESULT hr = FMOD_System_GetVersion(FmodSystem, &version);
    CHECK_ERROR
    return UINT2NUM(version);
}

VALUE rb_System_init(VALUE self, VALUE num_channel, VALUE flags)
{
    FMOD_RESULT hr = FMOD_System_Init(FmodSystem, NUM2LONG(num_channel), NUM2LONG(flags), NULL);
    CHECK_ERROR
    return self;
}

VALUE rb_System_isRecording(VALUE self, VALUE id)
{
    int state;
    FMOD_RESULT hr = FMOD_System_IsRecording(FmodSystem, NUM2LONG(id), &state);
    CHECK_ERROR
    return (state ? Qtrue : Qfalse);
}

VALUE rb_System_playSound(int argc, VALUE* argv, VALUE self) // sound, paused = C_FALSE => Channel
{
    VALUE sound, paused;
    rb_scan_args(argc, argv, "11", &sound, &paused);
    if(rb_obj_is_kind_of(sound, rb_cFmodSound) == Qfalse)
    {
        rb_raise(rb_eTypeError, "Expected FMOD::Sound, got %s", RSTRING_PTR(rb_class_name(CLASS_OF(sound))));
        return Qnil;
    }
    GET_SOUND(sound, fsound)
    VALUE channel = rb_class_new_instance(0, NULL, rb_cFmodChannel);
    rb_check_type(channel, T_DATA);
    FMOD_RESULT hr = FMOD_System_PlaySound(FmodSystem,
        fsound,
        NULL,
        RTEST(paused),
        (FMOD_CHANNEL**)(&RDATA(channel)->data)
    );
    CHECK_ERROR
    rb_ivar_set(channel, current_sound, sound);
    return channel;
}

VALUE rb_System_recordStart(VALUE self, VALUE id, VALUE sound, VALUE loop)
{
    if(rb_obj_is_kind_of(sound, rb_cFmodSound) == Qfalse)
    {
        rb_raise(rb_eTypeError, "Expected FMOD::Sound, got %s", RSTRING_PTR(rb_class_name(CLASS_OF(sound))));
        return Qnil;
    }
    rb_check_type(sound, T_DATA);
    FMOD_RESULT hr = FMOD_System_RecordStart(FmodSystem,
        NUM2LONG(id),
        (FMOD_SOUND*)(RDATA(sound)->data),
        RTEST(loop)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_System_recordStop(VALUE self, VALUE id)
{
    FMOD_RESULT hr = FMOD_System_RecordStop(FmodSystem, NUM2LONG(id));
    CHECK_ERROR
    return self;
}

VALUE rb_System_release(VALUE self)
{
    FMOD_RESULT hr = FMOD_System_Release(FmodSystem);
    CHECK_ERROR
    return self;
}

VALUE rb_System_setDriver(VALUE self, VALUE driver)
{
    FMOD_RESULT hr = FMOD_System_SetDriver(FmodSystem, NUM2LONG(driver));
    CHECK_ERROR
    return self;
}

VALUE rb_System_setOutput(VALUE self, VALUE output)
{
    FMOD_RESULT hr = FMOD_System_SetOutput(FmodSystem,
        (FMOD_OUTPUTTYPE)(NUM2LONG(output))
    );
    CHECK_ERROR
    return self;
}

VALUE rb_System_setSoftwareChannels(VALUE self, VALUE max_channels)
{
    FMOD_RESULT hr = FMOD_System_SetSoftwareChannels(FmodSystem, NUM2LONG(max_channels));
    CHECK_ERROR
    return self;
}

VALUE rb_System_setSoftwareFormat(VALUE self, VALUE samplerate, VALUE speakermode, VALUE numrawspeakers)
{
    FMOD_RESULT hr = FMOD_System_SetSoftwareFormat(FmodSystem,
        NUM2LONG(samplerate),
        (FMOD_SPEAKERMODE)(NUM2LONG(speakermode)),
        NUM2LONG(numrawspeakers)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_System_setStreamBufferSize(VALUE self, VALUE filebuffersize, VALUE filebuffersizetype)
{
    FMOD_RESULT hr = FMOD_System_SetStreamBufferSize(FmodSystem,
        NUM2UINT(filebuffersize),
        NUM2UINT(filebuffersizetype)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_System_update(VALUE self)
{
    FMOD_RESULT hr = FMOD_System_Update(FmodSystem);
    CHECK_ERROR
    return self;
}
