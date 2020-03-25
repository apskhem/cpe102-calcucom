class CalMath {
    friend double powInt(double, const int);
    /* The method reduces power of n by -1 of any form. */
    friend string reduceN(string);
    /* The method performs simple calculation of string expression */
    friend double calStrNum(string);
    /* The methood reads expression and find '+', '-' and var. */
    bool hasSignOrVar(const string, char);
};

double powInt(double base, const int n) {
    if (n == 0) return 1;

    double result = base;
    for (unsigned short i = 1; i < n; i++) {
        result *= base;
    }

    return (n > 0 ? result : 1/result);
}

string reduceN(string n) {
    string result = "";
    bool isNHasVar = false;
    char hasOp = 0;

    for (unsigned short i = 0; i < n.length; i++) {
        if (n[i] == var) isNHasVar = true;

        // perform simple calculation for n
        hasOp = (n[i] == '+' || n[i] == '-' || n[i] == '*' || n[i] == '/');
    }

    if (!isNHasVar && hasOp) {
        string newCal = "";

        result = newCal;
    }

    return result;
}

double calStrNum(string t) {
    array<char> ops;
    array<string> parts;
    unsigned short splitIndex = 0;
    
    for (unsigned short i = (t[0] == '+' || t[0] == '-'); i < t.length; i++) {
        if (t[i] == '+' || t[i] == '-' || t[i] == '*' || t[i] == '/') {
            ops.push(t[i]);
            parts.push(t.split(splitIndex, i));
            
            splitIndex = i+1;
            if (t[i+1] == '+' || t[i+1] == '-') i++;
        }
    }

    parts.push(t.split(splitIndex));

    if (ops.length == 0)
        return parseNum(parts[0]);

    double result = 0;
    for (unsigned short i = 0; i < ops.length; i++) {
        if (ops[i] == '+') {
            result += parseNum(parts[i]) + parseNum(parts[i+1]);
        }
        else if (ops[i] == '-') {
            result += parseNum(parts[i]) - parseNum(parts[i+1]);
        }
        else if (ops[i] == '*') {
            result += parseNum(parts[i]) * parseNum(parts[i+1]);
        }
        else if (ops[i] == '/') {
            result += parseNum(parts[i]) / parseNum(parts[i+1]);
        }
    }

    return result; 
}


bool hasSignOrVar(const string expr, char var) {
    for (unsigned short i = (expr[0] == '+' || expr[0] == '-'); i < expr.length; i++) {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == var) {
            return true;
        }
    }

    return false;
}

/* ################################ */
/* ################################ */

class Number {
    friend double parseNum(string, const unsigned=0, unsigned=-1);
    friend bool isNum(char);
};

double parseNum(string t, const unsigned start, unsigned end) {
    if (end == -1) end = t.length;
    unsigned decimalPlace = 0;
    bool passNumber = false;
    short isMinus = 1;
    string parseText = "";
    for (unsigned i = start; i < end; i++) {
        if (t[i] >= 46 && t[i] <= 57 && t[i] != '.') {
            passNumber = true;
            parseText += t[i];
        }
        else if (t[i] == '-' && t[i + 1] >= 46 && t[i + 1] <= 57)
            isMinus = -1;
        else if (t[i] == '.' && passNumber)
            decimalPlace = parseText.length;
        else if (passNumber)
            break;
    }
    
    if (parseText == "") return 0;

    double parseResult = 0;
    for (int i = parseText.length-1; i >= 0; i--) {
        parseResult += (parseText[i]-48) * powInt(10, parseText.length-1-i);
    }

    return (decimalPlace ? parseResult / powInt(10, parseText.length - decimalPlace) : parseResult) * isMinus;
}

bool isNum(char t) {
    return (t >= 46 && t <= 57);
}