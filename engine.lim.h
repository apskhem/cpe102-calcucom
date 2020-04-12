#ifndef LIM_H
#define LIM_H

double findLim(string, double, const char &);

double findLim(string expr, double x, const char &var)
{
    double result = evalExpr(splitTerm(expr), x, var);
    double NAN;
    double INFINITY;

    if (result <= INFINITY)
    {
        return result;
    }
    else
    {
        string a = "", b = "";
        int pos = expr.search('/');
        int posM = expr.search('-');
        int posMul = expr.search('*');
        int posP = expr.search('^');

        double resultA = evalExpr(splitTerm(a), x, var);
        double resultB = evalExpr(splitTerm(b), x, var);

        if (expr[pos] == '/')
        {
            a = expr.slice(0, pos);
            b = expr.slice(pos+1);

            if (resultA <= INT_MAX && resultB == 0)
            {
                return NAN; //case ค่าคงที่ หาร ์ NAN
            }
            else if (resultA == NAN && resultB == NAN)
            {
                double diffA = evalExpr(splitTerm(diff(a, var)), x, var);
                double diffB = evalExpr(splitTerm(diff(diff(b, var), var)), x, var);

                if (diffA / diffB <= INT_MAX)
                {
                    return resultA <= INT_MAX && resultB;
                }
                else
                {
                    expr = diff(a, var) + "/" + diff(b, var);
                }

                //case NAN หาร NAN
            }
            else if (resultA == 0 && resultB == 0)
            {
                if (evalExpr(splitTerm(diff(a, var)), x, var) / evalExpr(splitTerm(diff(diff(b, var), var)), x, var) <= INT_MAX)
                {
                    return resultA <= INT_MAX && resultB;
                }
                else
                {
                    expr = diff(a, var) + "/" + diff(b, var);
                }
                // case 0/0
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        else if (expr[pos] != '/')
        {
            int posM = expr.search('-');

            if (expr[posM] == '-')
            {
                for (unsigned int i = 0; i < posM; ++i)
                {
                    a += expr[i];
                }
                for (unsigned int j = posM + 1; j <= expr.length; ++j)
                {
                    b += expr[j];
                }
            }

            int posln = a.search("ln");
            int posln2 = b.search("ln");

            if (expr[posln] == 'l' && expr[posln2] == 'l' && resultA == NAN && resultB == NAN)
            {
                if (log(resultA / resultB) <= INT_MAX)
                {
                    return log(resultA / resultB);
                }
                else
                {
                    expr = "Not to find";
                } //เคส NAN - NAN
            }
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////

        else if (expr[pos] != '/' && expr[posM] != '-')
        {
            int posMul = expr.search('*');

            if (expr[posMul] == '*')
            {
                for (unsigned int i = 0; i < posMul; ++i)
                {
                    a += expr[i];
                }
                for (unsigned int j = posMul + 1; j <= expr.length; ++j)
                {
                    b += expr[j];
                }
            }
            if (resultA == NAN && resultB == 0 || resultB == NAN && resultA == 0)
            {

                if (resultA / resultB <= INT_MAX)
                {
                    return resultA / resultB;
                }
                else if (resultB / resultA <= INT_MAX)
                {
                    return resultB / resultA;
                }
                else
                {
                    expr = "Not to find";
                }

                 //เคส NAN * 0 หรือ 0*NAN
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        else if (expr[pos] != '/' && expr[posM] != '-' && expr[posMul] != '*')
        {
            int posP = expr.search('^');

            if (expr[posP] == '^')
            {
                for (unsigned int i = 0; i < posP; ++i)
                    a += expr[i];
                for (unsigned int j = posP + 1; j <= expr.length; ++j)
                    b += expr[j];
            }
            if (resultA == NAN && resultB == 0)
            {
                expr = b + "ln(" + expr.slice(0, expr.length) + ")";
            }
            else if (resultB == NAN && resultA == 0)
            {

                expr = b + "ln(" + expr.slice(0, expr.length) + ")";

            } //เคส NAN ^ 0 หรือ 0 ^ NAN

            else if (resultA == 1 && resultB == NAN)
            {
                expr = b + "ln(" + expr.slice(0, expr.length) + ")";

                //เคส ค่าคงที่ ^ 0 หรือ ค่าคงที่ ^ NAN
            }
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( evalExpr(splitTerm(expr), x, var) == NAN)
        {
            findLim(expr, x, var);
        } 

        // if( evalExpr(readExpr(eqation),x,'x')==NAN){
        // FindLim(eqation,a,b,x);}
    }
}

#endif