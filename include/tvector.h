#ifndef __TVECTOR_H__
#define __TVECTOR_H__

#include <iostream>
#include <string>
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// ������ �������
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // ������ �������
  int StartIndex; // ������ ������� �������� �������
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // ����������� �����������
  virtual ~TVector();
  int GetSize()      { return Size;       } // ������ �������
  int GetStartIndex(){ return StartIndex; } // ������ ������� ��������

  ValType& operator[](int pos);             // ������
  ValType& operator[](int pos) const;       // ������ �����������
  bool operator==(const TVector &v) const;  // ���������
  bool operator!=(const TVector &v) const;  // ���������
  TVector& operator=(const TVector &v);     // ������������

  // ��������� ��������
  TVector  operator+(const ValType &val);   // ��������� ������
  TVector  operator-(const ValType &val);   // ������� ������
  TVector  operator*(const ValType &val);   // �������� �� ������

  // ��������� ��������
  TVector  operator+(const TVector &v);     // ��������
  TVector  operator-(const TVector &v);     // ���������
  ValType  operator*(const TVector &v);     // ��������� ������������

  // ����-�����

//  template <class ValType>
   friend istream& operator>>(istream &in, TVector &v)
  {
	   for (int i = 0; i < v.Size; i++)
		   in >> v.pVector[i];
    return in;
  }

 //  template <class ValType>
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
	  for (int i = 0; i < v.Size + v.StartIndex; i++)
		 out << v[i] << ' ' << endl;
    return out;
  }
};

template <class ValType> // ������
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
template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos) const
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

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if (s > MAX_VECTOR_SIZE)
 	{
 		throw "����������� MAX_VECTOR_SIZE < s";
 	}
 	if (s < 0)
 	{
 		throw "����������� s < 0";
 	}
 	if (si < 0){
 		throw "����������� si < 0";
 	}
 	pVector = new ValType[s];
 	Size = s;
 	StartIndex = si;
 	for (int i = StartIndex; i < Size + StartIndex; i++)
 	{
 		(*this)[i] = ValType();
 	}
} /*-------------------------------------------------------------------------*/

template <class ValType> //����������� �����������
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



template <class ValType> // ���������
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

template <class ValType> // ���������
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

template <class ValType> // ������������
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

template <class ValType> // ��������� ������
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector temp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] = pVector[i] + val;
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������� ������
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector temp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] = pVector[i] - val;
	return temp;
} /*-------------------------------------------------------------------------*/ 

template <class ValType> // �������� �� ������
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector temp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] = pVector[i] * val;
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if ((Size != v.Size) ||( StartIndex != v.StartIndex))
	{
 		throw "�������� �������� ������ �����";
 	}

	TVector temp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] = pVector[i] + v.pVector[i];
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if ((Size != v.Size) ||( StartIndex != v.StartIndex))
 	{
 		throw "��������� �������� ������ �����";
 	}
	TVector temp(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		temp.pVector[i] = pVector[i] - v.pVector[i];
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������������
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	ValType res = 0;
	if ((Size != v.Size) ||( StartIndex != v.StartIndex))
 	{
 		throw "��������� ������������ �������� ������ �����";
 	}
 
	for (int i = 0; i < Size; i++)
		res = res + (v.pVector[i] * pVector[i]);
	return res;
} /*-------------------------------------------------------------------------*/
#endif