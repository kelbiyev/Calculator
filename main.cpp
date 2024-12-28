#include <iostream>
#include "calculator.h"

using std::cin;
using std::cout;
using std::string;

int main() {

    cout << "Введите exit для выхода из программы. Выражения вводить без пробелов.\n";

    while (true) {
        cout << "Введите выражение: ";
        string str;
        std::getline(cin, str);

        if (str == "exit") {
            break;
        }

        if (str.empty()) {
            cout << "Ошибка: Введено пустое поле.\n";
            continue;
        }

        if (!isValidExpression(str)) {
            cout << "Ошибка: Выражение введено с ошибками.\n";
            continue;
        }

        try {
            double result = CalcBrackets(str);
            cout << "Результат: " << result << "\n";
        } catch (const std::exception& e) {
            cout << e.what() << "\n";
        }
    }

    return 0;
}
