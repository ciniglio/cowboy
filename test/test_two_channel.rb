require_relative './test_helper.rb'

class TestTwoChannel < Test::Unit::TestCase
  def test_odd_input
    assert_raise Exception do
      a = Cowboy::CowboyData.new [1,2,3].pack('D*'), 8, 2
    end
  end

  def test_even_input
    assert_nothing_raised do
      a = Cowboy::CowboyData.new [1,2,3,4], nil, 2
    end
  end

  def test_output
    a = Cowboy::CowboyData.new [1,1,2,2,3,3,4,4].pack('D*'), 8, 2
    c = Cowboy::fft_1d a
    assert_equal c[0], 10
    assert_equal c[1], Complex(-2,2)
    assert_equal c[2], Complex(-2,0)
    assert_equal c.size, 3 #n/2+1
  end

  def test_output2
    a = Cowboy::CowboyData.new [1,1,2,2,3,3,4,4].pack('F*'), 4, 2
    c = Cowboy::fft_1d a
    assert_equal c[0], 10
    assert_equal c[1], Complex(-2,2)
    assert_equal c[2], Complex(-2,0)
    assert_equal c.size, 3 #n/2+1
  end

  def test_output3
    a = Cowboy::CowboyData.new [0,1,0,2,0,3,0,4].pack('S*'), 2, 2
    c = Cowboy::fft_1d a
    assert_not_equal c[0], 10
    assert_not_equal c[1], Complex(-2,2)
    assert_not_equal c[2], Complex(-2,0)
    assert_equal c.size, 3 #n/2+1
  end
end
