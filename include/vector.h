#pragma once

#include "allocator.h"
#include <memory>
#include <type_traits>

namespace VectorRealize 
{
  // Реализация класса вектора
  template<typename T, class Allocator = std::allocator<T>>
  class Vector final
  {
  private:

    T * arr = nullptr;    //  указатель на массив
    size_t sz = 0;        //  количество элементов
    size_t cap = 0;       //  количество выделенной памяти
    Allocator alloc;      //  аллокатор
  
    using AllocTraits = std::allocator_traits<Allocator>;

  public:

    Vector();

    ~Vector();

    void reserve( size_t n );  

    void push_back( const T& value );

    void pop_back();

    T& operator[]( size_t );

    T& at( size_t t ); 

  };
}

#include "vector.hpp"
