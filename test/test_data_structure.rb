require_relative './test_helper.rb'

class TestDataStructure < Test::Unit::TestCase
  def test_init
    a = Cowboy::CowboyData.new("a", 2)
    assert_not_nil a
  end

  def test_access
    a = Cowboy::CowboyData.new("a", 2)
    assert_equal a.data, "a"
    assert_equal a.size, 2
  end

  def test_no_size
    a = Cowboy::CowboyData.new("a")
    assert_equal a.data, "a"
    assert_equal a.size, nil
    b = Cowboy::CowboyData.new((0...15).to_a)
    assert_equal b.size, -1
  end
end
