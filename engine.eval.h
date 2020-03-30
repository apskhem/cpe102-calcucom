#ifndef CALCULATION_H
#define CALCULATION_H

#include <cmath>

double evalExpr(array<string> terms, const double &value, const char &var);
double eval(string term, const double &value, const char &var);
array<string> readImplExpr(string);
string implDiff(string, const char &);

const double PI = 3.14159265358979323846;

double evalExpr(array<string> terms, const double &value, const char &var) {
    double result = 0;
    for (unsigned i = 0; i < terms.length; i++) {
        result += eval(terms[i], value, var);
    }
    return result;
}

double eval(string term, const double &value, const char &var) {
    TermComponents tc(term, var);

    if (!tc.factors.length && tc.a) return tc.a;
    else if (!tc.factors.length && !tc.a) return 0;

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
                double preResult;

                if (tc.factors[i].func == "sin")
                    preResult = sin(chainEval * 180 / PI);
                else if (tc.factors[i].func == "cos")
                    preResult = cos(chainEval * 180 / PI);
                else if (tc.factors[i].func == "tan")
                    preResult = tan(chainEval * 180 / PI);
                else if (tc.factors[i].func == "csc")
                    preResult = 1/sin(chainEval * 180 / PI);
                else if (tc.factors[i].func == "sec")
                    preResult = 1/cos(chainEval * 180 / PI);
                else if (tc.factors[i].func == "cot")
                    preResult = 1/tan(chainEval * 180 / PI);
            } break;
            case 2: {
                double chainEval = evalExpr(readExpr(tc.factors[i].u), value, var);
                double logbase = parseNum(tc.factors[i].func.slice(3));
                if (!logbase) logbase = 10;

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
            default: error();
        }

        // sum the result
        if (tc.divIndex[divPlace] == i) {
            result /= preResult;
            divPlace++;
        }
        else {
            result *= preResult;
        }
    }

    return result;
}

array<string> readImplExpr(string term)
{
    array<string> each_term;
    bool x_y_idx = 0, func_idx = 0;

    for (unsigned i = 0; i < term.length; i++)
    {
        if (term[i] == 'x' || term[i] == 'y')
        {
            x_y_idx = true;
            break;
        }
        else if (term[i] == 's' || term[i] == 'c' || term[i] == 't' || term[i] == 'l' || term[i] == '^')
        {
            func_idx = true;
            break;
        }
    }
    if (func_idx = true)
    {
        unsigned start = 0;
        unsigned leftPar = 0, rightPar = 0;

        for (unsigned i = 0; i < term.length; i++)
        {
            if (term[i] == '(')
                leftPar++;
            else if (term[i] == ')')
                rightPar++;

            if ((term[i] == 's' || term[i] == 'c' || term[i] == 't' || a[i] == 'l') && leftPar == rightPar)
            {
                i += 3; //skip in(
                leftPar++;
                while (term[i] != ')')
                    i++;
                each_term.push(term.slice(start, i + 1));
                start = i + 1;
            }

            else if (term[i] == '^')
            {
                unsigned stop = i;

                if (term[i] != 'x' || term[i] != 'y' || term[i] != ')')
                {
                    while (isNum(term[++i]))
                        stop++;
                }
                each_term.push(term.slice(start, stop + 1));
                start = stop + 1;
            }

            if (i == term.length - 1)
                each_term.push(term.slice(start, i));
        }
    }
    else if (x_y_idx = true)
    {
        unsigned start = 0;
        unsigned leftPar = 0, rightPar = 0;

        for (unsigned i = 0; i < term.length; i++)
        {
            if (term[i] == '(')
                leftPar++;
            else if (term[i] == ')')
                rightPar++;

            if ((term[i] == 'x' || term[i] == 'y') && term[i + 1] != '^' && leftPar == rightPar)
            {
                each_term.push(term.slice(start, i + 1));
                start = i + 1;
            }
            if (i == term.length - 1)
                each_term.push(term.slice(start, i));
        }
    }
    return each_term;
}

string implDiff(string term, char var) // xy , ysin(x) , (x+y)^2
{
    array<string> each_term;
    string result = "";
    bool x_y = false, x_only = false, y_only = false;

    if (term.includes("x") && term.includes("y")) x_y = true;
    else if (term.includes("x")) x_only = true;
    else if (term.includes("y")) y_only = true;

    if (var == 'x') //dy/dx******
    {
        if (x_y) //xy
        {
            each_term = readImplExpr(term); //x,y

            for (unsigned i = 0; i < each_term.length; i++)
            {
                double a = parseNum(each_term[i]);

                if (i > 0)
                    result += "+";

                result += "(" + toString(a) + ")";

                for (unsigned j = 0; j < each_term.length; i++) {
                    result += "(";
                    if (each_term[i].includes("x"))
                        result += (i == j ? diff(each_term[i], 'x') : each_term[i]) + ")";
                    else if (each_term[i].includes("y"))
                        result += (i == j ? diff(each_term[i], 'y') : each_term[i]) + ")(dy/dx)";
                }
            }
        }
        else if (x_only) { //3sin(x)
            result = diffExpr(readExpr(term), var);
        }
        else if (y_only)
        {
            each_term = readExpr(term); //3sin(y)

            for (unsigned i = 0; i < each_term.length; i++)
            {
                double a = parseNum(each_term[i]);

                if (i > 0)
                    result += "+";

                result += "(" + toString(a) + ")";

                for (unsigned j = 0; j < each_term.length; i++)
                {
                    result += "(";
                    result += (i == j ? diff(each_term[i], 'y') : each_term[i]);
                    result += ")(dy/dx)";
                }
            }
        }
    }

    else if (var == 'y')
    {
        if (x_y) //xy
        {
            each_term = readImplExpr(term); //x,y

            for (unsigned i = 0; i < each_term.length; i++)
            {
                double a = parseNum(each_term[i]);

                if (i > 0)
                    result += "+";

                result += "(" + toString(a) + ")";

                for (unsigned j = 0; j < each_term.length; i++)
                {
                    result += "(";
                    if (each_term[i].includes("x"))
                        result += (i == j ? diff(each_term[i], 'x') : each_term[i]) + ")(dx/dy)";
                    else if (each_term[i].includes("y"))
                        result += (i == j ? diff(each_term[i], 'y') : each_term[i]) + ")";
                }
            }
        }
        else if (x_only)
        {
            each_term = readExpr(term); //3sin(x)

            for (unsigned i = 0; i < each_term.length; i++)
            {
                double a = parseNum(each_term[i]);

                if (i > 0)
                    result += "+";

                result += "(" + toString(a) + ")";

                for (unsigned j = 0; j < each_term.length; i++)
                {
                    result += "(";
                    result += (i == j ? diff(each_term[i], 'x') : each_term[i]);
                    result += ")(dx/dy)";
                }
            }
        }
        else if (y_only)
        {
            result = diffExpr(readExpr(term), var);
        }

        return result;
    }
}

#endif