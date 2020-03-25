#ifndef DERIVATIVE_H
#define DERIVATIVE_H

/* The method splits expression into arrays of string term. */
array<string> readExpr(string);
/* The methood turns arrays of term into a new derivative expression. */
string exprDiff(array<string>, char);
/* The methood turns a single term into a new derivative term. */
string diff(string, char);

class TermComponents {
    public:
        string src;
        array<string> u, n, trig, log, arc, deno_term;
        array<unsigned short> trigIndex, varIndex, logIndex, nIndex, arcIndex;
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
                trigIndex.push(i);

                i += 4; // skip 'sin^...' or 'sin(...'
                if (checkForN(i, i-1)) { // find: a*sin^n(u)
                    while(term[i++] != '(');
                    u.push(tfunc + "(" + ElementInsidePar(i) + ")");
                }
                else { // find: a*sin(u) or a*sin^1(u)
                    trig.push(tfunc);
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
                arcIndex.push(i);

                i += 4; // skip 'sin^...' or 'sin(...'
                if (checkForN(i, i-1)) { // find: a*sin^n(u)
                    while(term[i++] != '(');
                    u.push("a" + tfunc + "(" + ElementInsidePar(i) + ")");
                }
                else { // find: a*sin(u) or a*sin^1(u)
                    arc.push("a" + tfunc);
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

        // find (type): function inside '(...)'
        else if (term[i] == '(') {
            if (term[i+1] != ')' && isNum(term[i+1])) {
                u.push(ElementInsidePar(++i));

                checkForN(i, i+1);
            }
            else
                error("no element inside parentheses '(...)'");
        }

        // find (type): division
        else if (term[i] == ')' && term[i+1] == '/') {
            forcedOp = 1;
            if(term[i+1] != ')' && isNum(term[i+1])){
                deno_term.push(ElementInsidePar(++i));

                checkForN(i, i+1);
            }
            else
                error("no element inside parentheses '(...)'");
        }
    }

    // completion
    if (varIndex > 0 && (u.length > 0 || log.length > 0 || trig.length > 0 || arc.length > 0)) {
        u.unshift(src.slice(0, src.search("(")));
        //++ marge var like (2x)(4x^4) to 8x^5
    }
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
    expr = expr.replace(" ", "").toLowerCase();

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

        result += diff(terms[i], var);
    }
    return result;
}

