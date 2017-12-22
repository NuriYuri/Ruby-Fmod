#ifndef RF_RUBY_FMOD_H
#define RF_RUBY_FMOD_H
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "ruby.h"
#include <fmod.hpp>

#define _rbf (VALUE (*)(...))

extern VALUE rb_mFmod;
extern VALUE rb_mFmodSystem;
extern VALUE rb_cFmodSound;
extern VALUE rb_cFmodChannel;

inline long normalize_long(long value, long min, long max) {
    if(value < min)
        return min;
    if(value > max)
        return max;
    return value;
}
inline double normalize_double(double value, double min, double max) {
    if(value < min)
        return min;
    if(value > max)
        return max;
    return value;
}

#endif
