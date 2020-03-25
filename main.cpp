#include <iostream>
#include <cmath>

#include "klib.array.h"
#include "klib.string.h"
#include "klib.number.h"
#include "derivative.h"
#include "calculation.h"

/* The method recieves user input from fisrt place */
void userRequest(string &, string &, unsigned);
/* The method calcalate the derivative value of implicit expression */
array<string> operation(string);
/* The mothod throw error when the errors was occured */
void error(string);

int main()
{
    /* parts of user input variables */
    string expr = "", numberOfDiff = "";

    /* parts of program variables */
    string blank;
    unsigned option;
    bool isFirstPass = false;

    /*  decorate here */
    std::cout << "     ___     ___     ___    _________    __           ________    ________      ___      ___    _________     \n";
    std::cout << "    [   ]   [    ]  [   ]  [   ______]  [  ]         [   _____]  [ ______ ]    [   ]    [   ]  [   ______]    \n";
    std::cout << "    [   ]  [  ][  ] [   ]  [   ______   [  ]         [  ]       [ ]      [ ]   [    ]  [    ]  [   ______     \n";
    std::cout << "     [   ][  ] [  ][   ]   [   ______]  [  ]         [  ]      [ ]        [ ]  [     ][  [  ]  [   ______]    \n";
    std::cout << "      [     ]   [     ]    [  |______   [  ]______   [  ]_____  [ ]______[ ]   [  ][ ][ ][  ]  [  ]______     \n";
    std::cout << "       [___]     [___]     [_________]  [_________]  [________]  [________]    [__] [__] [__]  [_________]    \n";
    std::cout << "                                            _____    ____                                                     \n";
    std::cout << "                                           [_   _]  [    ]                                                    \n";
    std::cout << "                                             | |    [ ][ ]                                                    \n";
    std::cout << "                                             |_|    [____]                                                    \n";
    std::cout << "                                                                                                              \n";
    std::cout << "     ________      __       __           ________    __     __    ________    ________      ___      ___      \n";
    std::cout << "    [   _____]    [  ]     [  ]         [   _____]  [  ]   [  ]  [   _____]  [ ______ ]    [   ]    [   ]     \n";
    std::cout << "    [  ]         [ ][ ]    [  ]         [  ]        [  ]   [  ]  [  ]       [ ]      [ ]   [    ]  [    ]     \n";
    std::cout << "    [  ]        [  __  ]   [  ]         [  ]        [  ]   [  ]  [  ]      [ ]        [ ]  [     ][  [  ]     \n";
    std::cout << "    [  ]_____  [  ]  [  ]  [  ]______   [  ]_____   [  ]___[  ]  [  ]_____  [ ]______[ ]   [  ][ ][ ][  ]     \n";
    std::cout << "    [________] [__]  [__]  [_________]  [________]  [_________]  [________]  [________]    [__] [__] [__]     \n";

    system("pause");
    system("cls");

    std::cout << "\nEnter f(x) = ";
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

    // ++ simplify each term
    string result = "";

    switch (option)
    {
    case 1: // Eval
    {
        array<string> terms_sep = operation(expr); //-(3x^2)

        double x; //3x^2 + 2x^3 + 3x^5
        std::cout << "Please enter x value to evaluate : ";
        std::cin >> x;
        unsigned short count = 0;

        double answer = cal(terms[0], x);

        for (unsigned short i = 0; i < terms_sep.length; i++)
        {
            if (terms_sep[i] == '+')
            {
                answer += cal(terms[i + 1], x);
                count++;
            }
            else if (terms_sep[i] == '-')
            {
                answer -= cal(terms[i + 1], x);
                count++;
            }
            else if (terms_sep[i] == '*')
            {
                answer *= cal(terms[i + 1], x);
                count++;
            }
            else if (terms_sep[i] == '/')
            {
                answer /= cal(terms[i + 1], x);
                count++;
            }
        }
        if (count == 0)
            answer = cal(terms[0], x);

        std::cout << "f(x) = " << answer;
    }
    break;
    case 2:
    { // Diff
        numberOfDiff += "'";
        result = exprDiff(terms, 'x');
    }
    break;
    case 3:
    { // Impl
        unsigned short choice;
        string impl_expr, pre_expr, post_expr;

        std::cout << "Please enter new expresion : "; // xy = ysin(x)
        getline(std::cin, impl_expr);
        sscanf(impl_expr, "%[^=] %s=%s", pre_expr, post_expr);

        array<string> pre_term = readExpr(pre_expr);   //xy
        array<string> post_term = readExpr(post_expr); //ysin(x)

        std::cout << "[1] to find dy/dx \t[2] to find dx/dy";
        std::cin >> choice;

        switch (choice)
        {
        case 1: //dy/dx
        {
            result = "dy/dx = ";
            for (unsigned short i = 0; i < pre_term.length; i++)
            {
                result += implFunc(pre_term[i], 'x');
            }
            for (unsigned i = 0; i < post_term.length; i++)
            {
                result += implFunc(post_term[i], 'x');
            }
        }
        case 2: //dx/dy
        {
            result = "dx/dy = ";
            for (unsigned short i = 0; i < terms.length; i++)
            {
                result += implFunc(terms[i], 'y');
            }
        }
        }
    }
    break;
        // ++ re-arrange the result; cleaner result
        expr = result;
    }
}

array<string> operation(string term)
{
    array<string> term_sep;
    int leftPar = 0, rightPar = 0;

    for (int i = 0; i < term.length; i++) //(2x^2)*3
    {
        if (term[i] == ')')
            rightPar++;
        if (term[i] == '(') //-2x+3
            leftPar++;
        if (leftPar == rightPar)
        {
            if (term[i] == '+')
                term_sep.push("+");
            if (term[i] == '-' && i != 0)
                term_sep.push("-");
            if (term[i] == '*' || term[i] == '(' || term[i] == ')') // 2(2x+3)
            {
                if (term[i] == '(')
                    leftPar++;
                if (term[i] == ')')
                    rightPar++;

                term_sep.push("*");
            }
            if (term[i] == '/')
                term_sep.push("/");
        }
    }
    return term_sep;
}

void error(string msg)
{
    std::cout << "Bad arithmetic expression: " << msg << ".\n\n";
    throw 0;
}
