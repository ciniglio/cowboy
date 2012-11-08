require_relative './test_helper.rb'

class TestEnumerable < Test::Unit::TestCase
  def test_size
    a = Cowboy::CowboyData.new (0...10000).to_a
    c = Cowboy::fft_1d a
    assert_equal c.size, 5001
  end

  def test_each
    a = Cowboy::CowboyData.new (0...4).to_a
    c = Cowboy::fft_1d a
    assert_equal (c.respond_to? :each), true
    assert_block do
      c.each do |i|
        assert_not_nil i
      end
    end
  end

  def test_map
    a = Cowboy::CowboyData.new (0...10).to_a
    c = Cowboy::fft_1d a
    assert_equal (c.respond_to? :map), true
  end

  def test_range
    a = Cowboy::CowboyData.new (0...10000).to_a
    c = Cowboy::fft_1d a
    assert_equal c[0..1].size, 2
    assert_equal c[0..500].size, 501
    assert_equal c[0..1], [c[0],c[1]]
  end

  def test_neg_range
    a = Cowboy::CowboyData.new (0...10000).to_a
    c = Cowboy::fft_1d a
    assert_equal c[0..-1].size, c.size
    ar = []
    for i in c
      ar << i
    end
    assert_equal c[0..-1], ar
  end
end
