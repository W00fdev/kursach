#ifndef KURSACH_POSTFIX_H
#define KURSACH_POSTFIX_H

#include <iostream>
#include <cmath>
#include "stack.h"

void read_expression(char* in, char* out, bool getline_input = true);

// ADDITIONAL

int find_str_len(const char* str) {
    int index = 0;
    while (str[index++] != '\0');
    return index;
}

// wrapper for tests don't do anything special
void read_expression(const char* in, char* out) {
    char* allocated_expression = new char[128];
    for (int i = 0; i < 128; i++) {
        allocated_expression[i] = in[i];
        if (in[i] == '\0') break;
    }

    read_expression(allocated_expression, out, false);

    delete [] allocated_expression;
}


// ADDITIONAL




/* Необходимо реализовать:
 *
 * аргументом (cos, sin, tg, ctg, ln, log, sqrt и др.
 * (хотя бы одну не из списка)),                        sh
 * константы pi, e открывающая и закрывающая скобки
 */


struct _operator {
    bool is_bracer = false;     // is openning bracer ?

    int priority = 0;   // for prefix func doesn't matter
    int operands_count = 0; // 1 == prefix func, 2 == binary op
    int op_size = 0;    // размер оператора в буквах
    char op[4]; // резерв в 4 символа для функций или арифмет.оператора == op[0]
};

void make_operator(_operator& op) {

    if (op.op_size == 1) {
       // arithmetical operator:
       op.operands_count = 2;
       if (op.op[0] == '+' || op.op[0] == '-') op.priority = 1;
       else if (op.op[0] == '*' || op.op[0] == '/') op.priority = 2;
       else if (op.op[0] == '^') op.priority = 3;
       else if (op.op[0] == '(') op.is_bracer = true;
       else throw std::invalid_argument("Error while binary operator making");

       return;
    }

    throw std::invalid_argument("Error while binary operator making");
}

void pop_operator(char* out, int& out_index, _stack<_operator>& stack_of_ops) {
    _operator current_op = stack_of_ops.pop();

    if (out_index != 0) {
        if (out[out_index - 1] != ' ')
            out[out_index++] = ' ';
    }

    for (int i = 0; i < current_op.op_size; i++) {
        out[out_index++] = current_op.op[i];
    }
    out[out_index++] = ' ';
}

void search_for_func(const char* in, int& in_index, _stack<_operator>& stack_of_ops) {
    _operator func_op;
    func_op.operands_count = 1; // function

    if (in[in_index] == 'l' && in[in_index + 1] == 'n')  {
        func_op.op_size = 2; func_op.op[0] = 'l'; func_op.op[1] = 'n';
        in_index++;
    }
    else if (in[in_index] == 't' && in[in_index + 1] == 'g') {
        func_op.op_size = 2; func_op.op[0] = 't'; func_op.op[1] = 'g';
        in_index++;
    }
    else if (in[in_index] == 's' && in[in_index + 1] == 'h') {
        func_op.op_size = 2; func_op.op[0] = 's'; func_op.op[1] = 'h';
        in_index++;
    }
    else if (in[in_index] == 'c' && in[in_index + 1] == 't' && in[in_index + 2] == 'g') {
        func_op.op_size = 3; func_op.op[0] = 'c'; func_op.op[1] = 't'; func_op.op[2] = 'g';
        in_index += 2;
    }
    else if (in[in_index] == 'c' && in[in_index + 1] == 'o' && in[in_index + 2] == 's') {
        func_op.op_size = 3; func_op.op[0] = 'c'; func_op.op[1] = 'o'; func_op.op[2] = 's';
        in_index += 2;
    }
    else if (in[in_index] == 's' && in[in_index + 1] == 'i' && in[in_index + 2] == 'n') {
        func_op.op_size = 3; func_op.op[0] = 's'; func_op.op[1] = 'i'; func_op.op[2] = 'n';
        in_index += 2;
    }
    else if (in[in_index] == 'l' && in[in_index + 1] == 'o' && in[in_index + 2] == 'g') {
        func_op.op_size = 3; func_op.op[0] = 'l'; func_op.op[1] = 'o'; func_op.op[2] = 'g';
        in_index += 2;
    }
    else if (in[in_index] == 's' && in[in_index + 1] == 'q' && in[in_index + 2] == 'r' && in[in_index + 3] == 't') {
        func_op.op_size = 4; func_op.op[0] = 's'; func_op.op[1] = 'q'; func_op.op[2] = 'r'; func_op.op[3] = 't';
        in_index += 3;
    }
    else {
        throw std::invalid_argument("Error function making");
    }

    stack_of_ops.push(func_op);
}

