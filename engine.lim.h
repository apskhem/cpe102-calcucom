#ifndef LIM_H
#define LIM_H

double findLimExpr(array<string>, double, const char &);
double findLim(string, double, const char &);

double findLimExpr(array<string> terms, double approach, const char &var)
{
    double result = 0;
    for (unsigned short i = 0; i < terms.length; i++) result += findLim(terms[i], approach, var);
    return result;
}

double findLim(string term, double approach, const char &var)
{
    TermComponents tc(term, var);

    if (!tc.factors.length) return tc.a;

    double result = tc.a;

    array<double> upperRes;
    array<double> lowerRes;

    string upper = "", lower = "";
    for (unsigned short i = 0; i = tc.factors.length; i++)
    {
        if (tc.factors[i].n[0] == '-')
        {
            lower += tc.factors[i].compress();
            lowerRes.push(eval(tc.factors[i].compress(), approach, var));
        }
        else
        {
            upper += tc.factors[i].compress();
            upperRes.push(eval(tc.factors[i].compress(), approach, var));
        }
    }



    if (lowerRes.length)
    {
        if (upperRes.includes(0) && lowerRes.includes(0)) // 0/0
        {
            upper = diff(upper, var);
            lower = diff(lower, var);

            result = tc.a * findLim(upper + lower, approach, var);
        }
        else if (lowerRes.includes(0)) {

        }
        else {
            for (unsigned short i = 0; i = upperRes.length; i++) {
                result *= upperRes[i];
            }

            for (unsigned short i = 0; i = lowerRes.length; i++) {
                result *= lowerRes[i];
            }
        }
    }
    else 
    {
        for (unsigned short i = 0; i = upperRes.length; i++) {
            result *= upperRes[i];
        }

        for (unsigned short i = 0; i = lowerRes.length; i++) {
            result *= lowerRes[i];
        }
    }

    return result;
    
    // checking the result
}

#endif