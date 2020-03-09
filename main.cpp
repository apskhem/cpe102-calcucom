// Update: 6:35pm 9 Mar, 2020
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// UTILITY FUNCTIONS
string StrRemoveSpace(string &);
string StrSplice(string, unsigned short, unsigned short);

template<class number>
string Stringify(number);

double ParseNum(string);
bool IsNumber(char);

// Khem's Functiions
void UserRequest(string, unsigned short);
vector<string> ReadExpr(string);
string Diff(string, char);

// Leng's Functions
void PrintResult(vector<string>, unsigned short);
string ImplicitFunc(string);
float cal(string, float);
float implicit_cal(string, float, float);

// Dan's Functions
//graph

// Mhee's Functions

int main() {
    string expr, blank;
    unsigned short option;
    
    do {
        cout << "Enter f(x) = ";
        getline(cin, expr);
        
        cout << "Press: \t[1] to evaluate the function.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n";
        cout << "=>\t";
        cin >> option;
        cin.ignore();
        
        cout << "The result is...\n\n";
        
        switch (option) {
            case 1: Selection(expr, 1); break;
            case 2: Selection(expr, 2); break;
            case 3: Selection(expr, 3); break;
        }
        
        cout << "Press 'enter' to continue...";
        getline(cin, blank);
        cout << endl;
        
        cout << "Press: \t[1] to evaluate the result.\n\t[2] to derivative the function.\n\t[3] Implicit Function\n\t";
        cout << "[4] to try a new expression.\n\t[5] to end the program.\n";
        cout << "=>\t";
        cin >> option;
        cin.ignore();
        
    } while (option != 5);

    return 0;
}

void UserRequest(string expr, unsigned short option) {

    vector<string> terms;
    terms = ReadExpr(expr);

    // ++ simplify each term

    string result = "";
    float cal_equation = 0;

    switch (option) {
        case 1: { // Eval
            float x;
            cout<<"Please enter x value : ";
            cin>>x;
            cout<<"f(x) = "<<cal(term,x);
        } break;
        case 2: { // Diff
            result = "f'(x) = ";
            for (unsigned short i = 0; i < terms.size(); i++) {
                result += Diff(terms[i], 'x') + signs[i];
            }
        } break;
        case 3: { // Impl
            result = "dy/dx = ";
            for (unsigned short i = 0; i < term.size(); i++) {      //not yet
                result += Diff(terms[i], 'x') + terms[i];
            }
        } break;
        case 4:{

            result = "dx/dy = ";
            for
        }
        case 5:{

            float x,y;

            cout<<"Please enter x and y values : ";
            cin>>x>>y;
            cout<<"f(x) = "<<implicit_cal(term,x,y);
        }
    }

    // ++ re-arrange the result; cleaner result

    cout << result << "\n\n";
}

vector<string> ReadExpr(string expr) {
    vector<string> terms;
    string signs = "";
    
    unsigned short leftPar = 0, rightPar = 0;
    
    // pre-reading process
    StrRemoveSpace(expr);
    
    // reading equation process
    unsigned short splitIndex = 0;
    for (unsigned short i = 0; i < expr.size(); i++) {
        if (expr[i] == '(') leftPar++;
        else if (expr[i] == ')') rightPar++;
        
        if ((expr[i] == '+' || expr[i] == '-') && expr[i-1] != '^' && leftPar == rightPar) {
            terms.push_back(StrSplice(expr, splitIndex, i));
            signs += expr[i];
            splitIndex = i + 1;
        }
        
        if (i >= expr.size() - 1) {
            terms.push_back(StrSplice(expr, splitIndex, expr.size()));
        }
    }

    // check for errors
    if (leftPar != rightPar) throw "Bad arithmetic expression: no complete pair of parentheses ['()'].";

    return terms;
}

