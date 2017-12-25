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

@sound = FMOD::System.createStream("DIF.mp3", FMOD::MODE::LOOP_NORMAL | FMOD::MODE::FMOD_2D, nil)
p @sound.getFormat, length = @sound.getLength(FMOD::TIMEUNIT::MS), @sound.getNumTags

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
