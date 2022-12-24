// реализация пользовательского приложения
#include"arithmetic.h"

int main()
{
    string line("\n----------------------------------------------------------\n");
    cout << line << "Enter an arifmetic expression: " << line;
    string expr;
    getline(cin, expr);
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
    try
    {
        TPostfix arifm(expr);
        arifm.toPostfix();
        int choice = 1;
        do
        {
            cout << line << "Result: " << arifm.calculate() << line;
            cout << line << "Enter 1 to calculate with new parameters" << endl;
            cout << "Or 0 to stop work with the current expression: ";
            cin >> choice;
        } while (choice);
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }

    return 0;
}