string diff(string term, char var) {
    TermComponents tc = TermComponents(term);

    if (tc.varIndex.length == 0 && tc.u.length == 0) return ""; // only c

    string result = "";
    double a = isNum(term[0]) ? parseNum(term) : 1;

    if (tc.u.length > 1 || tc.log.length > 1 || tc.trig.length > 1 || tc.arc.length > 1) { 
        for (unsigned i = 0; i < u.length; i++) {
            if (i > 0)
                result += "+";

            for (unsigned j = 0; j < u.length; j++) {
                result += "(";
                result += i == j ? exprDiff(readExpr(u[i]), var) : u[i];
                result += ")";
            }
        }
    }
    else if (u.length && tc.deno_term.length && tc.forcedOp == 1) { //divide  (3x+2)(2x^2) / (5x+20)(4x+13) => u / v
        // 3/4 ; 3 = numerator, 4 = denominator
        string numerator = "";
        string denominator = "";

        for(unsigned i = 0; i < tc.u.length; i++){     //(3x+2)(2x^2)
            if (i > 0)
                numerator += "+";

            for(unsigned j = 0; j < u.length; j++){
                numerator += "(";
                numerator += (i == j ? exprDiff(readExpr(u[i]), var) : u[i]);
                numerator += ")";
            }
        }
        
        for(unsigned i = 0; i < tc.deno_term.length; i++){     //(5x+20)(4x+13)
            if (i > 0)
                denominator += "+";

            for(unsigned j = 0; j < tc.deno_term.length; j++){
                denominator += "(";
                denominator += (i == j ? exprDiff(readExpr(tc.deno_term[i]), var) : u[i]);
                denominator += ")";
            }
        }

        result += "[(" + denominator + ")(" + exprDiff(readExpr(numerator), var) +") ";
        result += "- (" + numerator + ")(" + exprDiff(readExpr(denominator), var) + ")] ";
        result += "/ (" + denominator + ")^2";
    }
    else if (tc.u.length == 1) {
        if (tc.trig.length) { // CASE: a*sin(u) or a*sin^1(u)
            string diffTrigon1, diffTrigon2;

            string chainDiff = diff(tc.u[0], var);
            bool isChainHasOnlyNum = hasSignOrVar(chainDiff, var);

            if (tc.trig[0] == "cos" || tc.trig[0] == "cot" || tc.trig[0] == "csc") a = -1;

            if (tc.trig[0] == "sin" || tc.trig[0] == "cos" || tc.trig[0] == "tan" || tc.trig[0] == "cot") {

                if (tc.trig[0] == "sin") diffTrigon1 = "cos";
                else if (tc.trig[0] == "cos") diffTrigon1 = "sin"; //-
                else if (tc.trig[0] == "tan") diffTrigon1 = "sec^2";
                else if (tc.trig[0] == "cot") diffTrigon1 = "csc^2"; //-

                result = isChainHasOnlyNum
                    ? toString(a * parseNum(chainDiff)) + diffTrigon1 + "(" + tc.u[0] + ")"
                    : toString(a) + diffTrigon1 + "(" + tc.u[0] + ")(" + chainDiff + ")";
            }
            else {
                if (tc.trig[0] == "csc") {
                    diffTrigon1 = "csc";
                    diffTrigon2 = "cot";
                }
                else if (tc.trig[0] == "sec") {
                    diffTrigon1 = "sec";
                    diffTrigon2 = "tan";
                }

                result = isChainHasOnlyNum
                    ? toString(a * parseNum(chainDiff)) + diffTrigon1 + "(" + tc.u[0] + ")" + diffTrigon2 + "(" + tc.u[0] + ")"
                    : toString(a) + diffTrigon1 + "(" + tc.u[0] + ")" + diffTrigon2 + "(" + tc.u[0] + ")(" + chainDiff + ")";
            }
        }
        else if (tc.trigIndex.length) { // CASE: a*sin^n(u)
            string redN = reduceN(tc.n[0]);
            string chainDiff = diff(tc.u[0], var);

            string blockInsideTrig = tc.u[0].slice(tc.u[0].search("("));

            result = redN == "1"
                ? toString(a * calStrNum(redN)) + tc.u[0] + "*" + chainDiff
                : toString(a * calStrNum(redN)) + tc.u[0].slice(0, 3) + "^" + redN + blockInsideTrig + "*" + chainDiff;
        }
        else if (tc.arc.length) {
            string chainDiff = diff(tc.u[0], var);
            bool isChainHasOnlyNum = hasSignOrVar(chainDiff, var);

            if (tc.arc[0] == "acos" || tc.arc[0] == "acot" || tc.arc[0] == "acsc") a *= -1;

            result = isChainHasOnlyNum
                ? toString(a * parseNum(chainDiff)) + ")/";
                : toString(a) + "(" + chainDiff + ")/";

            if (tc.arc[0] == "asin" || tc.arc[0] == "acos") result += "((1-(" + tc.u[0] + ")^2)^(1/2))";
            else if (tc.arc[0] == "atan" || tc.arc[0] == "acot") result += "(1-(" + tc.u[0] + ")^2)";
            else if (tc.arc[0] == "asec" || tc.arc[0] == "acsc") result += "(|" + tc.u[0] + "|((" + tc.u[0] + ")^2-1)^(1/2))";
        }
        else if (tc.log.length) { // CASE: logb(u) or logb^1(u)
            string chainDiff = diff(tc.u[0], var);
            bool isChainHasOnlyNum = hasSignOrVar(chainDiff, var);

            if (tc.log[0].length > 2) { // log...
                result = isChainHasOnlyNum
                    ? toString(a * parseNum(chainDiff)) + "/((" + tc.u[0] + ")ln" + tc.log[0].slice(3) + ")"
                    : toString(a) + "(" + chainDiff + ")/((" + tc.u[0] + ")ln" + tc.log[0].slice(3) + ")";
            }
            else { // ln
                result = isChainHasOnlyNum
                    ? toString(a * parseNum(chainDiff)) + "/(" + tc.u[0] + ")"
                    : toString(a) + "(" + chainDiff + ")/(" + tc.u[0] + ")";
            }
        }
        else if (tc.logIndex.length) { // CASE: logb^n(u)
            string redN = reduceN(tc.n[0]);
            string chainDiff = diff(tc.u[0], var);
            string blockInsideTrig = tc.u[0].slice(tc.u[0].search("("));

            if (redN == "1")
                result = toString(a * calStrNum(redN)) + tc.u[0] + "*" + chainDiff;
            else if (tc.u[0].slice(0, 2) == "ln") // ln
                result = toString(a * calStrNum(redN)) + tc.u[0].slice(0, 2) + "^" + redN + blockInsideTrig + "*" + chainDiff;
            else // log
                result = toString(a * calStrNum(redN)) + tc.u[0].slice(0, tc.u[0].search("^")) + "^" + redN + blockInsideTrig + "*" + chainDiff;
        }
    }
    else if (u.length == 0) {
        switch (tc.src[varIndex[0] + 1]) {
            case '^': { // CASE: ax^n or ax^(n)
                string redN = reduceN(tc.n[0]);

                if (n - 1 == 0)
                    result = toString(a * calStrNum(redN));
                else if (n - 1 == 1)
                    result = toString(a * calStrNum(redN)) + "x";
                else
                    result = toString(a * calStrNum(redN)) + "x^" + redN;
            } break;
            case '*': { // CASE: ax*(n) or ax*(u)

            } break;
            default: { // CASE ax or ax^1
                result = toString(parseNum(tc.src));
            }
        }
    }

    return result;
}

#endif