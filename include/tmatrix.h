// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw std::out_of_range("Vector size should be greater than zero");
    if (sz < 0)
        throw "Vector size is negative";
    if (sz > MAX_VECTOR_SIZE)
        throw "Vector size is bigger than max vector size";
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    for (int i = 0; i < sz; i++)
        pMem[i] = 0;
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) 
  {
      sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = v.pMem;
      sz = v.sz;
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if(&v == this)
        return *this;
    sz = v.sz;
    delete[] pMem;
    pMem = new T[sz];
    for (int i = 0; i < sz; i++)
        pMem[i] = v.pMem[i];
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (&v == this)
        return *this;
     delete[] pMem;
     pMem = v.pMem;
     sz = v.sz;
     v.pMem = nullptr;
     v.sz = 0;
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if ((ind < 0) || (ind >= sz) || (ind >= MAX_VECTOR_SIZE - 1))
        throw "Not implemented";
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if ((ind < 0) || (ind >= sz) || (ind >= MAX_VECTOR_SIZE - 1))
        throw "Not implemented";
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz == v.sz) {
          for (int i = 0; i < v.sz; i++) {
              if (v.pMem[i] != pMem[i])
                  return false;
          }
          return true;
      }
      else
          return false;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (sz == v.sz) {
          for (int i = 0; i < v.sz; i++) {
              if (v.pMem[i] == pMem[i])
                  return false;
          }
          return true;
      }
      else
          return true;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector tmp(sz);
    tmp = *this;
    for (int i = 0; i < sz; i++)
        tmp.pMem[i] += val;
    return tmp;
  }
  TDynamicVector operator-(double val)
  {
    TDynamicVector tmp(sz);
    tmp = *this;
    for (int i = 0; i < sz; i++)
        tmp.pMem[i] -= val;
    return tmp;
  }
  TDynamicVector operator*(double val)
  {
    TDynamicVector tmp(sz);
    tmp = *this;
    for (int i = 0; i < sz; i++)
        tmp.pMem[i] *= val;
    return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz == v.size()) {
        TDynamicVector tmp(sz);
        for (int i = 0; i < sz; i++)
            tmp[i] = pMem[i] + v[i];
        return tmp;
    }
    else {
        throw "Add vectors with different sizes";
    }
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz == v.size()) {
          TDynamicVector tmp(sz);
          for (int i = 0; i < sz; i++)
              tmp[i] = pMem[i] - v[i];
          return tmp;
      }
      else {
          throw "Subtract vectors with different sizes";
      }
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (sz == v.size()) {
          T res{};
          for (int i = 0; i < sz; i++)
              res += pMem[i] * v[i];
          return res;
      }
      else {
          throw "Multiply vectors with different sizes";
      }
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    return false;
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
    return TDynamicMatrix<T>{};
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    return TDynamicVector<T>{};
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    // можно ли написать реализацию, используя operator+ вектора?
    return TDynamicMatrix<T>{};
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    return TDynamicMatrix<T>{};
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    return TDynamicMatrix<T>{};
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
  {
    return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v)
  {
    return ostr;
  }
};

#endif
