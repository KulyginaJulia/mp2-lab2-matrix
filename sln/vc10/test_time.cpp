#include <time.h>
#include <gtest.h>
#include "matrix_pointer.h"
#include "utmatrix.h"

TEST(Time, TPointerMatrix_time) {
	clock_t start, end;
	int size = 100;

	start = clock();
	TPointerMatrix<double> a(size), b(size);
	for (int i = 0; i < a.GetSize(); i++)
	{
		a[i][i] = i;
	}

	b = a*a;
	end = clock();
	cout << "TPointerMatrixTime: "<<((double)end - start) / ((double)CLOCKS_PER_SEC)<<endl;
}
TEST(Time, TMatrix_time) {
	clock_t start, end;
	int size = 100;

	start = clock();
	TMatrix<double> a(size), b(size);
	for (int i = 0; i < a.GetSize(); i++) {
		a[i][i] = i;
	}

	b = a*a;
	end = clock();
	cout << "TMatrixTime: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << endl;
} 