#include <iostream>
#include <cmath>

#include "klib.array.h"
#include "klib.string.h"
#include "klib.number.h"
#include "derivative.h"

/* The method recieves user input from fisrt place */
void userRequest(string &, string &, unsigned);
/* The method splits input expression into arrays of string */
array<string> readExpr(string);
/* The method calcalate the derivative value of implicit expression */
double cal(string, float);
void implFunc(string);
float implCal(string, float, float);
array<string> operation(string);

const double PI = 3.14159;

struct termComponents {
    string n;
    string e;
    string u;

    void categorizeTerm(string term) {
        termComponents value = {};
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
        value = {n, e, u};
    }
};

int main() {
    /* parts of user input variables */
    string expr = "", numberOfDiff = "";

    /* parts of program variables */
    string blank;
    unsigned option;
    bool isFirstPass = false;

    std::cout << "Enter f(x) = ";
    getline(std::cin, expr);

    while (true) {
        if (isFirstPass) {
            std::cout << "Press 'enter' to continue...";
            
            getline(std::cin, blank);
            std::cout << "------------------------------------------\n";
        }

        std::cout << "Press: \t[1] to evaluate the result.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n";

        if (isFirstPass) {
            std::cout << "\t[4] to try a new expression.\n\t[5] to end the program.\n";
        }
        
        std::cout << "=>\t";
        std::cin >> option;
        std::cin.ignore();

        if (option == 5) break;
        std::cout << "The result is...\n\n";

        switch (option) {
            case 1: userRequest(expr, numberOfDiff, 1); break;
            case 2: userRequest(expr, numberOfDiff, 2); break;
            case 3: userRequest(expr, numberOfDiff, 3); break;
            case 4: {
                std::cout << "Enter f(x) = ";
                getline(std::cin, expr);
                continue;
            } break;
        }

        if (option == 2) std::cout << "f" << numberOfDiff << "(x) = ";
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
    double cal_equation = 0;

    switch (option) {
        case 1:
        { // Eval
            float x;
            std::cout << "Please enter x value to evaluate : ";
            std::cin >> x;
            for (unsigned short i = 0; i < terms.length; i++)
            {
                // if (operation[i] == '+')
                // {
                //     categorizeTerm(terms[i]);
                //     cal_equation += cal(terms[i], x);
                // }
                // else if (operation[i] == '-')
                // {
                //     categorizeTerm(terms[i]);
                //     cal_equation -= cal(terms[i], x);
                // }
            }
            std::cout << "f(x) = " << cal_equation;
        }
        break;
        case 2:{ // Diff   
            numberOfDiff += "'";
            for (unsigned i = 0; i < terms.length; i++){
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
    }
    // ++ re-arrange the result; cleaner result
    expr = result;
}

array<string> readExpr(string expr) {
    array<string> terms;
    array<string> operation;

    unsigned leftPar = 0, rightPar = 0;

    // pre-reading process
    expr = expr.replace(" ", "");

    // reading equation process
    unsigned splitIndex = 0;
    for (unsigned i = 0; i < expr.length; i++) {
        if (expr[i] == '(')
            leftPar++;
        else if (expr[i] == ')')
            rightPar++;

        if ((expr[i] == '+' || expr[i] == '-') && expr[i - 1] != '^' && leftPar == rightPar) {
            terms.push(expr.slice(splitIndex, i));
            splitIndex = i + (expr[i] == '+' ? 1 : 0);

            if (expr[i] == '+')
                operation.push("+");
            if (expr[i] == '-')
                operation.push("-");
        }

        if (i >= expr.length - 1) {
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

    for (int i = 0; i < term.length; i++)
    {
        if (term[i] == '(') // (x+2)
        {
            i++; //skip (
            leftPar++;
            while (leftPar != rightPar)
            {
                if (term[i] == '+')
                    term_sep.push("+");
                if (term[i] == '-')
                    term_sep.push("-");
                if (term[i] == '*' || term[i] == '(')
                {
                    term_sep.push("*");
                    leftPar++;
                }
                if (term[i] == '/')
                    term_sep.push("/");
                if (term[i] == ')')
                    rightPar++;
            }
        }
    }
    return term_sep;
}

double cal(string term, float x)
{
    termComponents var;
    var.categorizeTerm(term);
    double result = 0, func_sum = 0;
    array<string> term_sep = operation(term);
    double a = parseNum(term);
    double a_n = parseNum(var.n);
    double a_u = parseNum(var.u);

    for (unsigned short i = 0; i < var.n.length; i++)
    {
        if (var.n[i] == 'x')
        {
        }

        else if (var.n[i] == 'x')
        {
            // var.n[i] = a_n * x; // later-error
        }
    }

    for (unsigned short i = 0; i < var.u.length; i++)
    {

        if (var.u[i] == 'x')
        {
            //var.u[i] = a_u * x // later-error
        }
    }

    for (unsigned short i = 0; i < term.length; i++)
    {
        if (term[i] == 'x') {
            // term[i] = x; // later-error
        }
        else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i + 4 < term.length) //trigon
        {
            string tfunc = term.slice(i, i + 3);
            if (tfunc == "sin")
            {
                result = a * sin(parseNum(var.u) * 180 / PI);
            }
            else if (tfunc == "cos")
            {
                result = a * cos(parseNum(var.u) * 180 / PI);
            }
            else if (tfunc == "tan")
            {
                result = a * tan(parseNum(var.u) * 180 / PI);
            }
            else if (tfunc == "cot")
            {
                result = a / tan(parseNum(var.u) * 180 / PI);
            }
            else if (tfunc == "sec")
            {
                result = a / cos(parseNum(var.u) * 180 / PI);
            }
            else if (tfunc == "csc")
            {
                result = a / sin(parseNum(var.u) * 180 / PI);
            }
        }
        else if (term[i] == 'l')
        {
            if (term[i + 1] == 'n')
            { //ln
                ;
            }
            else
            { //log
                ;
            }
        }
    }
    return result;
}

float implCal(string t, float x, float y) {

}

void implFunc(string t) {
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