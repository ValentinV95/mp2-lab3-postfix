// реализация пользовательского приложения
#include"arithmetic.h"

int main()
{
    string line("\n----------------------------------------------------------\n");
    cout << line << "Enter an arifmetic expression: " << line;
    string expr;
    cin >> expr;
    try
    {
        TPostfix arifm(expr);
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
