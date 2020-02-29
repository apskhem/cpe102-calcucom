#include <iostream>
#include <cmath>
#include <string>
using namespace std;

string ReadEquation(string eq);
string Derivative(string);
string Integral(string);

// HELPER FUNCTIONS
void StringSpaceRemove(string &);
string StringSplit(string, unsigned short, unsigned short);
int ParseInt(string);
float ParseFloat(string);
bool isNumber(char);

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
        
        cout << "Press Enter to continue...";
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
    string term[eq.size()/2] = {};
    string signs = "";
    
    unsigned short termIndex = 0;
    unsigned short splitIndex = 0;
    unsigned short numberOfParentheses = 0;
    
    // pre-reading process
    StringSpaceRemove(eq);
    
    // reading equation process
    for (unsigned short i = 0; i < eq.size(); i++) {
        if (eq[i] == '(' || eq[i] == ')') numberOfParentheses++;
        
        if ((eq[i] == '+' || eq[i] == '-') && numberOfParentheses % 2 == 0) {
            term[termIndex++] = StringSplit(eq, splitIndex, i);
            signs += eq[i];
            splitIndex = i + 1;
        }
        
        if (i >= eq.size() - 1) {
            term[termIndex++] = StringSplit(eq, splitIndex, i + 1);
        }
    }
    
    // process each term
    string result = "";
    for (unsigned short i = 0; i < termIndex; i++) {
        result += Derivative(term[i]) + signs[i];
    }
    
    // re-arrange the result; cleaner result
    
    return result;
}

string Derivative(string term) {
    string result = "";
    unsigned short collectX = 0;
    unsigned short collectXIndex[term.size()] = {};
    double a;
    
    for (unsigned short i = 0; i < term.size(); i++) {
        if (term[i] == 'x') {
            collectXIndex[collectX++] = i;
        }
    }
    
    if (collectX != 0) {
        int n, a;
        
        // reading 'x';
        switch (term[collectXIndex[0] + 1]) {
            case '^': {
                unsigned short tpos = collectXIndex[0] + (term[collectXIndex[0] + 2] == '(' ? 3 : 2);
                string strN = "";
                a = ParseInt(StringSplit(term, 0, collectXIndex[0]));
                n = ParseInt(StringSplit(term, tpos, term.size()));
                
                for (unsigned short i = tpos; i < term.size() && isNumber(term[i]); i++) {
                    strN += term[i];
                }
                
                if (n - 1 == 0) {
                    result = to_string(a*n);
                }
                else {
                    result = to_string(a*n) + "x^" + to_string(n-1);
                }
            } break;
            case '(': {
                
            } break;
            case '*': {
                
            } break;
        }
    }
    
    return result;
}

// HELPER FUNCTIONS
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

int ParseInt(string t) {
    return atoi(t.c_str());
}

float ParseFloat(string t) {
    return atof(t.c_str());
}

bool isNumber(char t) {
    return (t >= 46 && t <= 57);
}