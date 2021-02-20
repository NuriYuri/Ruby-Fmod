#include "Ruby-Fmod.h"

#define GET_SOUND_SAFE \
    GET_SOUND(self, fsound) \
    if(fsound == NULL) \
        rb_raise(rb_eFmodError, "Sound not created by Fmod");

ID subsound_table = Qnil;
ID subsound_parent = Qnil;

void rb_Sound_Free(void* data)
{
    if(data != NULL)
    {
        FMOD_Sound_Release((FMOD_SOUND*)data);
    }
}

VALUE rb_Sound_Alloc(VALUE klass)
{
    return Data_Wrap_Struct(klass, NULL, rb_Sound_Free, NULL);
}

void Init_Sound()
{
    rb_define_alloc_func(rb_cFmodSound, rb_Sound_Alloc);
    rb_define_method(rb_cFmodSound, "getDefaults", _rbf rb_Sound_getDefaults, 0);
    rb_define_method(rb_cFmodSound, "getFormat", _rbf rb_Sound_getFormat, 0);
    rb_define_method(rb_cFmodSound, "getLength", _rbf rb_Sound_getLength, 1);
    rb_define_method(rb_cFmodSound, "getLoopCount", _rbf rb_Sound_getLoopCount, 0);
    rb_define_method(rb_cFmodSound, "getLoopPoints", _rbf rb_Sound_getLoopPoints, 2);
    rb_define_method(rb_cFmodSound, "getMode", _rbf rb_Sound_getMode, 0);
    rb_define_method(rb_cFmodSound, "getMusicChannelVolume", _rbf rb_Sound_getMusicChannelVolume, 1);
    rb_define_method(rb_cFmodSound, "getMusicNumChannels", _rbf rb_Sound_getMusicNumChannels, 0);
    rb_define_method(rb_cFmodSound, "getMusicSpeed", _rbf rb_Sound_getMusicSpeed, 0);
    rb_define_method(rb_cFmodSound, "getName", _rbf rb_Sound_getName, 0);
    rb_define_method(rb_cFmodSound, "getNumSubSounds", _rbf rb_Sound_getNumSubSounds, 0);
    rb_define_method(rb_cFmodSound, "getNumTags", _rbf rb_Sound_getNumTags, 0);
    rb_define_method(rb_cFmodSound, "getOpenState", _rbf rb_Sound_getOpenState, 0);
    rb_define_method(rb_cFmodSound, "getSubSound", _rbf rb_Sound_getSubSound, 1);
    rb_define_method(rb_cFmodSound, "getSubSoundParent", _rbf rb_Sound_getSubSoundParent, 0);
    rb_define_method(rb_cFmodSound, "getTag", _rbf rb_Sound_getTag, 2);
    rb_define_method(rb_cFmodSound, "readData", _rbf rb_Sound_readData, 1); // Returns the number of byte read
    rb_define_method(rb_cFmodSound, "release", _rbf rb_Sound_release, 0);
    rb_define_method(rb_cFmodSound, "seekData", _rbf rb_Sound_seekData, 1);
    rb_define_method(rb_cFmodSound, "setDefaults", _rbf rb_Sound_setDefaults, 2);
    rb_define_method(rb_cFmodSound, "setLoopCount", _rbf rb_Sound_setLoopCount, 1);
    rb_define_method(rb_cFmodSound, "setLoopPoints", _rbf rb_Sound_setLoopPoints, 4);
    rb_define_method(rb_cFmodSound, "setMode", _rbf rb_Sound_setMode, 1);
    rb_define_method(rb_cFmodSound, "setMusicChannelVolume", _rbf rb_Sound_setMusicChannelVolume, 2);
    rb_define_method(rb_cFmodSound, "setMusicSpeed", _rbf rb_Sound_setMusicSpeed, 1);
    subsound_table = rb_intern("@subsound_table");
    subsound_parent = rb_intern("@parent");
    Init_SoundEx();
}


void rb_Sound_store_sound_to_subsound_table(VALUE self, VALUE sound, long id)
{
    VALUE table = rb_ivar_get(self, subsound_table);
    if(table == Qnil)
    {
        table = rb_ary_new();
        rb_ivar_set(self, subsound_table, table);
    }
    rb_ary_store(table, id, sound);
}

