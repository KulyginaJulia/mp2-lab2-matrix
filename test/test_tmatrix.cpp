#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m1(5), m2(5);
	
	m1[0][0] = 5;
	m2 = m1;
	
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m1(8);
	TMatrix<int> m2(8);

	m2 = m1;
	m1[0][0] = 5;
	
	EXPECT_NE(m1, m2);
}

TEST(TMatrix, can_get_size)
{
	 TMatrix<int> m(4);

	EXPECT_EQ(4, m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(4);
	m[0][1] = 4;

	EXPECT_EQ(4, m[0][1]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(4);

	ASSERT_ANY_THROW(m[0][-2]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(4);

	ASSERT_ANY_THROW(m[1][500]);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	const int size = 2;
	TMatrix<int> m(size);

	m[0][0] = 1;
	m[0][1] = 2;
	m = m;

	EXPECT_EQ(1, m[0][0]);
	EXPECT_EQ(2, m[0][1]);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	const int size = 2;
	TMatrix<int> m1(size), m2(size);

	for (int i = 0; i < size; i++)
	{
		m1[i][1] = 1;
	}
	m2 = m1;

	EXPECT_NE(0, m2[0][1]);
	EXPECT_NE(0, m2[1][1]);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	const int size1 = 2, size2 = 5;
	TMatrix<int> m1(size1), m2(size2);
	for (int i = 0; i < size1; i++)
	{
		m1[i][0] = 1;
	}

	m2 = m1;

	EXPECT_EQ(2, m2.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	const int size1 = 2, size2 = 5;
	TMatrix<int> m1(size1), m2(size2);
	for (int i = 0; i < size1; i++)
	{
		m1[i][0] = 1;
	}
	m2 = m1;

	EXPECT_NE(0, m2[0][0]);
	EXPECT_NE(0, m2[1][0]);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> m1(4), m2(4);

	m1[0][1] = 5;
	m2[0][1] = 5;

	EXPECT_EQ(1, m1 == m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> m1(4);

	EXPECT_EQ(1, m1 == m1);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> m1(4);
	TMatrix<int> m2(5);

	EXPECT_NE(1, m1 == m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m1(4), m2(4), m3(4);

	m1[0][0] = 1;
	m2[0][0] = 2;
	m3 = m1 + m2;
	
	for (int i = 0; i < 4; i++ )
		for (int j = 0; j < 10; j++)
			m2[i][j] = m2[i][j] + m1[i][j];

	EXPECT_EQ(m3, m2);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m1(4);
	TMatrix<int> m2(5);
	
	ASSERT_ANY_THROW(TMatrix<int> m(m1 + m2));
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m1(4), m2(4), m3(4);

	m1[0][0] = 1;
	m2[0][0] = 2;
	m3 = m2 - m1;
	
	for (int i = 0; i < 4; i++ )
		for (int j = 0; j < 10; j++)
			m2[i][j] = m2[i][j] - m1[i][j];

	EXPECT_EQ(m3, m2);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m1(4);
	TMatrix<int> m2(5);
	
	ASSERT_ANY_THROW(TMatrix<int> m(m2 - m1));
}

TEST(TMatrix, can_multiply_matrixes_with_equal_size)//Можно найти произведение двух матриц с одинаковым размером
{
	const int size = 4;
	TMatrix<int> m1(size), m2(size);
	TMatrix<int> m3(size), m4(size);
	
	m1[0][0] = 1;
	m2[0][0] = 2;
	m3 = m2 * m1;
	
	for (int i = 0; i < size; i++ )
		for(int j = 0; j < size; j++ )
			for (int k = 0; k < size; k++)
				// Умножить строку A на столбец B, чтобы получить строку, столбец элемента.
                m4[i][j] = m4[i][j] + m1[i][k] * m2[k][j];

	EXPECT_EQ(m3, m4);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TMatrix<int> m1(4), m2(5);
	
	ASSERT_ANY_THROW(TMatrix<int> m(m1 * m2));
}