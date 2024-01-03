require 'mkmf'
ext_name = 'RubyFmod'

if Dir.exist?('/opt/homebrew')
    $INCFLAGS << " -I'/opt/homebrew/include'"
    $LDFLAGS << " -L'/opt/homebrew/lib'"
end

have_library('fmod')

create_makefile(ext_name)
