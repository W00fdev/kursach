#include <gmock/gmock.h>
#include "../postfix.h"

bool compare_str(const char* str1, const char* str2) {
    int len = find_str_len(str1);
    if (len != find_str_len(str2))  return false;

    for (int i = 0; i < len; i++) {
        if (str1[i] != str2[i]) return false;
    }

    return true;
}

TEST(calculator_test, default_test) {
    char* out_1 = new char[128];
    char* out_2 = new char[128];
    char* out_3 = new char[128];
    char* out_4 = new char[128];
    char* out_5 = new char[128];

    const char* in_1 = "sin 1 ^ 2 + cos 1 ^ 2";
    read_expression(in_1, out_1);
    ASSERT_TRUE(compare_str(out_1, "1 sin 2 ^ 1 cos 2 ^ + "));
    ASSERT_EQ(compute_expression(out_1), 1);

    const char* in_2 = "3 + 4 * 2 / ( 1 - 5 ) ^ 2";
    read_expression(in_2, out_2);
    ASSERT_TRUE(compare_str(out_2, "3 4 2 * 1 5 - 2 ^ / + "));
    ASSERT_EQ(compute_expression(out_2), 3.5);

    const char* in_3 = "( 100 + 3 * 9 - 7 * 5 / 10 ) ^ 3 - 10";
    read_expression(in_3, out_3);
    ASSERT_TRUE(compare_str(out_3, "100 3 9 * + 7 5 * 10 / - 3 ^ 10 - "));

    const char* in_4 = "1 / 100 - 5 ^ ( 3 )";
    read_expression(in_4, out_4);
    ASSERT_TRUE(compare_str(out_4, "1 100 / 5 3 ^ - "));
    ASSERT_EQ(compute_expression(out_4), -124.99);

    const char* in_5 = "1 / 100 - 5 ^ ( - 3 )";
    read_expression(in_5, out_5);
    ASSERT_TRUE(compare_str(out_5, "1 100 / 5 0 3 - ^ - "));
    ASSERT_EQ(compute_expression(out_5), 0.002);

    delete[] out_1;
    delete[] out_2;
    delete[] out_3;
    delete[] out_4;
    delete[] out_5;
}


TEST(calculator_test, functions_test) {
    char* out_1 = new char[128];
    char* out_2 = new char[128];
    char* out_3 = new char[128];

    const char* in_1 = "tg 1 * ctg 1";
    read_expression(in_1, out_1);
    ASSERT_TRUE(compare_str(out_1, "1 tg 1 ctg * "));
    ASSERT_EQ(compute_expression(out_1), 1);

    const char* in_2 = "tg 1 - sin 1 / cos 1";
    read_expression(in_2, out_2);
    ASSERT_TRUE(compare_str(out_2, "1 tg 1 sin 1 cos / - "));

    const char* in_3 = "e * sh 10 + ctg 5 - ( ln 3 ^ log 10 ) / sqrt ( 2 * pi )";
    read_expression(in_3, out_3);
    ASSERT_TRUE(compare_str(out_3, "e 10 sh * 5 ctg + 3 ln 10 log ^ 2 pi * sqrt / - "));

    delete[] out_1;
    delete[] out_2;
    delete[] out_3;
}

TEST(calculator_test, bracer_test) {
    char* out_1 = new char[128];
    char* out_2 = new char[128];
    char* out_3 = new char[128];

    const char* in_1 = "( ( 1.5 - 3.5 ) * ( tg 1 * ctg 1 ) )";
    read_expression(in_1, out_1);
    ASSERT_TRUE(compare_str(out_1, "1.5 3.5 - 1 tg 1 ctg * * "));
    ASSERT_EQ(compute_expression(out_1), -2);

    const char* in_2 = "e * ( 1 + ( pi + e ) * 4 )";
    read_expression(in_2, out_2);
    ASSERT_TRUE(compare_str(out_2, "e 1 pi e + 4 * + * "));

    const char* in_3 = "( 1 + 3 ) / 4";
    read_expression(in_3, out_3);
    ASSERT_TRUE(compare_str(out_3, "1 3 + 4 / "));
    ASSERT_EQ(compute_expression(out_3), 1);

    delete[] out_1;
    delete[] out_2;
    delete[] out_3;
}

TEST(calculator_test, exception_test) {
    char* out_1 = new char[128];
    char* out_2 = new char[128];
    char* out_3 = new char[128];
    char* out_4 = new char[128];
    char* out_5 = new char[128];

    // Bracer error
    const char* in_1 = "( ( )";
    ASSERT_ANY_THROW(read_expression(in_1, out_1));

    // func name (cos != co)
    const char* in_2 = "pi*3-056+10*co";
    ASSERT_ANY_THROW(read_expression(in_2, out_2));

    // don't have operands but only operators
    const char* in_3 = "* / +";
    read_expression(in_3, out_3);
    ASSERT_ANY_THROW(compute_expression(out_3));

    // don't have such operand
    const char* in_4 = "1 % 4";
    ASSERT_ANY_THROW(read_expression(in_4, out_4));

    // + is a binary operator not unary
    const char* in_5 = "1 + ";
    read_expression(in_5, out_5);
    ASSERT_ANY_THROW(compute_expression(out_5));

    delete[] out_1;
    delete[] out_2;
    delete[] out_3;
    delete[] out_4;
    delete[] out_5;
}

