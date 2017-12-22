require 'mkmf'
ext_name = 'RubyFmod'
have_library('fmod')

create_makefile(ext_name)
