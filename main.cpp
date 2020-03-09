#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

string ReadEquation(string , int);
string Diff(string);
string Integral(string);
string implicitFunc(string, int);
string showResult(string, int);

// Update: 8:00pm 3 Mar, 2020

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
        
        cout << "Press: \t[1] to evaluate the function.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n";
        cout << "=>\t";
        cin >> option;
        cin.ignore();
        
        cout << "The result is...\n\n";
        
        switch (option) {
            case 1: cout << ReadEquation(equation,1) << "\n\n"; break;
            case 2: cout << ReadEquation(equation,2) << "\n\n"; break;
            case 3: cout << ReadEquation(equation,3) << "\n\n"; break;
        }
        
        cout << "Press 'enter' to continue...";
        getline(cin, blank);
        cout << endl;
        
        cout << "Press: \t[1] to evaluate the result.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n\t";
        cout << "[4] to try a new equation.\n\t[5] to end the program.\n";
        cout << "=>\t";
        cin >> option;
        cin.ignore();
        
    } while (option != 5);

    return 0;
}

string ReadEquation(string eq) {
    vector<string> term(0);
    string signs = "";
    
    unsigned short leftPar = 0;
    unsigned short rightPar = 0;
    
    // pre-reading process
    StringSpaceRemove(eq);
    
    // reading equation process
    unsigned short splitIndex = 0;
    for (unsigned short i = 0; i < eq.size(); i++) {
        if (eq[i] == '(') leftPar++;
        else if (eq[i] == ')') rightPar++;
        
        if ((eq[i] == '+' || eq[i] == '-') && eq[i-1] != '^' && leftPar == rightPar) {
            term.push_back(StringSplit(eq, splitIndex, i));
            signs += eq[i];
            splitIndex = i + 1;
        }
        
        if (i >= eq.size() - 1) {
            term.push_back(StringSplit(eq, splitIndex, i + 1));
        }
    }

    showResult(term, N);

    return result;
}

string showResult(string eq, int N){

    if(N == 1){     //normal function
        string result = "f'(x) = ";
        for (unsigned short i = 0; i < term.size(); i++) {
            result += Diff(term[i]) + signs[i];
        }
    }
    else if(N == 2){       //dy/dx
        string result = "dy/dx = ";
        for (unsigned short i = 0; i < term.size(); i++) {      //not yet
            result += Diff(term[i]) + signs[i]; 
        }
    }
    else if(N==3){      //dx/dy
        string result = "dx/dy = ";
        for (unsigned short i = 0; i < term.size(); i++) {      //not yet
            result += Diff(term[i]) + signs[i];
        }

    }
}


