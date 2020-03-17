class Mathf {
    friend double powInt(double, const int);
};

double powInt(double base, const int n) {
    double result = base, inverse = 1;
    if (n == 0) {
        return 1;
    }
    else if (n == 1) {
        return base;
    }
    else if (n > 0) {
        for (int i = 1; i < n; i++) {
            result *= base;
        }
        return result;
    }
    else if (n < 0) {
        for (int i = 0; i > n; i--) {
            inverse /= base;
        }
        return inverse;
    }
}

class Number {
    friend double parseNum(string);
    friend bool isNum(char);
};

double parseNum(string t) {
    unsigned decimalPlace = 0;
    bool passNumber = false;
    short isMinus = 1;
    string parseText = "";
    for (unsigned i = 0; i < t.length; i++) {
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
    
    if (!decimalPlace)
        return parseResult * isMinus;
    else
        return parseResult / powInt(10, parseText.length - decimalPlace) * isMinus;
}

bool isNum(char t) {
    return (t >= 46 && t <= 57);
}