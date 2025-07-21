#include "testa.h"

int add(int a, int b) {
    return a + b;
}

TEST(test_addition) {
    ASSERT_EQ_INT(add(1,1), 2);
}

TEST(test_float) {
    ASSERT_EQ_FLOAT(1.0, 1.000003, 0.001);
}

TEST(test_double) {
    ASSERT_EQ_DOUBLE(2.001, 2.0001, 0.0000001);
}

TEST(compare_strings) {
    ASSERT_EQ_STR("string", "string1");
}

TEST(compare_chars) {
    ASSERT_EQ_CHAR('a', 'a');
}

TEST(compare_ptrs) {
    int a_val = 50;
    int b_val = 40;
    int *a = &a_val;
    int *b = &b_val;
    ASSERT_EQ_PTR(a, b);
}

TEST(test_equal) {
    ASSERT_TRUE(true);
}

TEST(test_false) {
    ASSERT_FALSE(false);
}

int main() {
    run_all_tests();

    return 0;
}