int rb_Sound_is_subsound_present(VALUE self, long id)
{
    VALUE table = rb_ivar_get(self, subsound_table);
    if(table == Qnil)
        return C_FALSE;
    if(rb_ary_entry(table, id) == Qnil)
        return C_FALSE;
    return C_TRUE;
}

VALUE rb_Sound_get_sub_sound(VALUE self, long id)
{
    if(rb_Sound_is_subsound_present(self, id))
    {
        VALUE table = rb_ivar_get(self, subsound_table);
        return rb_ary_entry(table, id);
    }
    VALUE sound = rb_class_new_instance(0, NULL, rb_cFmodSound);
    rb_Sound_store_sound_to_subsound_table(self, sound, id);
    return sound;
}

VALUE rb_Sound_getDefaults(VALUE self)
{
    GET_SOUND_SAFE
    float frequency;
    int priority;
    FMOD_RESULT hr = FMOD_Sound_GetDefaults(fsound, &frequency, &priority);
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_float_new(frequency));
    rb_ary_push(return_data, rb_int2inum(priority));
    return return_data;
}

VALUE rb_Sound_getFormat(VALUE self)
{
    GET_SOUND_SAFE
    FMOD_SOUND_TYPE type;
    FMOD_SOUND_FORMAT format;
    int channels;
    int bits;
    FMOD_RESULT hr = FMOD_Sound_GetFormat(fsound, &type, &format, &channels, &bits);
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_int2inum(type));
    rb_ary_push(return_data, rb_int2inum(format));
    rb_ary_push(return_data, rb_int2inum(channels));
    rb_ary_push(return_data, rb_int2inum(bits));
    return return_data;
}

VALUE rb_Sound_getLength(VALUE self, VALUE timeunit)
{
    GET_SOUND_SAFE
    unsigned int length;
    FMOD_RESULT hr = FMOD_Sound_GetLength(fsound, &length, NUM2LONG(timeunit));
    CHECK_ERROR
    return UINT2NUM(length);
}

VALUE rb_Sound_getLoopCount(VALUE self)
{
    GET_SOUND_SAFE
    int loopcount;
    FMOD_RESULT hr = FMOD_Sound_GetLoopCount(fsound, &loopcount);
    CHECK_ERROR
    return rb_int2inum(loopcount);
}

VALUE rb_Sound_getLoopPoints(VALUE self, VALUE startunit, VALUE stopunit)
{
    GET_SOUND_SAFE
    unsigned int start, end;
    FMOD_RESULT hr = FMOD_Sound_GetLoopPoints(fsound,
        &start,
        NUM2LONG(startunit),
        &end,
        NUM2LONG(stopunit)
    );
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, UINT2NUM(start));
    rb_ary_push(return_data, UINT2NUM(end));
    return return_data;
}

VALUE rb_Sound_getMode(VALUE self)
{
    GET_SOUND_SAFE
    FMOD_MODE mode;
    FMOD_RESULT hr = FMOD_Sound_GetMode(fsound, &mode);
    CHECK_ERROR
    return UINT2NUM(mode);
}

VALUE rb_Sound_getMusicChannelVolume(VALUE self, VALUE channelid)
{
    GET_SOUND_SAFE
    float volume;
    FMOD_RESULT hr = FMOD_Sound_GetMusicChannelVolume(fsound, NUM2LONG(channelid), &volume);
    CHECK_ERROR
    return rb_float_new(volume);
}

VALUE rb_Sound_getMusicNumChannels(VALUE self)
{
    GET_SOUND_SAFE
    int numchannels;
    FMOD_RESULT hr = FMOD_Sound_GetMusicNumChannels(fsound, &numchannels);
    CHECK_ERROR
    return rb_int2inum(numchannels);
}

VALUE rb_Sound_getMusicSpeed(VALUE self)
{
    GET_SOUND_SAFE
    float speed;
    FMOD_RESULT hr = FMOD_Sound_GetMusicSpeed(fsound, &speed);
    CHECK_ERROR
    return rb_float_new(speed);
}

VALUE rb_Sound_getName(VALUE self)
{
    GET_SOUND_SAFE
    char name[1024];
    FMOD_RESULT hr = FMOD_Sound_GetName(fsound, name, 1024);
    CHECK_ERROR
    return rb_str_new_cstr(name);
}

VALUE rb_Sound_getNumSubSounds(VALUE self)
{
    GET_SOUND_SAFE
    int numsubsound;
    FMOD_RESULT hr = FMOD_Sound_GetNumSubSounds(fsound, &numsubsound);
    CHECK_ERROR
    return rb_int2inum(numsubsound);
}

