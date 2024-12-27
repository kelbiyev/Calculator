#include "calc.h"
#include <stdexcept>

using std::string;

bool isValidExpression(const string& str) {
    bool lastOperator = false;
    int openBrackets = 0;
    bool lastPoint = false;
    int pointCount = 0;

    for (size_t i = 0; i < str.size(); ++i) {
        char s = str[i];
        if (s == ' ') {
            return false;
        }
        if (isdigit(s) || s == '.') {
            if (s == '.' && lastPoint == true) {
                return false; 
            }
            if (s == '.' && lastPoint == false) {
                lastPoint = true;
                ++pointCount; 
            }
            if (isdigit(s)) {
                lastPoint = false;
            }
            if (pointCount > 1) { 
                return false;
            }
            lastOperator = false;
        } else if (s == '+' || s == '-' || s == '*' || s == '/' || s == '^') {
            lastPoint = false;
            pointCount = 0; 
            if (lastOperator && s != '-') return false;
            if (s == '-' && (i == 0 || str[i - 1] == '(' || !isdigit(str[i - 1]))) {
                lastOperator = false;
            } else {
                lastOperator = true;
            }
        } else if (s == '(') {
            lastPoint = false;
            pointCount = 0;
            ++openBrackets;
            lastOperator = true;
        } else if (s == ')') {
            lastPoint = false;
            pointCount = 0; 
            if (openBrackets == 0 || lastOperator) {
                return false;
            }
            --openBrackets;
            lastOperator = false;
        } else if (!isspace(s)) {
            return false;
        }
    }

    return openBrackets == 0 && !lastOperator;
}

double Calculate(const string& str) {
    string temp = "";
    std::vector<double> numbers;
    std::vector<char> operations;

    for (size_t i = 0; i < str.size(); ++i) {
        char s = str[i];
        if (isdigit(s) || s == '.') {
            temp += s;
        } else if (s == '-' && (i == 0 || str[i - 1] == '(' || !isdigit(str[i - 1]))) {

            temp += s;
        } else if (s == '+' || s == '-' || s == '*' || s == '/' || s == '^') {
            if (!temp.empty()) {
                numbers.push_back(std::stod(temp));
                temp = "";
            }
            operations.push_back(s);
        }
    }
    if (!temp.empty()) {
        numbers.push_back(std::stod(temp));
    }

    for (size_t i = 0; i < operations.size(); ++i) {
        if (operations[i] == '*' || operations[i] == '/' || operations[i] == '^') {
            double result;
            if (operations[i] == '*') {
                result = numbers[i] * numbers[i + 1];
            } else if (operations[i] == '/') {
                if (numbers[i + 1] == 0) {
                    throw std::runtime_error("Error: Division by zero!");
                }
                result = numbers[i] / numbers[i + 1];
            } else if (operations[i] == '^') {
                result = pow(numbers[i], numbers[i + 1]);
            }
            numbers[i] = result;
            numbers.erase(numbers.begin() + i + 1);
            operations.erase(operations.begin() + i);
            --i;
        }
    }

    double result = numbers[0];
    for (size_t i = 0; i < operations.size(); ++i) {
        if (operations[i] == '+') {
            result += numbers[i + 1];
        } else if (operations[i] == '-') {
            result -= numbers[i + 1];
        }
    }

    return result;
}
double CalcBrackets(string str) {
    std::stack<size_t> brackets; 
    if(!isValidExpression(str)) {
        throw std::runtime_error("Error");
    }
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '(') {
            brackets.push(i);
        } else if (str[i] == ')') {
            if (brackets.empty()) throw std::runtime_error("Error");

            size_t openIndex = brackets.top();
            brackets.pop();

            string subExpression = str.substr(openIndex + 1, i - openIndex - 1);
            double result = CalcBrackets(subExpression);

            str.replace(openIndex, i - openIndex + 1, std::to_string(result));
            i = openIndex + std::to_string(result).size() - 1;
        }
    }

    return Calculate(str);
}
