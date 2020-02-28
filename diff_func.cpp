#include <iostream>
#include <cmath>
#include <string>

using namespace std;

string Derivative(string);

int main(){


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

    switch(term)

        case () //n > 1
            n<<"*"<<Derivative(u)<<"*"<<u<<"^("<<n-1<<")";

        case()  //logBase !=0; u == log
            Derivative(v)<<"/("<<u<<"*ln("<<a<<")";

        case() //logBase == 0; u == log
            cout<<"Invalid arithmatic expression";

        case() // u = ln;
            Derivative(v)<<"/("<<u<<")";

        case()  // 
            Derivative(u)<<"*"<<a<<"^("<<u<<")ln("<<a<<")";

        case()    // u == e;
            Derivative(u)<<"*e^("<<u<<")";

        case()  //
    

    
    return result;
}
