#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "utility.h"
#include "derivative.h"
using namespace std;

// Khem's Functiions
void UserRequest(string, unsigned short);
vector<string> ReadExpr(string);

// Leng's Functions
void PrintResult(vector<string>, unsigned short);
void ImplicitFunc(string);
float cal(string, float);
float implicit_cal(string, float, float);

// Dan's Functions

// Mhee's Functions

int main()
{
    string expr, blank;
    unsigned short option;

    do
    {
        cout << "Enter f(x) = ";
        getline(cin, expr);

        cout << "Press: \t[1] to evaluate the function.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n";
        cout << "=>\t";
        cin >> option;
        cin.ignore();

        cout << "The result is...\n\n";

        switch (option)
        {
            case 1:
                UserRequest(expr, 1);
                break;
            case 2:
                UserRequest(expr, 2);
                break;
            case 3:
                UserRequest(expr, 3);
                break;
        }

        cout << "Press 'enter' to continue...";
        getline(cin, blank);
        cout << endl;

        cout << "Press: \t[1] to evaluate the result.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n\t";
        cout << "[4] to try a new expression.\n\t[5] to end the program.\n";
        cout << "=>\t";
        cin >> option;
        cin.ignore();

    } while (option != 5);

    return 0;
}

void UserRequest(string expr, unsigned short option)
{

    vector<string> terms;
    terms = ReadExpr(expr);

    // ++ simplify each term

    string result = "";
    float cal_equation = 0;

    switch (option)
    {
        case 1:
        { // Eval
            float x;
            cout << "Please enter x value : ";
            cin >> x;
            cout << "f(x) = " << cal(terms, x);
        }
        break;
        case 2:
        { // Diff
            result = "f'(x) = ";
            for (unsigned short i = 0; i < terms.size(); i++)
            {
                result += Diff(terms[i], 'x') + signs[i];
            }
        }
        break;
        case 3:
        { // Impl
            result = "dy/dx = ";
        }
        break;
        case 4:
        { //Implicit
            result = "dx/dy = ";
        }
        case 5:
        {

            float x, y;

            cout << "Please enter x and y values : ";
            cin >> x >> y;
            cout << "f(x) = " << implicit_cal(terms, x, y);
    }
    }

    // ++ re-arrange the result; cleaner result

    cout << result << "\n\n";
}

vector<string> ReadExpr(string expr)
{
    vector<string> terms;
    string signs = "";

    unsigned short leftPar = 0, rightPar = 0;

    // pre-reading process
    StrRemoveSpace(expr);

    // reading equation process
    unsigned short splitIndex = 0;
    for (unsigned short i = 0; i < expr.size(); i++)
    {
        if (expr[i] == '(')
            leftPar++;
        else if (expr[i] == ')')
            rightPar++;

        if ((expr[i] == '+' || expr[i] == '-') && expr[i - 1] != '^' && leftPar == rightPar)
        {
            terms.push_back(StrSplice(expr, splitIndex, i));
            signs += expr[i];
            splitIndex = i + 1;
        }

        if (i >= expr.size() - 1)
        {
            terms.push_back(StrSplice(expr, splitIndex, expr.size()));
        }
    }

    // check for errors
    if (leftPar != rightPar)
        throw "Bad arithmetic expression: no complete pair of parentheses ['()'].";

    return terms;
}

float cal(string t, float x)
{
    float cal_result = 0;

    for (int i = 0; i < t.size(); i++)
    {

        if (t[i] = "x")
            t[i] = x;

        cal_result += ;
    }

    return cal_result;
}

float implicit_cal(string t, float x, float y)
{

    float cal_result = 0;

    for (int i = 0; i < t.size(); i++)
        if (t[i] = "x")
            t[i] = x;
    if (t[i] = "y")
        t[i] = y;

    cal_result += "";
}

void ImplicitFunc(string t)
{
    int choice;

    cout << "Press: \t[1] to evaluate dy/dx\n\t[2] to evaluate dx/dy\n";
    cout << "=>\t";
    cin >> choice;
    cin.ignore();

    if (choice == 1)
    { // dy/dx
        string result = "";
        ReadExpr(t);
    }

    else if (choice == 2)
    { //dx/dy
        string result = "";
        ReadExpr(t);
    }
    else
        cout<<"Please enter 1 or 2";
}