#ifndef DERIVATIVE_H
#define DERIVATIVE_H

#include <cmath>

/* The method splits expression into arrays of string term. */
array<string> splitTerm(string expr);
/* The methood derivatives the expression. */
string diffExpr(array<string> terms, const char &var);
/* The methood derivatives a term. */
string diff(const string &term, const char &var);
/* The method reforms the expression to be an clearier expression. */
string simplifyExpr(string expr);
/* The method finds tangent of expression */
string tangent(string expr, double posX, const char &var);
/* The method shows graph of the expression */
void showGraph(const string &expr, const double &scale, const char &var);
/* The method evaluates the expression. */
double evalExpr(array<string> terms, const double &value, const char &var);
/* The method evaluates a term. */
double eval(string term, const double &value, const char &var);
/* The method implicitly derivatives the expression. */
string implExprDiff(array<string> rightTerms, array<string> leftTerms, const char &var);

void mulMinusN(string &expr);

const double PI = 3.14159265358979323846;
const double e = 2.71828;

struct factor {
    unsigned type = 0; // 0 = u, 1 = trig, 2 = log, 3 = arc, 4 = var, 5 = n of var
    unsigned uType = 0; // 0 = u, 1 = trig, 2 = log, 3 = arc, 4 = var, 5 = n of var
    string func = ""; // log10, asin, tan
    string n = "1";
    string u = "";

    /* The method subtracts power of n by -1 of any form, and returns the subtracted number. */
    double subtractN(string &receiver, const char &var='x') {
        if (n == "1") return 1;
        int divIndex = n.search("/");

        if (divIndex != -1) {
            double upper = parseNum(n.slice(0, divIndex));
            double lower = parseNum(n.slice(divIndex+1));
            
            receiver = "^(" + toString(upper-lower) + "/" + toString(lower) + ")";
            return upper / lower;
        }
        else {
            if (parseNum(n)-1 != 1) {
                if (n.includes("-")) receiver = "^(" + toString(parseNum(n)-1) + ")";
                else receiver = "^" + toString(parseNum(n)-1);
            }

            return parseNum(n);
        }
    }

    /* The method compresses the whole factor into a string factors. */
    string compress() {
        string resN;

        if (n.includes("/")) resN = "^(" + n + ")";
        else if (n != "1") resN = "^" + n;

        if (splitTerm(u).length > 1 || u[0] == 'l' || u[0] == 'a' || u[0] == 's' || u[0] == 'c' || u[0] == 't') {
            return "(" + u + ")" + resN;
        }
        else if (func != "") {
            return func + "(" + u + ")";
        }
        else {
            return u + resN;
        }
    }
};

class TermComponents {
    public:
        string src;
        array<factor> factors;
        double a = 1;
        string otherVar = "";
    
        TermComponents(string term, char var);
    private:
        /* the start position of 'i' should be the position of '(' + 1 */
        string itemInsidePar(unsigned short &i);
        /* checkingPos should be the index position of '^' */
        bool checkForN(unsigned short &i, string &receiver);
};

