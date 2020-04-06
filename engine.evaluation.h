#ifndef EVALUATION_H
#define EVALUATION_H

#include <cmath>

string findRelativeMinMax(array<string> terms, const char &var);
/* The method evaluates the expression. */
double evalExpr(array<string> terms, const double &value, const char &var);
/* The method evaluates a term. */
double eval(string term, const double &value, const char &var);

const double PI = 3.14159265358979323846;
const double e = 2.71828;

double evalExpr(array<string> terms, const double &value, const char &var) {
    double result = 0;
    for (unsigned i = 0; i < terms.length; i++) {
        result += eval(terms[i], value, var);
    }
    return result;
}

double eval(string term, const double &value, const char &var) {
    TermComponents tc(term, var);

    if (!tc.factors.length) {
        if (tc.a) return tc.a;
        else return 0;
    }

    double result = tc.a;
    unsigned divPlace = 0;

    for (unsigned short i = 0; i < tc.factors.length; i++) {
        double preResult;

        switch (tc.factors[i].type) {
            case 0: {
                double chainEval = evalExpr(readExpr(tc.factors[i].u), value, var);
                double n = evalExpr(readExpr(tc.factors[i].n), value, var);

                preResult = pow(chainEval, n);
            } break;
            case 1: {
                double chainEval = evalExpr(readExpr(tc.factors[i].u), value, var);

                if (tc.factors[i].func == "sin")
                    preResult = sin(chainEval * PI / 180);
                else if (tc.factors[i].func == "cos")
                    preResult = cos(chainEval * PI / 180);
                else if (tc.factors[i].func == "tan")
                    preResult = tan(chainEval * PI / 180);
                else if (tc.factors[i].func == "csc")
                    preResult = 1/sin(chainEval * PI / 180);
                else if (tc.factors[i].func == "sec")
                    preResult = 1/cos(chainEval * PI / 180);
                else if (tc.factors[i].func == "cot")
                    preResult = 1/tan(chainEval * PI / 180);
            } break;
            case 2: {
                double chainEval = evalExpr(readExpr(tc.factors[i].u), value, var);
                double logbase = tc.factors[i].func.length == 3 ? 10 : parseNum(tc.factors[i].func.slice(3));

                preResult = tc.factors[i].func.length > 2 ? log(chainEval)/log(logbase) : log(chainEval);
            } break;
            case 3: {
                double chainEval = evalExpr(readExpr(tc.factors[i].u), value, var);

                if (tc.factors[i].func == "sin")
                    preResult = asin(chainEval);
                else if (tc.factors[i].func == "cos")
                    preResult = acos(chainEval);
                else if (tc.factors[i].func == "tan")
                    preResult = atan(chainEval);
                else if (tc.factors[i].func == "csc")
                    preResult = 1/asin(chainEval);
                else if (tc.factors[i].func == "sec")
                    preResult = 1/acos(chainEval);
                else if (tc.factors[i].func == "cot")
                    preResult = 1/atan(chainEval);
            } break;
            case 4: {
                double n = evalExpr(readExpr(tc.factors[i].n), value, var);

                preResult = pow(value, n);
            } break;
            case 5: {
                double n = evalExpr(readExpr(tc.factors[i].n), value, var);

                preResult = pow(parseNum(tc.factors[i].u), n);
            } break;
            default: error("fault at 'eval' function");
        }

        // sum the result
        if (tc.divIndex.length && tc.divIndex[divPlace] == i) {
            result /= preResult;
            divPlace++;
        }
        else {
            result *= preResult;
        }
    }

    return result;
}

string findRelativeMinMax(array<string> terms, const char &var) {

    array<string> diffedTerms = readExpr(diffExpr(terms, var));

    array<factor> factors;
    double a = 0, b = 0, c = 0;
    
    for (unsigned short i = 0; i < diffedTerms.length-1; i++) {
        TermComponents tc(diffedTerms[i], var);

        // checks tc
        if (tc.factors.length != 1 && tc.factors.length != 0) error("only one factor per term in this mode is allowed");

        if (tc.factors[i].n != "1" || tc.factors[i].n != "2") error("power of n in this mode is maximum at 3", 3);

        if (!tc.factors.length) c = tc.a;
        else if (tc.factors[i].n == "1") b = tc.a;
        else if (tc.factors[i].n == "2") a = tc.a;

        factors.push(tc.factors[i]);
    }

    if (b*b-4*a*c < 0) error("imagine number is not allowed in this mode", 2);

    double c1 = (-b - sqrt(b*b-4*a*c)) / (2*a);
    double c2 = (-b + sqrt(b*b-4*a*c)) / (2*a);

    double p1 = evalExpr(terms, c1, var);
    double p2 = evalExpr(terms, c2, var);

    if (p1 > p2) { // swap
        double temp_c = c1;
        double temp_p = p1;

        c1 = c2;
        c2 = temp_c;

        p1 = p2;
        p2 = temp_p;
    }

    std::cout << "relative min is [" <<  p1 << ", " << c2 << "]\n";
    std::cout << "relative max is [" <<  p2 << ", " << c1 << "]\n";
}

#endif