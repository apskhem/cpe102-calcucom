class CalNumber {
    /* The method powers the input number. */
    friend double powInt(double, const int);
    /* The method parses string to number (int, float etc.). */
    friend double parseNum(string, const unsigned=0, unsigned=-1);
    /* The method checks if input char is number or not. */
    friend bool isNum(char);
    /* The method reduces power of n by -1 of any form. */
    friend string reduceN(string);
    /* The methood reads expression and find '+', '-' and var. */
    bool hasSignOrVar(string, char);
};

double powInt(double base, const int n) {
    if (n == 0) return 1;

    double result = base;
    for (unsigned short i = 1; i < n; i++) {
        result *= base;
    }

    return (n > 0 ? result : 1/result);
}

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

string reduceN(string n, char var, double &numOutput) {
    unsigned short divIndex = 0;

    for (unsigned short i = 0; i < n.length; i++) {
        if (n[i] == var) {
            numOutput = 1;
            return "";
        }
        else if (n[i] == '/') {
            divIndex = i;
            break;
        }
    }

    if (divIndex) {
        string newCal = "";
        double upper = parseNum(n.slice(0, divIndex))
        double lower = parseNum(n.slice(divIndex+1));

        numOutput = upper / lower;
        return toString(upper-lower) + "/" + toString(lower);
    }
    else {
        return toString(parseNum(n)-1);
    }
}

bool hasSignOrVar(string expr, char var) {
    for (unsigned short i = (expr[0] == '+' || expr[0] == '-'); i < expr.length; i++) {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == var) {
            return true;
        }
    }

    return false;
}