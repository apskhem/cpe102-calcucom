#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;
#include "klib.string.h"
#include "klib.number.h"
#include "klib.array.h"

typedef unsigned short uint2;
typedef unsigned int uint4;
@@ -32,38 +33,36 @@ float implicit_cal(string, float, float);

// Mhee's Functions

int main()
{
int main() {
    string expr, blank;
    uint2 option;

    do
    {
        cout << "Enter f(x) = ";
        getline(cin, expr);
    do {
        std::cout << "Enter f(x) = ";
        std::getline(std::cin, expr);

        cout << "Press: \t[1] to evaluate the function.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n";
        cout << "=>\t";
        cin >> option;
        cin.ignore();
        std::cout << "Press: \t[1] to evaluate the function.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n";
        std::cout << "=>\t";
        std::cin >> option;
        std::cin.ignore();

        cout << "The result is...\n\n";
        std::cout << "The result is...\n\n";

        switch (option) {
            case 1: UserRequest(expr, 1); break;
            case 2: UserRequest(expr, 2); break;
            case 3: UserRequest(expr, 3); break;
        }

        cout << "Press 'enter' to continue...";
        getline(cin, blank);
        cout << endl;
        std::cout << "Press 'enter' to continue...";
        std::getline(std::cin, blank);
        std::cout << "\n";

        cout << "Press: \t[1] to evaluate the result.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n\t";
        cout << "[4] to try a new expression.\n\t[5] to end the program.\n";
        cout << "=>\t";
        cin >> option;
        cin.ignore();
        std::cout << "Press: \t[1] to evaluate the result.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n\t";
        std::cout << "[4] to try a new expression.\n\t[5] to end the program.\n";
        std::cout << "=>\t";
        std::cin >> option;
        std::cin.ignore();

    } while (option != 5);

@@ -81,13 +80,13 @@ void UserRequest(string expr, uint2 option) {
    switch (option) {
        case 1: { // Eval
            float x;
            cout << "Please enter x value to evaluate : ";
            cin >> x;
            std::cout << "Please enter x value to evaluate : ";
            std::cin >> x;
            for (unsigned short i = 0; i < term.size(); i++)
            {
                cal_equation += cal(terms[i], x);
            }
            cout << "f(x) = " << cal_equation;
            std::cout << "f(x) = " << cal_equation;
        }
        break;
        case 2: { // Diff
@@ -111,15 +110,15 @@ void UserRequest(string expr, uint2 option) {

            float x, y;

            cout << "Please enter x and y values : ";
            cin >> x >> y;
            cout << "f(x) = " << implicit_cal(terms, x, y);
            std::cout << "Please enter x and y values : ";
            std::cin >> x >> y;
            std::cout << "f(x) = " << implicit_cal(terms, x, y);
        }
    }

    // ++ re-arrange the result; cleaner result

    cout << result << "\n\n";
    std::cout << result << "\n\n";
}

vector<string> ReadExpr(string expr)
@@ -139,14 +138,12 @@ vector<string> ReadExpr(string expr)
        else if (expr[i] == ')')
            rightPar++;

        if ((expr[i] == '+' || expr[i] == '-') && expr[i - 1] != '^' && leftPar == rightPar)
        {
        if ((expr[i] == '+' || expr[i] == '-') && expr[i - 1] != '^' && leftPar == rightPar) {
            terms.push_back(StrSplice(expr, splitIndex, i));
            splitIndex = i + (expr[i] == '+' ? 1 : 0);
        }

        if (i >= expr.size() - 1)
        {
        if (i >= expr.size() - 1) {
            terms.push_back(StrSplice(expr, splitIndex, expr.size()));
        }
    }
@@ -158,27 +155,22 @@ vector<string> ReadExpr(string expr)
    return terms;
}

float cal(string term, float x)
{
float cal(string term, float x) {
    double result = 0;

    for (unsigned short i = 0; i < term.size(); i++)
    {
    for (unsigned short i = 0; i < term.size(); i++) {
        if (term[i] == 'x')
            term[i] = x;
        else if (term[i] == 's' || term[i] == 'c' || term[i] == 't')
        {
        else if (term[i] == 's' || term[i] == 'c' || term[i] == 't') {

        }
    }
    return result;
}

float implicit_cal(string t, float x, float y)
{
float implicit_cal(string t, float x, float y) {

    for (int i = 0; i < t.size(); i++)
    {
    for (int i = 0; i < t.size(); i++) {
        if (t[i] == 'x')
            t[i] = x;
        if (t[i] == 'y')
@@ -187,26 +179,23 @@ float implicit_cal(string t, float x, float y)
    cal_result += "";
}

void ImplicitFunc(string t)
{
void ImplicitFunc(string t) {
    int choice;

    cout << "Press: \t[1] to evaluate dy/dx\n\t[2] to evaluate dx/dy\n";
    cout << "=>\t";
    cin >> choice;
    cin.ignore();
    std::cout << "Press: \t[1] to evaluate dy/dx\n\t[2] to evaluate dx/dy\n";
    std::cout << "=>\t";
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1)
    { // dy/dx
    if (choice == 1) { // dy/dx
        string result = "";
        ReadExpr(t);
    }

    else if (choice == 2)
    { //dx/dy
    else if (choice == 2) { //dx/dy
        string result = "";
        ReadExpr(t);
    }
    else
        cout << "Please enter 1 or 2";
        std::cout << "Please enter 1 or 2";
} 