#include <iostream>
#include <cmath>
#include <string>
using namespace std;

string ReadEquation(string eq);
string Diff(string);
string Integral(string);

// UTILITY FUNCTIONS
void StringSpaceRemove(string &);
string StringSplit(string, unsigned short, unsigned short);
string Num2Str(int);
int ParseInt(string);
float ParseFloat(string);
bool IsNumber(char);

int main() {
    string equation, blank;
    unsigned short option;
    
    do {
        
        cout << "Enter f(x) = ";
        getline(cin, equation);
        
        cout << "Press: \t[1] to evaluate the function.\n\t[2] to derivative the function.\n\t[3] to integral the function.\n";
        cout << "=>\t";
        cin >> option;
        cin.ignore();
        
        cout << "The result is...\n\n";
        
        switch (option) {
            case 1: cout << ReadEquation(equation) << "\n\n"; break;
            case 2: cout << ReadEquation(equation) << "\n\n"; break;
            case 3: cout << ReadEquation(equation) << "\n\n"; break;
        }
        
        cout << "Press 'enter' to continue...";
        getline(cin, blank);
        cout << endl;
        
        cout << "Press: \t[1] to evaluate the result.\n\t[2] to derivative the function.\n\t[3] to integral the function.\n\t";
        cout << "[4] to try a new equation.\n\t[5] to end the program.\n";
        cout << "=>\t";
        cin >> option;
        cin.ignore();
        
    } while (option != 5);

    return 0;
}

string ReadEquation(string eq) {
    string term[eq.size()/2+1] = {};
    string signs = "";
    
    unsigned short termIndex = 0;
    unsigned short splitIndex = 0;
    
    unsigned short leftPar = 0;
    unsigned short rightPar = 0;
    
    // pre-reading process
    StringSpaceRemove(eq);
    
    // reading equation process
    for (unsigned short i = 0; i < eq.size(); i++) {
        if (eq[i] == '(') leftPar++;
        else if (eq[i] == ')') rightPar++;
        
        if ((eq[i] == '+' || eq[i] == '-') && eq[i-1] != '^' && leftPar == rightPar) {
            term[termIndex++] = StringSplit(eq, splitIndex, i);
            signs += eq[i];
            splitIndex = i + 1;
        }
        
        if (i >= eq.size() - 1) {
            term[termIndex++] = StringSplit(eq, splitIndex, i + 1);
        }
    }
    
    // ++ simplify each term
    
    // process each term
    string result = "f'(x) = ";
    for (unsigned short i = 0; i < termIndex; i++) {
        result += Diff(term[i]) + signs[i];
    }
    
    // ++ re-arrange the result; cleaner result
    
    return result;
}

