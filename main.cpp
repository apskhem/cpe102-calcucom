#include <iostream>

void error(const char * msg) {
    std::cout << "Bad arithmetic expression: " << msg << ".\n\n";
    throw 0;
}

#include "klib.array.h"
#include "klib.string.h"
#include "klib.number.h"
#include "engine.base.h"
#include "engine.eval.h"
// #include "engine.lim.h"
// #include "engine.mhee.h"

string numOfDiff(const unsigned &num);

int main() {
    /* parts of user input variables */
    string expr = "";
    char var;
    unsigned numberOfDiff = 0;

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

    std::cout << "Press 'enter' to continue...";
    getline(std::cin, blank);

    // run first menu
    std::cout << "\nIndependent variable (single character)\n";
    std::cout << "=>\t";
    std::cin >> var;
    std::cout << "Enter f(" << var << ") = ";
    getline(std::cin, expr);

    while (true) {
        if (isFirstPass) {
            std::cout << "Press 'enter' to continue...";
            getline(std::cin, blank);
            std::cout << "------------------------------------------\n";
        }

        std::cout << "Mode: \t[1] Evaluate the expression.";
        std::cout << "\t[2] Derivative the expression.\n";
        std::cout << "\t[3] Implicit derivative the expression.\n";
        std::cout << "\t[4] Find tangent\n";
        std::cout << "\t[5] Find relative min/max\n";
        std::cout << "\t[6] Show Graph\n";
        std::cout << "\t[7] Try a new expression.\n";
        std::cout << "\t[8] End program.\n";

        std::cout << "=>\t";
        std::cin >> option;
        std::cin.ignore();

        if (option == 8) break;
        std::cout << "The result is...\n\n";

        switch (option) {
            case 1: { // evaluation
                double evalValue;
                std::cout << "Please enter value of " << var << " to evaluate the expression.\n";
                std::cout << "=>\t";
                std::cin >> evalValue;

                std::cout << "f(" << evalValue << ") = " << evalExpr(readExpr(expr), evalValue, var) << endl;
                std::cout << "of f" << numOfDiff(numberOfDiff) << "(" << var << ") = ";
            } break;
            case 2: { // derivative
                numberOfDiff++;
                expr = simplifyExpr(diffExpr(readExpr(expr), var));

                std::cout << "f" << numOfDiff(numberOfDiff) << "(" << var << ") = ";
            } break;
            case 3: { // implicit Derivative
                unsigned short choice;
                string impl_expr, pre_expr, post_expr;

                std::cout << "Please enter new expresion : "; // xy = ysin(x)
                getline(std::cin, impl_expr);
                sscanf(impl_expr, "%[^=] %s=%s", pre_expr, post_expr);

                array<string> pre_term = readExpr(pre_expr);   //xy
                array<string> post_term = readExpr(post_expr); //ysin(x)

                std::cout << "[1] to find dy/d" << var << "\n\t[2] to find d" << var << "/dy";
                std::cin >> choice;
                string preResult;

                if (choice == 1) {
                    for (unsigned short i = 0; i < pre_term.length; i++) preResult += implDiff(pre_term[i], var);
                    for (unsigned short i = 0; i < post_term.length; i++) preResult += implDiff(post_term[i], var);

                    std::cout << "dy/d" << var << " = " << preResult;
                }
                else if (choice == 2) {
                    preResult = "dx/dy = ";
                    for (unsigned short i = 0; i < terms.length; i++) preResult += implDiff(terms[i], 'y');

                    std::cout << "d" << var << "/dy = " << preResult;
                }
            } break;
            case 4: { // find tangent
                double pos;
                std::cout << "Enter the position to find tangent of the expression.";
                std::cout << "=>\t";
                std::cin >> pos;
                
                std::cout << "tangent(x) = " << tangent(expr, pos, var);
                std::cout << "of f" << numOfDiff(numberOfDiff) << "(" << var << ") = ";
            }
            case 5: { // find relative min/max

            } break;
            case 6: { // show graph
                double scale;
                std::cout << "Enter graph scale [-50, 50] (1)";
                std::cout << "=>\t";
                std::cin >> scale;
                showGraph(expr, scale, var);

                std::cout << "of f" << numOfDiff(numberOfDiff) << "(" << var << ") = ";
            } break;
            case 7: { // new expression
                std::cout << "Enter f(" << var << ") = ";
                getline(std::cin, expr);
                numberOfDiff = 0;
                continue;
            } break;
            default: error();
        }

        std::cout << expr << "\n\n";

        isFirstPass = true;
    }

    return 0;
}

string numOfDiff(const unsigned &num) {
    if (numberOfDiff == 0) return "";
    else if (numberOfDiff < 4) return string("'").repeat(numberOfDiff);
    else "(" + toString(num) + ")";
}