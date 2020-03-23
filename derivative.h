#ifndef DERIVATIVE_H
#define DERIVATIVE_H

/* The method splits expression into arrays of term. */
array<string> readExpr(string);
/* The methood turns arrays of term into a new derivative expression. */
string exprDiff(array<string> terms, char var);
/* The methood turns a single term into a new derivative term. */
string diff(string term, char var);

class TermComponents {
    public:
        string src;
        array<string> u, n, trigon, log, arc;
        array<unsigned short> trigonIndex, varIndex, logIndex, nIndex, arcIndex, allIndex;
        unsigned forcedOp = 0; // 1 = mul
    
        TermComponents(string term);
    private:
        /* the start position of 'i' should be the position of '(' + 1 */
        string ElementInsidePar(unsigned &i);
        /* checkingPos should be the index position of '^' */
        bool checkForN(unsigned &i, unsigned checkingPos);
};

TermComponents::TermComponents(string term) {
    src = term;
    for (unsigned short i = 0; i < term.length; i++) {
        // find (type): position and #of x
        if (term[i] == var) {
            varIndex.push(i);
            checkForN(i, i+1);
        }

        // find (type): trigonometric function.
        else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i + 5 < term.length) {
            string tfunc = term.slice(i, i + 3);

            if (tfunc == "sin" || tfunc == "cos" || tfunc == "tan" || tfunc == "csc" || tfunc == "sec" || tfunc == "cot") {
                trigonIndex.push(i);

                i += 4; // skip 'sin^...' or 'sin(...'
                if (checkForN(i, i-1)) { // find: a*sin^n(u)
                    while(term[i++] != '(');
                    u.push(tfunc + "(" + ElementInsidePar(i) + ")");
                }
                else { // find: a*sin(u) or a*sin^1(u)
                    trigon.push(tfunc);
                    u.push(ElementInsidePar(i));
                }
            }
            else {
                error("none standard arithmatic expression presented");
            }
        }

        // find (type): inverse trigon function
        else if (term[i] == 'a') {
            string tfunc = term.slice(i+1, i+4);

            if (tfunc == "sin" || tfunc == "cos" || tfunc == "tan" || tfunc == "csc" || tfunc == "sec" || tfunc == "cot")  {
                tfunc = "a" + tfunc;
                arcIndex.push(i);

                i += 4; // skip 'sin^...' or 'sin(...'
                if (checkForN(i, i-1)) { // find: a*sin^n(u)
                    while(term[i++] != '(');
                    u.push(tfunc + "(" + ElementInsidePar(i) + ")");
                }
                else { // find: a*sin(u) or a*sin^1(u)
                    arc.push(tfunc);
                    u.push(ElementInsidePar(i));
                }
            }
            else {
                error("none standard arithmatic expression presented");
            }
        }

        // find (type): logarithm function
        else if (term[i] == 'l' && i + 4 < term.length) {
            string l = term.slice(i, i+2); // lo || ln

            if (l == "lo" || l == "ln") {
                logIndex.push(i);

                i+=3; // skip 'log...' or 'ln(...'
                if (l == "lo") {
                    if (!isNum(term[i]))
                        error("no base value after 'log'");

                    while(isNum(term[i++]));
                    
                    if (checkForN(i, i)) {
                        while(term[i++] != '(');
                        u.push(ElementInsidePar(i));
                    }
                    else {
                        log.push("log" + term.slice(logIndex[logIndex.length-1], i));
                        u.push(ElementInsidePar(i));
                    }
                }
                else if (l == "ln") {
                    log.push("ln");
                }

                u.push(ElementInsidePar(i));
            }
            else {
                error("none standard arithmatic expression presented");
            }
        }

        // find (type): function inside '('
        else if (term[i] == '(') {
            if (term[i+1] != ')' && isNum(term[i+1])) {
                u.push(ElementInsidePar(++i));

                checkForN(i, i+1);
            }
            else
                error("no element inside parentheses '(...)'");
        }

        // find (type): division
        else if (term[i] == '/') {
            forcedOp = 1;
        }
    }

    // completion
}

