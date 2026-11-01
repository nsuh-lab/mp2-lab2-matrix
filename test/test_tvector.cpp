#include <sstream>
#include "gtest.h"
#include "tmatrix.h"

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, can_move_vector_using_move_constructor)
{
  TDynamicVector<int> v(2);
  TDynamicVector<int> expected(2);

  v[0] = 0;
  v[1] = 1;

  expected = v;
  TDynamicVector<int> v1(std::move(v));
  EXPECT_EQ(v1, expected);
  EXPECT_EQ(v.size(), 0);
}

TEST(TDynamicVector, can_move_vector_using_move_operator)
{
	TDynamicVector<int> v(2);
	TDynamicVector<int> v1;
	TDynamicVector<int> expected(2);

	v[0] = 0;
	v[1] = 1;

	expected = v;
	v1 = std::move(v);

	EXPECT_EQ(v1, expected);
	EXPECT_EQ(v.size(), 0);
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(3);
	
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;

	TDynamicVector<int> v1(v);

	EXPECT_EQ(v1, v);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(v);

	v[0] = 1;
	v[1] = 2;
	v[2] = 3;

	EXPECT_NE(v, v1);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(4);

  ASSERT_ANY_THROW(v.at(-1) = 2);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(MAX_VECTOR_SIZE);

  ASSERT_ANY_THROW(v.at(MAX_VECTOR_SIZE-1) = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> expected(4);

	v[0] = 1;
	expected[0] = 1;
	v = v;

	EXPECT_EQ(v, expected);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(4);
	TDynamicVector<int> expected(4);

	v1[0] = 1;
	v1[1] = 2;
	expected[0] = 1;
	expected[1] = 2;
	v = v1;

	EXPECT_EQ(v, expected);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(3);

	v = v1;

	EXPECT_EQ(v.size(), v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(4);
	TDynamicVector<int> expected(4);

	v1[0] = 0;
	v1[1] = 1;
	expected[0] = 0;
	expected[1] = 1;
	v = v1;

	EXPECT_EQ(v, expected);

}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);

	v[0] = 1;
	v[1] = 2;
	v1[0] = 1;
	v1[1] = 2;

	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(3);

	EXPECT_EQ(v, v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(4);

	EXPECT_NE(v, v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int c = 5;
	TDynamicVector<int> v(5);
	TDynamicVector<int> res(5);
	TDynamicVector<int> expected(5);

	for (int i = 0; i < v.size(); i++)
		v[i] = i;
	for (int i = 0; i < expected.size(); i++)
		expected[i] = i + 5;
	res = v + 5;

	EXPECT_EQ(res, expected);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int c = 5;
	TDynamicVector<int> v(5);
	TDynamicVector<int> res(5);
	TDynamicVector<int> expected(5);

	for (int i = 0; i < v.size(); i++)
		v[i] = i;
	for (int i = 0; i < expected.size(); i++)
		expected[i] = i - 5;
	res = v - 5;

	EXPECT_EQ(res, expected);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int c = 5;
	TDynamicVector<int> v(5);
	TDynamicVector<int> res(5);
	TDynamicVector<int> expected(5);

	for (int i = 0; i < v.size(); i++)
		v[i] = i;
	for (int i = 0; i < expected.size(); i++)
		expected[i] = i * 5;
	res = v * 5;

	EXPECT_EQ(res, expected);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(5);
	TDynamicVector<int> res(5);
	TDynamicVector<int> expected(5);

	for (int i = 0; i < v.size(); i++) {
		v[i] = i;
		v1[i] = i;
	}
	res = v + v1;
	for (int i = 0; i < expected.size(); i++)
		expected[i] = 2 * i;

	EXPECT_EQ(res, expected);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(6);

	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(5);
	TDynamicVector<int> res(5);
	TDynamicVector<int> expected(5);

	for (int i = 0; i < v.size(); i++) {
		v[i] = i;
		v1[i] = i;
	}
	res = v - v1;

	EXPECT_EQ(res, expected);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(6);

	ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(5);
	int res;
	int expected;

	for (int i = 0; i < v.size(); i++) {
		v[i] = i;
		v1[i] = i;
	}
	res = v * v1;
	expected = 30;

	EXPECT_EQ(res, expected);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(6);

	ASSERT_ANY_THROW(v * v1);
}

TEST(TDynamicVector, can_read_vector)
{
  TDynamicVector<int> v(5);
  TDynamicVector<int> expected(5);
  for (int i = 0; i < 5; i++) expected[i] = i;
  
  std::stringstream sstr;
  sstr << "0 1 2 3 4\n";
  sstr >> v;
  
  EXPECT_EQ(expected, v);
}

TEST(TDynamicVector, can_write_vector)
{
  TDynamicVector<int> v(5);
  for (int i = 0; i < 5; i++) v[i] = i;
  std::string expected = "0 1 2 3 4 ";
  
  std::stringstream sstr;
  sstr << v;
  
  EXPECT_EQ(expected, sstr.str());
}
