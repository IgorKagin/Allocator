#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "vector.h"
#include <map>
#include <cstddef>


using std::cout;
using std::cin;
using std::endl;
using namespace Alloc;


template <typename Map>
void Print( const Map& map )
{
  for ( const auto& pair : map )
  {
    std::cout << pair.first << " " << pair.second << std::endl;
  }
}

long long fact( int& n )
{
  long long factorial = 1;
  for ( int i = 1; i <= n; ++i )
  {
    factorial *= i;
  }
  return factorial;
}

void MapWithStandardAllocator()
{
  using Map = std::map<int, long long>;

  Map map;

  for ( int i = 0; i < 10; ++i )
  {
    map[ i ] = fact( i );
  }

  Print( map );
}

void MapWithCustomAllocator()
{
  const constexpr size_t count = 11;
  using Map = std::map<int, long long, std::less<int>, Allocator<long long, count>>;

  Map map;

  for ( int i = 0; i < 10; ++i )
  {
    map[ i ] = fact( i );
  }

  Print( map );
}

void CustomVectorWithStandardAllocator()
{
  Vector<int> vector;

  for ( uint16_t i = 0; i < 10; ++i )
  {
    vector.push_back( i );
  }
}

void CustomVectorWithCustomAllocator()
{
  Vector<int, Allocator<int>> vector;

  for ( uint16_t i = 0; i < 10; ++i )
  {
    vector.push_back( i );
    cout<< vector.at( i ) << endl;
  }

}
int main(int, char **)
{
  try
  {
    // Реализация std::map с стандартным аллокатором
    cout << "////////////////MapWithStandardAllocator()////////////////" << endl;
    MapWithStandardAllocator();

    // Реализация std::map с собственным аллокатором
    cout << "////////////////MapWithCustomAllocator()////////////////" << endl;
    MapWithCustomAllocator();

    // Реализация вектора с стандартным аллокатором
    cout << "////////////////CustomVectorWithStandardAllocator()////////////////" << endl;
    CustomVectorWithStandardAllocator();

    // Реализация вектора с собственным аллокатором
    cout << "////////////////CustomVectorWithCustomAllocator()////////////////" << endl;
    CustomVectorWithCustomAllocator();
  }
  catch ( const std::exception& e )
  {
    cout << e.what() << endl;
  }

  return 0;
}
