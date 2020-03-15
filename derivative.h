#ifndef DERIVATIVE_H
#define DERIVATIVE_H

string Diff(string term, char var) {
    vector<string> u, trigon;
    vector<uint2> trigonIndex, varIndex;
    unit2 outerPair = 0; // for (...)(...)

    for (uint2 i = 0; i < term.size(); i++) {
        // find (type): position and #of x
        if (term[i] == var)
            varIndex.push_back(i);

        // find (type): trigonometric function.
        else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i + 4 < term.size()) {
            string tfunc = StrSplice(term, i, i + 3);

            if (tfunc == "sin" || tfunc == "cos" || tfunc == "tan" || tfunc == "csc" || tfunc == "sec" || tfunc == "cot") {

                uint2 leftPar = 0, rightPar = 0;
                trigonIndex.push_back(i);
                string tempU = "";

                if (term[i + 3] == '^') { // find: a*sin^n(u)
                    i += 4; // skip 'sin^...'
                    while (IsNumber(term[i]))
                        i++;

                    leftPar++;
                    tempU = term[i++];
                    while (i < term.size() && leftPar != rightPar) {
                        if (term[i] == '(') leftPar++;
                        else if (term[i] == ')') rightPar++;

                        tempU += term[i++];
                    }

                    u.push_back(tfunc + tempU);
                }
                else { // find: a*sin(u) or a*sin^1(u)
                    trigon.push_back(tfunc);

                    i += 4; // skip 'sin(...'
                    while (i < term.size() && (term[i] != ')' || leftPar != rightPar)) {
                        if (term[i] == '(') leftPar++;
                        else if (term[i] == ')') rightPar++;

                        tempU += term[i++];
                    }
                    u.push_back(tempU);
                }
            }
        }

        // find (type): logarithm function
        else if (term[i] == 'l' && i + 2 < term.size()) {
            string l;
            if (StrSplice(term, i, i + 3) == "log") {
                l = "log";
            }
            else if (StrSplice(term, i, i + 2) == "ln") {
                l = "ln";
            }
        }
    }

    if (varIndex.size() == 0 && u.size() == 0)
        return "";
    if (term.size() == 1 && term[0] == var)
        return "1";

    string result = "";
    double n = 1, a = 1;

    // main diff function in many cases below...
    if (u.size() == 0) {
        switch (term[varIndex[0] + 1]) {
            case '^': { // CASE: ax^n
                uint2 tpos = varIndex[0] + (term[varIndex[0] + 2] == '(' ? 3 : 2);

                a = varIndex[0] == 0 ? 1 : ParseNum(StrSplice(term, 0, varIndex[0]));
                n = ParseNum(StrSplice(term, tpos, term.size()));

                string strN = "";
                for (uint2 i = tpos; i < term.size() && IsNumber(term[i]); i++) {
                    strN += term[i];
                }

                if (n - 1 == 0)
                    result = Stringify(a * n);
                else if (n - 1 == 1)
                    result = Stringify(a * n) + "x";
                else
                    result = Stringify(a * n) + "x^" + Stringify(n - 1);
            } break;
            case '(': { // CASE: ax^(n)

            } break;
            case '*': { // CASE: ax*(n) or ax*(u)

            } break;
            default: { // CASE ax or ax^1
                result = StrSplice(term, 0, varIndex[0]);
            }
        }
    }
    else {
        if (trigon.size() > 0) { // CASE: a*sin(u) or a*sin^1(u)
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
            a *= trigonIndex[0] == 0 ? 1 : ParseNum(term);

            string chainDiff = Diff(u[0], var);
            bool hasSign = false;
            bool hasXorU = false;

            for (uint2 i = 0; i < chainDiff.size(); i++) {
                if (chainDiff[i] == '+' || chainDiff[i] == '-')
                    hasSign = true;
                else if (chainDiff[i] == var)
                    hasXorU = true;
            }

            if (hasSign)
                result = Stringify(a) + trigon[0] + "(" + u[0] + ")*(" + chainDiff + ")";
            else if (hasXorU)
                result = Stringify(a) + trigon[0] + "(" + u[0] + ")*" + chainDiff;
            else
                result = Stringify(a * ParseNum(chainDiff)) + trigon[0] + "(" + u[0] + ")";
        }
        else if (trigonIndex.size() > 0) { // CASE: a*sin^n(u)
            a = trigonIndex[0] == 0 ? 1 : ParseNum(term);
            n = ParseNum(StrSplice(term, trigonIndex[0] + 4, term.size()));
            string chainDiff = Diff(u[0], var);

            uint2 fisrtParPos = 0;
            for (uint2 i = 0; i < u[0].size() && u[0][i] != '('; i++) { // find fisrt '(' pos
                fisrtParPos++;
            }

            if (n - 1 == 1)
                result = Stringify(a * n) + u[0] + "*" + chainDiff;
            else {
                string tempBlock = StrSplice(u[0], fisrtParPos, u[0].size());
                result = Stringify(a * n) + StrSplice(u[0], 0, 3) + "^" + to_string(n - 1) + tempBlock + "*" + chainDiff;
            }
        }
    }

    return result;
}

#endif