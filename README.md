# Cowboy

This is a Ruby wrapper for [FFTW3](http://fftw.org). It currently only
supports 1-dimension transforms, but I'll be adding support for
multiple dimensions soon.

## Installation

### Prerequisites

[FFTW3](http://fftw.org) is required. You can generally get it from
your OS's package manager (e.g. `sudo port install fftw3`).

### Gem installation

Add this line to your application's Gemfile:

    gem 'cowboy'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install cowboy

## Usage

After installing, you can call `Cowboy::fft_1d` with a 1d array of
real numbers. This will return an array of complex numbers. Note that
your input array will be blanked out.

### Windowing

`Cowboy::fft` will do some windowing before calling `fft_1d`. This
currently behaves somewhat unintelligently and discards points around
the end of the array (for window size N, it discards N/2 from the
beginning and N/2 from the end) to allow for a full window at every
point.

The default is to use a
[Hamming Window](http://en.wikipedia.org/wiki/Window_function#Hamming_window)
with a window size of 29. This is configurable as the second and third
arguments to `fft`. (e.g. `Cowboy::fft(my_array, my_windowing_func,
12)`)

### Shifting

`Cowboy::Frequencies` is a class that, initialized an array of complex
numbers (ideally the output of a call to `fft`), will shift them to
their correct order (e.g. `[-nyquist, +nyquist]`). There is also a
function `buckets` that will give you the frequency buckets in order.

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Added some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
