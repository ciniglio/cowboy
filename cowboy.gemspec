# -*- encoding: utf-8 -*-
require File.expand_path('../lib/cowboy/version', __FILE__)

Gem::Specification.new do |gem|
  gem.authors       = ["Alejandro Ciniglio"]
  gem.email         = ["mail@alejandrociniglio.com"]
  gem.description   = %q{Cowboy is a wrapper for fftw
                         (C fourier transform library)}
  gem.summary       = %q{Cowboy allows you to access
                         blazing fast FFTs from within Ruby}
  gem.homepage      = "https://github.com/ciniglio/cowboy"

  gem.files         = `git ls-files`.split($\)
  gem.executables   = gem.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.name          = "cowboy"
  gem.require_paths = ["lib"]
  gem.version       = Cowboy::VERSION

  gem.extensions    = ["ext/cowboy/extconf.rb"]
end