TermComponents::TermComponents(string term, char var) {
    src = term;
    bool trackMinus = false;
    if (term[0] == '-') a = -1;
    for (unsigned short i = a == -1; i < term.length; i++) {
        // find (type): c number.
        if (isNum(term[i])) {
            if (term[i] == '0') error("lead 0 in context");

            unsigned startpos = i;

            while (isNum(term[i+1]) && i < term.length) i++;

            if (term[i+1] == '^') {
                factor item;

                item.type = 5;
                item.u = term.slice(startpos, i+1);
                checkForN(++i, item.n);
                factors.push(item);
            }
            else {
                a *= trackMinus ? 1/parseNum(term.slice(startpos, i+1)) : parseNum(term.slice(startpos, i+1));
            }
        }

        // find (type): e number.
        else if (term[i] == 'e') {
            if (term[i+1] == '^') {
                factor item;

                item.type = 5;
                checkForN(++i, item.n);
                item.u = "e";
                factors.push(item);
            }
            else {
                a *= trackMinus ? 1/2.71828182845904523 : 2.71828182845904523;
            }
        }

        // find (type): trigonometric function.
        else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i+5 < term.length) {
            string tfunc = term.slice(i, i + 3);

            if (tfunc == "sin" || tfunc == "cos" || tfunc == "tan" || tfunc == "csc" || tfunc == "sec" || tfunc == "cot") {
                factor item;

                i += 3; // skip 'sin...'
                if (checkForN(i, item.n)) { // find: a*sin^n(u)
                    while (term[i++] != '(');
                    item.u = tfunc + "(" + itemInsidePar(i) + ")";
                }
                else { // find: a*sin(u) or a*sin^1(u)
                    item.type = 1;
                    item.func = tfunc;
                    item.u = itemInsidePar(++i);
                }

                factors.push(item);
            }
            else error("none standard arithmatic expression presented");
        }

        // find (type): logarithm function
        else if (term[i] == 'l' && i + 4 < term.length) {
            factor item;
            unsigned startlog = i;

            while (term[i] != '^' && term[i] != '(') i++;

            string lfunc = term.slice(startlog, i);

            if (!lfunc.includes("log") && !lfunc.includes("ln")) error("none standard arithmatic expression presented");

            if (term[i] == '^' && checkForN(i, item.n)) { // logb^n
                while (term[i++] != '(');
                item.u = lfunc + "(" + itemInsidePar(i) + ")";
            }
            else {
                item.type = 2;
                item.func = lfunc;
                item.u = itemInsidePar(++i);
            }

            factors.push(item);
        }

        // find (type): inverse trigon function
        else if (term[i] == 'a') {
            string tfunc = term.slice(i+1, i+4);

            if (tfunc == "sin" || tfunc == "cos" || tfunc == "tan" || tfunc == "csc" || tfunc == "sec" || tfunc == "cot")  {
                factor item;

                i += 4; // skip 'asin...'
                if (checkForN(i, item.n)) { // find: a*sin^n(u)
                    while (term[i++] != '(');
                    item.u = "a" + tfunc + "(" + itemInsidePar(i) + ")";
                }
                else { // find: a*sin(u) or a*sin^1(u)
                    item.type = 3;
                    item.func = tfunc;
                    item.u = itemInsidePar(++i);
                }

                factors.push(item);
            }
            else error("none standard arithmatic expression presented");
        }

        // find (type): var
        else if (term[i] == var) {
            factor item;
            item.type = 4;
            item.u = term[i];

            if(!checkForN(++i, item.n)) i--;
            else if (item.n.includes(var) && item.u.includes(var)) error("there's no support for calculation of u^u", 2);

            factors.push(item);
        }

        else if (term[i] >= 97 && term[i] <= 122) {
            otherVar += string(term[i]);
        }

        // find (type): function inside '(...)'
        else if (term[i] == '(') {
            factor item;

            item.u = itemInsidePar(++i);
            if(!checkForN(++i, item.n)) i--;

            factors.push(item);
        }

        // find (spliter): division
        else if (term[i] == '/') {
            trackMinus = true;
            continue;
        }

        else error("error in expression checking");

        // finalize end round
        if (trackMinus && factors.length) {
            mulMinusN(factors[factors.length - 1].n);
        }

        trackMinus = false;
    }
}

string TermComponents::itemInsidePar(unsigned short &i) {
    unsigned short l = 1, r = 0, start = i;
    while (i < src.length) {
        if (src[i] == '(') l++;
        else if (src[i] == ')' && l == ++r) {
            if (i - start < 1) error("no element inside parentheses '(...)'");
            return src.slice(start, i);
        }
        i++;
    }

    return "";
}

bool TermComponents::checkForN(unsigned short &i, string &receiver) {
    if (src[i] == '^') {
        if (src[++i] == '(') receiver = itemInsidePar(++i);
        else {
            if (src[i] == '0') error("using power of 0");
            if (src[i] == '/') error("no power of n after '^...'");

            unsigned startpos = i;
            if (isNum(src[i])) {
                while (i < src.length && isNum(src[i])) i++;

                receiver = src.slice(startpos, i--);
            }
            else { // only single var
                receiver = src[i];
            }
        }

        return true;
    }

    return false;
}

/* ################################ */
/* ################################ */

array<string> splitTerm(string expr) {
    array<string> terms;

    unsigned leftPar = 0, rightPar = 0;

    // pre-reading process
    expr = expr.replace(" ", "").toLowerCase();

    if (!expr.length) error("no input expression");

    // reading equation process
    unsigned splitIndex = 0;

    for (unsigned i = (expr[0] == '+' || expr[0] == '-'); i < expr.length; i++) {
        if (expr[i] == '(') leftPar++;
        else if (expr[i] == ')') rightPar++;

        if ((expr[i] == '+' || expr[i] == '-') && expr[i - 1] != '^' && leftPar == rightPar) {
            terms.push(expr.slice(splitIndex, i));
            splitIndex = i + (expr[i] == '+' ? 1 : 0);
        }
    }

    // collect last term
    terms.push(expr.slice(splitIndex));

    // check for errors
    if (leftPar != rightPar) error("no complete pair of parentheses '()'");

    return terms;
}

