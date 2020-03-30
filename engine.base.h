#ifndef DERIVATIVE_H
#define DERIVATIVE_H

/* The mothod throw error when the errors was occured */
void error(const char * = "error");
/* The method splits expression into arrays of string term. */
array<string> readExpr(string expr);
/* The methood turns arrays of term into a new derivative expression. */
string diffExpr(array<string> terms, const char &var);
/* The methood turns a single term into a new derivative term. */
string diff(const string &term, const char &var);
/* The method reforms the expression to be an clearier expression. */
string simplifyExpr(string expr);
/* The method finds tangent of expression */
string tangent(string expr, double posX, const char &var);
/* The method shows graph of the expression */
void showGraph(const string &expr, const double &scale, const char &var);

struct factor {
    unsigned type = 0; // 0 = u, 1 = trig, 2 = log, 3 = arc, 4 = var, 5 = n of var
    unsigned uType = 0; // 0 = u, 1 = trig, 2 = log, 3 = arc, 4 = var, 5 = n of var
    string func = ""; // log10, asin, tan
    string n = "1";
    string u = "";

    /* The method subtracts power of n by -1 of any form, and returns the subtracted number. */
    double subtractN(string &receiver, const char &var='x') {
        if (n == "1") return 1;
        unsigned short divIndex = 0;

        if ((divIndex = n.search("/")) == -1) {
            double upper = parseNum(n.slice(0, divIndex));
            double lower = parseNum(n.slice(divIndex+1));
            
            receiver = "^(" + toString(upper-lower) + "/" + toString(lower) + ")";
            return upper / lower;
        }
        else {
            if (parseNum(n)-1 != 1) {
                receiver = "^" + toString(parseNum(n)-1);
            }

            return parseNum(n);
        }
    }

