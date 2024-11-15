// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

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
        if (sz <= 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz >= MAX_VECTOR_SIZE)
            throw out_of_range("Vector size shouldn't be greater than max vector size");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        this->pMem = new T[v.sz]();
        for (int i = 0; i < v.sz; i++)
            pMem[i] = v.pMem[i];
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        this->sz = v.sz;
        this->pMem = v.pMem;
        v.sz = 0;
        v.pMem = nullptr;
    }
    ~TDynamicVector()
    {
        sz = 0;
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (&v == this)
            return *this;
        delete[] this->pMem;
        sz = v.sz;
        this->pMem = new T[sz]();
        for (int i = 0; i < sz; i++)
            pMem[i] = v.pMem[i];
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (&v == this)
            return *this;
        delete[] this->pMem;
        sz = v.sz;
        this->pMem = v.pMem;
        v.sz = 0;
        v.pMem = nullptr;
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if ((0 <= ind) && (ind < sz))
            return this->pMem[ind];
        else
            throw exception();
        
    }
    const T& operator[](size_t ind) const
    {
        if ((0 <= ind) && (ind < sz))
            return this->pMem[ind];
        else
            throw exception();
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if ((0 <= ind) && (ind < sz))
            return this->pMem[ind];
        else
            throw exception();
    }
    const T& at(size_t ind) const
    {
        if ((0 <= ind) && (ind < sz))
            return const &(this->pMem[ind]);
        else
            throw exception();
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (this->sz != v.sz)
            return 0;
        else
            for (int i = 0; i < sz; i++)
                if (this->pMem[i] != v.pMem[i])
                    return 0;
        return 1;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector<T> NewV(sz);
        for (int i = 0; i < sz; i++)
            NewV.pMem[i] = pMem[i] + val;
        return NewV;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector<T> NewV(sz);
            for (int i = 0; i < sz; i++)
                NewV.pMem[i] = pMem[i] - val;
        return NewV;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector<T> NewV(sz);
            for (int i = 0; i < sz; i++)
                NewV.pMem[i] = pMem[i] * val;
        return NewV;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw exception();
        TDynamicVector a(min(sz, v.sz));
        for (int i = 0; i < a.sz; i++)
            a.pMem[i] = this->pMem[i] + v.pMem[i];
        return a;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw exception();
        TDynamicVector a(min(sz, v.sz));
        for (int i = 0; i < a.sz; i++)
            a.pMem[i] = this->pMem[i] - v.pMem[i];
        return a;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz)
            throw exception();
        T s = 0;
        for (int i = 0; i < min(sz, v.sz); i++)
            s += this->pMem[i] * v.pMem[i];
        return abs(s);
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
      std::swap(lhs.sz, rhs.sz);
      std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i]; // требуется оператор>> для типа T
      return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
      return ostr;
    }
    friend istream& operator>>(istream& istr, T a)
    {
        istr >> a;
        return a;
    }
    friend ostream& operator<<(ostream& ostr, T a)
    {
        ostr << a;
        return a;
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
        if ((s < 1) | (s > MAX_MATRIX_SIZE))
            throw exception();
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::size;
    using TDynamicVector<TDynamicVector<T>>::at;

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>:: operator == (m);
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        return TDynamicVector<TDynamicVector<T>>:: operator *(val);
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        TDynamicVector<T> a(v.sz);
        for (int i = 0; i < sz; i++)
            a[i] = v * pMem[i];
        return a;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        TDynamicMatrix NewM(sz);
        for (size_t i = 0; i < sz; i++)
            NewM.pMem[i] = pMem[i] + m.pMem[i];
        return NewM;

    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        TDynamicMatrix NewM(sz);
        for (size_t i = 0; i < sz; i++)
            NewM.pMem[i] = pMem[i] - m.pMem[i];
        return NewM;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw exception();
        TDynamicMatrix NewM(sz);
        for (int i = 0; i < M.N; i++)
            for (int j = 0; j < M.N; j++)
                for (int k = 0; k < N; k++)
                     NewM.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
        return NewM;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (int i = 0; i < v.s; i++)
            for (int j = 0; j < v.sz; j++)
                istr >> v[i][j];
        return istr;

    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (int i = 0; i < v.sz; i++)
            for (int j = 0; j < v.sz; j++)
                ostr << v[i][j] << " ";
        ostr << endl;
        return ostr;
    }
};

#endif
