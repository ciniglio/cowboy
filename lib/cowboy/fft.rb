module Cowboy
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
