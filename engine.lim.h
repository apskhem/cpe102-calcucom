#ifndef LIM_H
#define LIM_H

double FindLim(string &, double);

double FindLim(string &equation, double x){
	
	string a = "", b = "";

    if (evalExpr(readExpr(equation), x, 'x') <= INT_MAX)
    {
        return evalExpr(readExpr(equation), x, 'x');
    }
    else
    {
        int pos = equation.search('/');
        int posM = equation.search('-');
        int posMul = equation.search('*');
        int posP = equation.search('^');

        if (equation[pos] == '/')
        {
            for (unsigned int i = 0; i < pos; ++i)
            {
                a += equation[i];
            }
            for (unsigned int j = pos + 1; j <= equation.length; ++j)
            {
                b += equation[j];
            }

            if (evalExpr(readExpr(a), x, 'x') <= INT_MAX && evalExpr(readExpr(b), x, 'x') == 0)
            {
                return NAN; //case ค่าคงที่ หาร ์ NAN
            }
            else if (evalExpr(readExpr(a), x, 'x') == NAN && evalExpr(readExpr(b), x, 'x') == NAN)
            {
                if (evalExpr(readExpr(diff(a, 'x')), x, 'x') / evalExpr(readExpr(diff(diff(b, 'x'), 'x')), x, 'x') <= INT_MAX)
                {
                    return evalExpr(readExpr(a), x, 'x') <= INT_MAX && evalExpr(readExpr(b), x, 'x');
                }
                else
                {
                    equation = diff(a, 'x') + "/" + diff(b, 'x');
                }

                //case NAN หาร NAN
            }
            else if (evalExpr(readExpr(a), x, 'x') == 0 && evalExpr(readExpr(b), x, 'x') == 0)
            {
                if (evalExpr(readExpr(diff(a, 'x')), x, 'x') / evalExpr(readExpr(diff(diff(b, 'x'), 'x')), x, 'x') <= INT_MAX)
                {
                    return evalExpr(readExpr(a), x, 'x') <= INT_MAX && evalExpr(readExpr(b), x, 'x');
                }
                else
                {
                    equation = diff(a, 'x') + "/" + diff(b, 'x');
                }
                // case 0/0
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        else if (equation[pos] != '/')
        {
            int posM = equation.search('-');

            if (equation[posM] == '-')
            {
                for (unsigned int i = 0; i < posM; ++i)
                {
                    a += equation[i];
                }
                for (unsigned int j = posM + 1; j <= equation.length; ++j)
                {
                    b += equation[j];
                }
            }

            int posln = a.search("ln");
            int posln2 = b.search("ln");

            if (equation[posln] == 'ln' && equation[posln2] == 'ln')
            {

                if (evalExpr(readExpr(a), x, 'x') == NAN && evalExpr(readExpr(b), x, 'x') == NAN)
                {

                    if (log(evalExpr(readExpr(a), x, 'x') / evalExpr(readExpr(b), x, 'x')) <= INT_MAX)
                    {
                        return log(evalExpr(readExpr(a), x, 'x') / evalExpr(readExpr(b), x, 'x'));
                    }
                    else
                    {
                        equation = "Not to find";
                    } //เคส NAN - NAN
                }
            }
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////

        else if (equation[pos] != '/' && equation[posM] != '-')
        {
            int posMul = equation.search('*');

            if (equation[posMul] == '*')
            {
                for (unsigned int i = 0; i < posMul; ++i)
                {
                    a += equation[i];
                }
                for (unsigned int j = posMul + 1; j <= equation.length; ++j)
                {
                    b += equation[j];
                }
            }
            if (evalExpr(readExpr(a), x, 'x') == NAN && evalExpr(readExpr(b), x, 'x') == 0 || evalExpr(readExpr(b), x, 'x') == NAN && evalExpr(readExpr(a), x, 'x') == 0)
            {

                if (evalExpr(readExpr(a), x, 'x') / evalExpr(readExpr(b), x, 'x') <= INT_MAX)
                {
                    return evalExpr(readExpr(a), x, 'x') / evalExpr(readExpr(b), x, 'x');
                }
                else if (evalExpr(readExpr(b), x, 'x') / evalExpr(readExpr(a), x, 'x') <= INT_MAX)
                {
                    return evalExpr(readExpr(b), x, 'x') / evalExpr(readExpr(a), x, 'x');
                }
                else
                {
                    equation = "Not to find";
                }

                ; //เคส NAN * 0 หรือ 0*NAN
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        else if (equation[pos] != '/' && equation[posM] != '-' && equation[posMul] != '*')
        {
            int posP = equation.search('^');

            if (equation[posP] == '^')
            {
                for (unsigned int i = 0; i < posP; ++i)
                {
                    a += equation[i];
                }
                for (unsigned int j = posP + 1; j <= equation.length; ++j)
                {
                    b += equation[j];
                }
            }
            if (evalExpr(readExpr(a), x, 'x') == NAN && evalExpr(readExpr(b), x, 'x') == 0)
            {
                string p;
                p = equation.slice(0, equation.length);

                equation = b + "ln(" + p + ")";
            }
            else if (evalExpr(readExpr(b), x, 'x') == NAN && evalExpr(readExpr(a), x, 'x') == 0)
            {
                string p;
                p = equation.slice(0, equation.length);

                equation = b + "ln(" + p + ")";

            } //เคส NAN ^ 0 หรือ 0 ^ NAN

            else if (evalExpr(readExpr(a), x, 'x') == 1 && evalExpr(readExpr(b), x, 'x') == NAN)
            {
                string p;
                p = equation.slice(0, equation.length);

                equation = b + "ln(" + p + ")";

                ; //เคส ค่าคงที่ ^ 0 หรือ ค่าคงที่ ^ NAN
            }
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}

#endif
