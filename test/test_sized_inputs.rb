require_relative './test_helper.rb'

class TestSizedInputs < Test::Unit::TestCase
  def test_doubles
    a = Cowboy::CowboyData.new [1,2,3,4].pack('D*'), 8
    c = Cowboy::fft_1d a
    assert_equal c.size, 3
    assert_equal c[0], 10
    assert_equal c[1], Complex(-2,2)
    assert_equal c[2], Complex(-2,0)
  end

  def test_long
    a = Cowboy::CowboyData.new [1,2,3,4].pack('F*'), 4
    c = Cowboy::fft_1d a
    assert_equal c.size, 3
    assert_equal c[0], 10
    assert_equal c[1], Complex(-2,2)
    assert_equal c[2], Complex(-2,0)
  end

  def test_short
    a = Cowboy::CowboyData.new [1,2,3,4].pack('S*'), 2
    c = Cowboy::fft_1d a
    assert_equal c.size, 3
    assert_equal c[0], 10
    assert_equal c[1], Complex(-2,2)
    assert_equal c[2], Complex(-2,0)
  end

  def test_char
    a = Cowboy::CowboyData.new [1,2,3,4].pack('C*'), 1
    c = Cowboy::fft_1d a
    assert_equal c.size, 3
    assert_equal c[0], 10
    assert_equal c[1], Complex(-2,2)
    assert_equal c[2], Complex(-2,0)
  end
end
