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

int main() {
    string equation, blank;
    unsigned short option;
    
    do {
        
        cout << "Enter f(x) = ";
        getline(cin, equation);
        
        cout << "Press: \t[1] to evaluate the result.\n\t[2] to derivative the function.\n\t[3] to integral the function.\n";
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
        
    } while (option != 4);

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
    int aasd;
    return result;
}
