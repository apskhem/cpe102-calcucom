#ifndef CALCULATION_H
#define CALCULATION_H

const double PI = 3.14159265358979323846;

double log_func(double b, double u)
{
    int log_value = 0;
    log_value = log10(u) / log10(b);

    return log_value;
}

double cal(string term, float x) //-3(x+2)
{
    TermComponents var(term);

    double n_value = 0;
    array<string> n_operation = operation(var.n);
    array<string> n_term = readExpr(var.n);
    array<double> each_n_value;

    for (unsigned short list = 0; list < n_term.length; list++) // 3x^{2sin(3x)+2x^3+5ln(3x)}
    {
        double a_n = parseNum(n_term[list]);

        for (unsigned short i = 0; i < n_term[list].length; i++)
        {
            string n_n = "";

            if (n_term[list][i] == 'x' && n_term[list][i + 1] == '^') // 2x^3
            {
                double n_value;
                int sliceStart = i + 2; // number next to '^'
                i++;                    //skip ^
                while (isNum(n_term[list][++i]))
                    ;

                string n_n = n_term[list].slice(sliceStart, i); //3

                double n_n_value = parseNum(n_n);

                for (unsigned short i = 0; i < n_n.length; i++)
                {
                    if (n_n[i] == 'x')
                        n_n_value *= x;
                }
                n_value = a_n * pow(x, n_n_value);

                each_n_value.push(n_value);
            }
            else if (n_term[list][i] == 's' || n_term[list][i] == 'c' || n_term[list][i] == 't') //2sin(3x)
            {
                string tfunc = n_term[list].slice(i, i + 3); //sin
                string u_n = "";

                int leftPar = 0, rightPar = 0;
                i + 4; //skip sin(
                leftPar++;

                while (n_term[list][i] != ')')
                {
                    u_n += n_term[list][i]; //3x
                    i++;
                }

                double u_n_value = parseNum(u_n); //3

                for (unsigned short i = 0; i < u_n.length; i++)
                {
                    if (u_n[i] == 'x')
                        u_n_value *= x;
                }

                double n_value;

                if (tfunc == "sin")
                    n_value = a_n * sin(u_n_value * PI / 180);
                else if (tfunc == "cos")
                    n_value = a_n * cos(u_n_value * PI / 180);
                else if (tfunc == "tan")
                    n_value = a_n * tan(u_n_value * PI / 180);
                else if (tfunc == "cot")
                    n_value = a_n / tan(u_n_value * PI / 180);
                else if (tfunc == "sec")
                    n_value = a_n / cos(u_n_value * PI / 180);
                else if (tfunc == "csc")
                    n_value = a_n / sin(u_n_value * PI / 180);

                each_n_value.push(n_value);
            }
            else if (n_term[list][i] == 'l') //log & ln             //5ln(3x)
            {
                if (term[i + 1] == 'o') //5log10(3x)
                {
                    string u_n = "", b_n = "";
                    int leftPar = 0, rightPar = 0;

                    i += 3; //skip og(

                    while (term[i] != '(') //10
                    {
                        b_n += term[i];
                        i++;
                    }

                    double b_n_value = parseNum(b_n);

                    i++; //skip (
                    while (term[i] != ')')
                    {
                        u_n += term[i];
                        i++;
                    }

                    double u_n_value = parseNum(u_n);
                    for (unsigned short i = 0; i < u_n.length; i++)
                    {
                        if (u_n[i] == 'x')
                            u_n_value *= x;
                    }
                    double n_value;

                    n_value = a_n * log_func(b_n_value, u_n_value);

                    each_n_value.push(n_value);
                }

                else if (term[i + 1] == 'n') //3x^{ln(5x)}
                {
                    string u_n = "";
                    double log_value;
                    int leftPar = 0, rightPar = 0;

                    i += 2; //skip n(

                    while (term[i] != ')')
                    {
                        u_n += term[i];
                        i++;
                    }

                    double u_n_value = parseNum(u_n);
                    for (unsigned int i = 0; i < u_n.length; i++)
                    {
                        if (u_n[i] == 'x')
                            u_n_value *= x;
                    }
                    double n_value;

                    n_value = a_n * log(u_n_value);

                    each_n_value.push(n_value);
                }
            }
        }
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

    double u_value = 0;
    array<string> u_term = readExpr(var.u); //3sin({2sin(5x)+3x+7ln(3x)+5x^2})
    array<string> u_operation = operation(var.u);
    array<double> each_u_value;

    for (unsigned short list = 0; list < u_term.length; list++) //2sin(5x), 3x, 7ln(3x), 5x^2
    {
        double a_u = parseNum(u_term[list]); //list[0] a_u = 2

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
}

    string implFunc(string term, char var) // xy , ysin(x) , (x+y)^2
    {
        array<string> each_term = readExpr(term); //y , sin(x)
        string result = "";
        double a = parseNum(term);

        result += toCalStr(a);

        if (var == 'x') //dy/dx
        {
            for (unsigned i = 0; i < each_term.length; i++)
            {
                if (i > 0) // xy
                    result += "+";

                if (each_term.includes("x") && each_term.includes("y")) // (x+y)^2
                {
                    string mini_result = "(";
                    array<string> mini_each_term = readExpr(each_term[i]); // x,y

                    for (unsigned j = 0; j < mini_each_term.length; j++)
                    {
                        if (j > 0)
                            mini_result += "+";
                        if (each_term.includes("x"))
                            mini_result += "(" + toCalStr(parseNum(mini_each_term[i])) + diff(mini_each_term[i], 'x') + ")";
                        if (each_term.includes("y"))
                            mini_result += "(" + toCalStr(parseNum(mini_each_term[i])) + diff(mini_each_term[i], 'y') + ")(dy/dx)";
                        mini_result += ")";
                    }
                    result += diff();
                }
                else if (each_term.includes("x")) //x
                    result += "(" + diff(each_term[i], 'x') + ")";
                else if (each_term.includes("y")) //y
                {
                    result += "(" + diff(each_term[i], 'y') + ")";
                    result += "(dy/dx)";
                }
            }
        }
        if (var == 'y')
        {
            for (unsigned i = 0; i < each_term.length; i++)
            {
                if (i > 0) // xy
                    result += "+";

                if (each_term.includes("x") && each_term.includes("y")) // (x+y)
                {
                    string mini_result = "(";
                    array<string> mini_each_term = readExpr(each_term[i]); // x,y

                    for (unsigned j = 0; j < mini_each_term.length; j++)
                    {
                        if (j > 0) // xy
                            result += "+";
                        if (each_term.includes("x"))
                            mini_result += "(" + toCalStr(parseNum(mini_each_term[i])) + diff(mini_each_term[i], 'x') + ")(dx/dy)";
                        if (each_term.includes("y"))
                            mini_result += "(" + toCalStr(parseNum(mini_each_term[i])) + diff(mini_each_term[i], 'y') + ")";
                        mini_result += ")";
                    }
                    result += diff(each_term[i], 'y')
                }
                else if (each_term.includes("x")) //x
                {
                    result += "(" + diff(each_term[i], 'x') + ")";
                    result += "(dx/dy)";
                }
                else if (each_term.includes("y")) //y
                    result += "(" + diff(each_term[i], 'y') + ")";
            }
        }

        return result;
    }

#endif