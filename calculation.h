#ifndef CALCULATION_H
#define CALCULATION_H

struct termComponents
{
    string n;
    string b;
    string u;

    void categorizeTerm(string term)
    {
        termComponents value = {};
        string n = "", u = "", e = "";
        unsigned int leftPar = 0, rightPar = 0;

        for (unsigned short i = 0; i < term.length; i++)
        {
            if (term[i] == '^') //x^
            {
                if (term[i + 1] != '(') //x^328
                {
                    i++; //skip ^
                    while (isNum(term[i]) || term[i] == 'x')
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
            else if (term[i] == '(') //sin(u)
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
                        b += term[i];
                        i++;
                    }
                }
                else if (term[i + 2] == 'g') //log
                {
                    i += 2; //skip og
                    while (isNum(term[i]))
                    {
                        b += term[i];
                        i++;
                    }
                }
            }
        }
        value = {n, b, u};
    }
};

struct var_storage{
    double n;
    double u;
};

const double PI = 3.14159265358979323846;

double cal(string term, float x)
{
    termComponents var;
    var.categorizeTerm(term);

    array<string> term_sep = operation(term); //operation between each term

    array<string> n_sep = operation(var.n); //operation between each n

    double result = 0, n = 0, u = 0;
    double a = parseNum(term);
    double a_n = parseNum(var.n);
    double a_u = parseNum(var.u);

    for (unsigned short i = 0; i < var.n.length; i++) // 3x^2sin(3x)
    {
        string n_n = "";
        array<string> n_operate = operation(var.n); //ดูก่อน

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

            double u_value = parseNum(u_n);

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

                n = a_n * logb_value(u_value);
            }

            else if (term[i + 1] == 'n') //x^{ln(5x)}
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

    for (unsigned short i = 0; i < var.u.length; i++) //u
    {
        if (var.u[i] == 's' || var.u[i] == 'c' || var.u[i] == 't') //3{sin(2x)}
        {
            string tfunc = var.u.slice(i, i + 3);
            string u_u = "";
            int leftPar = 0, rightPar = 0;

            i + 4; //skip sin(
            leftPar++;

            while (leftPar != rightPar)
            {
                if (var.u == '(')
                    leftPar++;
                if (var.u == ')')
                    rightPar++;

                u_u += var.u[i]; //3sin{(2x)}
                i++;
            }

            double u_value = parseNum(u_u); //2

            for (unsigned short i = 0; i < u_u.length; i++)
            {
                if (u_u[i] == 'x')
                    u_value *= x;
            }

            if (tfunc == "sin")
                u = a_u * sin(u_value * PI / 180);
            else if (tfunc == "cos")
                u = a_u * cos(u_value * PI / 180);
            else if (tfunc == "tan")
                u = a_u * tan(u_value * PI / 180);
            else if (tfunc == "cot")
                u = a_u / tan(u_value * PI / 180);
            else if (tfunc == "sec")
                u = a_u / cos(u_value * PI / 180);
            else if (tfunc == "csc")
                u = a_u / sin(u_value * PI / 180);
        }
    }
    
    var_storage var_value = {n,u};

    for (unsigned short i = 0; i < term.length; i++)
    {
        if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i + 4 < term.length) //trigon
        {
            string tfunc = term.slice(i, i + 3);        // 3sin
            if (tfunc == "sin")
                result = a * sin(parseNum(var.u) * 180 / PI);   
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

float implCal(string t, float x, float y)
{
    ;
}

#endif