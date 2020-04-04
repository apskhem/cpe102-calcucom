#include <iostream>

void error(const char *msg, const unsigned cond=1) {
    switch (cond) {
        case 1: std::cout << "Bad arithmetic expression: "; break;
        case 2: std::cout << "Lack of features: "; break;
        case 3: std::cout << "Exceed program's limitation: "; break;
        case 4: std::cout << "Wrong user input: "; break;
        case 5: std::cout << "Systematic fault: "; break;
    };

    std::cout << msg << ".\n\n";
    
    throw 0;
}

#include "klib.array.h"
#include "klib.string.h"
#include "klib.number.h"
#include "engine.base.h"
// #include "engine.lim.h"
#include "engine.max_min.h"





double Analys(string ,string &,string &,double); 


int main(){
    double x;
    string Eqation ="",FirstEqa="",SecondEqa="";
    // cout<<"Input x :";
    // cin>>x;
    Analys(Eqation,FirstEqa,SecondEqa,x);





}

double Analys(string eqation, string &a, string &b,double x)
{

    int pos = eqation.search('/');
    if (eqation[pos] == '/')
    {
        for (unsigned int i = 0; i < pos; ++i)
        {
            a += eqation[i];
        }
        for (unsigned int j = pos + 1; j <= eqation.length; ++j)
        {
            b += eqation[j];
        }
            
        if(evalExpr(readExpr(a),x,'x')<=INT_MAX && evalExpr(readExpr(b),x,'x')==0){
                    return NAN;
        }
        else if (evalExpr(readExpr(a),x,'x')==NAN && evalExpr(readExpr(b),x,'x')==NAN){
                    return  evalExpr(readExpr(diff(a,'x')),x,'x')/ evalExpr(readExpr(diff(diff(b,'x'),'x')),x,'x');

            }
        else if (evalExpr(readExpr(a),x,'x')==0 && evalExpr(readExpr(b),x,'x')==0){
                    return  evalExpr(readExpr(diff(a,'x')),x,'x')/ evalExpr(readExpr(diff(diff(b,'x'),'x')),x,'x');
        }


    }
    else if (eqation[pos] != '/')
    {
            int posM = eqation.search('-');

            if (eqation[posM] == '-')
    {
        for (unsigned int i = 0; i < pos; ++i)
        {
            a += eqation[i];
        }
        for (unsigned int j = pos + 1; j <= eqation.length; ++j)
        {
            b += eqation[j];
        }
    }


else if (eqation[pos] != '/' && eqation[posM] !='-')
    {
            int posMul = eqation.search('*');

            if (eqation[posMul] == '*')
    {
        for (unsigned int i = 0; i < pos; ++i)
        {
            a += eqation[i];
        }
        for (unsigned int j = pos + 1; j <= eqation.length; ++j)
        {
            b += eqation[j];
        }
    }

    }
}



    