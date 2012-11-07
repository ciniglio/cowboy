require_relative './test_helper.rb'

class TestFloatInputs < Test::Unit::TestCase
  def test_doubles_pos
    a = Cowboy::CowboyData.new [1.5,2.5,3.5,4.5].pack('D*'), 8
    c = Cowboy::fft_1d a
    assert_equal c.size, 3
    assert_equal c[0], 12
    assert_equal c[1], Complex(-2,2)
    assert_equal c[2], Complex(-2,0)
  end

  def test_long_pos
    a = Cowboy::CowboyData.new [1.5,2.5,3.5,4.5].pack('F*'), 4
    c = Cowboy::fft_1d a
    assert_equal c.size, 3
    assert_equal c[0], 12
    assert_equal c[1], Complex(-2,2)
    assert_equal c[2], Complex(-2,0)
  end

  def test_doubles_mix
    a = Cowboy::CowboyData.new [-1.5,2.5,-3.5,4.5].pack('D*'), 8
    c = Cowboy::fft_1d a
    assert_equal c.size, 3
    assert_equal c[0], 2
    assert_equal c[1], Complex(2,2)
    assert_equal c[2], Complex(-12,0)
  end

  def test_long_mix
    a = Cowboy::CowboyData.new [-1.5,2.5,-3.5,4.5].pack('F*'), 4
    c = Cowboy::fft_1d a
    assert_equal c.size, 3
    assert_equal c[0], 2
    assert_equal c[1], Complex(2,2)
    assert_equal c[2], Complex(-12,0)
  end
end
