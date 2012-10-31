class Cowboy::Hamming
  def initialize(n)
    @n = n
    create_kernel
  end

  def convolve(arr)
    raise "Array smaller than window size" if arr.size < @n
    a = []
    for i in (0...(arr.size - (@n - 1)))
      n = 0.0
      for j in (0...@n)
        c = @kernel[j] * arr[i+j]
        n += c
      end
      a << n
    end
    return a
  end

  private
  def create_kernel
    a = []
    for j in (0...@n)
      c = 0.54 - 0.46 * Math.cos((2*Math::PI * j)/(@n - 1))
      a << c
    end
    @kernel = a
  end
end
