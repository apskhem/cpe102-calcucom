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

int main() {
    /* parts of user input variables */
    string expr = "";
    char var = 'x';
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


    std::cout << "\nEnter f(x) = ";
    getline(std::cin, expr);

    while (true) {
        if (isFirstPass) {
            std::cout << "Press 'enter' to continue...";

            getline(std::cin, blank);
            std::cout << "------------------------------------------\n";
        }

        std::cout << "Mode: \t[1] to evaluate the result.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n";

        if (isFirstPass) std::cout << "\t[4] to try a new expression.\n\t[5] to end the program.\n";

        std::cout << "=>\t";
        std::cin >> option;
        std::cin.ignore();

        if (option == 5) break;
        std::cout << "The result is...\n\n";

        switch (option) {
            case 1: { // Evaluation
                array<string> termOps = readExprOps(expr); //-(3x^2)

                double x; //3x^2 + 2x^3 + 3x^5
                std::cout << "Please enter x value to evaluate : ";
                std::cin >> x;

                std::cout << "f(" << x << ") = " << evalExpr(readExpr(expr), x, var);
            } break;
            case 2: { // Derivative
                numberOfDiff++;
                expr = simplifyExpr(diffExpr(readExpr(expr), var));

                if (numberOfDiff < 4)
                    std::cout << "f" << string("'").repeat(numberOfDiff) << "(x) = ";
                else
                    std::cout << "f(" << numberOfDiff << ")(x) = ";
            } break;
            case 3: { // Implicit Derivative
                unsigned short choice;
                string expr, pre_expr, post_expr;

                std::cout << "Please enter new expresion : "; // xy = ysin(x)
                getline(std::cin, expr);
                sscanf(expr, "%[^=] %s=%s", pre_expr, post_expr);

                array<string> pre_term = readExpr(pre_expr);   //xy
                array<string> post_term = readExpr(post_expr); //ysin(x)

                string pre_equation, post_equation;

                std::cout << "[1] to find dy/dx \t[2] to find dx/dy";
                std::cin >> choice;

                switch (choice) {
                    case 1: { //dy/dx
                        for (unsigned  i = 0; i < pre_term.length; i++) 
                            pre_equation += implDiff(pre_term[i], 'x');
                        for (unsigned i = 0; i < post_term.length; i++) 
                            post_equation += implDiff(post_term[i], 'x');
                        std::cout << "dy/dx = " << reFormat(pre_equation, post_equation);

                    }
                    case 2: { //dx/dy
                        for (unsigned  i = 0; i < pre_term.length; i++) 
                            pre_equation += implDiff(pre_term[i], 'y');
                        for (unsigned  i = 0; i < post_term.length; i++) 
                            post_equation += implDiff(post_term[i], 'y');
                        std::cout << "dx/dy = " << reFormat(pre_equation, post_equation);
                    }
                }
            } break;
            case 4: {
                std::cout << "Enter f(x) = ";
                getline(std::cin, expr);
                continue;
            } break;
            default: error();
        }

        std::cout << expr << "\n\n";

        isFirstPass = true;
    }

    return 0;
}