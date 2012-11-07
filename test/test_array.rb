require_relative './test_helper.rb'

require 'cowboy'
require 'test/unit'

class TestArray < Test::Unit::TestCase
  def test_version
    assert_not_nil Cowboy::VERSION
  end

  def test_ffd_1d_4
    a = Cowboy::CowboyData.new [1,2,3,4]
    c = Cowboy::fft_1d a
    assert_equal c[0], 10
    assert_equal c[1], Complex(-2,2)
    assert_equal c[2], Complex(-2,0)
    assert_equal c.size, 3 #n/2+1
  end

  def test_ffd_1d_8
    a = Cowboy::CowboyData.new [1,2,1,2,1,2,1,2]
    c = Cowboy::fft_1d a
    assert_equal c[0], 12
    assert_equal c[1], 0
    assert_equal c[4], -4
  end
end
