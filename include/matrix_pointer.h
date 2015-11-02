#include "tvector.h"

template <class ValType>
class TPointerMatrix {
private:
	TVector<ValType> **pMatrix;
	int Size;
public:
	TPointerMatrix(int s = 10);
	TPointerMatrix(const TPointerMatrix &mt);                    // копировани€
	TPointerMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
	virtual ~TPointerMatrix();

	int GetSize() const { return Size; }
	TVector<ValType>& operator[](int pos) const;             // доступ
	bool operator==(const TPointerMatrix &mt) const;      // сравнение
	bool operator!=(const TPointerMatrix &mt) const;      // сравнение
	TPointerMatrix& operator= (const TPointerMatrix &mt);        // присваивание
	TPointerMatrix  operator+ (const TPointerMatrix &mt);        // сложение
	TPointerMatrix  operator- (const TPointerMatrix &mt);        // вычитание
	TPointerMatrix  operator* (const TPointerMatrix &mt);		 // умножение двух матриц

	// ввод / вывод
	friend istream& operator>>(istream &in, TPointerMatrix &mt) {
		in >> mt.Size;
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream & operator<<(ostream &out, const TPointerMatrix &mt) {
		out << mt.Size << endl;
		for (int i = 0; i < mt.Size; i++)
			out << mt.pMatrix[i] << endl;
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
TVector<ValType>& TPointerMatrix<ValType>::operator[](int pos) const {
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
		throw "¬ектора разной длины + matrix_pointer";
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
		throw "¬ектора разной длины - matrix_pointer";
	}
	TPointerMatrix<ValType> result(Size);
	for (int i = 0; i < Size; i++) {
		result[i] = (*this)[i] - mt[i];
	}
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> 
TPointerMatrix<ValType> TPointerMatrix<ValType>::operator* (const TPointerMatrix<ValType> &mt) {
	if (Size != mt.Size) 
		throw "–азные размеры матриц * utmatrix";
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