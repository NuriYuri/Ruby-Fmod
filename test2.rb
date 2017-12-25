require "./lib/RubyFmod.so"

#> Init System
#FMOD::System.init(32, FMOD::INIT::NORMAL)
begin
  @sound = FMOD::System.createStream("DIF.mp3", FMOD::MODE::LOOP_NORMAL | FMOD::MODE::FMOD_2D, nil)
rescue FMOD::Error
  p $!.hr
  puts("Error (" + $!.class.to_s + ") : " + $!.message)
end
