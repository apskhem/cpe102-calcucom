#include <iostream>
#include <cmath>

#include "klib.array.h"
#include "klib.string.h"
#include "klib.number.h"
#include "derivative.h"

void UserRequest(string, unsigned);
array<string> ReadExpr(string);
void PrintResult(array<string>, unsigned);
void ImplicitFunc(string);
float cal(string, float);
float implicit_cal(string, float, float);
void classified_var(string);

const double PI = 3.14159;

struct variable
{
    string n;
    string e;
    string u;
    string func;
};

int main()
{
    string expr, blank;
    unsigned option;

    do
    {
        std::cout << "Enter f(x) = ";
        std::getline(std::cin, expr);

        std::cout << "Press: \t[1] to evaluate the function.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n";
        std::cout << "=>\t";
        std::cin >> option;
        std::cin.ignore();

        std::cout << "The result is...\n\n";

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

void UserRequest(string expr, unsigned option)
{
    array<string> terms = ReadExpr(expr);

    // ++ simplify each term

    string result = "";
    double cal_equation = 0;

    switch (option)
    {
    case 1:
    { // Eval
        float x;
        std::cout << "Please enter x value to evaluate : ";
        std::cin >> x;
        for (unsigned short i = 0; i < terms.length; i++)
        {
            if (operation[i] == "+")
            {
                classified_var(terms);
                cal_equation += cal(terms[i], x);
            }
            else if (operation[i] == "-")
            {
                classified_var(terms);
                cal_equation -= cal(terms[i], x);
            }
        }
        std::cout << "f(x) = " << cal_equation;
    }
    break;
    case 2:
    { // Diff
        result = "f'(x) = ";
        for (unsigned i = 0; i < terms.length; i++)
        {
            if (i > 0 && terms[i][0] != '-')
                result += "+";

            result += Diff(terms[i], 'x');
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

        std::cout << "Please enter x and y values : ";
        std::cin >> x >> y;
        std::cout << "f(x) = " << implicit_cal(terms, x, y);
    }
    }

    // ++ re-arrange the result; cleaner result

    std::cout << result << "\n\n";
}

array<string> ReadExpr(string expr)
{
    array<string> terms;
    array<string> operation;

    unsigned leftPar = 0, rightPar = 0;

    // pre-reading process
    expr = expr.replace(" ", "");

    // reading equation process
    unsigned splitIndex = 0;
    for (unsigned i = 0; i < expr.length; i++)
    {
        if (expr[i] == '(')
            leftPar++;
        else if (expr[i] == ')')
            rightPar++;

        if ((expr[i] == '+' || expr[i] == '-') && expr[i - 1] != '^' && leftPar == rightPar)
        {
            terms.push_back(expr.slice(splitIndex, i));
            splitIndex = i + (expr[i] == '+' ? 1 : 0);

            if (expr[i] == '+')
                operation.push_back("+");
            if (expr[i] == '-')
                operation.push_back("-");
        }

        if (i >= expr.length - 1)
        {
            terms.push_back(expr.slice(expr, splitIndex, expr.length));
        }
    }

    // check for errors
    if (leftPar != rightPar)
        throw "Bad arithmetic expression: no complete pair of parentheses ['()'].";

    return terms;
}

void classified_var(string term)
{
    string n = "", u = "", e = "";
    unsigned int leftPar = 0, rightPar = 0;

    for (unsigned int i = 0; i < term.length; i++)
    {
        if (term[i] == '^') //x^
        {
            if (term[i + 1] != '(') //x^328
            {
                i++; //skip ^
                while (isNum(term[i]))
                {
                    n += term[i];
                    i++;
                }
            }
            else //x^(328)
            {
                i += 2; //skip ^(
                leftPar++;
                while (leftPar != rightPar)
                {
                    if (term[i] == '(')
                        leftPar++;
                    if (term[i] == ')')
                        rightPar++;

                    n += term[i];
                    i++;
                }
            }
        }
        else if (term[i] == '(')
        {
            i++; //skip (
            leftPar++;
            while (leftPar != rightPar)
            {
                if (term[i] == '(')
                    leftPar++;
                if (term[i] == ')')
                    rightPar++;

                u += term[i];
                i++;
            }
        }
        if (term[i] == 'l')
        {
            if (term[i + 1] == 'n') //ln
            {
                i++; //skip n
                while (isNum(term[i]))
                {
                    e += term[i];
                    i++;
                }
            }
            else if (term[i + 2] == 'g') //log
            {
                i += 2; //skip og
                while (isNum(term[i]))
                {
                    e += term[i];
                    i++;
                }
            }
        }
    }
    variable value = {n, e, u};
}

float cal(string term, float x)
{
    double result = 0, func_sum = 0;
    float a = parseNum(term);
    float a_n = parseNum(n);
    float a_u = parseNum(u);

    for (unsigned short i = 0; i < n.length; i++)
    {
        if (n[i] == 'x' ){
            
        }

        else if(n[i] == 'x'){
            n[i] = a_n * x;
        }
    }

    for(unsigned short i = 0; i< u.length; i++){

        if (u[i] == 'x'){
            u[i] = a_u * x
        }
    }

    for (unsigned short i = 0; i < term.length; i++)
    {
        if (term[i] == 'x')
            term[i] = x;
        else if (term[i] == '+')
            result = ;
        else if (term[i] == '-')
            else if (term[i] == '*') else if (term[i] == '/')

                else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i + 4 < term.length) //trigon
            {
                string tfunc = term.slice(i, i + 3);
                if (tfunc == "sin")
                {
                    result = a * sin(u * 180 / PI);
                }
                else if (tfunc == "cos")
                {
                    result = a * cos(u * 180 / PI);
                }
                else if (tfunc == "tan")
                {
                    result = a * tan(u * 180 / PI);
                }
                else if (tfunc == "cot")
                {
                    result = a / tan(u * 180 / PI);
                }
                else if (tfunc == "sec")
                {
                    result = a / cos(u * 180 / PI);
                }
                else if (tfunc == "csc")
                {
                    result = a / sin(u * 180 / PI);
                }
            }
        else if (term[i] == 'l')
        {
            if (term[i + 1] == 'n')
            { //ln
                result = a * log()
            }
            else
            { //log
                result = a * log
            }
        }
    }
    return result;
}


float implicit_cal(string t, float x, float y)
{

    for (int i = 0; i < t.length; i++)
    {
        if (t[i] == 'x')
            t[i] = x;
        if (t[i] == 'y')
            t[i] = y;
    }
    cal_result += "";
}

void ImplicitFunc(string t)
{
    int choice;

    std::cout << "Press: \t[1] to evaluate dy/dx\n\t[2] to evaluate dx/dy\n";
    std::cout << "=>\t";
    std::cin >> choice;
    std::cin.ignore();

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
        std::cout << "Please enter 1 or 2";
}
