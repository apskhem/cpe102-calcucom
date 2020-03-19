#include <iostream>
#include <cmath>

#include "klib.array.h"
#include "klib.string.h"
#include "klib.number.h"
#include "derivative.h"
#include "calculation.h"

/* The method recieves user input from fisrt place */
void userRequest(string &, string &, unsigned);
/* The method splits input expression into arrays of string */
array<string> readExpr(string);
/* The method calcalate the derivative value of implicit expression */
void implFunc(string);
array<string> operation(string);
/* The method classify what operation btw each term*/

int main()
{
    /* parts of user input variables */
    string expr = "", numberOfDiff = "";

    /* parts of program variables */
    string blank;
    unsigned option;
    bool isFirstPass = false;

    std::cout << "Enter f(x) = ";
    getline(std::cin, expr);

    while (true)
    {
        if (isFirstPass)
        {
            std::cout << "Press 'enter' to continue...";

            getline(std::cin, blank);
            std::cout << "------------------------------------------\n";
        }

        std::cout << "Press: \t[1] to evaluate the result.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n";

        if (isFirstPass)
        {
            std::cout << "\t[4] to try a new expression.\n\t[5] to end the program.\n";
        }

        std::cout << "=>\t";
        std::cin >> option;
        std::cin.ignore();

        if (option == 5)
            break;
        std::cout << "The result is...\n\n";

        switch (option)
        {
        case 1:
            userRequest(expr, numberOfDiff, 1);
            break;
        case 2:
            userRequest(expr, numberOfDiff, 2);
            break;
        case 3:
            userRequest(expr, numberOfDiff, 3);
            break;
        case 4:
        {
            std::cout << "Enter f(x) = ";
            getline(std::cin, expr);
            continue;
        }
        break;
        }

        if (option == 2)
            std::cout << "f^(" << numberOfDiff << ")(x) = ";
        std::cout << expr << "\n\n";

        isFirstPass = true;
    }

    return 0;
}

void userRequest(string &expr, string &numberOfDiff, unsigned option)
{
    array<string> terms = readExpr(expr);
    array<string> terms_sep = operation(expr);

    // ++ simplify each term
    string result = "";

    switch (option)
    {
    case 1:
    {             // Eval
        double x; //3x^2 + 2x^3 + 3x^5
        std::cout << "Please enter x value to evaluate : ";
        std::cin >> x;

        double answer = cal(terms[0], x);
        for (unsigned short i = 0; i < terms_sep.length; i++)
        {
            if (terms_sep[i] == '+')
                answer += cal(terms[i + 1], x);
            else if (terms_sep[i] == '-')
                answer -= cal(terms[i + 1], x);
            else if (terms_sep[i] == '*')
                answer *= cal(terms[i + 1], x);
            else if (terms_sep[i] == '/')
                answer /= cal(terms[i + 1], x);
        }
        std::cout << "f(x) = " << answer;
    }
    break;
    case 2:
    { // Diff
        numberOfDiff += "'";
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
    { //implicit cal

        float x, y;

        std::cout << "Please enter x and y values : ";
        std::cin >> x >> y;
        std::cout << "f(x) = ";
    }
        // ++ re-arrange the result; cleaner result
        expr = result;
    }
}

array<string> readExpr(string expr)
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
            terms.push(expr.slice(splitIndex, i));
            splitIndex = i + (expr[i] == '+' ? 1 : 0);

            if (expr[i] == '+')
                operation.push("+");
            if (expr[i] == '-')
                operation.push("-");
        }

        if (i >= expr.length - 1)
        {
            terms.push(expr.slice(splitIndex, expr.length));
        }
    }

    // check for errors
    if (leftPar != rightPar)
        throw "Bad arithmetic expression: no complete pair of parentheses ['()'].";

    return terms;
}

array<string> operation(string term)
{
    array<string> term_sep;
    int leftPar = 0, rightPar = 0;

    for (int i = 0; i < term.length; i++) //(2x^2)*3
    {
        if (term[i] == ')')
            rightPar++;
        if (term[i] == '(')
            leftPar++;
        if (leftPar == rightPar)
        {
            if (term[i] == '+')
                term_sep.push("+");
            if (term[i] == '-')
                term_sep.push("-");
            if (term[i] == '*' || term[i] == '(' || term[i] == ')') // 2(2x+3)
            {
                if(term[i] == '(')
                    leftPar++;
                if(term[i] == ')')
                    rightPar++;
                    
                term_sep.push("*");
            }
            if (term[i] == '/')
                term_sep.push("/");
        }
    }
    return term_sep;
}

void implFunc(string t)
{
    int choice;

    std::cout << "Press: \t[1] to evaluate dy/dx\n\t[2] to evaluate dx/dy\n";
    std::cout << "=>\t";
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1)
    { // dy/dx
        string result = "";
        readExpr(t);
    }

    else if (choice == 2)
    { //dx/dy
        string result = "";
        readExpr(t);
    }
    else
        std::cout << "Please enter 1 or 2";
}