    /* The method compresses the whole factor into a string factors. */
    string compress() {
        string resN;

        if (n.includes("/")) resN = "^(" + n + ")";
        else if (n != "1") resN = "^" + n;

        if (readExpr(u).length > 1 || u[0] == 'l' || u[0] == 'a' || u[0] == 's' || u[0] == 'c' || u[0] == 't') {
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
        array<unsigned> divIndex;
    
        TermComponents(string term, char var);
    private:
        /* the start position of 'i' should be the position of '(' + 1 */
        string itemInsidePar(unsigned short &i);
        /* checkingPos should be the index position of '^' */
        bool checkForN(unsigned short &i, string &receiver);
};

TermComponents::TermComponents(string term, char var) {
    src = term;
    a = parseNum(term) == 0 ? 1 : parseNum(term);
    for (unsigned short i = 0; i < term.length; i++) {
        // find (type): position and #of x
        if (term[i] == var) {
            factor item;
            item.type = 4;
            item.u = var;
            if(!checkForN(++i, item.n)) i--;

            factors.push(item);
        }

        // find (type): trigonometric function.
        else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i + 5 < term.length) {
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
            string lfunc = term.slice(i, i+2); // lo || ln

            factor item;
            unsigned startlog = i;

            i+=3; // skip 'log...' or 'ln(...'
            if (lfunc == "lo") {
                while(isNum(term[i])) i++;

                lfunc = term.slice(startlog, i);
                
                if (checkForN(i, item.n)) { // logb^n
                    while (term[i++] != '(');
                    item.u = lfunc + "(" + itemInsidePar(i) + ")";
                }
                else { // logb
                    item.type = 2;
                    item.func = lfunc;
                    item.u = itemInsidePar(++i);
                }
            }
            else if (lfunc == "ln") {
                if (checkForN(i, item.n)) {
                    while (term[i++] != '(');
                    item.u = "ln(" + itemInsidePar(i) + ")";
                }
                else {
                    item.type = 2;
                    item.func = "ln";
                    item.u = itemInsidePar(++i);
                }
            }
            else error("none standard arithmatic expression presented");

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

        else if (term[i] == '^') {
            factor item;

            item.type = 5;
            checkForN(++i, item.n);
            item.u = toString(a);
            a = 1;

            factors.push(item);
            break;
        }

        // find (type): function inside '(...)'
        else if (term[i] == '(') {
            if (term[i+1] != ')' && isNum(term[i+1])) {
                factor item;

                item.u = itemInsidePar(++i);
                if(!checkForN(++i, item.n)) i--;

                factors.push(item);
            }
            else error("no element inside parentheses '(...)'");
        }

        // find (type): division
        else if (term[i] == ')' && term[i+1] == '/') {
            divIndex.push(factors.length);
        }
    }
}

string TermComponents::itemInsidePar(unsigned short &i) {
    unsigned short l = 1, r = 0, start = i;
    while (i < src.length) {
        if (src[i] == '(') l++;
        else if (src[i] == ')' && l == ++r) {
            if (i - start == 1) error("no element inside parentheses '(...)'");
            return src.slice(start, i);
        }
        i++;
    }

    return "";
}

bool TermComponents::checkForN(unsigned short &i, string &receiver) {
    if (src[i] == '^') {
        if (isNum(src[++i]) || src[i] == '-') {
            if (src[i] == '0')
                error("using power of 0");

            unsigned startpos = i;
            while (isNum(src[i]) || src[i] == '-') i++;

            receiver = src.slice(startpos, i--);

            return true;
        }
        else if (src[i] == '(') {
            receiver = itemInsidePar(++i);

            return true;
        }
        else error("no number after '^...'");
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

    if (expr == "") error("no input expression");

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
        if (i > 0 && diff(terms[i], var)[0] != '-')
            result += "+";

        result += diff(terms[i], var);
    }
    return result;
}

string diff(const string &term, const char &var) {
    TermComponents tc(term, var);

    if (!tc.factors.length && tc.a == 1) return ""; // only c
    else if (!tc.factors.length) return tc.a;

    string result = tc.a;

    if (tc.factors.length > 1) { 
        if (tc.divIndex.length) {
            string dividend = tc.factors[0].compress(), divisor = tc.factors[1].compress();

            result += "((" + divisor + ")(" + diffExpr(readExpr(dividend), var) + ")-(" + dividend + ")(" + diffExpr(readExpr(divisor), var) + "))/(" + divisor + ")^2";
        }
        else {
            for (unsigned i = 0; i < tc.factors.length; i++) {
                if (i > 0) result += "+";

                for (unsigned j = 0; j < tc.factors.length; j++) {
                    result += "(";
                    result += i == j ? diffExpr(readExpr(tc.factors[i].compress()), var) : tc.factors[i].compress();
                    result += ")";
                }
            }
        }
    }
    else if (tc.factors.length == 1) {
        switch (tc.factors[0].type) {
            case 0: {
                string chainDiff = diff(tc.factors[0].u, var);
                string subN = "";
                double numSubN = tc.factors[0].subtractN(subN);

                result = subN == "1"
                    ? toCalStr(tc.a * 2) + "(" + tc.factors[0].u + ")(" + chainDiff + ")"
                    : toCalStr(tc.a * numSubN) + "(" + tc.factors[0].u + ")" + subN + "(" + chainDiff + ")";
            } break;
            case 1: {
                string chainDiff = diff(tc.factors[0].u, var);
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
                string chainDiff = diff(tc.factors[0].u, var);

                if (tc.factors[0].func.length > 2) { // log...
                    string logbase = tc.factors[0].func.slice(3) == "" ? "10" : tc.factors[0].func.slice(3);

                    result = hasSignOrVar(chainDiff, var)
                        ? toCalStr(tc.a) + "(" + chainDiff + ")/((" + tc.factors[0].u + ")ln" + logbase + ")"
                        : toCalStr(tc.a * parseNum(chainDiff)) + "/((" + tc.factors[0].u + ")ln" + logbase + ")";
                }
                else { // ln...
                    result = hasSignOrVar(chainDiff, var)
                        ? toCalStr(tc.a) + "(" + chainDiff + ")/(" + tc.factors[0].u + ")"
                        : toCalStr(tc.a * parseNum(chainDiff)) + "/(" + tc.factors[0].u + ")";
                }
            } break;
            case 3: {
                string chainDiff = diff(tc.factors[0].u, var);

                if (tc.factors[0].func == "cos" || tc.factors[0].func == "cot" || tc.factors[0].func == "csc") tc.a *= -1;

                result = hasSignOrVar(chainDiff, var)
                    ? toCalStr(tc.a) + "(" + chainDiff + ")/"
                    : toCalStr(tc.a * parseNum(chainDiff)) + ")/";

                if (tc.factors[0].func == "sin" || tc.factors[0].func == "cos") result += "((1-(" + tc.factors[0].u + ")^2)^(1/2))";
                else if (tc.factors[0].func == "tan" || tc.factors[0].func == "cot") result += "(1-(" + tc.factors[0].u + ")^2)";
                else if (tc.factors[0].func == "sec" || tc.factors[0].func == "csc") result += "(|" + tc.factors[0].u + "|((" + tc.factors[0].u + ")^2-1)^(1/2))";
            } break;
            case 4: { // CASE: ax^n or ax^(n)
                string subN = "";
                double numSubN = tc.factors[0].subtractN(subN);

                result = numSubN == 1
                    ? toCalStr(tc.a)
                    : toCalStr(tc.a * numSubN) + string(var) + subN;
            } break;
            case 5: {
                string chainDiff = diff(tc.factors[0].n, var);
                result = "(" + chainDiff + ")" + tc.factors[0].u + "^(" + tc.factors[0].n + ")";
            }
            default: error();
        }
    }

    return result;
}


string tangent(string expr, double posX, const char &var) {
    string slopeFunc = diffExpr(readExpr(expr), var);
    dobule slope = evalExpr(readExpr(slopeFunc), posX, var);

    // tangent = m(x1)(x-x1) + y1;
    string x1 = posX < 0 ? "-" : "";
    x1 += toString(posX);
    x1 = (x1[0] == '-' ? "-" : "+") + x1;

    return toString(slope) + "(" + string(var) + x1 + ")" + evalExpr(readExpr(expr), posX);
}

void showGraph(const string &expr, const double &scale, const char &var) {
    const unsigned short h = 101, w = 101;
    char graph[h][w] = {};

    array<string> read = readExpr(expr);

    for (unsigned short i = 0; i < w; i++) {
        double y = evalExpr(read, i/scale, var);
        if (y > -50/scale && y < 50/scale) {
            graph[int(y)][i] = '*';
        }
    }

    for (unsigned short row = 0; row < h; row++) {
        std::cout << '\t';
        for (unsigned short cell = 0; cell < w; cell++) {
            if (row == 50 && cell == 50) {
                if (graph[row][cell] == '*') std::cout << '*'
                else std::cout << '|';
            }
            else if (cell == 50) {
                if (graph[row][cell] == '*') std::cout << '*'
                else std::cout << '|';
            }
            else if (row == 50) {
                if (graph[row][cell] == '*') std::cout << '*'
                else std::cout << '-';
            }
            else {
                std::cout << ' ';
            }
        }

        if (row == 50) std::cout << " " << var;

        std::cout << '\n';
    }
}

#endif