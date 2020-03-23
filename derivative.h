#ifndef DERIVATIVE_H
#define DERIVATIVE_H

array<string> readExpr(string);
string exprDiff(array<string> terms, char var);
string diff(string term, char var);

class TermComponents {
    // 3x^2 + 3sin(2x) + 5log10(3x) + 7ln(5x) + 5x^(2x+3)
    public:
        array<string> u, n, trigon, log;
        array<unsigned short> trigonIndex, varIndex, logIndex;
    
        TermComponents(string) {
            for (unsigned short i = 0; i < term.length; i++) {
                // find (type): position and #of x
                if (term[i] == var)
                    varIndex.push(i);

                // find (type): trigonometric function.
                else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i + 5 < term.length) {
                    string tfunc = term.slice(i, i + 3);

                    if (tfunc == "sin" || tfunc == "cos" || tfunc == "tan" || tfunc == "csc" || tfunc == "sec" || tfunc == "cot") {
                        trigonIndex.push(i);
                        string tempU = "";

                        i += 4; // skip 'sin^...'
                        if (term[i-1] == '^') { // find: a*sin^n(u)
                            if (term[i] == '(') {

                            }
                            else {
                                while (isNum(term[i++]));
                            }
                            
                            tempU = tfunc + "(";
                        }
                        else if (term[i-1] == '(') { // find: a*sin(u) or a*sin^1(u)
                            trigon.push(tfunc);
                        }

                        // loop for collect U
                        unsigned short leftPar = 1, rightPar = 0;
                        while (i < term.length) {
                            if (term[i] == '(') leftPar++;
                            else if (term[i] == ')') {
                                if (leftPar == ++rightPar) break;
                            }

                            tempU += term[i++];
                        }

                        u.push(tempU);
                    }
                }

                // find (type): logarithm function
                else if (term[i] == 'l' && i + 4 < term.length) {
                    string l = term.slice(i, i+2); // lo || ln

                    if (l == "lo" || l == "ln") {
                        logIndex.push(i);
                        string tempU = "";

                        i+=3; // skip 'log...' or 'ln(...'
                        if (l == "lo") {
                            log.push("log");

                            if (!isNum(term[i]))
                                throw "Bad arithmetic expression: no base value after 'log'.";

                            while(isNum(term[i++]));

                            if (term[i++] == '^') { // also skip '(...'
                                if (term[i] == '(') {

                                }
                                else {
                                    while(isNum(term[i++]));
                                }
                            }
                        }
                        else if (l == "ln") {
                            log.push("ln");
                        }

                        // loop for collect U
                        unsigned short leftPar = 1, rightPar = 0;
                        while (i < term.length) {
                            if (term[i] == '(') leftPar++;
                            else if (term[i] == ')') {
                                if (leftPar == ++rightPar) break;
                            }

                            tempU += term[i++];
                        }

                        u.push(tempU);
                    }
                }

                // find (type): function inside '('
                else if (term[i] == '(') {
                    string tempU = "";
                    unsigned short leftPar = 1, rightPar = 0;
                    while (i < term.length) {
                        if (term[i] == '(') leftPar++;
                        else if (term[i] == ')') {
                            if (leftPar == ++rightPar) break;
                        }

                        tempU += term[i++];
                    }

                    u.push(tempU);
                }
            }
        }
};

array<string> readExpr(string expr) {
    array<string> terms;

    unsigned leftPar = 0, rightPar = 0;

    // pre-reading process
    expr = expr.replace(" ", "");

    // reading equation process
    unsigned splitIndex = 0;
    for (unsigned i = 0; i < expr.length; i++) {
        if (expr[i] == '(') leftPar++;
        else if (expr[i] == ')') rightPar++;

        if ((expr[i] == '+' || expr[i] == '-') && expr[i - 1] != '^' && leftPar == rightPar) {
            terms.push(expr.slice(splitIndex, i));
            splitIndex = i + (expr[i] == '+' ? 1 : 0);
        }

        if (i >= expr.length - 1) {
            terms.push(expr.slice(splitIndex));
        }
    }

    // check for errors
    if (leftPar != rightPar)
        throw "Bad arithmetic expression: no complete pair of parentheses ['()'].";

    return terms;
}

