void StrRemoveSpace(string &t) {
    string result = "";
    for (unsigned short i = 0; i < t.size(); i++) {
        if (t[i] != ' ')
            result += t[i];
    }

    t = result;
}

string StrSplice(string t, unsigned short from, unsigned short to) {
    string result = "";
    for (unsigned short i = from; i < to; i++) {
        result += t[i];
    }

    return result;
}

template <class number>
string Stringify(number n) {
    return (n == 1 ? "" : to_string(int(n)));
}

double ParseNum(string t) {
    unsigned short decimalPlace = 0;
    bool passNumber = false;
    short isMinus = 1;
    string newT = "";
    for (unsigned short i = 0; i < t.size(); i++) {
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

bool IsNumber(char t) {
    return (t >= 46 && t <= 57);
}