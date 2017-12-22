ext_name = 'Ruby-Fmod'
require 'rake/extensiontask'

spec = Gem::Specification.new do |s|
  s.name = ext_name
  s.platform = Gem::Platform::RUBY
  s.version = '0.1.0'
  s.summary = "Ruby-Fmod is a binding of Fmod inside Ruby"
  s.description = "Ruby-Fmod uses Fmod to work properly"
  s.authors = ["Nuri Yuri"]
  #s.homepage = "https://psdk.pokemonworkshop.com/litergss"
  s.extensions = FileList["ext/Ruby-Fmod/extconf.rb"]
  s.files = FileList["ext/Ruby-Fmod/*.h", "ext/Ruby-Fmod/*.cpp"]
  s.metadata    = { "source_code_uri" => "https://github.com/NuriYuri/Ruby-Fmod" }
end

Gem::PackageTask.new(spec) do |pkg|
end

Rake::ExtensionTask.new(ext_name, spec)  
