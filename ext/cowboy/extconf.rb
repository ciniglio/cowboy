require 'mkmf'
create_makefile('cowboy/cowboy')

LIBDIR = RbConfig::CONFIG['libdir']
INCLUDEDIR = RbConfig::CONFIG['includedir']

HEADER_DIRS = [
              '/opt/local/include',
              '/usr/local/include',
              INCLUDEDIR,
              '/usr/include',
]

LIB_DIRS = [
            '/opt/local/lib',
            '/usr/local/lib',
            LIBDIR,
            '/usr/lib',
]

dir_config('fftw', HEADER_DIRS, LIB_DIRS)

unless find_header('fftw3.h')
  abort "FFTw is missing, please install FFTw"
end

unless find_library('fftw3', "fftw_malloc")
  abort "FFTw is missing, please install FFTw"
end
