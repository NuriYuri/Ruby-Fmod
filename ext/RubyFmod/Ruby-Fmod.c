#include "Ruby-Fmod.h"

VALUE rb_mFmod = Qnil;
VALUE rb_mFmodSystem = Qnil;
VALUE rb_cFmodSound = Qnil;
VALUE rb_cFmodChannel = Qnil;
VALUE rb_eFmodError = Qnil;

ID FmodErrorHr = Qnil;
ID current_sound = Qnil;

FMOD_SYSTEM* FmodSystem = NULL;

VALUE rb_FmodError_Init(VALUE self, VALUE hr);
VALUE rb_FmodError_hr(VALUE self);
void InitConstants();
VALUE rb_FmodError_new(VALUE self, VALUE message);

extern void Init_RubyFmod();
void Init_RubyFmod()
{
    FMOD_RESULT hr = FMOD_System_Create(&FmodSystem, FMOD_VERSION);
    if(hr != FMOD_OK)
        rb_raise(rb_eRuntimeError, "Could not create Fmod System Object : %s", FMOD_ErrorString(hr));
    
    rb_mFmod = rb_define_module("FMOD");
    rb_mFmodSystem = rb_define_module_under(rb_mFmod, "System");
    rb_cFmodSound = rb_define_class_under(rb_mFmod, "Sound", rb_cObject);
    rb_cFmodChannel = rb_define_class_under(rb_mFmod, "Channel", rb_cObject);
    rb_eFmodError = rb_define_class_under(rb_mFmod, "Error", rb_eStandardError);
 
    current_sound = rb_intern("@current_sound");

    Init_System();
    Init_Sound();
    Init_Channel();
    InitConstants();
}

VALUE rb_FmodRaiseError(FMOD_RESULT hr) {
    rb_raise(rb_eFmodError, "FmodError %d : %s", hr, FMOD_ErrorString(hr));
    return Qnil;
}