VALUE rb_Sound_getNumTags(VALUE self)
{
    GET_SOUND_SAFE
    int numtag, numtagupdated;
    FMOD_RESULT hr = FMOD_Sound_GetNumTags(fsound, &numtag, &numtagupdated);
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_int2inum(numtag));
    rb_ary_push(return_data, rb_int2inum(numtagupdated));
    return return_data;
}

VALUE rb_Sound_getOpenState(VALUE self)
{
    GET_SOUND_SAFE
    FMOD_OPENSTATE openstate;
    unsigned int percentbuffered;
    int starving;
    int diskbusy;
    FMOD_RESULT hr = FMOD_Sound_GetOpenState(fsound, &openstate, &percentbuffered, &starving, &diskbusy);
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_int2inum(openstate));
    rb_ary_push(return_data, UINT2NUM(percentbuffered));
    rb_ary_push(return_data, starving ? Qtrue : Qfalse);
    rb_ary_push(return_data, diskbusy ? Qtrue : Qfalse);
    return return_data;
}

VALUE rb_Sound_getSubSound(VALUE self, VALUE index)
{
    GET_SOUND_SAFE
    long id = NUM2LONG(index);
    VALUE sound = rb_Sound_get_sub_sound(self, id);
    rb_check_type(sound, T_DATA);
    FMOD_RESULT hr = FMOD_Sound_GetSubSound(fsound, id, (FMOD_SOUND**)(&RDATA(sound)->data));
    CHECK_ERROR
    rb_ivar_set(sound, subsound_parent, self);
    return sound;
}

VALUE rb_Sound_store_child_in_parent_table(VALUE child, VALUE parent, FMOD_SOUND* fsound)
{
    FMOD_SOUND* psound = (FMOD_SOUND*)(RDATA(parent)->data);
    FMOD_SOUND* csound;
    // Getting the subSound index
    int numsubsound;
    FMOD_RESULT hr = FMOD_Sound_GetNumSubSounds(psound, &numsubsound);
    CHECK_ERROR
    for(int i = 0; i < numsubsound;i++)
    {
        hr = FMOD_Sound_GetSubSound(psound, i, &csound);
        CHECK_ERROR
        if(csound == fsound)
        {
            // Check if there's an child sound in the table
            if(rb_Sound_is_subsound_present(parent, i))
            {
                // Check if the other child is the same, if different => error
                if(rb_Sound_get_sub_sound(parent, i) != child)
                {
                    rb_raise(rb_eFmodError, "Duplicate subsound in parent's child sound table.");
                    return parent;
                }
            }
            // Store sound to table
            rb_Sound_store_sound_to_subsound_table(parent, child, i);
            return parent;
        }
    }
    return parent;
}

VALUE rb_Sound_getSubSoundParent(VALUE self)
{
    GET_SOUND_SAFE
    VALUE parent = rb_ivar_get(self, subsound_parent);
    if(parent != Qnil)
        return parent;
    parent = rb_class_new_instance(0, NULL, rb_cFmodSound);
    rb_check_type(parent, T_DATA);
    FMOD_RESULT hr = FMOD_Sound_GetSubSoundParent(fsound, (FMOD_SOUND**)(&RDATA(parent)->data));
    CHECK_ERROR
    rb_ivar_set(self, subsound_parent, parent);
    return rb_Sound_store_child_in_parent_table(self, parent, fsound);
}