string ElementInsidePar(unsigned &i) {
    string result = "";
    unsigned short leftPar = 1, rightPar = 0;
    while (i < src.length) {
        if (src[i] == '(') leftPar++;
        else if (src[i] == ')') {
            if (leftPar == ++rightPar) break;
        }

        result += src[i++];
    }

    return result;
}

bool TermComponents::checkForN(unsigned &i, unsigned checkingPos) {
    if (src[checkingPos] == '^')) {
        if (isNum(src[++checkingPos])) {
            n.push(parseNum(src, i = checkingPos));

            while (isNum(src[i+1])) i++;

            return true;
        }
        else if (src[checkingPos] == '(') {
            nIndex.push(i = ++checkingPos);
            n.push(ElementInsidePar(i));

            return true;
        }
        else {
            error("no number after '^...'");
        }
    }

    return false;
}

/* ################################ */
/* ################################ */

array<string> readExpr(string expr) {
    array<string> terms;

    unsigned leftPar = 0, rightPar = 0;

    // pre-reading process
    expr = expr.replace(" ", "");

    if (expr == "")
        error("no input expression");

    // reading equation process
    unsigned splitIndex = 0;

    for (unsigned i = (expr[0] == '+' || expr[0] == '-'); i < expr.length; i++) {
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
        error("no complete pair of parentheses '()'");

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

    string result = "";
    double a = isNum(tc.src[0]) ? parseNum(tc.src) : 1;

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
            string diffTrigon1, diffTrigon2;

            string chainDiff = diff(u[0], var);
            bool hasSign = (chainDiff.includes("+") || chainDiff.includes("-"));
            bool hasVarOrU = chainDiff.includes(var);

            if (trigon[0] == "cos" || trigon[0] == "cot" || trigon[0] == "csc") a = -1;

            if (trigon[0] == "sin" || trigon[0] == "cos" || trigon[0] == "tan" || trigon[0] == "cot") {

                if (trigon[0] == "sin") diffTrigon1 = "cos";
                else if (trigon[0] == "cos") diffTrigon1 = "sin"; //-
                else if (trigon[0] == "tan") diffTrigon1 = "sec^2";
                else if (trigon[0] == "cot") diffTrigon1 = "csc^2"; //-

                if (hasSign || hasVarOrU)
                    result = toCalStr(a) + diffTrigon1 + "(" + u[0] + ")(" + chainDiff + ")";
                else
                    result = toCalStr(a * parseNum(chainDiff)) + diffTrigon1 + "(" + u[0] + ")";
            }
            else {
                if (trigon[0] == "csc") {
                    diffTrigon1 = "csc";
                    diffTrigon2 = "cot";
                }
                if (trigon[0] == "sec") {
                    diffTrigon1 = "sec";
                    diffTrigon2 = "tan";
                }

                if (hasSign || hasVarOrU)
                    result = toCalStr(a) + diffTrigon1 + "(" + u[0] + ")" + diffTrigon2 + "(" + u[0] + ")(" + chainDiff + ")";
                else
                    result = toCalStr(a * parseNum(chainDiff)) + diffTrigon1 + "(" + u[0] + ")" + diffTrigon2 + "(" + u[0] + ")(" + chainDiff + ")";
            }
        }
        else if (trigonIndex.length > 0) { // CASE: a*sin^n(u)
            n = parseNum(tc, trigonIndex[0] + 4);
            string chainDiff = diff(u[0], var);

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
        else if (log.length) {
            if (trigonIndex[0] != 0) a *= parseNum(tc.src);

            if (log[0] == "ln")
            dobule b = parseNum(tc.src, trigonIndex[0] + 2);
        }
    }
    else if (u.length == 0) {
        switch (tc.src[varIndex[0] + 1]) {
            case '^': { // CASE: ax^n or ax^(n)
                string redN = reduceN(tc.n[0]);

                if (n - 1 == 0)
                    result = toCalStr(a * calStrNum(redN));
                else if (n - 1 == 1)
                    result = toCalStr(a * calStrNum(redN)) + "x";
                else
                    result = toCalStr(a * calStrNum(redN)) + "x^" + redN;
            } break;
            case '*': { // CASE: ax*(n) or ax*(u)

            } break;
            default: { // CASE ax or ax^1
                result = toCalStr(parseNum(tc.src));
            }
        }
    }

    return result;
}

#endif