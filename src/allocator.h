#pragma once

#include <algorithm>
#include <numeric>
#include <array>
#include <map>


namespace Alloc
{
  template<typename T, std::size_t N>
  class Pool
  {
  private:
    using pool = std::array<T, N>;

    bool firstAllocate = true;

    std::map<pool*, size_t> memory;


  public:

    ~Pool()
    {
      for ( auto& p : memory )
      {
        auto ptr = p.first;
        //cout << ptr << endl;
        delete p.first;
       
      }
      //memory.clear();
      //::operator delete[]( start );
    }

    Pool()
    {

    }
    Pool( const Pool& ) = delete;
    Pool( Pool&& ) = delete;
    Pool& operator = ( const Pool& ) = delete;
    Pool& operator = ( Pool&& ) = delete;

    T* alloc(const std::size_t& count )
    {
      T* start;

      if ( firstAllocate )
      {
        firstAllocate = false;

        auto ptr = new pool();

        memory.emplace( std::make_pair( ptr, count ) );

        auto& arr = *ptr;

        start = &arr[ 0 ];

        return start;
      }

      for ( auto& p : memory )
      {
        if ( p.second + count > N )
          throw std::bad_alloc();

        auto& arr = *p.first;

        start = &arr[ 0 ] + p.second;

        p.second += count;

        cout << "p.second:" << p.second << endl;
      }

      return start;
    }

    void dealloc( T* & ptr, const size_t& n )
    {
      auto arr = std::prev( memory.upper_bound( reinterpret_cast< pool* >( ptr ) ) );
      ::operator delete( arr->first, n );
    }

  };


  template<typename T, std::size_t N>
  class Allocator
  {
  private:

    Pool<T,N>* allocatorPool;

    //Pool<T, N>* allocatorPooltypeOther;

  public:

    using value_type = T;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;

    template< typename U >
    struct rebind
    {
      typedef Allocator<U, N> other;
    };

    Allocator():allocatorPool(new  Pool<T, N>() )
    {

    }
    Allocator( const Allocator& ) = default;
    Allocator& operator = ( const Allocator& other ) = default;
    Allocator( Allocator&& ) = delete;
    Allocator& operator = ( Allocator&& ) = delete;

    template <typename U, std::size_t S>
    Allocator( const Allocator<U, S>& typeOther)//:allocatorPool( typeOther.allocatorPool )//:allocatorPooltypeOther( new  Pool<T, N>() )
    {
      //typeOther.allocate( 1 );//allocate( 1 );
    }

    ~Allocator()
    {
      delete allocatorPool;
    }

    //
    pointer allocate( size_type count )
    {
      //if ( allocatorPooltypeOther )
      //{
      //  allocatorPooltypeOther->alloc( count );
      //}
      return allocatorPool->alloc( count );
    }

    //
    void deallocate( T* ptr, size_type n )
    {
      //if( allocatorPooltypeOther )
      //{
      //  allocatorPooltypeOther->dealloc( ptr );
      //}
      allocatorPool->dealloc( ptr, n );

    }
  };

  // Analogous to std::allocator<void>, as defined in ISO C++ Standard, Section 20.4.1
  //template<size_t N>
  //class Allocator<void, N>
  //{
  //public:
  //  typedef void* pointer;
  //  typedef const void* const_pointer;
  //  typedef void value_type;
  //  template<typename U>
  //  struct rebind
  //  {
  //    typedef Allocator<U, N> other;
  //  };
  //};

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

}

//#include "allocator.hpp"