void InitConstants()
{
    VALUE mod = rb_mFmod;
    // Fmod Define constants
    rb_define_const(mod, "VERSION", rb_int2inum(FMOD_VERSION));
    rb_define_const(mod, "MAX_CHANNEL_WIDTH", rb_int2inum(FMOD_MAX_CHANNEL_WIDTH));
    rb_define_const(mod, "MAX_SYSTEMS", rb_int2inum(FMOD_MAX_SYSTEMS));
    rb_define_const(mod, "MAX_LISTENERS", rb_int2inum(FMOD_MAX_LISTENERS));
    // DEBUG
    mod = rb_define_module_under(rb_mFmod, "DEBUG");
    rb_define_const(mod, "LEVEL_NONE", rb_int2inum(FMOD_DEBUG_LEVEL_NONE));
    rb_define_const(mod, "LEVEL_ERROR", rb_int2inum(FMOD_DEBUG_LEVEL_ERROR));
    rb_define_const(mod, "LEVEL_WARNING", rb_int2inum(FMOD_DEBUG_LEVEL_WARNING));
    rb_define_const(mod, "LEVEL_LOG", rb_int2inum(FMOD_DEBUG_LEVEL_LOG));
    rb_define_const(mod, "TYPE_MEMORY", rb_int2inum(FMOD_DEBUG_TYPE_MEMORY));
    rb_define_const(mod, "TYPE_FILE", rb_int2inum(FMOD_DEBUG_TYPE_FILE));
    rb_define_const(mod, "TYPE_CODEC", rb_int2inum(FMOD_DEBUG_TYPE_CODEC));
    rb_define_const(mod, "TYPE_TRACE", rb_int2inum(FMOD_DEBUG_TYPE_TRACE));
    rb_define_const(mod, "DISPLAY_TIMESTAMPS", rb_int2inum(FMOD_DEBUG_DISPLAY_TIMESTAMPS));
    rb_define_const(mod, "DISPLAY_LINENUMBERS", rb_int2inum(FMOD_DEBUG_DISPLAY_LINENUMBERS));
    rb_define_const(mod, "DISPLAY_THREAD", rb_int2inum(FMOD_DEBUG_DISPLAY_THREAD));
    // FMOD_MEMORY
    mod = rb_define_module_under(rb_mFmod, "MEMORY");
    rb_define_const(mod, "NORMAL", rb_int2inum(FMOD_MEMORY_NORMAL));
    rb_define_const(mod, "STREAM_FILE", rb_int2inum(FMOD_MEMORY_STREAM_FILE));
    rb_define_const(mod, "STREAM_DECODE", rb_int2inum(FMOD_MEMORY_STREAM_DECODE));
    rb_define_const(mod, "SAMPLEDATA", rb_int2inum(FMOD_MEMORY_SAMPLEDATA));
    rb_define_const(mod, "DSP_BUFFER", rb_int2inum(FMOD_MEMORY_DSP_BUFFER));
    rb_define_const(mod, "PLUGIN", rb_int2inum(FMOD_MEMORY_PLUGIN));
    rb_define_const(mod, "PERSISTENT", rb_int2inum(FMOD_MEMORY_PERSISTENT));
    rb_define_const(mod, "ALL", rb_int2inum(FMOD_MEMORY_ALL));
    // CHANNELMASK
    mod = rb_define_module_under(rb_mFmod, "CHANNELMASK");
    rb_define_const(mod, "FRONT_LEFT", rb_int2inum(FMOD_CHANNELMASK_FRONT_LEFT));
    rb_define_const(mod, "FRONT_RIGHT", rb_int2inum(FMOD_CHANNELMASK_FRONT_RIGHT));
    rb_define_const(mod, "FRONT_CENTER", rb_int2inum(FMOD_CHANNELMASK_FRONT_CENTER));
    rb_define_const(mod, "LOW_FREQUENCY", rb_int2inum(FMOD_CHANNELMASK_LOW_FREQUENCY));
    rb_define_const(mod, "SURROUND_LEFT", rb_int2inum(FMOD_CHANNELMASK_SURROUND_LEFT));
    rb_define_const(mod, "SURROUND_RIGHT", rb_int2inum(FMOD_CHANNELMASK_SURROUND_RIGHT));
    rb_define_const(mod, "BACK_LEFT", rb_int2inum(FMOD_CHANNELMASK_BACK_LEFT));
    rb_define_const(mod, "BACK_RIGHT", rb_int2inum(FMOD_CHANNELMASK_BACK_RIGHT));
    rb_define_const(mod, "BACK_CENTER", rb_int2inum(FMOD_CHANNELMASK_BACK_CENTER));
    rb_define_const(mod, "MONO", rb_int2inum(FMOD_CHANNELMASK_MONO));
    rb_define_const(mod, "STEREO", rb_int2inum(FMOD_CHANNELMASK_STEREO));
    rb_define_const(mod, "LRC", rb_int2inum(FMOD_CHANNELMASK_LRC));
    rb_define_const(mod, "QUAD", rb_int2inum(FMOD_CHANNELMASK_QUAD));
    rb_define_const(mod, "SURROUND", rb_int2inum(FMOD_CHANNELMASK_SURROUND));
    rb_define_const(mod, "CHANNELMASK_5POINT1", rb_int2inum(FMOD_CHANNELMASK_5POINT1));
    rb_define_const(mod, "CHANNELMASK_5POINT1_REARS", rb_int2inum(FMOD_CHANNELMASK_5POINT1_REARS));
    rb_define_const(mod, "CHANNELMASK_7POINT0", rb_int2inum(FMOD_CHANNELMASK_7POINT0));
    rb_define_const(mod, "CHANNELMASK_7POINT1", rb_int2inum(FMOD_CHANNELMASK_7POINT1));
    // INIT
    mod = rb_define_module_under(rb_mFmod, "INIT");
    rb_define_const(mod, "NORMAL", rb_int2inum(FMOD_INIT_NORMAL));
    rb_define_const(mod, "STREAM_FROM_UPDATE", rb_int2inum(FMOD_INIT_STREAM_FROM_UPDATE));
    rb_define_const(mod, "MIX_FROM_UPDATE", rb_int2inum(FMOD_INIT_MIX_FROM_UPDATE));
    rb_define_const(mod, "INIT_3D_RIGHTHANDED", rb_int2inum(FMOD_INIT_3D_RIGHTHANDED));
    rb_define_const(mod, "CHANNEL_LOWPASS", rb_int2inum(FMOD_INIT_CHANNEL_LOWPASS));
    rb_define_const(mod, "CHANNEL_DISTANCEFILTER", rb_int2inum(FMOD_INIT_CHANNEL_DISTANCEFILTER));
    rb_define_const(mod, "PROFILE_ENABLE", rb_int2inum(FMOD_INIT_PROFILE_ENABLE));
    rb_define_const(mod, "VOL0_BECOMES_VIRTUAL", rb_int2inum(FMOD_INIT_VOL0_BECOMES_VIRTUAL));
    rb_define_const(mod, "GEOMETRY_USECLOSEST", rb_int2inum(FMOD_INIT_GEOMETRY_USECLOSEST));
    rb_define_const(mod, "PREFER_DOLBY_DOWNMIX", rb_int2inum(FMOD_INIT_PREFER_DOLBY_DOWNMIX));
    rb_define_const(mod, "THREAD_UNSAFE", rb_int2inum(FMOD_INIT_THREAD_UNSAFE));
    rb_define_const(mod, "PROFILE_METER_ALL", rb_int2inum(FMOD_INIT_PROFILE_METER_ALL));
    rb_define_const(mod, "MEMORY_TRACKING", rb_int2inum(FMOD_INIT_MEMORY_TRACKING));
    // FMOD_MODE
    mod = rb_define_module_under(rb_mFmod, "MODE");
    rb_define_const(mod, "DEFAULT", rb_int2inum(FMOD_DEFAULT));
    rb_define_const(mod, "LOOP_OFF", rb_int2inum(FMOD_LOOP_OFF));
    rb_define_const(mod, "LOOP_NORMAL", rb_int2inum(FMOD_LOOP_NORMAL));
    rb_define_const(mod, "LOOP_BIDI", rb_int2inum(FMOD_LOOP_BIDI));
    rb_define_const(mod, "FMOD_2D", rb_int2inum(FMOD_2D));
    rb_define_const(mod, "FMOD_3D", rb_int2inum(FMOD_3D));
    rb_define_const(mod, "CREATESTREAM", rb_int2inum(FMOD_CREATESTREAM));
    rb_define_const(mod, "CREATESAMPLE", rb_int2inum(FMOD_CREATESAMPLE));
    rb_define_const(mod, "CREATECOMPRESSEDSAMPLE", rb_int2inum(FMOD_CREATECOMPRESSEDSAMPLE));
    rb_define_const(mod, "OPENUSER", rb_int2inum(FMOD_OPENUSER));
    rb_define_const(mod, "OPENMEMORY", rb_int2inum(FMOD_OPENMEMORY));
    rb_define_const(mod, "OPENMEMORY_POINT", rb_int2inum(FMOD_OPENMEMORY_POINT));
    rb_define_const(mod, "OPENRAW", rb_int2inum(FMOD_OPENRAW));
    rb_define_const(mod, "OPENONLY", rb_int2inum(FMOD_OPENONLY));
    rb_define_const(mod, "ACCURATETIME", rb_int2inum(FMOD_ACCURATETIME));
    rb_define_const(mod, "MPEGSEARCH", rb_int2inum(FMOD_MPEGSEARCH));
    rb_define_const(mod, "NONBLOCKING", rb_int2inum(FMOD_NONBLOCKING));
    rb_define_const(mod, "UNIQUE", rb_int2inum(FMOD_UNIQUE));
    rb_define_const(mod, "FMOD_3D_HEADRELATIVE", rb_int2inum(FMOD_3D_HEADRELATIVE));
    rb_define_const(mod, "FMOD_3D_WORLDRELATIVE", rb_int2inum(FMOD_3D_WORLDRELATIVE));
    rb_define_const(mod, "FMOD_3D_INVERSEROLLOFF", rb_int2inum(FMOD_3D_INVERSEROLLOFF));
    rb_define_const(mod, "FMOD_3D_LINEARROLLOFF", rb_int2inum(FMOD_3D_LINEARROLLOFF));
    rb_define_const(mod, "FMOD_3D_LINEARSQUAREROLLOFF", rb_int2inum(FMOD_3D_LINEARSQUAREROLLOFF));
    rb_define_const(mod, "FMOD_3D_INVERSETAPEREDROLLOFF", rb_int2inum(FMOD_3D_INVERSETAPEREDROLLOFF));
    rb_define_const(mod, "FMOD_3D_CUSTOMROLLOFF", rb_int2inum(FMOD_3D_CUSTOMROLLOFF));
    rb_define_const(mod, "FMOD_3D_IGNOREGEOMETRY", rb_int2inum(FMOD_3D_IGNOREGEOMETRY));
    rb_define_const(mod, "IGNORETAGS", rb_int2inum(FMOD_IGNORETAGS));
    rb_define_const(mod, "LOWMEM", rb_int2inum(FMOD_LOWMEM));
    rb_define_const(mod, "VIRTUAL_PLAYFROMSTART", rb_int2inum(FMOD_VIRTUAL_PLAYFROMSTART));
    // TIMEUNIT
    mod = rb_define_module_under(rb_mFmod, "TIMEUNIT");
    rb_define_const(mod, "MS", rb_int2inum(FMOD_TIMEUNIT_MS));
    rb_define_const(mod, "PCM", rb_int2inum(FMOD_TIMEUNIT_PCM));
    rb_define_const(mod, "PCMBYTES", rb_int2inum(FMOD_TIMEUNIT_PCMBYTES));
    rb_define_const(mod, "RAWBYTES", rb_int2inum(FMOD_TIMEUNIT_RAWBYTES));
    rb_define_const(mod, "PCMFRACTION", rb_int2inum(FMOD_TIMEUNIT_PCMFRACTION));
    rb_define_const(mod, "MODORDER", rb_int2inum(FMOD_TIMEUNIT_MODORDER));
    rb_define_const(mod, "MODROW", rb_int2inum(FMOD_TIMEUNIT_MODROW));
    rb_define_const(mod, "MODPATTERN", rb_int2inum(FMOD_TIMEUNIT_MODPATTERN));
    // DRIVER_STATE
    mod = rb_define_module_under(rb_mFmod, "DRIVER_STATE");
    rb_define_const(mod, "CONNECTED", rb_int2inum(FMOD_DRIVER_STATE_CONNECTED));
    rb_define_const(mod, "DEFAULT", rb_int2inum(FMOD_DRIVER_STATE_DEFAULT));
    // OUTPUTTYPE
    mod = rb_define_module_under(rb_mFmod, "OUTPUTTYPE");
    rb_define_const(mod, "AUTODETECT", rb_int2inum(FMOD_OUTPUTTYPE_AUTODETECT));
    rb_define_const(mod, "UNKNOWN", rb_int2inum(FMOD_OUTPUTTYPE_UNKNOWN));
    rb_define_const(mod, "NOSOUND", rb_int2inum(FMOD_OUTPUTTYPE_NOSOUND));
    rb_define_const(mod, "WAVWRITER", rb_int2inum(FMOD_OUTPUTTYPE_WAVWRITER));
    rb_define_const(mod, "NOSOUND_NRT", rb_int2inum(FMOD_OUTPUTTYPE_NOSOUND_NRT));
    rb_define_const(mod, "WAVWRITER_NRT", rb_int2inum(FMOD_OUTPUTTYPE_WAVWRITER_NRT));
    rb_define_const(mod, "WASAPI", rb_int2inum(FMOD_OUTPUTTYPE_WASAPI));
    rb_define_const(mod, "ASIO", rb_int2inum(FMOD_OUTPUTTYPE_ASIO));
    rb_define_const(mod, "PULSEAUDIO", rb_int2inum(FMOD_OUTPUTTYPE_PULSEAUDIO));
    rb_define_const(mod, "ALSA", rb_int2inum(FMOD_OUTPUTTYPE_ALSA));
    rb_define_const(mod, "COREAUDIO", rb_int2inum(FMOD_OUTPUTTYPE_COREAUDIO));
    rb_define_const(mod, "AUDIOTRACK", rb_int2inum(FMOD_OUTPUTTYPE_AUDIOTRACK));
    rb_define_const(mod, "OPENSL", rb_int2inum(FMOD_OUTPUTTYPE_OPENSL));
    rb_define_const(mod, "AUDIOOUT", rb_int2inum(FMOD_OUTPUTTYPE_AUDIOOUT));
    rb_define_const(mod, "AUDIO3D", rb_int2inum(FMOD_OUTPUTTYPE_AUDIO3D));
    rb_define_const(mod, "WEBAUDIO", rb_int2inum(FMOD_OUTPUTTYPE_WEBAUDIO));
    rb_define_const(mod, "NNAUDIO", rb_int2inum(FMOD_OUTPUTTYPE_NNAUDIO));
    rb_define_const(mod, "WINSONIC", rb_int2inum(FMOD_OUTPUTTYPE_WINSONIC));
    rb_define_const(mod, "AAUDIO", rb_int2inum(FMOD_OUTPUTTYPE_AAUDIO));
    // SPEAKERMODE
    mod = rb_define_module_under(rb_mFmod, "SPEAKERMODE");
    rb_define_const(mod, "DEFAULT", rb_int2inum(FMOD_SPEAKERMODE_DEFAULT));
    rb_define_const(mod, "RAW", rb_int2inum(FMOD_SPEAKERMODE_RAW));
    rb_define_const(mod, "MONO", rb_int2inum(FMOD_SPEAKERMODE_MONO));
    rb_define_const(mod, "STEREO", rb_int2inum(FMOD_SPEAKERMODE_STEREO));
    rb_define_const(mod, "QUAD", rb_int2inum(FMOD_SPEAKERMODE_QUAD));
    rb_define_const(mod, "SURROUND", rb_int2inum(FMOD_SPEAKERMODE_SURROUND));
    rb_define_const(mod, "SPEAKERMODE_5POINT1", rb_int2inum(FMOD_SPEAKERMODE_5POINT1));
    rb_define_const(mod, "SPEAKERMODE_7POINT1", rb_int2inum(FMOD_SPEAKERMODE_7POINT1));
    rb_define_const(mod, "SPEAKERMODE_7POINT1POINT4", rb_int2inum(FMOD_SPEAKERMODE_7POINT1POINT4));
    rb_define_const(mod, "MAX", rb_int2inum(FMOD_SPEAKERMODE_MAX));
    // SPEAKER
    mod = rb_define_module_under(rb_mFmod, "SPEAKER");
    rb_define_const(mod, "FRONT_LEFT", rb_int2inum(FMOD_SPEAKER_FRONT_LEFT));
    rb_define_const(mod, "FRONT_RIGHT", rb_int2inum(FMOD_SPEAKER_FRONT_RIGHT));
    rb_define_const(mod, "FRONT_CENTER", rb_int2inum(FMOD_SPEAKER_FRONT_CENTER));
    rb_define_const(mod, "LOW_FREQUENCY", rb_int2inum(FMOD_SPEAKER_LOW_FREQUENCY));
    rb_define_const(mod, "SURROUND_LEFT", rb_int2inum(FMOD_SPEAKER_SURROUND_LEFT));
    rb_define_const(mod, "SURROUND_RIGHT", rb_int2inum(FMOD_SPEAKER_SURROUND_RIGHT));
    rb_define_const(mod, "BACK_LEFT", rb_int2inum(FMOD_SPEAKER_BACK_LEFT));
    rb_define_const(mod, "BACK_RIGHT", rb_int2inum(FMOD_SPEAKER_BACK_RIGHT));
    rb_define_const(mod, "TOP_FRONT_LEFT", rb_int2inum(FMOD_SPEAKER_TOP_FRONT_LEFT));
    rb_define_const(mod, "TOP_FRONT_RIGHT", rb_int2inum(FMOD_SPEAKER_TOP_FRONT_RIGHT));
    rb_define_const(mod, "TOP_BACK_LEFT", rb_int2inum(FMOD_SPEAKER_TOP_BACK_LEFT));
    rb_define_const(mod, "TOP_BACK_RIGHT", rb_int2inum(FMOD_SPEAKER_TOP_BACK_RIGHT));
    rb_define_const(mod, "MAX", rb_int2inum(FMOD_SPEAKER_MAX));
    // SOUND_TYPE
    mod = rb_define_module_under(rb_mFmod, "SOUND_TYPE");
    rb_define_const(mod, "UNKNOWN", rb_int2inum(FMOD_SOUND_TYPE_UNKNOWN));
    rb_define_const(mod, "AIFF", rb_int2inum(FMOD_SOUND_TYPE_AIFF));
    rb_define_const(mod, "ASF", rb_int2inum(FMOD_SOUND_TYPE_ASF));
    rb_define_const(mod, "DLS", rb_int2inum(FMOD_SOUND_TYPE_DLS));
    rb_define_const(mod, "FLAC", rb_int2inum(FMOD_SOUND_TYPE_FLAC));
    rb_define_const(mod, "FSB", rb_int2inum(FMOD_SOUND_TYPE_FSB));
    rb_define_const(mod, "IT", rb_int2inum(FMOD_SOUND_TYPE_IT));
    rb_define_const(mod, "MIDI", rb_int2inum(FMOD_SOUND_TYPE_MIDI));
    rb_define_const(mod, "MOD", rb_int2inum(FMOD_SOUND_TYPE_MOD));
    rb_define_const(mod, "MPEG", rb_int2inum(FMOD_SOUND_TYPE_MPEG));
    rb_define_const(mod, "OGGVORBIS", rb_int2inum(FMOD_SOUND_TYPE_OGGVORBIS));
    rb_define_const(mod, "PLAYLIST", rb_int2inum(FMOD_SOUND_TYPE_PLAYLIST));
    rb_define_const(mod, "RAW", rb_int2inum(FMOD_SOUND_TYPE_RAW));
    rb_define_const(mod, "S3M", rb_int2inum(FMOD_SOUND_TYPE_S3M));
    rb_define_const(mod, "USER", rb_int2inum(FMOD_SOUND_TYPE_USER));
    rb_define_const(mod, "WAV", rb_int2inum(FMOD_SOUND_TYPE_WAV));
    rb_define_const(mod, "XM", rb_int2inum(FMOD_SOUND_TYPE_XM));
    rb_define_const(mod, "XMA", rb_int2inum(FMOD_SOUND_TYPE_XMA));
    rb_define_const(mod, "AUDIOQUEUE", rb_int2inum(FMOD_SOUND_TYPE_AUDIOQUEUE));
    rb_define_const(mod, "AT9", rb_int2inum(FMOD_SOUND_TYPE_AT9));
    rb_define_const(mod, "VORBIS", rb_int2inum(FMOD_SOUND_TYPE_VORBIS));
    rb_define_const(mod, "MEDIA_FOUNDATION", rb_int2inum(FMOD_SOUND_TYPE_MEDIA_FOUNDATION));
    rb_define_const(mod, "MEDIACODEC", rb_int2inum(FMOD_SOUND_TYPE_MEDIACODEC));
    rb_define_const(mod, "FADPCM", rb_int2inum(FMOD_SOUND_TYPE_FADPCM));
    rb_define_const(mod, "MAX", rb_int2inum(FMOD_SOUND_TYPE_MAX));
    // SOUND_FORMAT
    mod = rb_define_module_under(rb_mFmod, "SOUND_FORMAT");
    rb_define_const(mod, "NONE", rb_int2inum(FMOD_SOUND_FORMAT_NONE));
    rb_define_const(mod, "PCM8", rb_int2inum(FMOD_SOUND_FORMAT_PCM8));
    rb_define_const(mod, "PCM16", rb_int2inum(FMOD_SOUND_FORMAT_PCM16));
    rb_define_const(mod, "PCM24", rb_int2inum(FMOD_SOUND_FORMAT_PCM24));
    rb_define_const(mod, "PCM32", rb_int2inum(FMOD_SOUND_FORMAT_PCM32));
    rb_define_const(mod, "PCMFLOAT", rb_int2inum(FMOD_SOUND_FORMAT_PCMFLOAT));
    rb_define_const(mod, "BITSTREAM", rb_int2inum(FMOD_SOUND_FORMAT_BITSTREAM));
    rb_define_const(mod, "MAX", rb_int2inum(FMOD_SOUND_FORMAT_MAX));
    // OPENSTATE
    mod = rb_define_module_under(rb_mFmod, "OPENSTATE");
    rb_define_const(mod, "READY", rb_int2inum(FMOD_OPENSTATE_READY));
    rb_define_const(mod, "LOADING", rb_int2inum(FMOD_OPENSTATE_LOADING));
    rb_define_const(mod, "ERROR", rb_int2inum(FMOD_OPENSTATE_ERROR));
    rb_define_const(mod, "CONNECTING", rb_int2inum(FMOD_OPENSTATE_CONNECTING));
    rb_define_const(mod, "BUFFERING", rb_int2inum(FMOD_OPENSTATE_BUFFERING));
    rb_define_const(mod, "SEEKING", rb_int2inum(FMOD_OPENSTATE_SEEKING));
    rb_define_const(mod, "PLAYING", rb_int2inum(FMOD_OPENSTATE_PLAYING));
    rb_define_const(mod, "SETPOSITION", rb_int2inum(FMOD_OPENSTATE_SETPOSITION));
    rb_define_const(mod, "MAX", rb_int2inum(FMOD_OPENSTATE_MAX));
    // TAGTYPE
    mod = rb_define_module_under(rb_mFmod, "TAGTYPE");
    rb_define_const(mod, "UNKNOWN", rb_int2inum(FMOD_TAGTYPE_UNKNOWN));
    rb_define_const(mod, "ID3V1", rb_int2inum(FMOD_TAGTYPE_ID3V1));
    rb_define_const(mod, "ID3V2", rb_int2inum(FMOD_TAGTYPE_ID3V2));
    rb_define_const(mod, "VORBISCOMMENT", rb_int2inum(FMOD_TAGTYPE_VORBISCOMMENT));
    rb_define_const(mod, "SHOUTCAST", rb_int2inum(FMOD_TAGTYPE_SHOUTCAST));
    rb_define_const(mod, "ICECAST", rb_int2inum(FMOD_TAGTYPE_ICECAST));
    rb_define_const(mod, "ASF", rb_int2inum(FMOD_TAGTYPE_ASF));
    rb_define_const(mod, "MIDI", rb_int2inum(FMOD_TAGTYPE_MIDI));
    rb_define_const(mod, "PLAYLIST", rb_int2inum(FMOD_TAGTYPE_PLAYLIST));
    rb_define_const(mod, "FMOD", rb_int2inum(FMOD_TAGTYPE_FMOD));
    rb_define_const(mod, "USER", rb_int2inum(FMOD_TAGTYPE_USER));
    rb_define_const(mod, "MAX", rb_int2inum(FMOD_TAGTYPE_MAX));
    // TAGDATATYPE
    mod = rb_define_module_under(rb_mFmod, "TAGDATATYPE");
    rb_define_const(mod, "BINARY", rb_int2inum(FMOD_TAGDATATYPE_BINARY));
    rb_define_const(mod, "INT", rb_int2inum(FMOD_TAGDATATYPE_INT));
    rb_define_const(mod, "FLOAT", rb_int2inum(FMOD_TAGDATATYPE_FLOAT));
    rb_define_const(mod, "STRING", rb_int2inum(FMOD_TAGDATATYPE_STRING));
    rb_define_const(mod, "STRING_UTF16", rb_int2inum(FMOD_TAGDATATYPE_STRING_UTF16));
    rb_define_const(mod, "STRING_UTF16BE", rb_int2inum(FMOD_TAGDATATYPE_STRING_UTF16BE));
    rb_define_const(mod, "STRING_UTF8", rb_int2inum(FMOD_TAGDATATYPE_STRING_UTF8));
    rb_define_const(mod, "MAX", rb_int2inum(FMOD_TAGDATATYPE_MAX));
    // ERROR
    mod = rb_define_module_under(rb_mFmod, "ERR");
    rb_define_const(mod, "BADCOMMAND", rb_int2inum(FMOD_ERR_BADCOMMAND));
    rb_define_const(mod, "CHANNEL_ALLOC", rb_int2inum(FMOD_ERR_CHANNEL_ALLOC));
    rb_define_const(mod, "CHANNEL_STOLEN", rb_int2inum(FMOD_ERR_CHANNEL_STOLEN));
    rb_define_const(mod, "DMA", rb_int2inum(FMOD_ERR_DMA));
    rb_define_const(mod, "DSP_CONNECTION", rb_int2inum(FMOD_ERR_DSP_CONNECTION));
    rb_define_const(mod, "DSP_DONTPROCESS", rb_int2inum(FMOD_ERR_DSP_DONTPROCESS));
    rb_define_const(mod, "DSP_FORMAT", rb_int2inum(FMOD_ERR_DSP_FORMAT));
    rb_define_const(mod, "DSP_INUSE", rb_int2inum(FMOD_ERR_DSP_INUSE));
    rb_define_const(mod, "DSP_NOTFOUND", rb_int2inum(FMOD_ERR_DSP_NOTFOUND));
    rb_define_const(mod, "DSP_RESERVED", rb_int2inum(FMOD_ERR_DSP_RESERVED));
    rb_define_const(mod, "DSP_SILENCE", rb_int2inum(FMOD_ERR_DSP_SILENCE));
    rb_define_const(mod, "DSP_TYPE", rb_int2inum(FMOD_ERR_DSP_TYPE));
    rb_define_const(mod, "FILE_BAD", rb_int2inum(FMOD_ERR_FILE_BAD));
    rb_define_const(mod, "FILE_COULDNOTSEEK", rb_int2inum(FMOD_ERR_FILE_COULDNOTSEEK));
    rb_define_const(mod, "FILE_DISKEJECTED", rb_int2inum(FMOD_ERR_FILE_DISKEJECTED));
    rb_define_const(mod, "FILE_EOF", rb_int2inum(FMOD_ERR_FILE_EOF));
    rb_define_const(mod, "FILE_ENDOFDATA", rb_int2inum(FMOD_ERR_FILE_ENDOFDATA));
    rb_define_const(mod, "FILE_NOTFOUND", rb_int2inum(FMOD_ERR_FILE_NOTFOUND));
    rb_define_const(mod, "FORMAT", rb_int2inum(FMOD_ERR_FORMAT));
    rb_define_const(mod, "HEADER_MISMATCH", rb_int2inum(FMOD_ERR_HEADER_MISMATCH));
    rb_define_const(mod, "HTTP", rb_int2inum(FMOD_ERR_HTTP));
    rb_define_const(mod, "HTTP_ACCESS", rb_int2inum(FMOD_ERR_HTTP_ACCESS));
    rb_define_const(mod, "HTTP_PROXY_AUTH", rb_int2inum(FMOD_ERR_HTTP_PROXY_AUTH));
    rb_define_const(mod, "HTTP_SERVER_ERROR", rb_int2inum(FMOD_ERR_HTTP_SERVER_ERROR));
    rb_define_const(mod, "HTTP_TIMEOUT", rb_int2inum(FMOD_ERR_HTTP_TIMEOUT));
    rb_define_const(mod, "INITIALIZATION", rb_int2inum(FMOD_ERR_INITIALIZATION));
    rb_define_const(mod, "INITIALIZED", rb_int2inum(FMOD_ERR_INITIALIZED));
    rb_define_const(mod, "INTERNAL", rb_int2inum(FMOD_ERR_INTERNAL));
    rb_define_const(mod, "INVALID_FLOAT", rb_int2inum(FMOD_ERR_INVALID_FLOAT));
    rb_define_const(mod, "INVALID_HANDLE", rb_int2inum(FMOD_ERR_INVALID_HANDLE));
    rb_define_const(mod, "INVALID_PARAM", rb_int2inum(FMOD_ERR_INVALID_PARAM));
    rb_define_const(mod, "INVALID_POSITION", rb_int2inum(FMOD_ERR_INVALID_POSITION));
    rb_define_const(mod, "INVALID_SPEAKER", rb_int2inum(FMOD_ERR_INVALID_SPEAKER));
    rb_define_const(mod, "INVALID_SYNCPOINT", rb_int2inum(FMOD_ERR_INVALID_SYNCPOINT));
    rb_define_const(mod, "INVALID_THREAD", rb_int2inum(FMOD_ERR_INVALID_THREAD));
    rb_define_const(mod, "INVALID_VECTOR", rb_int2inum(FMOD_ERR_INVALID_VECTOR));
    rb_define_const(mod, "MAXAUDIBLE", rb_int2inum(FMOD_ERR_MAXAUDIBLE));
    rb_define_const(mod, "MEMORY", rb_int2inum(FMOD_ERR_MEMORY));
    rb_define_const(mod, "MEMORY_CANTPOINT", rb_int2inum(FMOD_ERR_MEMORY_CANTPOINT));
    rb_define_const(mod, "NEEDS3D", rb_int2inum(FMOD_ERR_NEEDS3D));
    rb_define_const(mod, "NEEDSHARDWARE", rb_int2inum(FMOD_ERR_NEEDSHARDWARE));
    rb_define_const(mod, "NET_CONNECT", rb_int2inum(FMOD_ERR_NET_CONNECT));
    rb_define_const(mod, "NET_SOCKET_ERROR", rb_int2inum(FMOD_ERR_NET_SOCKET_ERROR));
    rb_define_const(mod, "NET_URL", rb_int2inum(FMOD_ERR_NET_URL));
    rb_define_const(mod, "NET_WOULD_BLOCK", rb_int2inum(FMOD_ERR_NET_WOULD_BLOCK));
    rb_define_const(mod, "NOTREADY", rb_int2inum(FMOD_ERR_NOTREADY));
    rb_define_const(mod, "OUTPUT_ALLOCATED", rb_int2inum(FMOD_ERR_OUTPUT_ALLOCATED));
    rb_define_const(mod, "OUTPUT_CREATEBUFFER", rb_int2inum(FMOD_ERR_OUTPUT_CREATEBUFFER));
    rb_define_const(mod, "OUTPUT_DRIVERCALL", rb_int2inum(FMOD_ERR_OUTPUT_DRIVERCALL));
    rb_define_const(mod, "OUTPUT_FORMAT", rb_int2inum(FMOD_ERR_OUTPUT_FORMAT));
    rb_define_const(mod, "OUTPUT_INIT", rb_int2inum(FMOD_ERR_OUTPUT_INIT));
    rb_define_const(mod, "OUTPUT_NODRIVERS", rb_int2inum(FMOD_ERR_OUTPUT_NODRIVERS));
    rb_define_const(mod, "PLUGIN", rb_int2inum(FMOD_ERR_PLUGIN));
    rb_define_const(mod, "PLUGIN_MISSING", rb_int2inum(FMOD_ERR_PLUGIN_MISSING));
    rb_define_const(mod, "PLUGIN_RESOURCE", rb_int2inum(FMOD_ERR_PLUGIN_RESOURCE));
    rb_define_const(mod, "PLUGIN_VERSION", rb_int2inum(FMOD_ERR_PLUGIN_VERSION));
    rb_define_const(mod, "RECORD", rb_int2inum(FMOD_ERR_RECORD));
    rb_define_const(mod, "REVERB_CHANNELGROUP", rb_int2inum(FMOD_ERR_REVERB_CHANNELGROUP));
    rb_define_const(mod, "REVERB_INSTANCE", rb_int2inum(FMOD_ERR_REVERB_INSTANCE));
    rb_define_const(mod, "SUBSOUNDS", rb_int2inum(FMOD_ERR_SUBSOUNDS));
    rb_define_const(mod, "SUBSOUND_ALLOCATED", rb_int2inum(FMOD_ERR_SUBSOUND_ALLOCATED));
    rb_define_const(mod, "SUBSOUND_CANTMOVE", rb_int2inum(FMOD_ERR_SUBSOUND_CANTMOVE));
    rb_define_const(mod, "TAGNOTFOUND", rb_int2inum(FMOD_ERR_TAGNOTFOUND));
    rb_define_const(mod, "TOOMANYCHANNELS", rb_int2inum(FMOD_ERR_TOOMANYCHANNELS));
    rb_define_const(mod, "TRUNCATED", rb_int2inum(FMOD_ERR_TRUNCATED));
    rb_define_const(mod, "UNIMPLEMENTED", rb_int2inum(FMOD_ERR_UNIMPLEMENTED));
    rb_define_const(mod, "UNINITIALIZED", rb_int2inum(FMOD_ERR_UNINITIALIZED));
    rb_define_const(mod, "UNSUPPORTED", rb_int2inum(FMOD_ERR_UNSUPPORTED));
    rb_define_const(mod, "VERSION", rb_int2inum(FMOD_ERR_VERSION));
    rb_define_const(mod, "EVENT_ALREADY_LOADED", rb_int2inum(FMOD_ERR_EVENT_ALREADY_LOADED));
    rb_define_const(mod, "EVENT_LIVEUPDATE_BUSY", rb_int2inum(FMOD_ERR_EVENT_LIVEUPDATE_BUSY));
    rb_define_const(mod, "EVENT_LIVEUPDATE_MISMATCH", rb_int2inum(FMOD_ERR_EVENT_LIVEUPDATE_MISMATCH));
    rb_define_const(mod, "EVENT_LIVEUPDATE_TIMEOUT", rb_int2inum(FMOD_ERR_EVENT_LIVEUPDATE_TIMEOUT));
    rb_define_const(mod, "EVENT_NOTFOUND", rb_int2inum(FMOD_ERR_EVENT_NOTFOUND));
    rb_define_const(mod, "STUDIO_UNINITIALIZED", rb_int2inum(FMOD_ERR_STUDIO_UNINITIALIZED));
    rb_define_const(mod, "STUDIO_NOT_LOADED", rb_int2inum(FMOD_ERR_STUDIO_NOT_LOADED));
    rb_define_const(mod, "INVALID_STRING", rb_int2inum(FMOD_ERR_INVALID_STRING));
    rb_define_const(mod, "ALREADY_LOCKED", rb_int2inum(FMOD_ERR_ALREADY_LOCKED));
    rb_define_const(mod, "NOT_LOCKED", rb_int2inum(FMOD_ERR_NOT_LOCKED));
    rb_define_const(mod, "RECORD_DISCONNECTED", rb_int2inum(FMOD_ERR_RECORD_DISCONNECTED));
    rb_define_const(mod, "TOOMANYSAMPLES", rb_int2inum(FMOD_ERR_TOOMANYSAMPLES));
}
