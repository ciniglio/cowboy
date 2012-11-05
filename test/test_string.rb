require_relative './test_helper.rb'
require 'cowboy'
require 'test/unit'

class TestString < Test::Unit::TestCase
  def test_ffd_1d_4
    a = [1,2,3,4].pack('D*')
    c = Cowboy::fft_1d a
    assert_equal c[0], 10
    assert_equal c[1], Complex(-2,2)
    assert_equal c[2], Complex(-2,0)
    assert_equal c[3], Complex(-2,-2)
  end

  def test_ffd_1d_8
    a = [1,2,1,2,1,2,1,2].pack('D*')
    c = Cowboy::fft_1d a
    assert_equal c[0], 12
    assert_equal c[1], 0
    assert_equal c[4], -4
  end
end
