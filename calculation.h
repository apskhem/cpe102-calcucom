#ifndef CALCULATION_H
#define CALCULATION_H

struct termComponents
{
    string n;
    string b;
    string u;

    void categorizeTerm(string term)
    {
        termComponents variable = {};

        unsigned int leftPar = 0, rightPar = 0;

        for (unsigned short i = 0; i < term.length; i++)
        {
            if (term[i] == '^') //x^
            {
                if (term[i + 1] != '(') //x^32
                {
                    i++;                   //skip ^
                    while (isNum(term[i])) //x^{32}
                    {
                        n += term[i];
                        i++;
                    }
                    while (term[i] == 'x') //x^{x}
                    {
                        n += term[i];
                        i++;
                    }
                    if (term[i] == 's' || term[i] == 'c' || term[i] == 't') //x^{sin(2x)}
                    {
                        while (term[i] != ')')
                            n += term[i];
                        i++;
                    }
                    if (term[i] == 'l') //x^{log10(5x)}
                    {
                        if (term[i + 1] == 'n') //ln
                        {
                            while (term[i] != ')')
                            {
                                n += term[i];
                                i++;
                            }
                        }
                        else if (term[i + 2] == 'g') //log
                        {
                            while (term[i] != ')')
                            {
                                n += term[i++];
                                i++;
                            }
                        }
                    }
                }
                else if (term[i + 1] == '(') //x^(328x)
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
            if (term[i] == 'l')
            {
                if (term[i + 2] == 'g') //log
                {
                    i += 2; //skip og
                    while (isNum(term[i]))
                    {
                        b += term[i];
                        i++;
                    }
                }
            }
            if (term[i] == '(') //sin(u)
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
        }
        variable = {n, b, u};
    }
};

const double PI = 3.14159265358979323846;

double log_func(double b, double u)
{
    int log_value = 0;

    log_value = log10(u) / log10(b);

    return log_value;
}

double cal(string term, float x) //-3(x+2)
{
    termComponents var;
    var.categorizeTerm(term);

    double result = parseNum(term), n = 0;
    double a_n = parseNum(var.n);

    for (unsigned short i = 0; i < var.n.length; i++) // 3x^2sin(3x)
    {
        string n_n = "";

        if (var.n[i] == 'x' && var.n[i + 1] == '^') // x^{3x^2}     //power
        {
            int sliceStart = i + 2; // number next to '^'
            i++;                    //skip ^
            while (isNum(var.n[++i]))
                ;

            string power_of_n = var.n.slice(sliceStart, i);
            double n_n = parseNum(power_of_n);

            n = a_n * pow(x, n_n);
        }
        else if (var.n[i] == 's' || var.n[i] == 'c' || var.n[i] == 't') //x^{2sin(2x)}  //trigon
        {
            string tfunc = var.n.slice(i, i + 3);
            string u_n = "";
            int leftPar = 0, rightPar = 0;
            i + 4; //skip sin(
            leftPar++;

            while (leftPar != rightPar)
            {
                if (var.n == '(')
                    leftPar++;
                if (var.n == ')')
                    rightPar++;

                u_n += var.n[i]; //x^2sin({3x})
                i++;
            }

            double u_value = parseNum(u_n); //3

            for (unsigned short i = 0; i < u_n.length; i++)
            {
                if (u_n[i] == 'x')
                    u_value *= x;
            }

            if (tfunc == "sin")
                n = a_n * sin(u_value * PI / 180);
            else if (tfunc == "cos")
                n = a_n * cos(u_value * PI / 180);
            else if (tfunc == "tan")
                n = a_n * tan(u_value * PI / 180);
            else if (tfunc == "cot")
                n = a_n / tan(u_value * PI / 180);
            else if (tfunc == "sec")
                n = a_n / cos(u_value * PI / 180);
            else if (tfunc == "csc")
                n = a_n / sin(u_value * PI / 180);
        }
        else if (var.n[i] == 'l') //log & ln
        {
            if (term[i + 1] == 'o') //x^{3log10(5x)}
            {
                string u_n = "", b_n = "";
                int leftPar = 0, rightPar = 0;

                i += 3; //skip og(

                while (term[i] != '(') //10
                {
                    b_n += term[i];
                    i++;
                }

                double b_value = parseNum(b_n);

                i++; //skip (
                while (term[i] != ')')
                {
                    u_n += term[i];
                    i++;
                }

                double u_value = parseNum(u_n);
                for (unsigned short i = 0; i < u_n.length; i++)
                {
                    if (u_n[i] == 'x')
                        u_value *= x;
                }

                n = a_n * log_func(b_value, u_value);
            }

            else if (term[i + 1] == 'n') //3x^{ln(5x)}
            {
                string u_n = "";
                double log_value = 0;
                int leftPar = 0, rightPar = 0;

                i += 2; //skip n(

                while (term[i] != ')')
                {
                    u_n += term[i];
                    i++;
                }

                double u_value = parseNum(u_n);
                for (unsigned int i = 0; i < u_n.length; i++)
                {
                    if (u_n[i] == 'x')
                        u_value *= x;
                }
                n = a_n * log(u_value);
            }
        }
    }

    double u = 0;
    array<string> u_term = readExpr(var.u); //3sin({2sin(5x)+3x+7ln(3x)+5x^2})
    array<string> u_operation = operation(var.u);
    array<double> each_u_value;
    double a_u = 0;

    for (unsigned short list = 0; list < u_term.length; list++) //2sin(5x), 3x, 7ln(3x), 5x^2
    {
        a_u = parseNum(u_term[list]); //list[0] a_u = 2

        for (unsigned short i = 0; i < u_term[list].length; i++) // 2sin(5x)
        {
            if (u_term[list][i] == '^')     //5x^2
            {
                if(u_term[list][i] || u_term[list][i+1] != '(') //5x^2
                {
                    string n_u = "";
                    i++; //skip ^
                    while(isNum(u_term[list][i]) || u_term[list][i] == 'x'){
                        n_u += u_term[list][i];
                        i++;
                    }
                    
                    double n_u_value = x;
                    double u_value = 0;

                    u_value = a_u * pow(x,x);

                    each_u_value.push(u_value);
                }
                else //5x^(2x)
                {
                    string n_u = "";
                    i++; //skip ^
                    while(isNum(u_term[list][i]) || u_term[list][i] == 'x'){
                        n_u += u_term[list][i];
                        i++;
                    }

                    double n_u_value = parseNum(n_u);       //2

                    for(unsigned short i = 0; i < n_u.length; i++){
                        if(n_u[i] == 'x')       //2x
                            n_u_value *= x;
                    }
                    double u_value = 0;
                    
                    u_value = a_u * pow(x,n_u_value);

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

    for (unsigned short i = 0; i < term.length; i++) //3sin(2x)
    {
        if (term[0] == '-' && !isNum(term[i + 1]))
        { //-(x+2)
            result *= -1;
        }
        if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i + 4 < term.length) //trigon
        {
            string tfunc = term.slice(i, i + 3); // 3xsin(2x)******
            if (tfunc == "sin")
                result *= sin(u);
            else if (tfunc == "cos")
            {
                result *= cos(u);
            }
            else if (tfunc == "tan")
            {
                result *= tan(u);
            }
            else if (tfunc == "cot")
            {
                result /= tan(u);
            }
            else if (tfunc == "sec")
            {
                result /= cos(u);
            }
            else if (tfunc == "csc")
            {
                result /= sin(u);
            }
        }
        else if (term[i] == 'l')
        {
            /*  if (term[i] == 'x')
            {
                result *= x;
            }*/
            if (term[i + 1] == 'n') //3xln(2x)*************
            {
                result *= log(u);
            }
            else if (term[i + 1] == 'o') //3log10(2x)
            {
                string base = "";
                i += 2; //skip og
                while (term[i] != '(')
                    base += term[i];

                double base_value = parseNum(base);

                result *= log_func(base_value, u);
            }
        }
        else if (term[i] == 'x' && term[i + 1] == '^') // 3x^2x
        {
            if (term[i] == 'x')
                result *= x;

            result = pow(result, n);
        }
    }
    return result;
}

float implCal(string t, float x, float y)
{
    ;
}

#endif