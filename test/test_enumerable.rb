require_relative './test_helper.rb'

class TestEnumerable < Test::Unit::TestCase
  def test_size
    a = (0...10000).to_a
    c = Cowboy::fft_1d a
    assert_equal c.size, a.size/2 + 1
  end

  def test_each
    a = (0...4).to_a
    c = Cowboy::fft_1d a
    assert_equal (c.respond_to? :each), true
    assert_block do
      c.each do |i|
        assert_not_nil i
      end
    end
  end

  def test_map
    a = (0...10).to_a
    c = Cowboy::fft_1d a
    assert_equal (c.respond_to? :map), true
  end
end
