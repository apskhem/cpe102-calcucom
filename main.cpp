#include <iostream>
#include <cmath>
#include <vector>

#include "klib.string.h"
#include "klib.number.h"
#include "klib.array.h"

typedef unsigned short uint2;
typedef unsigned int uint4;
typedef unsigned long long uint8;
typedef short int2;
typedef int int4;
typedef long long int8;
typedef float float4;
typedef double float8;
typedef long double float12;

#include "utility.h"
#include "derivative.h"

// Khem's Functiions
void UserRequest(string, uint2);
vector<string> ReadExpr(string);

// Leng's Functions
void PrintResult(vector<string>, uint2);
void ImplicitFunc(string);
float cal(string, float);
float implicit_cal(string, float, float);

// Dan's Functions

// Mhee's Functions

int main() {
    string expr, blank;
    uint2 option;

    do {
        std::cout << "Enter f(x) = ";
        std::getline(std::cin, expr);

        std::cout << "Press: \t[1] to evaluate the function.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n";
        std::cout << "=>\t";
        std::cin >> option;
        std::cin.ignore();

        std::cout << "The result is...\n\n";

        switch (option) {
            case 1: UserRequest(expr, 1); break;
            case 2: UserRequest(expr, 2); break;
            case 3: UserRequest(expr, 3); break;
        }

        std::cout << "Press 'enter' to continue...";
        std::getline(std::cin, blank);
        std::cout << "\n";

        std::cout << "Press: \t[1] to evaluate the result.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n\t";
        std::cout << "[4] to try a new expression.\n\t[5] to end the program.\n";
        std::cout << "=>\t";
        std::cin >> option;
        std::cin.ignore();

    } while (option != 5);

    return 0;
}

void UserRequest(string expr, uint2 option) {
    vector<string> terms = ReadExpr(expr);

    // ++ simplify each term

    string result = "";
    double cal_equation = 0;

    switch (option) {
        case 1: { // Eval
            float x;
            std::cout << "Please enter x value to evaluate : ";
            std::cin >> x;
            for (unsigned short i = 0; i < term.size(); i++)
            {
                cal_equation += cal(terms[i], x);
            }
            std::cout << "f(x) = " << cal_equation;
        }
        break;
        case 2: { // Diff
            result = "f'(x) = ";
            for (uint2 i = 0; i < terms.size(); i++) {
                if (i > 0 && terms[i][0] != '-')
                    result += "+";

                result += Diff(terms[i], 'x');
            }
        }
        break;
        case 3: { // Impl
            result = "dy/dx = ";
        }
        break;
        case 4: { //Implicit
            result = "dx/dy = ";
        }
        case 5: {

            float x, y;

            std::cout << "Please enter x and y values : ";
            std::cin >> x >> y;
            std::cout << "f(x) = " << implicit_cal(terms, x, y);
        }
    }

    // ++ re-arrange the result; cleaner result

    std::cout << result << "\n\n";
}

vector<string> ReadExpr(string expr)
{
    vector<string> terms;

    uint2 leftPar = 0, rightPar = 0;

    // pre-reading process
    StrRemoveSpace(expr);

    // reading equation process
    uint2 splitIndex = 0;
    for (uint2 i = 0; i < expr.size(); i++) {
        if (expr[i] == '(')
            leftPar++;
        else if (expr[i] == ')')
            rightPar++;

        if ((expr[i] == '+' || expr[i] == '-') && expr[i - 1] != '^' && leftPar == rightPar) {
            terms.push_back(StrSplice(expr, splitIndex, i));
            splitIndex = i + (expr[i] == '+' ? 1 : 0);
        }

        if (i >= expr.size() - 1) {
            terms.push_back(StrSplice(expr, splitIndex, expr.size()));
        }
    }

    // check for errors
    if (leftPar != rightPar)
        throw "Bad arithmetic expression: no complete pair of parentheses ['()'].";

    return terms;
}

float cal(string term, float x) {
    double result = 0;

    for (unsigned short i = 0; i < term.size(); i++) {
        if (term[i] == 'x')
            term[i] = x;
