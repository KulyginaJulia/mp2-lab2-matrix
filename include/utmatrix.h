// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

//#pragma once
#ifndef __TMATRIX_H___
#define __TMATRIX_H___

#include <iostream>
#include "tvector.h"
using namespace std;

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
  TMatrix  operator*(TMatrix &mt);		 //умножение двух матриц

 
	template <class ValType>
   friend istream& operator>>(istream &in, TMatrix<ValType> &mt);

  template <class ValType>
   friend ostream & operator<<( ostream &out, const TMatrix &mt);
};

	template <class ValType>
   istream& operator>>(istream &in, TMatrix<ValType> &mt){
     for (int i = 0; i < mt.Size; i++)
       in >> mt.pVector[i];
     return in;
   }
  template <class ValType>
  ostream & operator<<( ostream &out, const TMatrix<ValType> &mt)
   {
 	  for (int i = 0; i < mt.Size + mt.StartIndex; i++)
 	     out << mt.pVector[i] << endl;
     return out;
   }

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s) //Конструктор
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

/*template <class ValType> // умножение двух матриц
TMatrix<ValType> TMatrix<ValType>::operator*(TMatrix<ValType> &mt)
{
	if (Size != mt.Size) {
		throw "Матрицы разного размера * utmatrix";
	}
	TMatrix<ValType> result(Size);
	for (int i = 0; i < Size; i++)
		for (int j = i; j < Size; j++)
			for (int k = 0; k <= j; k++)
				result[i][j] = result[i][j] + ((*this)[i][k])*(mt[k][j]);
	return result;
} *//*-------------------------------------------------------------------------*/

template <class ValType>
TMatrix<ValType> TMatrix<ValType> :: operator* ( TMatrix<ValType> & mt)//умножение двух матриц
{
	if (Size != mt.Size) 
		throw "Разные размеры матриц * utmatrix";
	TMatrix<ValType> result(Size);
	for (int i = 0; i < (this->Size); i++){
		for (int j = i; j < (this->Size); j++){
			result[i][j] = 0;
			for (int k = 0; k <= j; k++){
			result[i][j] = result[i][j] + ((*this)[i][k] * (mt[k][j]));
			}
		}
	}
	return result;
}/*-------------------------------------------------------------------------*/
// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3


#endif