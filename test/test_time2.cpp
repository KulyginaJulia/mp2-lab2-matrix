#include <time.h>
#include <gtest.h>
#include "utmatrix.h"
TEST(Time, TMatrix_time) {
	clock_t start, end;
	int size = 250;

	start = clock();
	TMatrix<int> m1(size), m2(size);
	for (int i = 0; i < m1.GetSize(); i++) {
		m1[i][i] = i;
	}

	m2 = m1*m1;
	end = clock();
	cout << "TMatrixTime: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << endl;
} 