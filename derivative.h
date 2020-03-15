#ifndef DERIVATIVE_H
#define DERIVATIVE_H

string Diff(string term, char var) {
    array<string> u, trigon;
    array<uint2> trigonIndex, varIndex;
    unit2 outerPair = 0; // for (...)(...)

    for (uint2 i = 0; i < term.length; i++) {
        // find (type): position and #of x
        if (term[i] == var)
            varIndex.push_back(i);

        // find (type): trigonometric function.
        else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i + 4 < term.length) {
            string tfunc = term.slice(i, i + 3);

            if (tfunc == "sin" || tfunc == "cos" || tfunc == "tan" || tfunc == "csc" || tfunc == "sec" || tfunc == "cot") {

                uint2 leftPar = 0, rightPar = 0;
                trigonIndex.push_back(i);
                string tempU = "";

                if (term[i + 3] == '^') { // find: a*sin^n(u)
                    i += 4; // skip 'sin^...'
                    while (isNum(term[i]))
                        i++;

                    leftPar++;
                    tempU = term[i++];
                    while (i < term.length && leftPar != rightPar) {
                        if (term[i] == '(') leftPar++;
                        else if (term[i] == ')') rightPar++;

                        tempU += term[i++];
                    }

                    u.push_back(tfunc + tempU);
                }
                else { // find: a*sin(u) or a*sin^1(u)
                    trigon.push_back(tfunc);

                    i += 4; // skip 'sin(...'
                    while (i < term.length && (term[i] != ')' || leftPar != rightPar)) {
                        if (term[i] == '(') leftPar++;
                        else if (term[i] == ')') rightPar++;

                        tempU += term[i++];
                    }
                    u.push_back(tempU);
                }
            }
        }

        // find (type): logarithm function
        else if (term[i] == 'l' && i + 2 < term.length) {
            string l;
            if (term.slice(i, i + 3) == "log") {
                l = "log";
            }
            else if (term.slice(i, i + 2) == "ln") {
                l = "ln";
            }
        }
    }

    if (varIndex.length == 0 && u.length == 0)
        return "";
    if (term.length == 1 && term[0] == var)
        return "1";

    string result = "";
    double n = 1, a = 1;

    // main diff function in many cases below...
    if (u.length == 0) {
        switch (term[varIndex[0] + 1]) {
            case '^': { // CASE: ax^n
                uint2 tpos = varIndex[0] + (term[varIndex[0] + 2] == '(' ? 3 : 2);

                a = varIndex[0] == 0 ? 1 : parseNum(term.slice(0, varIndex[0]));
                n = parseNum(term.slice(tpos, term.length));

                string strN = "";
                for (uint2 i = tpos; i < term.length && isNum(term[i]); i++) {
                    strN += term[i];
                }

                if (n - 1 == 0)
                    result = toCalStr(a * n);
                else if (n - 1 == 1)
                    result = toCalStr(a * n) + "x";
                else
                    result = toCalStr(a * n) + "x^" + toCalStr(n - 1);
            } break;
            case '(': { // CASE: ax^(n)

            } break;
            case '*': { // CASE: ax*(n) or ax*(u)

            } break;
            default: { // CASE ax or ax^1
                result = term.slice(0, varIndex[0]);
            }
        }
    }
    else {
        if (trigon.length > 0) { // CASE: a*sin(u) or a*sin^1(u)
            if (trigon[0] == "sin")
                trigon[0] = "cos";
            else if (trigon[0] == "cos")
                trigon[0] = "sin"; //-
            else if (trigon[0] == "tan")
                trigon[0] = "sec^2";
            else if (trigon[0] == "csc")
                trigon[0] = "csc()cot()"; //-
            else if (trigon[0] == "sec")
                trigon[0] = "sec()tan()";
            else if (trigon[0] == "cot")
                trigon[0] = "csc^2"; //-

            if (trigon[0] == "sin" || trigon[0] == "csc()*cot()" || trigon[0] == "csc^2") a = -1;
            a *= trigonIndex[0] == 0 ? 1 : parseNum(term);

            string chainDiff = Diff(u[0], var);
            bool hasSign = false;
            bool hasXorU = false;

            for (uint2 i = 0; i < chainDiff.length; i++) {
                if (chainDiff[i] == '+' || chainDiff[i] == '-')
                    hasSign = true;
                else if (chainDiff[i] == var)
                    hasXorU = true;
            }

            if (hasSign)
                result = toCalStr(a) + trigon[0] + "(" + u[0] + ")*(" + chainDiff + ")";
            else if (hasXorU)
                result = toCalStr(a) + trigon[0] + "(" + u[0] + ")*" + chainDiff;
            else
                result = toCalStr(a * parseNum(chainDiff)) + trigon[0] + "(" + u[0] + ")";
        }
        else if (trigonIndex.length > 0) { // CASE: a*sin^n(u)
            a = trigonIndex[0] == 0 ? 1 : parseNum(term);
            n = parseNum(term.slice(trigonIndex[0] + 4, term.length));
            string chainDiff = Diff(u[0], var);

            uint2 fisrtParPos = 0;
            for (uint2 i = 0; i < u[0].length && u[0][i] != '('; i++) { // find fisrt '(' pos
                fisrtParPos++;
            }

            if (n - 1 == 1)
                result = toCalStr(a * n) + u[0] + "*" + chainDiff;
            else {
                string tempBlock = u[0].slice(fisrtParPos, u[0].length);
                result = toCalStr(a * n) + u[0].slice(0, 3) + "^" + toCalStr(n - 1) + tempBlock + "*" + chainDiff;
            }
        }
    }

    return result;
}

#endif