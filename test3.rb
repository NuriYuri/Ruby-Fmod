require "./lib/RubyFmod.so"

def cv_time(time)
  ms = time % 1000
  time /= 1000
  s = time % 60
  time /= 60
  m = time % 60
  return m, s, ms
end

#> Init System
FMOD::System.init(32, FMOD::INIT::NORMAL)

@sound = FMOD::System.createStream("ZDO.mp3", FMOD::MODE::LOOP_NORMAL | FMOD::MODE::FMOD_2D, nil)
length = @sound.getLength(FMOD::TIMEUNIT::MS)
nb_tags, updated = @sound.getNumTags

def print_tag(sound, tag, iname)
  data = sound.getTag(iname, 0)
  case data[1]
  when FMOD::TAGDATATYPE::STRING_UTF16
    value = data[2].force_encoding("UTF-16LE").encode("UTF-8")
  when FMOD::TAGDATATYPE::STRING_UTF16BE
    value = data[2].force_encoding("UTF-16BE").encode("UTF-8")
  else
    value = data[2].to_s
  end
  puts "#{tag} : #{value}"
rescue FMOD::Error
  if($!.hr == FMOD::ERR::TAGNOTFOUND)
    puts "#{tag} : Not found."
  else
    puts $!.message
  end
end
#CF : http://help.mp3tag.de/main_tags.html
puts "TAGS"
print_tag(@sound, "Title", "TIT2")
print_tag(@sound, "Artist", "TPE1")
print_tag(@sound, "Album", "TALB")
print_tag(@sound, "Year", "TYER")
print_tag(@sound, "Genre", "TCON")
print_tag(@sound, "Track", "TYER")
print_tag(@sound, "Comment", "COMM")

lm, ls, lms = cv_time(length)

@channel = FMOD::System.playSound(@sound) #or sound, false)
@channel.setLoopCount(0)
while @channel.isPlaying
  pos = @channel.getPosition(FMOD::TIMEUNIT::MS)
  pm, ps, pms = cv_time(pos)
  dec = (pos * 10)/length
  print(sprintf("\r%02d:%02d:%03d [%s%s] %02d:%02d:%03d", 
                pm, ps, pms, "=" * dec, " " * (10-dec),
                lm, ls, lms))
  FMOD::System.update
  sleep(0.01)
end
pos = @channel.getPosition(FMOD::TIMEUNIT::MS)
pm, ps, pms = cv_time(pos)
dec = (pos * 10)/length
print(sprintf("\r%02d:%02d:%03d [%s%s] %02d:%02d:%03d\n", 
              pm, ps, pms, "=" * dec, " " * (10-dec),
              lm, ls, lms))
@sound.release
FMOD::System.close