string exprDiff(array<string> terms, char var) {
    string result = "";
    for (unsigned i = 0; i < terms.length; i++) {
        if (i > 0 && diff(terms[i])[0] != '-')
            result += "+";

        result += diff(TermComponents(terms[i]), var);
    }
    return result;
}

string diff(TermComponents tc, char var) {
    if (varIndex.length == 0 && u.length == 0) return ""; // only c
    if (tc.length == 1 && tc[0] == var) return "1"; // only single x

    string result = "";
    double n = 1, a = 1;

    if (u.length > 1) { // (2x+3)(6x^3-2x)
        for (unsigned i = 0; i < u.length; i++) {
            if (i > 0)
                result += "+";

            for (unsigned j = 0; j < u.length; j++) {
                result += "(";
                result += (i == j ? exprDiff(readExpr(u[i]), var) : u[i]);
                result += ")";
            }
        }
    }
    else if (u.length == 1) {
        if (trigon.length) { // CASE: a*sin(u) or a*sin^1(u)
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
            if (trigonIndex[0] != 0) a *= parseNum(tc);

            string chainDiff = diff(u[0], var);
            bool hasSign = (chainDiff.includes("+") || chainDiff.includes("-"));
            bool hasVarOrU = chainDiff.includes(var);

            if (hasSign || hasVarOrU)
                result = toCalStr(a) + trigon[0] + "(" + u[0] + ")(" + chainDiff + ")";
            else
                result = toCalStr(a * parseNum(chainDiff)) + trigon[0] + "(" + u[0] + ")";
        }
        else if (trigonIndex.length > 0) { // CASE: a*sin^n(u)
            if (trigonIndex[0] != 0) a *= parseNum(tc);
            n = parseNum(tc, trigonIndex[0] + 4);
            string chainDiff = diff(u[0], var);

            unsigned short fisrtParPos = 0;
            for (unsigned short i = 0; i < u[0].length && u[0][i] != '('; i++) { // find fisrt '(' pos
                fisrtParPos++;
            }

            if (n - 1 == 1)
                result = toCalStr(a * n) + u[0] + "*" + chainDiff;
            else {
                string tempBlock = u[0].slice(fisrtParPos, u[0].length);
                result = toCalStr(a * n) + u[0].slice(0, 3) + "^" + toCalStr(n - 1) + tempBlock + "*" + chainDiff;
            }
        }
        /*
        else if (arc.length){
            a *= parseNum(tc);

            string chainDiff = diff(u[0], var);
            bool hasSign = (chainDiff.includes("+") || chainDiff.includes("-"));
            bool hasVarOrU = chainDiff.includes(var);

            if (arc[0] == "sin")
            {
                if (hasSign || hasVarOrU) // 5arcsin(3x^2 + 5x) => 5(6x+5)
                    result = toCalStr(a) + "(" + chainDiff + ") / sqrt(1 - (" + u[0] + ")^2 )";
                else // 5arcsin(3x) => 5(3)
                    result = toCalStr(a * parseNum(chainDiff)) + ") / sqrt(1 - (" + u[0] + ")^2 )";
            }
            else if (arc[0] == "cos"){
                a *= -1;
                if (hasSign || hasVarOrU) // 5arccos(3x^2 + 5x) => 5(6x+5)
                    result = toCalStr(a) + "(" + chainDiff + ") / sqrt(1 - (" + u[0] + ")^2 )";
                else // 5arcsin(3x) => 5(3)
                    result = toCalStr(a * parseNum(chainDiff)) + ") / sqrt(1 - (" + u[0] + ")^2 )";
            }
            else if (arc[0] == "tan"){
                if (hasSign || hasVarOrU) // 5arctan(3x^2 + 5x) => 5(6x+5)
                    result = toCalStr(a) + "(" + chainDiff + ") / sqrt(1 + (" + u[0] + ")^2 )";
                else // 5arctan(3x) => 5(3)
                    result = toCalStr(a * parseNum(chainDiff)) + ") / sqrt(1 + (" + u[0] + ")^2 )";
            }
            else if (arc[0] == "cot"){
                a *= -1;
                if (hasSign || hasVarOrU) // 5arccot(3x^2 + 5x) => 5(6x+5)
                    result = toCalStr(a) + "(" + chainDiff + ") / sqrt(1 + (" + u[0] + ")^2 )";
                else // 5arccot(3x) => 5(3)
                    result = toCalStr(a * parseNum(chainDiff)) + ") / sqrt(1 + (" + u[0] + ")^2 )";
            }
            else if (arc[0] == "sec"){
                if (hasSign || hasVarOrU) // 5arcsec(3x^2 + 5x) => 5(6x+5)
                    result = toCalStr(a) + "(" + chainDiff + ") / |" + u[0] + "|(sqrt(" + u[0] + ")^2 -1 )";
                else // 5arctan(3x) => 5(3)
                    result = toCalStr(a * parseNum(chainDiff)) + ") / |" + u[0] + "|(sqrt(" + u[0] + ")^2 -1 )";
            }
            else if (arc[0] == "csc"){
                a *= -1;
                if (hasSign || hasVarOrU) // 5arcsec(3x^2 + 5x) => 5(6x+5)
                    result = toCalStr(a) + "(" + chainDiff + ") / |" + u[0] + "|(sqrt(" + u[0] + ")^2 -1 )";
                else // 5arctan(3x) => 5(3)
                    result = toCalStr(a * parseNum(chainDiff)) + ") / |" + u[0] + "|(sqrt(" + u[0] + ")^2 -1 )";
            }
        }
        else if (log.length) {
            if (trigonIndex[0] != 0)
            {
                a *= parseNum(tc);
                string chainDiff = diff(u[0], var);
                short idx = 0;
                for(unsigned i = 0; i < tc.log.length; i++){
                    if(!isNum(tc.log))
                        break;
                    else 
                        idx++;
                }
                string b = log.splice(3,3+idx);   

                bool hasSign = (chainDiff.includes("+") || chainDiff.includes("-"));
                bool hasVarOrU = chainDiff.includes(var);

                if  (hasSign || hasVarOrU)    // -5log10(5x^2 + sin(x)) => 5x + cos(x)
                    result = toCalStr(a) + "(" + chainDiff + ")/(" + u[0] + ")(ln(" + b + ")";
                else    // -5log10(5x+10) => 5      
                    result = toCalStr(a * parseNum(chainDiff))+ ")/(" + u[0] + ")(ln(" + b + ")";
            }
            if (log[0] == "ln"){
                a *= parseNum(tc);
                string chainDiff = diff(u[0], var);
                bool hasSign = (chainDiff.includes("+") || chainDiff.includes("-"));
                bool hasVarOrU = chainDiff.includes(var);

                if  (hasSign || hasVarOrU)    // -5ln(5x^2 + sin(x)) => 5x + cos(x)
                    result = toCalStr(a) + "(" + chainDiff + ")/(" + u[0] + ")";
                else    // -5ln(5x+10) => 5      
                    result = toCalStr(a * parseNum(chainDiff))+ ")/(" + u[0] + ")";
            }
        }
    }
    */
    else if (u.length == 0) {
        switch (tc[varIndex[0] + 1]) {
            case '^': { // CASE: ax^n or ax^(n)
                unsigned short nIndex = varIndex[0] + (tc[varIndex[0] + 2] == '(' ? 3 : 2);

                if (tc[varIndex[0] + 2] == '(') {

                }

                a = varIndex[0] == 0 ? 1 : parseNum(tc, 0, varIndex[0]);
                n = parseNum(tc, nIndex);

                string strN = "";
                for (unsigned short i = nIndex; i < tc.length && isNum(tc[i]); i++)
                    strN += tc[i];

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
                result = tc.slice(0, varIndex[0]);
            }
        }
    }

    return result;
}

#endif