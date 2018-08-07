#ifndef L_EXINFO_HEADER
#define L_EXINFO_HEADER
VALUE rb_ExInfo_Initialize(int argc, VALUE *argv, VALUE self);
VALUE rb_ExInfo_initialize_copy(VALUE self, VALUE other);
#endif /* L_EXINFO_HEADER */