string diffExpr(array<string> terms, const char &var) {
    string result = "";
    for (unsigned i = 0; i < terms.length; i++) {
        string preResult = diff(terms[i], var);

        if (preResult.includes("#"));
        else {
            if (i > 0 && preResult[0] != '-' && result.length) result += "+";

            result += preResult;
        }
    }

    result = result.replace("(1)", "");

    return (!result.length ? "0" : result);
}

string diff(const string &term, const char &var) {
    TermComponents tc(term, var);

    if (!tc.factors.length) return "#"; // only c

    string result = "";

    if (tc.factors.length > 1) { 
        for (unsigned i = 0; i < tc.factors.length; i++) {  
            string termRes = "";
            double diffA = 1;

            for (unsigned j = 0; j < tc.factors.length; j++) {
                string preRes = i == j ? diff(tc.factors[j].compress(), var) : tc.factors[j].compress();

                array<string> preTerms = splitTerm(preRes);

                if (i == j) {
                    diffA = parseNum(preRes);
                    if (!diffA) diffA = 1;
                    if (preRes == "1" || preRes == "-1") preRes = "";
                }

                bool withPar = false;
                for (unsigned short o = 0; o < preTerms.length; o++)
                    withPar = preTerms[o].length > 1 && preTerms[o].includes("-") || preTerms[o].includes("/");

                termRes += preTerms.length > 1 || withPar ? "(" + preRes + ")" : preRes;
            }

            // finalize terms
            if (i > 0 && tc.a * diffA > 0) result += "+";

            result += toCalStr(tc.a * diffA) + termRes;
        }
    }
    else if (tc.factors.length == 1) {
        switch (tc.factors[0].type) {
            case 0: {
                string chainDiff = diffExpr(splitTerm(tc.factors[0].u), var);
                if (chainDiff == "0") return "#";
                string subN = "";
                double numSubN = tc.factors[0].subtractN(subN);

                result = numSubN == 2
                    ? toCalStr(tc.a * 2) + "(" + tc.factors[0].u + ")(" + chainDiff + ")"
                    : toCalStr(tc.a * numSubN) + "(" + tc.factors[0].u + ")" + subN + "(" + chainDiff + ")";
            } break;
            case 1: {
                string chainDiff = diffExpr(splitTerm(tc.factors[0].u), var);
                if (chainDiff == "0") return "#";
                string diffTrigon1, diffTrigon2;

                if (tc.factors[0].func == "cos" || tc.factors[0].func == "cot" || tc.factors[0].func == "csc") tc.a *= -1;

                if (tc.factors[0].func == "sin" || tc.factors[0].func == "cos" || tc.factors[0].func == "tan" || tc.factors[0].func == "cot") {

                    if (tc.factors[0].func == "sin") diffTrigon1 = "cos";
                    else if (tc.factors[0].func == "cos") diffTrigon1 = "sin";
                    else if (tc.factors[0].func == "tan") diffTrigon1 = "sec^2";
                    else if (tc.factors[0].func == "cot") diffTrigon1 = "csc^2";

                    result = hasSignOrVar(chainDiff, var)
                        ? toCalStr(tc.a) + diffTrigon1 + "(" + tc.factors[0].u + ")(" + chainDiff + ")"
                        : toCalStr(tc.a * parseNum(chainDiff)) + diffTrigon1 + "(" + tc.factors[0].u + ")";
                }
                else {
                    if (tc.factors[0].func == "csc") {
                        diffTrigon1 = "csc";
                        diffTrigon2 = "cot";
                    }
                    else if (tc.factors[0].func == "sec") {
                        diffTrigon1 = "sec";
                        diffTrigon2 = "tan";
                    }

                    result = hasSignOrVar(chainDiff, var)
                        ? toCalStr(tc.a) + diffTrigon1 + "(" + tc.factors[0].u + ")" + diffTrigon2 + "(" + tc.factors[0].u + ")(" + chainDiff + ")"
                        : toCalStr(tc.a * parseNum(chainDiff)) + diffTrigon1 + "(" + tc.factors[0].u + ")" + diffTrigon2 + "(" + tc.factors[0].u + ")";
                }
            } break;
            case 2: {
                string chainDiff = diffExpr(splitTerm(tc.factors[0].u), var);
                if (chainDiff == "0") return "#";

                result = hasSignOrVar(chainDiff, var)
                    ? toCalStr(tc.a) + "(" + chainDiff + ")/"
                    : toString(tc.a * parseNum(chainDiff)) + "/";

                if (tc.factors[0].func.length > 2) { // log...
                    string logbase = tc.factors[0].func.length == 3 ? "10" : tc.factors[0].func.slice(3);

                    result += tc.factors[0].u.length > 1
                        ? "((" + tc.factors[0].u + ")ln(" + logbase + "))"
                        : "(" + tc.factors[0].u + "ln(" + logbase + "))";
                }
                else { // ln...
                    result += tc.factors[0].u.length > 1
                        ? "(" + tc.factors[0].u + ")"
                        : tc.factors[0].u;
                }
            } break;
            case 3: {
                string chainDiff = diffExpr(splitTerm(tc.factors[0].u), var);
                if (chainDiff == "0") return "#";

                if (tc.factors[0].func == "cos" || tc.factors[0].func == "cot" || tc.factors[0].func == "csc") tc.a *= -1;

                result = hasSignOrVar(chainDiff, var)
                    ? toCalStr(tc.a) + "(" + chainDiff + ")/"
                    : toString(tc.a * parseNum(chainDiff)) + "/";

                if (tc.factors[0].func == "sin" || tc.factors[0].func == "cos") result += "((1-(" + tc.factors[0].u + ")^2)^(1/2))";
                else if (tc.factors[0].func == "tan" || tc.factors[0].func == "cot") result += "(1+(" + tc.factors[0].u + ")^2)";
                else if (tc.factors[0].func == "sec" || tc.factors[0].func == "csc") result += "(|" + tc.factors[0].u + "|((" + tc.factors[0].u + ")^2-1)^(1/2))";
            } break;
            case 4: { // CASE: ax^n or ax^(n)
                string subN = "";
                double numSubN = tc.factors[0].subtractN(subN);

                result = numSubN == 1
                    ? toString(tc.a)
                    : toCalStr(tc.a * numSubN) + string(var) + subN;
            } break;
            case 5: { // CASE a^(u)
                string chainDiff = diffExpr(splitTerm(tc.factors[0].n), var);
                if (chainDiff == "0") return "#";

                string preN = tc.factors[0].n;

                preN = "^" + (tc.factors[0].n.length > 1 || tc.factors[0].n.includes("-") || tc.factors[0].n.includes("/") ? "(" + preN + ")" : preN);

                chainDiff = splitTerm(chainDiff).length > 1 || !isAllNum(chainDiff) ? "(" + chainDiff + ")" : chainDiff;

                result = tc.factors[0].u == "e"
                    ? chainDiff + tc.factors[0].u + preN
                    : chainDiff + "ln(" + tc.factors[0].u + ")" + tc.factors[0].u + preN;
            } break;
            default: error("fault at 'diff' function", 5);
        }
    }

    // finalize
    if (result == "1" && tc.otherVar.length) return tc.otherVar;
    else return ((!result.length ? "#" : result) + tc.otherVar);
}


