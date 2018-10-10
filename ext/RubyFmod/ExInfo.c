#include "Ruby-Fmod.h"

VALUE rb_cFmodExInfo = Qnil;

#define GET_EXINFO_SAFE \
    GET_EXINFO(self, exinfo) \
    if(exinfo == NULL) \
        rb_raise(rb_eFmodError, "CREATESOUNDEXINFO not created by Fmod");

#define GET_EXINFO(object, varname) \
    FMOD_CREATESOUNDEXINFO* varname; \
    Data_Get_Struct(object, FMOD_CREATESOUNDEXINFO, varname);

void rb_ExInfo_Free(void* data)
{
	if (data != NULL)
	{
		FMOD_CREATESOUNDEXINFO* exinfo = (FMOD_CREATESOUNDEXINFO*)(data);
		free(exinfo);
	}
}

VALUE rb_ExInfo_Alloc(VALUE klass)
{
	FMOD_CREATESOUNDEXINFO* exinfo = (FMOD_CREATESOUNDEXINFO*)malloc(sizeof(FMOD_CREATESOUNDEXINFO));
  memset(exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
	exinfo->cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	return Data_Wrap_Struct(klass, NULL, rb_ExInfo_Free, exinfo);
}

void Init_SoundEx()
{
	rb_cFmodExInfo = rb_define_class_under(rb_mFmod, "SoundExInfo", rb_cObject);
	rb_define_alloc_func(rb_cFmodExInfo, rb_ExInfo_Alloc);
	rb_define_method(rb_cFmodExInfo, "initialize", _rbf rb_ExInfo_Initialize, -1);
	rb_define_method(rb_cFmodExInfo, "initialize_copy", _rbf rb_ExInfo_initialize_copy, 1);
	// TODO rest !
}

VALUE rb_ExInfo_Initialize(int argc, VALUE *argv, VALUE self)
{
	GET_EXINFO_SAFE;
	if (argc > 0)
	{
		if(RTEST(argv[0]))
			exinfo->length = NUM2UINT(argv[0]);
		if (argc > 1)
		{
			if (RTEST(argv[1]))
				exinfo->fileoffset = NUM2UINT(argv[1]);
			if (argc > 2)
			{
				if (RTEST(argv[2]))
					exinfo->numchannels = NUM2INT(argv[2]);
				if (argc > 3)
				{
					if (RTEST(argv[3]))
						exinfo->defaultfrequency = NUM2INT(argv[3]);
					if (argc > 4)
					{
						if (RTEST(argv[4]))
							exinfo->format = (FMOD_SOUND_FORMAT)(NUM2INT(argv[4]));
						if (argc > 5)
						{
							if (RTEST(argv[5]))
								exinfo->decodebuffersize = NUM2UINT(argv[5]);
							if (argc > 6)
							{
								if (RTEST(argv[6]))
								{
									rb_check_type(argv[6], T_STRING);
									exinfo->dlsname = RSTRING_PTR(argv[6]);
								}
								if (argc > 7)
								{
									if (RTEST(argv[7]))
										exinfo->suggestedsoundtype = (FMOD_SOUND_TYPE)(NUM2INT(argv[7]));
									if (argc > 8)
									{
										if (RTEST(argv[8]))
											exinfo->filebuffersize = NUM2INT(argv[8]);
										if (argc > 9)
										{
											if (RTEST(argv[9]))
												exinfo->channelorder = (FMOD_CHANNELORDER)(NUM2INT(argv[9]));
											if (argc > 10)
											{
												if (RTEST(argv[10]))
													exinfo->channelmask = NUM2INT(argv[10]);
												if (argc > 11)
												{
													if (RTEST(argv[11]))
														exinfo->initialseekposition = NUM2UINT(argv[11]);
													if (argc > 12)
													{
														if (RTEST(argv[12]))
															exinfo->initialseekpostype = NUM2INT(argv[12]);
														if (argc > 13)
														{
															if (RTEST(argv[13]))
																exinfo->audioqueuepolicy = NUM2UINT(argv[13]);
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return self;
}

VALUE rb_ExInfo_initialize_copy(VALUE self, VALUE other)
{
	GET_EXINFO_SAFE
	if (rb_obj_is_kind_of(other, rb_cFmodExInfo) == Qtrue)
	{
		FMOD_CREATESOUNDEXINFO* exinfo2;
		Data_Get_Struct(other, FMOD_CREATESOUNDEXINFO, exinfo2);
		if(exinfo2)
			memcpy(exinfo, exinfo2, sizeof(FMOD_CREATESOUNDEXINFO));
	}
	return self;
}