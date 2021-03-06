#ifndef _MATRIX_POINTER_
#define _MATRIX_POINTER_


#include "tvector.h"

template <class ValType>
class TPointerMatrix {
private:
	TVector<ValType> **pMatrix;
	int Size;
public:
	TPointerMatrix(int s = 10);
	TPointerMatrix(const TPointerMatrix &mt);                    // �����������
	TPointerMatrix(const TVector<TVector<ValType> > &mt); // �������������� ����
	virtual ~TPointerMatrix();

	int GetSize() const { return Size; }
	void SetSize(int mySize) { Size = mySize; }
	TVector<ValType>& operator[](int pos);             // ������
	bool operator==(const TPointerMatrix &mt) const;      // ���������
	bool operator!=(const TPointerMatrix &mt) const;      // ���������
	TPointerMatrix& operator= (const TPointerMatrix &mt);        // ������������
	TPointerMatrix  operator+ (const TPointerMatrix &mt);        // ��������
	TPointerMatrix  operator- (const TPointerMatrix &mt);        // ���������
	TPointerMatrix  operator* (TPointerMatrix &mt);		 // ��������� ���� ������

	// ���� / �����
	//template <class ValType>
	friend istream& operator>>(istream &in, TPointerMatrix &mt) {
		int size;
		in >> size;
		mt.SetSize(size);
		for (int i = 0; i < mt.GetSize(); i++)
			in >> mt[i];
		return in;
	}

//	template <class ValType>
	friend ostream & operator<<(ostream &out, const TPointerMatrix &mt) {
		out << mt.GetSize() << endl;
		for (int i = 0; i < mt.GetSize(); i++)
			out << mt[i] << endl;
		return out;
	}
};

template <class ValType>
TPointerMatrix<ValType>::TPointerMatrix(int s){
	if (s < 0) {
		throw "s < 0  matrix_pointer";
	}
	if (s > MAX_MATRIX_SIZE) {
		throw "MAX_MATRIX_SIZE < s  matrix_pointer";
	}
	Size = s;
	pMatrix = new TVector<ValType>*[s];
	for (int i = 0; i < s; i++)
		pMatrix[i] = new TVector<ValType>(s-i,i);
} /*-------------------------------------------------------------------------*/

template <class ValType>
TPointerMatrix<ValType>::~TPointerMatrix()
{
	delete []pMatrix;
} /*-------------------------------------------------------------------------*/

template <class ValType> 
TPointerMatrix<ValType>::TPointerMatrix(const TPointerMatrix<ValType> &mt){
	Size = mt.Size;
	this->pMatrix = new  TVector<ValType>*[mt.GetSize()];
	for (int i = 0; i < mt.Size;i++)
	{
		pMatrix[i] = mt.pMatrix[i];
	}
}

template <class ValType> 
TVector<ValType>& TPointerMatrix<ValType>::operator[](int pos) {
	if (pos < 0 ) {
		throw "[] pos < 0 matrix_pointer";
	}if (pos > Size) {
		throw "[] pos > Size matrix_pointer";
	}
	return *(pMatrix[pos]);
} /*-------------------------------------------------------------------------*/

template <class ValType> 
TPointerMatrix<ValType>::TPointerMatrix(const TVector<TVector<ValType> > &mt) : TVector<TVector<ValType> >(mt) {}

template <class ValType> 
bool TPointerMatrix<ValType>::operator==(const TPointerMatrix<ValType> &mt) const {
	if (this == &mt) {
		return true;
	}

	if (Size != mt.Size) {
		return false;
	}

	for (int i = 0; i < Size; i++) {
		if (*pMatrix[i] != *(mt.pMatrix[i]))
			return false;
	}

	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> 
bool TPointerMatrix<ValType>::operator!=(const TPointerMatrix<ValType> &mt) const {
	return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> 
TPointerMatrix<ValType>& TPointerMatrix<ValType>::operator=(const TPointerMatrix<ValType> &mt) {
	if (this != &mt) {
		if (Size != mt.Size) {
			delete []pMatrix;
		}
		Size = mt.Size;

		pMatrix = new  TVector<ValType>*[mt.GetSize()];
		for (int i = 0; i < mt.GetSize(); i++) {
			pMatrix[i] = mt.pMatrix[i];
		}
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType>
TPointerMatrix<ValType> TPointerMatrix<ValType>::operator+(const TPointerMatrix<ValType> &mt) {
	if (Size != mt.Size) {
		throw "������� ������ ����� + matrix_pointer";
	}
	TPointerMatrix<ValType> result(Size);
	for (int i = 0; i < Size; i++) {
		result[i] = (*this)[i] + mt[i];
	}
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> 
TPointerMatrix<ValType> TPointerMatrix<ValType>::operator-(const TPointerMatrix<ValType> &mt) {
	if (Size != mt.Size) {
		throw "������� ������ ����� - matrix_pointer";
	}
	TPointerMatrix<ValType> result(Size);
	for (int i = 0; i < Size; i++) {
		result[i] = (*this)[i] - mt[i];
	}
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> 
TPointerMatrix<ValType> TPointerMatrix<ValType>::operator* ( TPointerMatrix<ValType> &mt) {
	if (Size != mt.Size) 
		throw "������ ������� ������ * utmatrix";
	TPointerMatrix<ValType> result(Size);
	for (int i = 0; i < (this->Size); i++){
		for (int j = i; j < (this->Size); j++){
			result[i][j] = 0;
			for (int k = 0; k <= j; k++){
			result[i][j] = result[i][j] + ((*this)[i][k] * (mt[k][j]));
			}
		}
	}
	return result;
} /*-------------------------------------------------------------------------*/ 

#endif