// main derivative function
string Diff(string term) {
    string u[term.size()/2] = {};
    string trigon[term.size()/4] = {};
    
    unsigned short collectU = 0;
    unsigned short collectTrigon = 0;
    unsigned short collectTrigonIndex[term.size()] = {};
    unsigned short collectX = 0;
    unsigned short collectXIndex[term.size()] = {};
    
    for (unsigned short i = 0; i < term.size(); i++) {
        if (term[i] == 'x') {
            collectXIndex[collectX++] = i;
        }
        
        // find trigonometric function and collect 'u' function.
        else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i+2<term.size()) {
            string tfunc = StringSplit(term, i, i+3);
            
            if (tfunc == "sin" || tfunc == "cos" || tfunc == "tan" || tfunc == "csc" || tfunc == "sec" || tfunc == "cot") {
                collectTrigonIndex[collectTrigon] = i;
                trigon[collectTrigon++] = tfunc;
                
                
                i+=4; // skip 'sin('
                unsigned short leftPar = 0;
                unsigned short rightPar  = 0;
                int collectPar = 0; // collect parenthes pair for finding function 'u'
                while (i < term.size() && (term[i] != ')' || leftPar != rightPar)) {
                    if (term[i] == '(') leftPar++;
                    else if (term[i] == ')') rightPar++;
                    
                    u[collectU] += term[i];
                    i++;
                }
                collectU++;
            }
        }
        
        // find logarithm function
        else if (term[i] == 'l' && i+2<term.size()) {
            string l;
            if (StringSplit(term, i, i+3) == "lon") {
                l = "lon";
            }
            else if (StringSplit(term, i, i+2) == "ln") {
                l = "ln";
            }
        }
    }
    
    // cout << u[0] << endl;
    // return "TEST";
    
    if (collectX == 0 && collectU == 0) return "";
    if (term.size() == 1 && term[0] == 'x') return "1";
    
    string result = "";
    int n, a;
    
    // reading 'x';
    if (collectU == 0) {
        switch (term[collectXIndex[0] + 1]) {
            case '^': {
                unsigned short tpos = collectXIndex[0] + (term[collectXIndex[0] + 2] == '(' ? 3 : 2);
                
                a = collectXIndex[0] == 0 ? 1 : ParseInt(StringSplit(term, 0, collectXIndex[0]));
                n = ParseInt(StringSplit(term, tpos, term.size()));
                
                string strN = "";
                for (unsigned short i = tpos; i < term.size() && IsNumber(term[i]); i++) {
                    strN += term[i];
                }
                
                if (n - 1 == 0) {
                    result = Num2Str(a*n);
                }
                else if (n - 1 == 1) {
                    result = Num2Str(a*n) + "x";
                }
                else {
                    result = Num2Str(a*n) + "x^" + to_string(n-1);
                }
            } break;
            case '(': {
                
            } break;
            case '*': {
                
            } break;
            default: { // x is ^1 but not show
                result = to_string(ParseInt(StringSplit(term, 0, collectXIndex[0])));
            }
        }
    }
    else {
        if (collectTrigon > 0) {
           if (trigon[0] == "sin") trigon[0] = "cos";
            else if (trigon[0] == "cos") trigon[0] = "-sin";
            else if (trigon[0] == "tan") trigon[0] = "sec^2";
            else if (trigon[0] == "csc") trigon[0] = "-csc()*cot()";
            else if (trigon[0] == "sec") trigon[0] = "sec()*tan()";
            else if (trigon[0] == "cot") trigon[0] = "-csc^2";
            
            a = collectTrigonIndex[0] == 0 ? 1 : ParseInt(StringSplit(term, 0, collectTrigonIndex[0]));
            n = 1;
            
            string chainDiff = Diff(u[0]);
            bool hasSign = false;
            bool hasXorU = false;
            
            for (unsigned short i = 0; i < chainDiff.size(); i++) {
                if (chainDiff[i] == '+' || chainDiff[i] == '-') {
                    hasSign = true;
                }
                else if (chainDiff[i] == 'x') {
                    hasXorU = true;
                }
            }
            
            if (hasSign) {
                result = Num2Str(a*n) + trigon[0] + "(" + u[0]  + ")*(" + chainDiff + ")"; 
            }
            else if (hasXorU) {
                result = Num2Str(a*n) + trigon[0] + "(" + u[0]  + ")*" + chainDiff;
            }
            else {
                result = Num2Str(a*ParseInt(chainDiff)) + trigon[0] + "(" + u[0]  + ")";
            }
        }
    }
    
    return result;
}

// UTILITY FUNCTIONS
void StringSpaceRemove(string &t) {
    string result = "";
    for (unsigned short i = 0; i < t.size(); i++) {
        if (t[i] != ' ')
            result += t[i];
    }
    
    t = result;
}

string StringSplit(string t, unsigned short from, unsigned short to) {
    string result = "";
    for (unsigned short i = from; i < to; i++) {
        result += t[i];
    }
    
    return result;
}

string Num2Str(int n) {
    if (n == 1) {
        return "";
    }
    else {
        return to_string(n);
    }
}

int ParseInt(string t) {
    return atoi(t.c_str());
}

float ParseFloat(string t) {
    return atof(t.c_str());
}

bool IsNumber(char t) {
    return (t >= 46 && t <= 57);
}