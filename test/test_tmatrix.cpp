#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> expected(2);

	m[0][0] = 0; expected[0][0] = 0;
	m[0][1] = 1; expected[0][1] = 1;
	m[1][0] = 1; expected[1][0] = 1;
	m[1][1] = 0; expected[1][1] = 0;

	TDynamicMatrix<int> m1(m);

	EXPECT_EQ(m1, expected);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(2);

	m[0][0] = 0; 
	m[0][1] = 1; 
	m[1][0] = 1; 
	m[1][1] = 0;

	TDynamicMatrix<int> m1(m);

	m[0][0] = 10;

	EXPECT_NE(m, m1);
}

TEST(TDynamicMatrix, can_get_size)
{
	size_t expected = 2;
	TDynamicMatrix<int> m(2);

	EXPECT_EQ(expected, m[0].size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(2);
	int el = 1;
	m[0][0] = 1;

	EXPECT_EQ(m[0][0], el);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(2);

	ASSERT_ANY_THROW(m.at(-1).at(0) = 2);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(MAX_MATRIX_SIZE);

	ASSERT_ANY_THROW(m.at(MAX_MATRIX_SIZE).at(0) = 3);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> expected(2);

	m[0][0] = 1; expected[0][0] = 1;

	m = m;

	EXPECT_EQ(m, expected);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> expected(2);

	m[0][0] = 1; expected[0][0] = 1;

	m1 = m;

	EXPECT_EQ(m1, expected);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	size_t expected = 3;

	m = m1;

	EXPECT_EQ(m[0].size(), expected);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> expected(2);

	m[0][0] = 1; expected[0][0] = 1;

	m1 = m;

	EXPECT_EQ(m1, expected);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);

	m[0][0] = 2;
	m1[0][0] = 2;

	EXPECT_EQ(m, m1);

}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);

	EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);

	EXPECT_NE(m, m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> res(2);
	TDynamicMatrix<int> expected(2);

	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 2;
	m[1][1] = 1;

	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[1][0] = 2;
	m1[1][1] = 1;

	expected[0][0] = 2;
	expected[0][1] = 4;
	expected[1][0] = 4;
	expected[1][1] = 2;

	res = m + m1;

	EXPECT_EQ(res, expected);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> res(3);

	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> res(2);
	TDynamicMatrix<int> expected(2);

	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 2;
	m[1][1] = 1;

	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[1][0] = 2;
	m1[1][1] = 1;

	expected[0][0] = 0;
	expected[0][1] = 0;
	expected[1][0] = 0;
	expected[1][1] = 0;

	res = m - m1;

	EXPECT_EQ(res, expected);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> res(3);

	ASSERT_ANY_THROW(m - m1);
}

TEST(TDynamicMatrix, can_read_matrix)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> expected(2);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			expected[i][j] = i;

	std::stringstream sstr;
	sstr << "0 0 1 1\n";
	sstr >> m;

	EXPECT_EQ(expected, m);
}

TEST(TDynamicMatrix, can_write_matrix)
{
	TDynamicMatrix<int> m(2);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			m[i][j] = i;
	std::string expected = "0 0  1 1  ";

	std::stringstream sstr;
	sstr << m;

	EXPECT_EQ(expected, sstr.str());
}
