#include "vector.h"

using namespace VectorRealize;

  template<typename T, class Allocator>
  Vector<T, Allocator>::Vector()
  {
#ifdef DEBUG_PRINT
    cout << "Vector()" << endl;
#endif
  }

  template<typename T, class Allocator>
  Vector<T, Allocator>::~Vector()
  {
#ifdef DEBUG_PRINT
    cout << "~Vector()" << endl;
#endif

    size_t i = 0;
    while ( i < cap )
    {
      AllocTraits::destroy( alloc, arr + i);
      ++i;
    }

    if ( std::is_same_v<decltype( alloc ), std::allocator<T>> )
      AllocTraits::deallocate( alloc, arr, cap );
    else
    {
      size_t i = 0;
      while ( i < cap )
      {
        AllocTraits::deallocate( alloc, arr + i, 1 );
        ++i;
      }
    }

  }

  template<typename T, class Allocator>
  void Vector<T, Allocator>::reserve( size_t n )  
  {
#ifdef DEBUG_PRINT
    cout << "reserve()" << endl;
#endif
    if ( n <= cap ) 
    { 
      return; 
    }

    size_t i = 0;  
    T* newarr;
    try
    {
      newarr = AllocTraits::allocate( alloc, n );

      for ( ; i < sz; ++i )
      {
        AllocTraits::construct( alloc, newarr + i, arr[ i ] );
        AllocTraits::destroy( alloc, arr + i );
      }

      if ( std::is_same_v<decltype( alloc ), std::allocator<T>> )
      {
        AllocTraits::deallocate( alloc, arr, sz );
      }
    }

    catch ( const std::exception&e )
    {
      for ( size_t j = 0; j < i; ++j )
      {
        AllocTraits::destroy( alloc, newarr + j );
        AllocTraits::deallocate( alloc, newarr + j, n );
        if ( std::is_same_v<decltype( alloc ), std::allocator<T>> )
          break;
      }
      throw;
    }
    arr = newarr;
    cap = n;
  }

  template<typename T, class Allocator>
  void Vector<T, Allocator>::push_back( const T& value )
  {
    if ( cap == sz )
    {
      reserve( sz + 10 );
    }
    AllocTraits::construct( alloc, arr + sz, value );

    ++sz;
  }

  template<typename T, class Allocator>
  void Vector<T, Allocator>::pop_back()
  {
    --sz;
    AllocTraits::destroy( alloc, arr + sz - 1 )
  }

  template<typename T, class Allocator>
  T& Vector<T, Allocator>::operator[]( size_t i)
  {
    return arr[ i ]; 
  }

  template<typename T, class Allocator>
  T& Vector<T, Allocator>::at( size_t t ) 
  {
    if ( t >= sz )
    {
      throw std::out_of_range( "Out of range" );
    }
    return arr[ t ]; 
  }