bool check_unary_minus(const char* in, int in_index) {
    if (in_index == 0) return true;     // expr:- 1
    if (in_index == 1) throw std::invalid_argument("Space symbol missed before unary minus");
    if (isdigit(in[in_index - 2])) return false;    // expr:2 - 3

    return true;
}

bool is_op(char s) {
    return s == '+' || s == '-' || s == '*' || s == '/' || s == '^';
}

bool is_func(char s) {
    return (s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z');
}

void read_expression(char* in, char* out, bool getline_input) {
    if (getline_input)
        std::cin.getline(in, 128);

    int expr_size = find_str_len(in);


    for (int i = 0; i < expr_size; i++) {
        in[i] = char(tolower(in[i]));
    }

    char s; // считанный символ
    int out_index = 0;
    _stack<_operator> stack_of_ops;

    for (int i = 0; i < expr_size; i++) {
        s = in[i];
        _operator current_op;

        if (isdigit(s) || s == '.' || s == 'e') {                         // NUM READING
            out[out_index++] = s;
        }
        else if (s == 'p') {                                              // PI READING
            if (i < expr_size - 1) {
                if (in[i+1] == 'i') {
                    out[out_index++] = 'p';
                    out[out_index++] = 'i';
                    i++;
                    continue;;
                }
            }

            throw std::runtime_error("Can't parse pi");
        }
        else if (s == '(') {
            current_op.op[current_op.op_size++] = s;
            make_operator(current_op);
            stack_of_ops.push(current_op);
        }
        else if (s == ')') {
            bool bracer_found = false;
            while (stack_of_ops.get_size() > 0) {
                if (stack_of_ops.top().is_bracer) {
                    stack_of_ops.pop();                         // remove openning bracer from stack
                    bracer_found = true;
                    break;
                }

                pop_operator(out, out_index, stack_of_ops);
            }

            if (!bracer_found)
                throw std::invalid_argument("Bracers error: waste closing bracer");
        }
        else if (is_op(s)) {                                           // BINARY OPERATOR READING
            current_op.op[current_op.op_size++] = s;

            if (s == '-' && check_unary_minus(in, i)) {
                make_operator(current_op);
                current_op.operands_count = 1;          // is a prefix minus
                out[out_index++] = '0';                 // add a null
            }
            else {
                make_operator(current_op);
                while (stack_of_ops.get_size() > 0) {
                    if (stack_of_ops.top().priority < current_op.priority // if o1 > o2 priority pop.
                        && stack_of_ops.top().operands_count == 2) {           // if top() == func
                        break;
                    }
                    pop_operator(out, out_index, stack_of_ops);
                }
            }

            stack_of_ops.push(current_op);
        }
        else if (is_func(s)) {                                         // FUNCTION READING
            search_for_func(in, i, stack_of_ops);
        }
        else if (s == ' ') {                                            // SEPARATOR READING
            if (out_index != 0) {
                if (out[out_index - 1] != ' ')
                    out[out_index++] = s;
            }
        } else if (s != '\0') {
            throw std::invalid_argument("Unknown symbol");
        }
    }

    while (stack_of_ops.get_size() > 0) {
        if (stack_of_ops.top().is_bracer)
            throw std::invalid_argument("wrong number of bracers");
        pop_operator(out, out_index, stack_of_ops);
    }


    out[out_index] = '\0';
    // В конце цикла вставить \0 в конец строки.
}


double compute_op(_operator& op, _stack<double>& stack_numbers) {
    if (stack_numbers.get_size() < op.operands_count) throw std::invalid_argument("Don't have enough operands");

    if (op.operands_count == 2) {
        // arithmetical operator

        if (op.op[0] == '+') return stack_numbers.pop() + stack_numbers.pop();
        if (op.op[0] == '-') {
            double b = stack_numbers.pop();
            double a = stack_numbers.pop();
            return a - b;
        }
        if (op.op[0] == '*') return stack_numbers.pop() * stack_numbers.pop();
        if (op.op[0] == '/') return 1 / stack_numbers.pop() * stack_numbers.pop();
        if (op.op[0] == '^') {
            double b = stack_numbers.pop();
            double a = stack_numbers.pop();
            return pow(a, b);
        }

        throw std::invalid_argument("Unknown arithmetical operator");
    }
    else if (op.operands_count == 1) {

        if (op.op_size == 2) {
            if (op.op[0] == 'l' && op.op[1] == 'n') {
                return log(stack_numbers.pop());
            } else if (op.op[0] == 't' && op.op[1] == 'g') {
                return tan(stack_numbers.pop());
            } else if (op.op[0] == 's' && op.op[1] == 'h') {
                double x = stack_numbers.pop();
                double e = exp(1.0);
                return (pow(e, x) - pow(e, -x)) / 2.0;
            }
        }
        else if (op.op_size == 3) {
            if (op.op[0] == 'c' && op.op[1] == 't' && op.op[2] == 'g') {
                return 1 / tan(stack_numbers.pop());
            }
            else if (op.op[0] == 'c' && op.op[1] == 'o' && op.op[2] == 's') {
                return cos(stack_numbers.pop());
            }
            else if (op.op[0] == 's' && op.op[1] == 'i' && op.op[2] == 'n') {
                return sin(stack_numbers.pop());
            }
            else if (op.op[0] == 'l' && op.op[1] == 'o' && op.op[2] == 'g') {
                return log10(stack_numbers.pop());
            }
        }
        else if (op.op_size == 4) {
            if (op.op[0] == 's' && op.op[1] == 'q' && op.op[2] == 'r' && op.op[3] == 't') {
                return sqrt(stack_numbers.pop());
            }
        }

        throw std::invalid_argument("Unknown function");
    }

    throw std::invalid_argument("Number of operands in operator error");
}

double compute_expression(char* out) {
    int precision = 1;
    bool point_reached = false;         // for stack_numbers
    bool start_reading_num = true;
    _stack<double> stack_numbers;

    int index = 0;
    double num_for_read = 0.0;

    while (out[index] != '\0') {
        char s = out[index];
        if (isdigit(s)) {
            start_reading_num = true;
            if (!point_reached) {
                num_for_read *= 10;
                num_for_read += (s - '0');
            } else {
                precision *= 10;
                num_for_read += (s - '0') / (double) precision;
            }
        } else if (s == '.') {
            point_reached = true;
        } else if (s == ' ') {
            if (start_reading_num)
                stack_numbers.push(num_for_read);

            num_for_read = 0.0;
            precision = 1;
            start_reading_num = false;
            point_reached = false;
        } else if (s == 'e') {
            stack_numbers.push(2.71828);
        } else if (s == 'p') {
            if (out[++index] == 'i')
                stack_numbers.push(3.1418);
            else
                throw std::invalid_argument("Error pi reading");
        }
        else if (is_op(s)) {
            _operator op;
            op.op[op.op_size++] = s;
            make_operator(op);
            double op_result = compute_op(op, stack_numbers);
            stack_numbers.push(op_result);
        } else if (is_func(s)) {
            _stack<_operator> stack_of_ops;
            search_for_func(out, index, stack_of_ops);
            double func_result = compute_op(stack_of_ops.top(), stack_numbers);
            stack_numbers.push(func_result);
        }
        index++;
    }

   return stack_numbers.pop();
}


#endif //KURSACH_POSTFIX_H
