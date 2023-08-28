#pragma once

#include <algorithm>
#include <numeric>
#include <array>
#include <map>
#include <assert.h>
#include <vector>

namespace Alloc
{
  const constexpr unsigned DefaultSize = 10;

  // Реализация класса пула памяти 
  template <typename T, size_t N = DefaultSize>
  class Pool
  {
  public:

    using pool = std::array<T, N>;

    static Pool& GetInstance()
    {
      if ( instance )
        return *instance;

      instance = new Pool();
      return *instance;
    }

    // Аллокация
    T* Allocate( size_t&  );

    // Деаллокация
    void Deallocate( T*, const size_t& ) noexcept;

  private:

    Pool();

    ~Pool();

    Pool( const Pool& ) = delete;
    Pool( Pool&& ) = delete;
    Pool& operator = ( const Pool& ) = delete;
    Pool& operator = ( Pool&& ) = delete;

    // Добавление нового массива в пул
    T* AppendNewChunk( size_t n ) noexcept;

    std::map<pool*, size_t> allocatorPool;  // пул 
    static Pool* instance;
  };

  template <typename T, size_t N>
  Pool<T, N>* Pool<T, N>::instance = nullptr;


  // Реализация класса аллокатора
  template <typename T, size_t N = DefaultSize>
  class Allocator
  {
    //static_assert( !std::is_same_v<T, void>, "Type of the allocator can not be void" );

  public:
    using value_type = T;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    template<typename U>
    struct rebind
    {
      typedef Allocator<U, N> other;
    };

    Allocator();

    Allocator( const Allocator& );

    template <typename U, size_t S>
    Allocator( const Allocator<U, S>& );

    ~Allocator();

    Allocator& operator = ( const Allocator& other ) = default;

    // Аллокация
    pointer allocate( size_type n )
    {
      return Pool<T, N>::GetInstance().Allocate( n );
    }

    // Деаллокация
    void deallocate( pointer p, size_type n )
    {
      Pool<T, N>::GetInstance().Deallocate( p, n );
    }
  };

  template<typename T, size_t N, typename U, size_t S>
  inline bool operator == ( const Allocator<T, N>&, const Allocator<U, S>& )
  {
    return true;
  }

  template<typename T, size_t N, typename U, size_t S>
  inline bool operator != ( const Allocator<T, N>&, const Allocator<U, S>& )
  {
    return false;
  }

  #include "allocator.hpp"
}
