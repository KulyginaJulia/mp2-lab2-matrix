#include "matrix_pointer.h"

#include <gtest.h>

TEST(TPointerMatrix, can_multiplied__matrix_on_itself) {
	
	TPointerMatrix<int> m(2), result(2);

	// 1 1
	// 1 3
	m[0][0] = 1;
	m[0][1] = 1;
	m[1][0] = 1;
	m[1][1] = 3;

	// 2 4
	// 4 10
	result[0][0] = 2;
	result[0][1] = 4;
	result[1][0] = 4;
	result[1][1] = 10;

	EXPECT_EQ(result, m*m);
}