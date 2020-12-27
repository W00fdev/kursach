/* Вариант 1
 * Преобразование алгебраических формул из инфиксной в постфиксную форму записи и вычисление значения выражения
 *
 */

#include <iostream>
#include <gmock/gmock.h>
//#include "postfix.h"

using namespace std;

int main() {
//
//    char* char_expression_in = new char[128];
//    char* char_expression_out = new char[128];
//
//    read_expression(char_expression_in, char_expression_out);
//
//    cout << char_expression_out << endl;
//    cout << "Result: " << compute_expression(char_expression_out);
//
//
//    delete[] char_expression_in;
//    delete[] char_expression_out;

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}





















//
////Пример ввода: 8 9 + 1 7 - *
//
////______Реализация______
//// Рассчёт ОПЗ:
//
//#include <iostream>
//#include <string>
//#include <functional>
//#include <vector>
//#include <map>
//#include <cctype>
//
//using namespace std;
//
//int main()
//{
//    map<char, function<int64_t(const int64_t&, const int64_t&)>> operations;
//    operations['+'] = [](const int64_t& a, const int64_t& b) { return a + b; };
//    operations['-'] = [](const int64_t& a, const int64_t& b) { return a - b; };
//    operations['*'] = [](const int64_t& a, const int64_t& b) { return a * b; };
//    operations['/'] = [](const int64_t& a, const int64_t& b) { return a / b; };
//
//    string expression;
//    vector<int64_t> stack_;
//    int64_t number = 0;
//    bool flag = true;
//
//    getline(cin, expression);
//
//    for (const auto& i : expression)
//    {
//        if (isdigit(i))
//        {
//            number *= 10;
//            number += (i - '0');
//            flag = true;
//        }
//        else
//        {
//            if (i != ' ')
//            {
//                int64_t num2 = stack_.back();
//                stack_.pop_back();
//                int64_t num1 = stack_.back();
//                stack_.pop_back();
//
//                stack_.push_back(operations[i](num1, num2));
//                flag = false;
//            }
//            else if (i == ' ' && flag)
//            {
//                stack_.push_back(number);
//                number = 0;
//            }
//        }
//    }
//
//    cout << stack_.back();
//
//    return 0;
//}