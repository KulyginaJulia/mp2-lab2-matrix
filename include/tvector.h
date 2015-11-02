#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
//#include "utmatrix.h"
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
  friend istream& operator>>(istream &in, TVector &v)
  {
	   for (int i = 0; i < v.Size; i++)
		   in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
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
 		throw "Конструктор MAX_VECTOR_SIZE < s";
 	}
 	if (s < 0)
 	{
 		throw "Конструктор s < 0";
 	}
 	if (si < 0){
 		throw "Конструктор si < 0";
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
 		throw "[] pos < 0";
 	}
 	if (pos >= StartIndex + Size)
 	{
 		throw "[] pos > MAX_VECTOR_SIZE" ;
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
 		throw "Сложение векторов разной длины";
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
 		throw "Вычитание векторов разной длины";
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
 		throw "Скалярное произведение векторов разной длины";
 	}
 
	for (int i = 0; i < Size; i++)
		res = res + (v.pVector[i] * pVector[i]);
	return res;
} /*-------------------------------------------------------------------------*/
#endif