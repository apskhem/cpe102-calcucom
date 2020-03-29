#ifndef CALCULATION_H
#define CALCULATION_H

#include <cmath>

double calLog(const double &, const double &);
array<string> readExprOps(string);
double cal(string, float);
array<string> readImplExpr(string);
string implDiff(string, const char &);

const double PI = 3.14159265358979323846;

double calLog(const double &b, const double &u) {
    return log(u)/log(b);
}

array<string> readExprOps(string term)
{
    array<string> res;
    unsigned leftPar = 0, rightPar = 0;

    for (unsigned i = 0; i < term.length; i++) //(2x^2)*3
    {
        if (term[i] == ')') rightPar++;
        else if (term[i] == '(') leftPar++;

        if (leftPar == rightPar) {
            if (term[i] == '+')
                res.push("+");
            else if (term[i] == '-' && i != 0)
                res.push("-");
            else if (term[i] == '*' || term[i] == '(' || term[i] == ')') // 2(2x+3)
            {
                if (term[i] == '(') leftPar++;
                if (term[i] == ')') rightPar++;

                res.push("*");
            }
            else if (term[i] == '/')
                res.push("/");
        }
    }
    return res;
}

double cal(string term, float x) //3x^{2sin(3x)+2x^3+5ln(3x)}
{
    TermComponents var(term, 'x');
    double n_value;
    double u_value;

    if (var.n.length)
    {
        // 3x^{2sin(3x)+2x^3+5ln(3x)}
        array<string> n_operation;
        array<string> n_term;
        array<double> each_n_value;

        for (unsigned i = 0; i < var.n.length; i++)
        {
            n_operation.push(readExprOps(var.n[i])); // + , +
            n_term.push(readExpr(var.n[i]));       //2sin(3x), 2x^3, 5ln(3x), 2x
        }

        for (unsigned short list = 0; list < n_term.length; list++)
        {
            if (n_term[list].includes("^")) //2x^(3x+2)
            {
                TermComponents n_equation(n_term[list], 'x');
                array<string> u_equation = readExpr(n_equation.n[0]); //3x, 2
                array<string> u_operation = readExprOps(n_equation.n[0]);
                double u_value; //3x+2
                array<double> each_u_value;

                for (unsigned i = 0; i < u_equation.length; i++)
                {
                    double u_n_value = parseNum(u_equation[i]);

                    for (unsigned j = 0; j < u_equation[i].length; i++)
                    {
                        if (u_equation[i][j] == 'x')
                            u_n_value *= x;
                    }
                    each_u_value.push(u_n_value);
                }

                u_value = each_u_value[0];

                for (unsigned i = 0; i < u_operation.length; i++)
                {
                    if (u_operation[i] == '+')
                        u_value += each_u_value[i + 1];
                    else if (u_operation[i] == '-')
                        u_value -= each_u_value[i + 1];
                    else if (u_operation[i] == '*')
                        u_value *= each_u_value[i + 1];
                    else if (u_operation[i] == '/')
                        u_value /= each_u_value[i + 1];
                }

                double n_n_value = parseNum(n_term[list]); //2

                n_n_value *= pow(x, u_value);

                each_n_value.push(n_n_value);
            }

            else if (n_term[list].includes("s") || n_term[list].includes("s") || n_term[list].includes("t"))
            {
                TermComponents n_equation(n_term[list], 'x');           //2sin(3x+2)
                array<string> u_equation = readExpr(n_equation.u[0]);   //3x, 2
                array<string> u_operation = readExprOps(n_equation.u[0]); //+
                array<double> each_u_value;
                double u_value;

                for (unsigned i = 0; i < u_equation.length; i++) //3x, 2
                {
                    double n_u_value = parseNum(u_equation[i]);

                    for (unsigned j = 0; j < u_equation[i].length; j++)
                    {
                        if (u_equation[i][j] == 'x')
                            n_u_value *= x;
                    }

                    each_u_value.push(n_u_value);
                }

                u_value = each_u_value[0];

                for (unsigned i = 0; i < u_operation.length; i++)
                {
                    if (u_operation[i] == '+')
                        u_value += each_u_value[i + 1];
                    else if (u_operation[i] == '-')
                        u_value -= each_u_value[i + 1];
                    else if (u_operation[i] == '*')
                        u_value *= each_u_value[i + 1];
                    else if (u_operation[i] == '/')
                        u_value /= each_u_value[i + 1];
                }

                double n_n_value = parseNum(n_term[list]);

                for (unsigned i = 0; i < n_equation.trig.length; i++)
                {
                    if (n_equation.trig.includes("sin"))
                        n_n_value *= sin(u_value);
                    else if (n_equation.trig.includes("cos"))
                        n_n_value *= cos(u_value);
                    else if (n_equation.trig.includes("tan"))
                        n_n_value *= tan(u_value);
                    else if (n_equation.trig.includes("cot"))
                        n_n_value /= tan(u_value);
                    else if (n_equation.trig.includes("sec"))
                        n_n_value /= cos(u_value);
                    else if (n_equation.trig.includes("csc"))
                        n_n_value /= sin(u_value);
                }

                each_n_value.push(n_n_value);
            }

            else if (n_term[list].includes("ln")) //5ln(3x+5)
            {
                TermComponents n_equation(n_term[list], 'x');
                array<string> u_equation = readExpr(n_equation.u[0]);
                array<string> u_operation = readExprOps(n_equation.u[0]);
                array<double> each_u_value;
                double u_value;

                for (unsigned i = 0; i < u_equation.length; i++) //3x , 5
                {
                    double n_u_value = parseNum(u_equation[i]);

                    for (unsigned j = 0; j < u_equation[i].length; j++)
                    {
                        if (u_equation[i][j] == 'x')
                            n_u_value *= x;
                    }

                    each_u_value.push(n_u_value);
                }

                u_value = each_u_value[0];

                for (unsigned i = 0; i < u_operation.length; i++)
                {
                    if (u_operation[i] == '+')
                        u_value += each_u_value[i + 1];
                    else if (u_operation[i] == '-')
                        u_value -= each_u_value[i + 1];
                    else if (u_operation[i] == '*')
                        u_value *= each_u_value[i + 1];
                    else if (u_operation[i] == '/')
                        u_value /= each_u_value[i + 1];
                }

                double n_n_value = parseNum(n_term[list]); //7

                n_n_value *= log(u_value);

                each_n_value.push(n_n_value);
            }

            else if (n_term[list].includes("log")) //7log10(5x+2)
            {
                TermComponents n_equation(n_term[list], 'x');
                array<string> u_equation = readExpr(n_equation.u[0]);
                array<string> u_operation = readExprOps(n_equation.u[0]);
                array<double> each_u_value;
                double b_value;
                double u_value;

                for (unsigned i = 0; i < n_equation.log[0].length; i++)
                {
                    i += 3; //skip log
                    b_value = parseNum(n_equation.log[0].slice(i, n_equation.log[0].length - 1));
                }

                for (unsigned i = 0; i < u_equation.length; i++) //5x , 2
                {
                    double n_u_value = parseNum(u_equation[i]);

                    for (unsigned j = 0; j < u_equation[i].length; j++)
                    {
                        if (u_equation[i][j] == 'x')
                            n_u_value *= x;
                    }

                    each_u_value.push(n_u_value);
                }

                u_value = each_u_value[0];

                for (unsigned i = 0; i < u_operation.length; i++)
                {
                    if (u_operation[i] == '+')
                        u_value += each_u_value[i + 1];
                    else if (u_operation[i] == '-')
                        u_value -= each_u_value[i + 1];
                    else if (u_operation[i] == '*')
                        u_value *= each_u_value[i + 1];
                    else if (u_operation[i] == '/')
                        u_value /= each_u_value[i + 1];
                }

                double n_n_value = parseNum(n_term[list]);
                n_n_value *= calLog(b_value, u_value);

                each_n_value.push(n_n_value);
            }
            else //3x
            {
                double u_value = parseNum(n_term[list]);

                for (unsigned i = 0; i < n_term[list].length; i++)
                {
                    if (n_term[list][i] == 'x')
                        u_value *= x;
                }

                each_n_value.push(u_value);
            }
        }

        n_value = each_n_value[0];

        for (unsigned i = 0; i < n_operation.length; i++) //get n value
        {
            if (n_operation[i] == '+')
                n_value += each_n_value[i + 1];
            else if (n_operation[i] == '-')
                n_value -= each_n_value[i + 1];
            else if (n_operation[i] == '*')
                n_value *= each_n_value[i + 1];
            else if (n_operation[i] == '/')
                n_value /= each_n_value[i + 1];
        }
    }

    //**********************************************
    if (var.u.length)
    {
        // 2sin(3x^(2x+5)+20sin(5x)+5log(20x)+2x)
        array<string> u_operation;
        array<string> u_term;
        array<double> each_u_value;

        for (unsigned i = 0; i < var.u.length; i++)
        {
            u_operation.push(readExprOps(var.u[i])); //3x^(2x+5), 20sin(5x), 5log(20x), 2x
            u_term.push(readExpr(var.u[i]));       // + , + , +
        }

        for (unsigned short list = 0; list < u_term.length; list++) //3x^(2x+5), 20sin(5x+20), 5log(20x)
        {
            if (u_term[list].includes("^")) // 3x^(2x+5)
            {
                TermComponents u_equation(u_term[list], 'x');
                array<string> n_equation = readExpr(u_equation.n[0]);   //2x, 5
                array<string> n_operation = readExprOps(u_equation.n[0]); // +
                array<double> each_n_value;

                for (unsigned i = 0; i < n_equation.length; i++) //2x,5
                {
                    double u_n_value = parseNum(n_equation[i]);

                    for (unsigned j = 0; j < n_equation[i].length; j++)
                    {
                        if (n_equation[i][j] == 'x')
                            u_n_value *= x;
                    }

                    each_n_value.push(u_n_value);
                }

                double n_value = each_n_value[0];

                for (unsigned i = 0; i < n_operation.length; i++)
                {
                    if (u_operation[i] == '+')
                        n_value += each_n_value[i + 1];
                    else if (u_operation[i] == '-')
                        n_value -= each_n_value[i + 1];
                    else if (u_operation[i] == '*')
                        n_value *= each_n_value[i + 1];
                    else if (u_operation[i] == '/')
                        n_value /= each_n_value[i + 1];
                }

                double u_u_value = parseNum(u_term[list]); //2

                u_u_value *= pow(x, n_value);

                each_u_value.push(u_u_value);
            }

            else if (u_term[list].includes("s") || u_term[list].includes("s") || u_term[list].includes("t"))
            {
                TermComponents u_equation(u_term[list], 'x');           //20sin(5x+20)
                array<string> each_u_term = readExpr(u_equation.u[0]);  //5x, 20
                array<string> u_operation = readExprOps(u_equation.u[0]); //+
                array<double> each_trig_value;

                for (unsigned i = 0; i < each_u_term.length; i++) //5x, 20
                {
                    double trig_u_value = parseNum(each_u_term[i]);

                    for (unsigned j = 0; j < each_u_term[i].length; j++)
                    {
                        if (each_u_term[i][j] == 'x')
                            trig_u_value *= x;
                    }

                    each_trig_value.push(trig_u_value);
                }

                double trig_value = each_trig_value[0]; //5x+20

                for (unsigned i = 0; i < u_operation.length; i++)
                {
                    if (u_operation[i] == '+')
                        trig_value += each_trig_value[i + 1];
                    else if (u_operation[i] == '-')
                        trig_value -= each_trig_value[i + 1];
                    else if (u_operation[i] == '*')
                        trig_value *= each_trig_value[i + 1];
                    else if (u_operation[i] == '/')
                        trig_value /= each_trig_value[i + 1];
                }

                double u_u_value = parseNum(u_term[list]); //20

                for (unsigned i = 0; i < u_term[list].length; i++)
                {
                    if (u_term[list].includes("sin"))
                        u_u_value *= sin(trig_value);
                    else if (u_term[list].includes("cos"))
                        u_u_value *= cos(trig_value);
                    else if (u_term[list].includes("tan"))
                        u_u_value *= tan(trig_value);
                    else if (u_term[list].includes("cot"))
                        u_u_value /= tan(trig_value);
                    else if (u_term[list].includes("sec"))
                        u_u_value /= cos(trig_value);
                    else if (u_term[list].includes("csc"))
                        u_u_value /= sin(trig_value);
                }

                each_u_value.push(u_u_value);
            }

            else if (u_term[list].includes("ln")) //5ln(20x+5)
            {
                TermComponents u_equation(u_term[list], 'x');
                array<string> each_u_term = readExpr(u_equation.u[0]); //20x, 5
                array<string> u_operation = readExprOps(u_equation.u[0]);
                array<double> each_log_value;

                for (unsigned i = 0; i < each_u_term.length; i++) //20x, 5
                {
                    double log_u_value = parseNum(each_u_term[i]);

                    for (unsigned j = 0; j < each_u_term[i].length; j++)
                    {
                        if (each_u_term[i][j] == 'x')
                            log_u_value *= x;
                    }

                    each_log_value.push(log_u_value);
                }

                double log_value = each_log_value[0];

                for (unsigned i = 0; i < u_operation.length; i++)
                {
                    if (u_operation[i] == '+')
                        log_value += each_log_value[i + 1];
                    else if (u_operation[i] == '-')
                        log_value -= each_log_value[i + 1];
                    else if (u_operation[i] == '*')
                        log_value *= each_log_value[i + 1];
                    else if (u_operation[i] == '/')
                        log_value /= each_log_value[i + 1];
                }

                double u_u_value = parseNum(u_term[list]); //5

                u_u_value *= log(log_value);

                each_u_value.push(u_u_value);
            }

            else if (u_term[list].includes("log")) //7log10(5x+2)
            {
                TermComponents u_equation(u_term[list], 'x');
                array<string> each_u_term = readExpr(u_equation.u[0]);
                array<string> u_operation = readExprOps(u_equation.u[0]);
                array<double> each_log_value;
                double b_value;

                for (unsigned i = 0; i < u_equation.log[0].length; i++)
                {
                    i += 3; //skip log
                    b_value = parseNum(u_equation.log[0].slice(i, u_equation.log[0].length - 1));
                }

                for (unsigned i = 0; i < each_u_term.length; i++) //5x , 2
                {
                    double log_u_value = parseNum(each_u_term[i]);

                    for (unsigned j = 0; j < each_u_term[i].length; j++)
                    {
                        if (each_u_term[i][j] == 'x')
                            log_u_value *= x;
                    }

                    each_log_value.push(log_u_value);
                }

                double log_value = each_log_value[0];

                for (unsigned i = 0; i < u_operation.length; i++)
                {
                    if (u_operation[i] == '+')
                        log_value += each_log_value[i + 1];
                    else if (u_operation[i] == '-')
                        log_value -= each_log_value[i + 1];
                    else if (u_operation[i] == '*')
                        log_value *= each_log_value[i + 1];
                    else if (u_operation[i] == '/')
                        log_value /= each_log_value[i + 1];
                }

                double u_u_value = parseNum(u_term[list]);
                u_u_value *= calLog(b_value, log_value);

                each_u_value.push(u_u_value);
            }
            else //3x
            {
                double u_u_value = parseNum(u_term[list]);

                for (unsigned i = 0; i < u_term[list].length; i++)
                {
                    if (u_term[list][i] == 'x')
                        u_u_value *= x;
                }

                each_u_value.push(u_u_value);
            }
        }

        u_value = each_u_value[0];

        for (unsigned i = 0; i < u_operation.length; i++) //get u value
        {
            if (u_operation[i] == '+')
                u_value += each_u_value[i + 1];
            else if (u_operation[i] == '-')
                u_value -= each_u_value[i + 1];
            else if (u_operation[i] == '*')
                u_value *= each_u_value[i + 1];
            else if (u_operation[i] == '/')
                u_value /= each_u_value[i + 1];
        }
    }

    //*******************************************

    double result = parseNum(term);

    for (unsigned i = 0; i < term.length; i++)
    {
        if (term[i] == 'x' && term[i + 1] == '^')
        {
            result *= pow(x, n_value);
        }
        
        else if (term[i] == ')' && term[i + 1] == '^') //(x+2)^2
        {
            double a_value;
            array<string> each_a_term = readExpr(var.u[0]);
            array<string> a_operation = readExprOps(var.u[0]);
            array<double> each_a_value;

            for (unsigned list = 0; list < each_a_term.length; list++) //x,2
            {
                double a_n = parseNum(each_a_term[list]);
                for (unsigned j = 0; j < each_a_term[list].length; j++)
                {
                    if (each_a_term[list][j] == 'x')
                        a_n *= x;
                }
                each_a_term.push(a_n);
            }

            a_value = each_a_value[0];

            for (unsigned i = 0; i < a_operation.length; i++)
            {
                if (a_operation[i] == '+')
                    a_value += each_a_value[i + 1];
                else if (a_operation[i] == '-')
                    a_value -= each_a_value[i + 1];
                else if (a_operation[i] == '*')
                    a_value *= each_a_value[i + 1];
                else if (a_operation[i] == '/')
                    a_value /= each_a_value[i + 1];
            }
            result *= (a_value, n_value);
        }

        else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i + 4 < term.length) //5sin(x)
        {
            string tfunc = term.slice(i, i + 3);
            if (tfunc == "sin")
                result *= sin(u_value);
            if (tfunc == "cos")
                result *= cos(u_value);
            if (tfunc == "tan")
                result *= tan(u_value);
            if (tfunc == "cot")
                result /= tan(u_value);
            if (tfunc == "sec")
                result /= cos(u_value);
            if (tfunc == "csc")
                result /= sin(u_value);
        }

        else if (term[i] == 'l')
        {
            if (term[i + 1] == 'o') //5log10(5x)
            {
                double b_value;

                for (unsigned i = 0; i < var.log.length; i++)
                {
                    i += 3; //skip log
                    b_value = parseNum(var.log[0].slice(i, var.log[0].length - 1));
                }

                result *= calLog(b_value, u_value);
            }
            else if (term[i + 1] == 'n') //5ln(5x)
            {
                result *= log(u_value);
            }
        }
        else // 3x
            result *= x;
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

    for (unsigned i = 0; i < term.length; i++)
    {
        if (term.includes("x") && term.includes("y"))
            x_y = true;
        else if (term.includes("x"))
            x_only = true;
        else if (term.includes("y"))
            y_only = true;
    }

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

                for (unsigned j = 0; j < each_term.length; i++)
                {
                    result += "(";
                    if (each_term[i].includes("x"))
                        result += (i == j ? diff(each_term[i], 'x') : each_term[i]) + ")";
                    else if (each_term[i].includes("y"))
                        result += (i == j ? diff(each_term[i], 'y') : each_term[i]) + ")(dy/dx)";
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
                    result += ")";
                }
            }
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
                    result += ")";
                }
            }
        }

        return result;
    }
}

#endif