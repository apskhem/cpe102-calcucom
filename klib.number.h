class Mathf {
    friend double powInt(double, const int);
}

double powInt(double base, const int n) {
    double inverse = 1;
    if (n == 0) {
        return 1;
    }
    else if (n == 1) {
        return base;
    }
    else if (n > 0) {
        for (int i = 1; i < n; i++) {
            base *= base;
        }
    }
    else if (n < 0) {
        for (int i = 0; i > n; i--) {
            inverse /= base;
        }
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

    int parseResult = 0;
    for (unsigned i = parseText.length-1; i >= 0; i--) {
        parseResult = parseText[i] * powInt(10, parseText.length-1-i);
    }
    
    if (!decimalPlace)
        return parseResult;
    else
        return parseResult / powInt(10, parseText.length - decimalPlace) * isMinus;
}

bool isNum(char t) {
    return (t >= 46 && t <= 57);
}