VALUE rb_Sound_getTag(VALUE self, VALUE name, VALUE index)
{
    GET_SOUND_SAFE
    rb_check_type(name, T_STRING);
    FMOD_TAG tag;
    FMOD_RESULT hr = FMOD_Sound_GetTag(fsound, RSTRING_PTR(name), NUM2LONG(index), &tag);
    CHECK_ERROR
    VALUE return_data = rb_ary_new();
    rb_ary_push(return_data, rb_int2inum(tag.type));
    rb_ary_push(return_data, rb_int2inum(tag.datatype));
    // Data push
    switch(tag.datatype)
    {
        case FMOD_TAGDATATYPE_INT:
            if(tag.datalen == SIZEOF_LONG_LONG)
                rb_ary_push(return_data, rb_ll2inum(*(long long*)(tag.data)));
            else if(tag.datalen == SIZEOF_INT)
                rb_ary_push(return_data, rb_int2inum(*(int*)(tag.data)));
            else if(tag.datalen == SIZEOF_SHORT)
                rb_ary_push(return_data, rb_int2inum(*(short*)(tag.data)));
            else
                rb_ary_push(return_data, rb_int2inum(*(char*)(tag.data)));
            break;
        case FMOD_TAGDATATYPE_FLOAT:
            if(tag.datalen == SIZEOF_FLOAT)
                rb_ary_push(return_data, rb_float_new((double)(*(float*)(tag.data))));
            else if(tag.datalen == SIZEOF_DOUBLE)
                rb_ary_push(return_data, rb_float_new(*(double*)(tag.data)));
            else if(tag.datalen == sizeof(long double))
                rb_ary_push(return_data, rb_float_new((double)(*(long double*)(tag.data))));
            else
                rb_ary_push(return_data, rb_str_new((char*)tag.data, tag.datalen));
            break;
        case FMOD_TAGDATATYPE_BINARY:
        case FMOD_TAGDATATYPE_STRING:
        case FMOD_TAGDATATYPE_STRING_UTF16:
        case FMOD_TAGDATATYPE_STRING_UTF16BE:
        case FMOD_TAGDATATYPE_STRING_UTF8:
        default:
            rb_ary_push(return_data, rb_str_new((char*)tag.data, tag.datalen));
            break;
    }
    rb_ary_push(return_data, tag.updated ? Qtrue : Qfalse);
    return return_data;

}

VALUE rb_Sound_readData(VALUE self, VALUE buffer) // Returns the number of byte read
{
    GET_SOUND_SAFE
    unsigned int read;
    rb_check_type(buffer, T_STRING);
    FMOD_RESULT hr = FMOD_Sound_ReadData(fsound, RSTRING_PTR(buffer), RSTRING_LEN(buffer), &read);
    CHECK_ERROR
    return UINT2NUM(read);
}

VALUE rb_Sound_release(VALUE self) // Is the subsound released ?
{
    GET_SOUND_SAFE
    FMOD_RESULT hr = FMOD_Sound_Release(fsound);
    CHECK_ERROR
    RDATA(self)->data = NULL;
    return Qnil;
}

VALUE rb_Sound_seekData(VALUE self, VALUE pcmoffset)
{
    GET_SOUND_SAFE
    FMOD_RESULT hr = FMOD_Sound_SeekData(fsound, NUM2UINT(pcmoffset));
    CHECK_ERROR
    return self;
}

VALUE rb_Sound_setDefaults(VALUE self, VALUE frequency, VALUE priority)
{
    GET_SOUND_SAFE
    FMOD_RESULT hr = FMOD_Sound_SetDefaults(fsound, NUM2DBL(frequency), NUM2LONG(priority));
    CHECK_ERROR
    return self;
}

VALUE rb_Sound_setLoopCount(VALUE self, VALUE count)
{
    GET_SOUND_SAFE
    FMOD_RESULT hr = FMOD_Sound_SetLoopCount(fsound, NUM2LONG(count));
    CHECK_ERROR
    return self;
}

VALUE rb_Sound_setLoopPoints(VALUE self, VALUE start, VALUE startunit, VALUE stop, VALUE stopunit)
{
    GET_SOUND_SAFE
    FMOD_RESULT hr = FMOD_Sound_SetLoopPoints(fsound,
        NUM2UINT(start),
        NUM2LONG(startunit),
        NUM2UINT(stop),
        NUM2LONG(stopunit)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Sound_setMode(VALUE self, VALUE mode)
{
    GET_SOUND_SAFE
    FMOD_RESULT hr = FMOD_Sound_SetMode(fsound, NUM2LONG(mode));
    CHECK_ERROR
    return self;
}

VALUE rb_Sound_setMusicChannelVolume(VALUE self, VALUE channelindex, VALUE volume)
{
    GET_SOUND_SAFE
    FMOD_RESULT hr = FMOD_Sound_SetMusicChannelVolume(fsound,
        NUM2LONG(channelindex),
        NUM2DBL(volume)
    );
    CHECK_ERROR
    return self;
}

VALUE rb_Sound_setMusicSpeed(VALUE self, VALUE speed)
{
    GET_SOUND_SAFE
    FMOD_RESULT hr = FMOD_Sound_SetMusicSpeed(fsound, NUM2DBL(speed));
    CHECK_ERROR
    return self;
}
