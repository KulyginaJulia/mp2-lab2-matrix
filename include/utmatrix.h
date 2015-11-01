﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

//#pragma once
#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include "utmatrix.h"
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  virtual ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента

  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream in, TVector &v)
  {
	   for (int i = 0; i < v.Size; i++)
		   in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream out, const TVector &v)
  {
	  for (int i = 0; i < v.Size + v.StartIndex; i++)
      out << v[i] << ' ' << endl;
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if (s > MAX_VECTOR_SIZE)
 	{
 		throw "Конструктор MAX_VECTOR_SIZE < s utmatrix";
 	}
 	if (s < 0)
 	{
 		throw "Конструктор s < 0 utmatrix";
 	}
 	if (si < 0){
 		throw "Конструктор si < 0 utmatrix";
 	}
 	pVector = new ValType[s];
 	Size = s;
 	StartIndex = si;
 	for (int i = StartIndex; i < Size + StartIndex; i++)
 	{
 		(*this)[i] = ValType();
 	}
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	pVector = new ValType[v.Size];
	Size = v.Size;
	StartIndex = v.StartIndex;
	for (int i = StartIndex; i < Size + StartIndex; i++)
		pVector[i] = v.pVector[i];

} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete []pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	 	if (pos < 0)
 	{
 		throw "[] pos < 0 utmatrix";
 	}
 	if (pos >= StartIndex + Size)
 	{
 		throw "[] pos > MAX_VECTOR_SIZE utmatrix" ;
 	}
 	if (pos < StartIndex) {
 		return *new ValType();
 	}
	return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (Size != v.Size) {
 		return false;
 	}
	 else 
		for ( int i = 0; i < Size; i++)
			if (this->pVector[i] != v.pVector[i] ){
				return false; break; 
			}
 	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	if (Size != v.Size) {
 		return true;
 	}
	 else 
		for ( int i = 0; i < Size; i++)
			if (this->pVector[i] == v.pVector[i] ){
				return true; break; 
			}
 	return false;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this != &v){
		if (Size != v.Size){
			delete []pVector;
			pVector = new ValType[v.Size];
		}
		Size = v.Size; StartIndex = v.StartIndex;
		for (int i = 0; i < Size; i++ )
			pVector[i] = v.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector temp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] = pVector[i] + val;
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector temp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] = pVector[i] - val;
	return temp;
} /*-------------------------------------------------------------------------*/ 

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector temp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] = pVector[i] * val;
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if ((Size != v.Size) ||( StartIndex != v.StartIndex))
	{
 		throw "Сложение векторов разной длины utmatrix";
 	}

	TVector temp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] = pVector[i] + v.pVector[i];
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if ((Size != v.Size) ||( StartIndex != v.StartIndex))
 	{
 		throw "Вычитание векторов разной длины utmatrix";
 	}
	TVector temp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] = pVector[i] - v.pVector[i];
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	ValType res = 0;
	if ((Size != v.Size) ||( StartIndex != v.StartIndex))
 	{
 		throw "Скалярное произведение векторов разной длины utmatrix";
 	}
 
	for (int i = 0; i < Size; i++)
		res = res + (v.pVector[i] * pVector[i]);
	return res;
} /*-------------------------------------------------------------------------*/

// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа

  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение

  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание
  TMatrix  operator*(const Tmatrix &mt);		 //умножение двух матриц

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt){
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
	  for (int i = 0; i < mt.Size; i++)
	     out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	if(s<0)
		throw "s < 0 utmatrix";
	else if(s > MAX_MATRIX_SIZE)
		throw "S >= MAX_MATRIX_SIZE utmatrix";
	else
	{
		Size = s;
		for(int i = 0;i < Size; i++)
			pVector[i] = TVector <ValType>(Size-i ,i);
		for (int i = 0; i < Size; i++)
			for (int j = 0; j < Size-i; j++)
				pVector[i][j]=0;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (Size != mt.Size)
		return false;
	else if (StartIndex != mt.StartIndex)
		return false;
	else
	{
		for (int i = StartIndex;i < StartIndex + Size; i++)
			if (pVector[i] != mt.pVector[i])
			{
				return true;
				break;
			}
		return true;
	}
	
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	if (Size != mt.Size)
		return true;
	else if (StartIndex != mt.StartIndex)
		return true;
	else
	{
		for (int i = StartIndex; i < StartIndex + Size; i++)
			if (pVector[i] == mt.pVector[i])
			{
				return true;
				break;
			}
			else
			return false;
	}
	return false;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this != &mt) {
 		if (Size != mt.Size) {
 			delete[] pVector;
 			pVector = new TVector<ValType>[mt.Size];
 		}
 		Size = mt.Size;
 		StartIndex = mt.StartIndex;
 		for (int i = 0; i < Size; i++)
 			pVector[i] = mt.pVector[i];
 	}
 	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (Size!=mt.Size)
 	{
 		throw "Матрицы разного размера + utmatrix";
 	}
	TMatrix<ValType> result(Size);
		for (int i = StartIndex; i < Size + StartIndex; i++)
				result.pVector[i] = pVector[i] + mt.pVector[i];
	return result;

} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (Size!=mt.Size)
 	{
 		throw "Матрицы разного размера - utmatrix";
 	}
	TMatrix<ValType> result(Size);
		for (int i = StartIndex; i < Size + StartIndex; i++)
				result.pVector[i] = pVector[i] - mt.pVector[i];
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножение двух матриц
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix<ValType> &mt)
{
	if (Size != mt.Size) {
		throw invalid_argument("Матрицы разного размера * utmatrix");
	}
	TMatrix<ValType> result(Size);
	for (int i = 0; i < Size; i++)
		for (int j = i; j < Size; j++)
			for (int k = 0; k <= j; k++)
				result[i][j] = result[i][j] + ((*this)[i][k])*(mt[k][j]);
	return result;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3


#endif