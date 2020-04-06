#include <iostream>

void error(const char *msg, const unsigned cond=1) {
    switch (cond) {
        case 1: std::cout << "Bad arithmetic expression: "; break;
        case 2: std::cout << "Lack of features: "; break;
        case 3: std::cout << "Exceed program's limitation: "; break;
        case 4: std::cout << "Wrong user input: "; break;
        case 5: std::cout << "Systematic fault: "; break;
    };

    std::cout << msg << ".\n\n";
    
    throw 0;
}

#include "klib.array.h"
#include "klib.string.h"
#include "klib.number.h"
#include "engine.base.h"
#incldue "engine.evaluation.h"
// #include "engine.lim.h"
#include "engine.max_min.h"

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

    std::cout << "Press 'enter' to start...";
    getline(std::cin, blank);

    // run first menu
    std::cout << "\nIndependent variable (single character)\n";
    std::cout << "=>\t";
    std::cin >> var;
    std::cin.ignore();
    std::cout << "Enter f(" << var << ") = ";
    getline(std::cin, expr);

    while (true) {

        if (isFirstPass) {
            std::cout << "Press 'enter' to continue...";
            getline(std::cin, blank);
            std::cout << "\n------------------------------------------\n";
        }

        std::cout << "Mode: \t[1] Evaluate the expression.\n";
        std::cout << "\t[2] Derivative the expression.\n";
        std::cout << "\t[3] Implicit derivative the expression.\n";
        std::cout << "\t[4] Find tangent.\n";
        std::cout << "\t[5] Find relative min/max.\n";
        std::cout << "\t[6] Show graph.\n";
        std::cout << "\t[7] Try a new expression.\n";
        std::cout << "\t[8] End program.\n";
        std::cout << "=>\t";
        std::cin >> option;
        std::cin.ignore();

        if (option == 8) break;

        switch (option) {
            case 1: { // evaluation
                double evalValue;
                std::cout << "Enter value of " << var << " to evaluate the expression.\n";
                std::cout << "=>\t";
                std::cin >> evalValue;
                std::cin.ignore();

                std::cout << "The result is...\n\n";

                std::cout << "f" << numOfDiff(numberOfDiff) << "(" << evalValue << ") = " << evalExpr(readExpr(expr), evalValue, var) << '\n';
                std::cout << "of f" << numOfDiff(numberOfDiff) << "(" << var << ") = ";
            } break;
            case 2: { // derivative
                numberOfDiff++;
                expr = diffExpr(readExpr(expr), var);
                if (!expr.length) expr = "0";

                std::cout << "The result is...\n\n";

                std::cout << "f" << numOfDiff(numberOfDiff) << "(" << var << ") = ";
            } break;
            case 3: { // implicit derivative
                unsigned short mode;
                string impl_expr;
                std::cout << "Enter implicit expresion [left=right].\n";
                std::cout << "=>\t";
                getline(std::cin, impl_expr);
                std::cin.ignore();

                if (impl_expr.search("=") == -1) error("no presence of [left=right] expression");

                impl_expr = impl_expr.replace(" ", "").toLowerCase();

                string leftExpr = impl_expr.split("=")[0];
                string rightExpr = impl_expr.split("=")[1];

                std::cout << "The result is...\n\n";

                std::cout << "dy/d" << var << " = " << implExprDiff(readExpr(leftExpr), readExpr(rightExpr), var) << "\n\n";

                 isFirstPass = true;
                 continue;
            } break;
            case 4: { // find tangent
                double pos;
                std::cout << "Enter the position to find tangent of the expression.\n";
                std::cout << "=>\t";
                std::cin >> pos;
                std::cin.ignore();
                
                std::cout << "tangent(x) = " << tangent(expr, pos, var) << " @ " << var << " = " << pos << '\n';
                std::cout << "of f" << numOfDiff(numberOfDiff) << "(" << var << ") = ";
            }
            case 5: { // find relative min/max
                findRelativeMinMax(readExpr(expr), var);

                std::cout << "of f" << numOfDiff(numberOfDiff) << "(" << var << ") = ";
            } break;
            case 6: { // show graph
                double scale;
                std::cout << "Enter graph scale [-50, 50] in scale 1.\n";
                std::cout << "=>\t";
                std::cin >> scale;
                std::cin.ignore();
                showGraph(expr, scale, var);

                std::cout << "of f" << numOfDiff(numberOfDiff) << "(" << var << ") = ";
            } break;
            case 7: { // new expression
                std::cout << "Enter f(" << var << ") = ";
                getline(std::cin, expr);
                std::cout << "\n\n";
                numberOfDiff = 0;
                continue;
            } break;
            default: error("out of selection scope", 4);
        }

        std::cout << expr << "\n\n";

        isFirstPass = true;
    }

    return 0;
}

string numOfDiff(const unsigned &num) {
    if (num == 0) return "";
    else if (num < 4) return string("'").repeat(num);
    else return "(" + toString(num) + ")";
}