// main derivative function
string Diff(string term) {
    vector<string> u(0);
    vector<string> trigon(0);
    vector<unsigned short> trigonIndex(0);
    vector<unsigned short> xIndex(0);
    
    for (unsigned short i = 0; i < term.size(); i++) {
        // find (type): position and #of x
        if (term[i] == 'x') {
            xIndex.push_back(i);
        }
        
        // find (type): trigonometric function.
        else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i+4<term.size()) {
            string tfunc = StringSplit(term, i, i+3);
            
            if (tfunc == "sin" || tfunc == "cos" || tfunc == "tan" || tfunc == "csc" || tfunc == "sec" || tfunc == "cot") {
                
                unsigned short leftPar = 0;
                unsigned short rightPar  = 0;
                trigonIndex.push_back(i);
                string tempU = "";
                
                if (term[i+3] == '^') { // find: a*sin^n(u)
                    i+=4; // skip 'sin^'
                    while (IsNumber(term[i])) i++;
                    
                    leftPar++;
                    tempU = term[i++];
                    while (i < term.size() && leftPar != rightPar) {
                        if (term[i] == '(') leftPar++;
                        else if (term[i] == ')') rightPar++;
                        
                        tempU += term[i++];
                    }
                    
                    u.push_back(tfunc + tempU);
                }
                else { // find: a*sin(u) or a*sin^1(u)
                    trigon.push_back(tfunc);
                    
                    i+=4; // skip 'sin('
                    while (i < term.size() && (term[i] != ')' || leftPar != rightPar)) {
                        if (term[i] == '(') leftPar++;
                        else if (term[i] == ')') rightPar++;
                        
                        tempU += term[i++];
                    }
                    u.push_back(tempU);
                }
            }
        }
        
        // find (type): logarithm function
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
    
    if (xIndex.size() == 0 && u.size() == 0) return "";
    if (term.size() == 1 && term[0] == 'x') return "1";
    
    string result = "";
    int n, a;
    
    // main diff function in many cases below...
    if (u.size() == 0) {
        switch (term[xIndex[0] + 1]) {
            case '^': { // case: ax^n
                unsigned short tpos = xIndex[0] + (term[xIndex[0] + 2] == '(' ? 3 : 2);
                
                a = xIndex[0] == 0 ? 1 : ParseInt(StringSplit(term, 0, xIndex[0]));
                n = ParseInt(StringSplit(term, tpos, term.size()));
                
                string strN = "";
                for (unsigned short i = tpos; i < term.size() && IsNumber(term[i]); i++) {
                    strN += term[i];
                }
                
                if (n - 1 == 0)
                    result = Num2Str(a*n);
                else if (n - 1 == 1)
                    result = Num2Str(a*n) + "x";
                else
                    result = Num2Str(a*n) + "x^" + to_string(n-1);
            } break;
            case '(': { // case: ax^(n)
                
            } break;
            case '*': { // case: ax*(n) or ax*(u)
                
            } break;
            default: { // case ax or ax^1
                result = StringSplit(term, 0, xIndex[0]);
            }
        }
    }
    else {
        if (trigon.size() > 0) { // case: a*sin(u) or a*sin^1(u)
           if (trigon[0] == "sin") trigon[0] = "cos";
            else if (trigon[0] == "cos") trigon[0] = "-sin";
            else if (trigon[0] == "tan") trigon[0] = "sec^2";
            else if (trigon[0] == "csc") trigon[0] = "-csc()*cot()";
            else if (trigon[0] == "sec") trigon[0] = "sec()*tan()";
            else if (trigon[0] == "cot") trigon[0] = "-csc^2";
            
            a = trigonIndex[0] == 0 ? 1 : ParseInt(term);
            
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
            
            if (hasSign)
                result = Num2Str(a) + trigon[0] + "(" + u[0]  + ")*(" + chainDiff + ")"; 
            else if (hasXorU)
                result = Num2Str(a) + trigon[0] + "(" + u[0]  + ")*" + chainDiff;
            else
                result = Num2Str(a*ParseInt(chainDiff)) + trigon[0] + "(" + u[0]  + ")";
        }
        else if (trigonIndex.size() > 0) { // case: a*sin^n(u)
            a = trigonIndex[0] == 0 ? 1 : ParseInt(term);
            n = ParseInt(StringSplit(term, trigonIndex[0] + 4, term.size()));
            string chainDiff = Diff(u[0]);
            
            unsigned short fisrtParPos = 0;
            for (unsigned short i = 0; i < u[0].size() && u[0][i] != '('; i++) { // find fisrt '(' pos
                fisrtParPos++;
            }
            
            if (n-1 == 1)
                result = Num2Str(a*n) + u[0] + "*" + chainDiff;
            else {
                string tempBlock = StringSplit(u[0], fisrtParPos, u[0].size());
                result = Num2Str(a*n) + StringSplit(u[0], 0, 3) + "^" + to_string(n-1) + tempBlock + "*" + chainDiff; 
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

string ImplicitFunc(string t){

    int choice;
    
    cout<<"Press: \t[1] to evaluate dy/dx\n\t[2] to evaluate dx/dy\n";
    cout << "=>\t";
    cin>>choice;
    cin.ignore();
    
    if(choice == 1){    // dy/dx
        string result;

        ReadEquation(t);

        result = ;
        
        
        return result;
    }
    
    else if (choice == 2){      //dx/dy
        
        string result;
        
        result = ;
        
        
        
        return result;
    }
    
    else    return "Please enter 1 or 2";
}