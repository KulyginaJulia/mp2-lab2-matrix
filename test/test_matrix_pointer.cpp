#include "matrix_pointer.h"

#include <gtest.h>

TEST(TPointerMatrix, can_multiplied__matrix_on_itself) {
	
	TPointerMatrix<int> m(2), result1(2), result2(2);

	// 1 0
	// 0 1
	m[0][0] = 1;
	m[1][1] = 1;

	// 1 0
	// 0 1
	result1[0][0] = 1;
	result1[1][1] = 1;
	result2 = m*m;

	EXPECT_EQ(result1[0][0], result2[0][0]);
//	EXPECT_EQ(result1[0][1], result2[0][1]);
//	EXPECT_EQ(result1[1][0], result2[1][0]);
//	EXPECT_EQ(result1[1][1], result2[1][1]);
}