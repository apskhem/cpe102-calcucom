#ifndef CALCULATION_H
#define CALCULATION_H

double log_func(double, double);
array<string> operation(string);
double cal(string, float);
array<string> impliRead(string);
string implFunc(string, char);

const double PI = 3.14159265358979323846;

double log_func(double b, double u)
{
    int log_value = 0;
    log_value = log10(u) / log10(b);

    return log_value;
}

array<string> operation(string term)
{
    array<string> term_sep;
    unsigned leftPar = 0, rightPar = 0;

    for (unsigned i = 0; i < term.length; i++) //(2x^2)*3
    {
        if (term[i] == ')')
            rightPar++;
        else if (term[i] == '(')
            leftPar++;

        if (leftPar == rightPar)
        {
            if (term[i] == '+')
                term_sep.push("+");
            else if (term[i] == '-' && i != 0)
                term_sep.push("-");
            else if (term[i] == '*' || term[i] == '(' || term[i] == ')') // 2(2x+3)
            {
                if (term[i] == '(')
                    leftPar++;
                if (term[i] == ')')
                    rightPar++;

                term_sep.push("*");
            }
            else if (term[i] == '/')
                term_sep.push("/");
        }
    }
    return term_sep;
}

double cal(string term, float x) //-3(x+2)
{
    TermComponents var(term, 'x');

    if (var.n.length)
    {
        double n_value; // 3x^{2sin(3x)+2x^3+5ln(3x)}
        array<string> n_operation;
        array<string> n_term;
        array<double> each_n_value;

        for (unsigned i = 0; i < var.n.length; i++)
        {
            n_operation.push(operation(var.n[i])); // + , +
            n_term.push(readExpr(var.n[i]));       //2sin(3x), 2x^3, 5ln(3x), 2x
        }

        for (unsigned short list = 0; list < n_term.length; list++)
        {
            if (n_term[list].includes("^")) //2x^(3x+2)
            {
                TermComponents n_equation(n_term[list], 'x');
                array<string> u_equation = readExpr(n_equation.n[0]); //3x, 2
                array<string> u_operation = operation(n_equation.n[0]);
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
                array<string> u_operation = operation(n_equation.u[0]); //+
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
                array<string> u_operation = operation(n_equation.u[0]);
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
                array<string> u_operation = operation(n_equation.u[0]);
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
                n_n_value *= log_func(b_value, u_value);

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

        for (unsigned i = 0; i < n_operation.length; i++)
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

        for (unsigned list = 0; list < n_operation.length; list++) //get n value
        {
            n_value = parseNum(each_n_value[0]);

            if (n_operation[list] == '+')
                n_value += each_n_value[list++];
            else if (n_operation[list] == '+')
                n_value += each_n_value[list++];
            else if (n_operation[list] == '+')
                n_value += each_n_value[list++];
            else if (n_operation[list] == '+')
                n_value += each_n_value[list++];
        }
    }

    //**********************************************
    if (var.u.length)
    {
        double u_value; // 2sin(3x^(2x+5)+20sin(5x)+5log(20x)+2x)
        array<string> u_operation;
        array<string> u_term;
        array<double> each_u_value;

        for (unsigned i = 0; i < var.u.length; i++)
        {
            u_operation.push(operation(var.u[i])); //3x^(2x+5), 20sin(5x), 5log(20x), 2x
            u_term.push(readExpr(var.u[i]));       // + , + , +
        }

        for (unsigned short list = 0; list < u_term.length; list++) //3x^(2x+5), 20sin(5x+20), 5log(20x)
        {
            if (u_term[list].includes("^")) // 3x^(2x+5)
            {
                TermComponents u_equation(u_term[list], 'x');
                array<string> n_equation = readExpr(u_equation.n[0]);   //2x, 5
                array<string> n_operation = operation(u_equation.n[0]); // +
                array<double> each_n_value;

                for (unsigned i = 0; i < n_equation.length; i++) //2x,5
                {
                    double u_n_value = parseNum(n_equation[i]);

                    if (n_equation[list][i] == 'x')
                        u_n_value *= x;

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
                array<string> u_operation = operation(u_equation.u[0]); //+
                array<double> each_u_value;

                for (unsigned i = 0; i < each_u_term.length; i++) //5x, 20
                {
                    double trig_value = parseNum(each_u_term[i]);

                    for (unsigned j = 0; j < each_u_term[j].length; j++)
                    {
                        if (u_equation[i] == 'x')
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

            for (unsigned short i = 0; i < u_term[list].length; i++) // 2sin(5x)
            {
                if (u_term[list][i] == '^') //5x^2
                {
                    if (u_term[list][i] || u_term[list][i + 1] != '(') //5x^2
                    {
                        string n_u = "";
                        i++; //skip ^
                        while (isNum(u_term[list][i]) || u_term[list][i] == 'x')
                        {
                            n_u += u_term[list][i];
                            i++;
                        }

                        double n_u_value = x;
                        double u_value = 0;

                        u_value = a_u * pow(x, x);

                        each_u_value.push(u_value);
                    }
                    else //5x^(2x)
                    {
                        string n_u = "";
                        i++; //skip ^
                        while (isNum(u_term[list][i]) || u_term[list][i] == 'x')
                        {
                            n_u += u_term[list][i];
                            i++;
                        }

                        double n_u_value = parseNum(n_u); //2

                        for (unsigned short i = 0; i < n_u.length; i++)
                        {
                            if (n_u[i] == 'x') //2x
                                n_u_value *= x;
                        }
                        double u_value = 0;

                        u_value = a_u * pow(x, n_u_value);

                        each_u_value.push(u_value);
                    }
                }
                if (u_term[list][i] == 's' || u_term[list][i] == 'c' || u_term[list][i] == 't')
                {
                    string tfunc = u_term[list].slice(i, i + 3); //sin
                    string u_u = "";                             //(5x)
                    double u_value = 0;
                    int leftPar = 0, rightPar = 0;

                    i + 4; //skip sin(
                    leftPar++;

                    while (leftPar != rightPar)
                    {
                        if (var.u == '(')
                            leftPar++;
                        if (var.u == ')')
                            rightPar++;

                        u_u += var.u[i]; // 5x)
                        i++;
                    }

                    double u_u_value = parseNum(u_u); //5

                    for (unsigned short i = 0; i < u_u.length; i++)
                    {
                        if (u_u[i] == 'x')
                            u_u_value *= x;
                    }

                    if (tfunc == "sin")
                        u_value = a_u * sin(u_u_value); // PI unit
                    else if (tfunc == "cos")
                        u_value = a_u * cos(u_u_value);
                    else if (tfunc == "tan")
                        u_value = a_u * tan(u_u_value);
                    else if (tfunc == "cot")
                        u_value = a_u / tan(u_u_value);
                    else if (tfunc == "sec")
                        u_value = a_u / cos(u_u_value);
                    else if (tfunc == "csc")
                        u_value = a_u / sin(u_u_value);

                    each_u_value.push(u_value); //value of each u
                }
                else if (u_term[list][i] == 'x') //3x
                {
                    double u_value = 0;
                    u_value = a_u * x;

                    each_u_value.push(u_value);
                }
                else if (u_term[list][i] == 'l') //7ln(3x)
                {
                    string u_u = "";
                    int leftPar = 0, rightPar = 0;

                    if (u_term[list][i + 1] == 'n') //ln
                    {
                        i + 2; //skip n(
                        leftPar++;
                        double u_value = 0;

                        while (leftPar != rightPar)
                        {
                            if (u_term[list][i] == '(')
                                leftPar++;
                            if (u_term[list][i] == ')')
                                rightPar++;

                            u_u += u_term[list][i]; // 3x)
                            i++;
                        }

                        double u_u_value = parseNum(u_u);

                        for (unsigned short i = 0; i < u_u.length; i++)
                        {
                            if (u_u[i] == 'x')
                                u_u_value *= x;
                        }
                        u_value = a_u * log(u_u_value);

                        each_u_value.push(u_value);
                    }

                    else if (u_term[list][i + 1] == 'o') //log10(3x)
                    {
                        i + 2; //skip og
                        string b_u = "", u_u = "";
                        double u_value = 0;

                        while (isNum(u_term[list][i]))
                        {
                            b_u += u_term[list][i];
                            i++;
                        }
                        double b_u_value = parseNum(b_u);

                        i++; //skip(
                        leftPar++;

                        while (leftPar != rightPar)
                        {
                            if (u_term[list][i] == '(')
                                leftPar++;
                            if (u_term[list][i] == ')')
                                rightPar++;

                            u_u += u_term[list][i]; // 3x)
                            i++;
                        }
                        double u_u_value = parseNum(u_u); //3

                        for (unsigned short i = 0; i < u_u.length; i++)
                        {
                            if (u_u[i] == 'x')
                                u_u_value *= x;
                        }

                        u_value = a_u * log_func(b_u_value, u_u_value);

                        each_u_value.push(u_value);
                    }
                }
            }
        }

        for (unsigned list = 0; list < u_operation.length; list++) //get u value
        {

            u_value = parseNum(each_u_value[0]);

            if (u_operation[list] == '+')
                u_value += each_u_value[list++];
            else if (u_operation[list] == '+')
                u_value += each_u_value[list++];
            else if (u_operation[list] == '+')
                u_value += each_u_value[list++];
            else if (u_operation[list] == '+')
                u_value += each_u_value[list++];
        }
    }
    double result = parseNum(term);

    for (unsigned short i = 0; i < term.length; i++) //3x^(5x+2) + 5sin(2x+5)
    {
        if (term[i] == 'x') //5x
        {
            result *= x;
        }
        else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i + 4 < term.length) //trigon
        {
            string tfunc = term.slice(i, i + 3);

            if (tfunc == "sin")
                result *= sin(u_value);
            else if (tfunc == "cos")
                result *= cos(u_value);
            else if (tfunc == "tan")
                result *= tan(u_value);
            else if (tfunc == "cot")
                result /= tan(u_value);
            else if (tfunc == "sec")
                result /= cos(u_value);
            else if (tfunc == "csc")
                result /= sin(u_value);
        }
        else if (term[i] == 'l') //5ln(3x+2)
        {
            if (term[i + 1] == 'n')
                result *= log(u_value);
            else if (term[i + 1] == 'o') //3log10(2x)
            {
                string b = "";
                i += 2; //skip og
                while (term[i] != '(')
                    b += term[i];

                double b_value = parseNum(b);

                result *= log_func(b_value, u_value);
            }
        }
        else if (term[i] == 'x' && term[i + 1] == '^') // 3x^2x
            result *= pow(result, n_value);
    }
    return result;
}

array<string> impliRead(string term)
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

string implFunc(string term, char var) // xy , ysin(x) , (x+y)^2
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
            each_term = impliRead(term); //x,y

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
            each_term = impliRead(term); //x,y

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