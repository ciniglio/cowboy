module Cowboy
  class Frequencies
    attr_reader :dc, :unshifted, :freq

    def initialize(unshifted_array)
      @unshifted = unshifted_array
      @dc = unshifted_array[0].real
      n = unshifted_array.size
      @freq = []
      for i in (n/2...n)
        @freq << unshifted_array[i].abs
      end
      for i in (0...n/2)
        @freq << unshifted_array[i].abs
      end
    end

    def buckets(sample_rate=nil)
      return @buckets if @buckets
      sample_rate ||= @freq.size
      nyquist = sample_rate/2.0
      sum = 0
      a = []
      n = @freq.size
      for i in (0...n)
        a << -nyquist + sum
        sum += (2 * nyquist/n)
      end
      @buckets = a
      return a
    end
  end

  def Cowboy::fft(arr, w=Hamming, n=29)
    if !w.nil?
      window = w.new(n)
      input = window.convolve(arr)
      fft_1d(input)
    else
      fft_1d(arr)
    end
  end
end
