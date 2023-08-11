#include "allocator.h"

using namespace Alloc;

template <typename T, size_t N>
Allocator<T, N>::Allocator()
{
#ifdef DEBUG_PRINT
  std::cout << "Allocator()" << std::endl;
#endif
}

template <typename T, size_t N>
Allocator<T, N>::Allocator( const Allocator& )
{
#ifdef DEBUG_PRINT
  std::cout << "Allocator(const Allocator&)" << std::endl;
#endif
}

template <typename T, size_t N>
template <typename U, size_t S>
Allocator<T, N>::Allocator( const Allocator<U, S>& )
{
#ifdef DEBUG_PRINT
  std::cout << " Allocator( const Allocator<U, S>& ) " << std::endl;
#endif
}

template <typename T, size_t N>
Allocator<T, N>::~Allocator()
{
#ifdef DEBUG_PRINT
  std::cout << "~Allocator()" << std::endl;
#endif
}

template <typename T, size_t N>
T* Pool<T, N>::Allocate( size_t& n )
{
  {
    for ( auto& chunk : allocatorPool )
    {
      auto& ar = *chunk.first;
      if ( chunk.second + n <= N )
      {
        T* ptr = &ar[ 0 ] + chunk.second;
        chunk.second += n;
#ifdef DEBUG_PRINT
        std::cout << "allocated: " << ptr << std::endl;
        std::cout << "used: " << chunk.second << std::endl;
#endif
        return ptr;
      }
      else
      {
        throw std::runtime_error( "Memory is filled" );
      }
    }
    return AppendNewChunk( n );
  }
}

template <typename T, size_t N>
void Pool<T, N>::Deallocate( T* p ) noexcept
{
#ifdef DEBUG_PRINT
  std::cout << "deallocate: " << p << std::endl;
#endif
  auto chunk = std::prev( allocatorPool.upper_bound( reinterpret_cast< pool* >( p ) ) );

#ifdef DEBUG_PRINT
  std::cout << "deallocate chunk: " << chunk->first << std::endl;
#endif

  if ( --chunk->second == 0 )
  {
    delete chunk->first;
    allocatorPool.erase( chunk );
  }
}

template <typename T, size_t N>
T* Pool<T, N>::AppendNewChunk( size_t n ) noexcept
{
  auto newChunk = new pool();
  allocatorPool.emplace( std::make_pair( newChunk, n ) );
  auto& ar = *newChunk;
  auto ptr = &ar[ 0 ];
#ifdef DEBUG_PRINT
  std::cout << "allocated new: " << ptr << std::endl;
#endif
  return ptr;
}

template <typename T, size_t N>
Pool<T, N>::Pool()
{
#ifdef DEBUG_PRINT
  std::cout << "Pool()" << std::endl;
#endif
}

template <typename T, size_t N>
Pool<T, N>::~Pool()
{
#ifdef DEBUG_PRINT
  std::cout << "~Pool()" << std::endl;
#endif
  for ( auto& chunk : allocatorPool )
  {
    delete chunk->first;
  }
}