string Diff(string term, char var) {
    vector<string> u, trigon;
    vector<unsigned short> trigonIndex, varIndex;
    
    for (unsigned short i = 0; i < term.size(); i++) {
        // find (type): position and #of x
        if (term[i] == var) {
            varIndex.push_back(i);
        }
        
        // find (type): trigonometric function.
        else if ((term[i] == 's' || term[i] == 'c' || term[i] == 't') && i+4<term.size()) {
            string tfunc = StrSplice(term, i, i+3);
            
            if (tfunc == "sin" || tfunc == "cos" || tfunc == "tan" || tfunc == "csc" || tfunc == "sec" || tfunc == "cot") {
                
                unsigned short leftPar = 0, rightPar  = 0;
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
            if (StrSplice(term, i, i+3) == "lon") {
                l = "lon";
            }
            else if (StrSplice(term, i, i+2) == "ln") {
                l = "ln";
            }
        }
    }
    
    if (varIndex.size() == 0 && u.size() == 0) return "";
    if (term.size() == 1 && term[0] == var) return "1";
    
    string result = "";
    double n = 1, a = 1;
    
    // main diff function in many cases below...
    if (u.size() == 0) {
        switch (term[varIndex[0] + 1]) {
            case '^': { // CASE: ax^n
                unsigned short tpos = varIndex[0] + (term[varIndex[0] + 2] == '(' ? 3 : 2);
                
                a = varIndex[0] == 0 ? 1 : ParseNum(StrSplice(term, 0, varIndex[0]));
                n = ParseNum(StrSplice(term, tpos, term.size()));
                
                string strN = "";
                for (unsigned short i = tpos; i < term.size() && IsNumber(term[i]); i++) {
                    strN += term[i];
                }
                
                if (n - 1 == 0)
                    result = Stringify(a*n);
                else if (n - 1 == 1)
                    result = Stringify(a*n) + "x";
                else
                    result = Stringify(a*n) + "x^" + to_string(n-1);
            } break;
            case '(': { // CASE: ax^(n)
                
            } break;
            case '*': { // CASE: ax*(n) or ax*(u)
                
            } break;
            default: { // CASE ax or ax^1
                result = StrSplice(term, 0, varIndex[0]);
            }
        }
    }
    else {
        if (trigon.size() > 0) { // CASE: a*sin(u) or a*sin^1(u)
            if (trigon[0] == "sin") trigon[0] = "cos";
            else if (trigon[0] == "cos") trigon[0] = "sin"; //-
            else if (trigon[0] == "tan") trigon[0] = "sec^2";
            else if (trigon[0] == "csc") trigon[0] = "csc()cot()"; //-
            else if (trigon[0] == "sec") trigon[0] = "sec()tan()";
            else if (trigon[0] == "cot") trigon[0] = "csc^2"; //-
            
            if (trigon[0] == "sin" || trigon[0] == "csc()*cot()" || trigon[0] == "csc^2") a = -1;
            a *= trigonIndex[0] == 0 ? 1 : ParseNum(term);
            
            string chainDiff = Diff(u[0], var);
            bool hasSign = false;
            bool hasXorU = false;
            
            for (unsigned short i = 0; i < chainDiff.size(); i++) {
                if (chainDiff[i] == '+' || chainDiff[i] == '-') hasSign = true;
                else if (chainDiff[i] == var) hasXorU = true;
            }
            
            if (hasSign)
                result = Stringify(a) + trigon[0] + "(" + u[0]  + ")*(" + chainDiff + ")"; 
            else if (hasXorU)
                result = Stringify(a) + trigon[0] + "(" + u[0]  + ")*" + chainDiff;
            else
                result = Stringify(a*ParseNum(chainDiff)) + trigon[0] + "(" + u[0]  + ")";
        }
        else if (trigonIndex.size() > 0) { // CASE: a*sin^n(u)
            a = trigonIndex[0] == 0 ? 1 : ParseNum(term);
            n = ParseNum(StrSplice(term, trigonIndex[0] + 4, term.size()));
            string chainDiff = Diff(u[0], var);
            
            unsigned short fisrtParPos = 0;
            for (unsigned short i = 0; i < u[0].size() && u[0][i] != '('; i++) { // find fisrt '(' pos
                fisrtParPos++;
            }
            
            if (n-1 == 1)
                result = Stringify(a*n) + u[0] + "*" + chainDiff;
            else {
                string tempBlock = StrSplice(u[0], fisrtParPos, u[0].size());
                result = Stringify(a*n) + StrSplice(u[0], 0, 3) + "^" + to_string(n-1) + tempBlock + "*" + chainDiff; 
            }
        }
    }
    
    return result;
}

float cal(string t, float x){

    float cal_result = 0;

    for(int i=0; i<t.size(); i++){

        if(t[i] = "x") 
            t[i] = x;

        cal_result += ;
    }
    
    return cal_result;
}

float implicit_cal(string t, float x, float y){

    float cal_result = 0;

    for(int i=0; i<t.size(); i++)
        if(t[i] = "x")
            t[i] = x;
        if(t[i] = "y")
            t[i] = y;
    
    cal_result +=   ;
    
}

// UTILITY FUNCTIONS
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

template<class number>
string Stringify(number n) {
    return (n == 1 ? "" : to_string(n));
}

double ParseNum(string t) {
    unsigned short decimalPlace = 0;
    bool passNumber = false;
    short mul = 1;
    string newT = "";
    for (unsigned short i = 0; i < t.size(); i++) {
        if (t[i] >= 46 && t[i] <= 57 && t[i] != '.') {
            passNumber = true;
            newT += t[i];
        }
        else if (t[i] == '-' && t[i+1] >= 46 && t[i+1] <= 57) mul = -1;
        else if (t[i] == '.' && passNumber) decimalPlace = newT.size();
        else if (passNumber) break;
    }
    
    return (newT == "" ? 0 : stoi(newT.c_str()) / pow(10, newT.size() - decimalPlace) * mul);
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

        ReadExpr(t, 3);

        result = "";
        
        
        return result;
    }
    
    else if (choice == 2){      //dx/dy
        
        string result;
        
        result = "";
        
        
        
        return result;
    }
    
    else    return "Please enter 1 or 2";
}