string tangent(string expr, double posX, const char &var) {
    string slopeFunc = diffExpr(splitTerm(expr), var);
    double slope = evalExpr(splitTerm(slopeFunc), posX, var);

    // tangent = m(x1)(x-x1) + y1;
    double c = posX * slope + evalExpr(splitTerm(expr), posX, var);
    
    string cStr = "";
    if (c != 0) cStr = (c < 0 ? "-" : "+") + toString(c);

    if (slope == 0 && !cStr.length) return "0";
    else if (slope == 0 && cStr.length) return cStr.slice(1);
    else return toString(slope) + string(var) + cStr;
}

void showGraph(const string &expr, const double &scale, const char &var) {
    const unsigned short h = 65, w = 65, mid = 32;

    array<string> read = splitTerm(expr);

    char graph[h][w] = {};

    for (unsigned short i = 0; i < w; i++) {
        int y = evalExpr(read, (i/scale)-mid, var) + mid;

        if (y >= 0 && y <= h) graph[y][i] = '*';
    }

    for (unsigned short row = h-1; row >= 1; row--) { // loop y
        std::cout << "\t\t";
        for (unsigned short col = 0; col < w; col++) { // loop x
            if (graph[row][col] == '*') {
                std::cout << '*';
            }
            else {
                if (row == mid && col == mid) std::cout << '+';
                else if (col == mid) std::cout << '|';
                else if (row == mid) std::cout << '-';
                else std::cout << ' ';
            }
        }

        if (row == mid) std::cout << ' ' << var;

        std::cout << '\n';
    }
}

