require 'mkmf'
ext_name = 'Ruby-Fmod'
have_library('fmod')

create_makefile(ext_name)
