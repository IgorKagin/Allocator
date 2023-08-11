#include "gtest/gtest.h"
#include "vector.h"
using namespace Alloc;

TEST(Test1, Alloc)
{
  struct a
  {
    char b = 'a';
  }first;

  std::vector<a, Allocator<a>> ownAlloc{};
  std::vector<a> stdAlloc{};

  ownAlloc.push_back( first );
  stdAlloc.push_back( first );

  EXPECT_EQ( ownAlloc.at(0).b, stdAlloc.at(0).b );
}

TEST( Test2, AllocContainer )
{
  Vector<double, Allocator<double>> owVector;
  std::vector<double> stdVector{};

  const constexpr uint8_t count = 10;
  const constexpr double value = 3.43;
  for ( uint8_t i = 0; i < count; ++i )
  {
    owVector.push_back( value + i );
    stdVector.push_back( value + i );

    auto resOwn = owVector.at( i );
    auto resStd = stdVector.at( i );

    ASSERT_EQ( resOwn, resStd );
  }
}