double evalExpr(array<string> terms, const double &value, const char &var) {
    double result = 0;
    for (unsigned short i = 0; i < terms.length; i++) result += eval(terms[i], value, var);
    return result;
}

double eval(string term, const double &value, const char &var) {
    TermComponents tc(term, var);
    
    if (!tc.factors.length) {
        if (tc.a) return tc.a;
        else return 0;
    }

    double result = tc.a;
    unsigned divPlace = 0;

    for (unsigned short i = 0; i < tc.factors.length; i++) {
        switch (tc.factors[i].type) {
            case 0: {
                double chainEval = evalExpr(splitTerm(tc.factors[i].u), value, var);
                double n = evalExpr(splitTerm(tc.factors[i].n), value, var);

                result *= n < 0 ? 1/pow(chainEval, n) : pow(chainEval, n);
            } break;
            case 1: {
                double chainEval = evalExpr(splitTerm(tc.factors[i].u), value, var);

                if (tc.factors[i].func == "sin")
                    result *= sin(chainEval * PI / 180);
                else if (tc.factors[i].func == "cos")
                    result *= cos(chainEval * PI / 180);
                else if (tc.factors[i].func == "tan")
                    result *= tan(chainEval * PI / 180);
                else if (tc.factors[i].func == "csc")
                    result *= 1/sin(chainEval * PI / 180);
                else if (tc.factors[i].func == "sec")
                    result *= 1/cos(chainEval * PI / 180);
                else if (tc.factors[i].func == "cot")
                    result *= 1/tan(chainEval * PI / 180);
            } break;
            case 2: {
                double chainEval = evalExpr(splitTerm(tc.factors[i].u), value, var);
                double logbase = tc.factors[i].func.length == 3 ? 10 : parseNum(tc.factors[i].func.slice(3));

                result *= tc.factors[i].func.length > 2 ? log(chainEval)/log(logbase) : log(chainEval);
            } break;
            case 3: {
                double chainEval = evalExpr(splitTerm(tc.factors[i].u), value, var);

                if (tc.factors[i].func == "sin")
                    result *= asin(chainEval);
                else if (tc.factors[i].func == "cos")
                    result *= acos(chainEval);
                else if (tc.factors[i].func == "tan")
                    result *= atan(chainEval);
                else if (tc.factors[i].func == "csc")
                    result *= 1/asin(chainEval);
                else if (tc.factors[i].func == "sec")
                    result *= 1/acos(chainEval);
                else if (tc.factors[i].func == "cot")
                    result *= 1/atan(chainEval);
            } break;
            case 4: {
                double n = evalExpr(splitTerm(tc.factors[i].n), value, var);

                result *= n < 0 ? 1/pow(value, n) : pow(value, n);
            } break;
            case 5: {
                double n = evalExpr(splitTerm(tc.factors[i].n), value, var);

                result *= n < 0 ? 1/pow(parseNum(tc.factors[i].u), n) : pow(parseNum(tc.factors[i].u), n);
            } break;
            default: error("fault at 'eval' function");
        }
    }

    return result;
}

string implExprDiff(array<string> leftTerms, array<string> rightTerms, const char &var) {
    string result = "";
    array<string> forms = leftTerms;

    // construct new form left = 0
    for (unsigned short i = 0; i < rightTerms.length; i++) {
        if (rightTerms[i][0] == '-')
            forms.push(rightTerms[i].slice(1));
        else
            forms.push("-" + rightTerms[i]);
    }

    string dUpper, dLower;
    
    dUpper = diffExpr(forms, var);
    dLower = diffExpr(forms, 'y');

    result = "-(" + dUpper + ")/(" + dLower + ")";

    return result;
}

void mulMinusN(string &expr) {
    array<string> terms = splitTerm(expr);
    string res = "";

    for (unsigned short i = 0; i < terms.length; i++) {
        if (terms[i][0] == '-' && i == 0) res += terms[i];
        else if (terms[i][0] != '-' && i == 0) res += "-" + terms[i];
        else if (terms[i][0] == '-') res += "+" + terms[i];
        else res += "-" + terms[i];
    }

    expr = res;
}

#endif
