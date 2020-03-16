
class Number {
    friend double parseNum(string);
    friend bool isNum(char);
}

double parseNum(string t) {
    unsigned decimalPlace = 0;
    bool passNumber = false;
    short isMinus = 1;
    string newT = "";
    for (unsigned i = 0; i < t.size(); i++) {
        if (t[i] >= 46 && t[i] <= 57 && t[i] != '.') {
            passNumber = true;
            newT += t[i];
        }
        else if (t[i] == '-' && t[i + 1] >= 46 && t[i + 1] <= 57)
            isMinus = -1;
        else if (t[i] == '.' && passNumber)
            decimalPlace = newT.size();
        else if (passNumber)
            break;
    }
    
    if (newT == "") return 0;
    
    if (!decimalPlace)
        return stoi(newT.c_str());
    else
        return stoi(newT.c_str()) / pow(10, newT.size() - decimalPlace) * isMinus;
}

bool isNum(char t) {
    return (t >= 46 && t <= 57);
}