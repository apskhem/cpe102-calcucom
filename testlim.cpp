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
#include "engine.max_min.h"





double Analys(string & ,string &,string &,double); 


int main(){
    double x;
    string Eqation ="";
    string FirstEqa="",SecondEqa="";
    // cout<<"Input x :";
    // cin>>x;
    Analys(Eqation,FirstEqa,SecondEqa,x);





}

double Analys(string &eqation, string &a, string &b,double x)
{

   if(evalExpr(readExpr(eqation),x,'x')<=INT_MAX){
       return evalExpr(readExpr(eqation),x,'x');
   }
else
{
    int pos = eqation.search('/');
    int posM = eqation.search('-');
    int posMul = eqation.search('*');
    int posP = eqation.search('^');

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
                    return NAN;  //case ค่าคงที่ หาร ์ NAN
        }
        else if (evalExpr(readExpr(a),x,'x')==NAN && evalExpr(readExpr(b),x,'x')==NAN){
                    if(evalExpr(readExpr(diff(a,'x')),x,'x')/ evalExpr(readExpr(diff(diff(b,'x'),'x')),x,'x')<=INT_MAX) {
                        return evalExpr(readExpr(a),x,'x')<=INT_MAX && evalExpr(readExpr(b),x,'x');
                    } 
                    else
                    {
                        eqation = diff(a,'x')+"/"+diff(b,'x');
                    }
                    
                                //case NAN หาร NAN
            }
        else if (evalExpr(readExpr(a),x,'x')==0 && evalExpr(readExpr(b),x,'x')==0){
                   if(evalExpr(readExpr(diff(a,'x')),x,'x')/ evalExpr(readExpr(diff(diff(b,'x'),'x')),x,'x')<=INT_MAX) {
                        return evalExpr(readExpr(a),x,'x')<=INT_MAX && evalExpr(readExpr(b),x,'x');
                    } 
                    else
                    {
                        eqation = diff(a,'x')+"/"+diff(b,'x');
                    }
                                // case 0/0
        }


    }
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    else if (eqation[pos] != '/')
    {
            int posM = eqation.search('-');

            if (eqation[posM] == '-')
    {
        for (unsigned int i = 0; i < posM; ++i)
        {
            a += eqation[i];
        }
        for (unsigned int j = posM + 1; j <= eqation.length; ++j)
        {
            b += eqation[j];
        }
    }

        int posln=a.search("ln");
        int posln2=b.search("ln");

        if(eqation[posln]=='ln' && eqation[posln2]=='ln'){

        if(evalExpr(readExpr(a),x,'x')==NAN && evalExpr(readExpr(b),x,'x')==NAN){


            if(log (evalExpr(readExpr(a),x,'x') /evalExpr(readExpr(b),x,'x'))<=INT_MAX){
            return  log (evalExpr(readExpr(a),x,'x') /evalExpr(readExpr(b),x,'x')) ; 
            }
            else
            {
                 eqation ="Not to find";
            }  //เคส NAN - NAN
        }
        }
    }


///////////////////////////////////////////////////////////////////////////////////////////////////////

    else if (eqation[pos] != '/' && eqation[posM] !='-')
    {
            int posMul = eqation.search('*');

            if (eqation[posMul] == '*')
    {
        for (unsigned int i = 0; i < posMul; ++i)
        {
            a += eqation[i];
        }
        for (unsigned int j = posMul + 1; j <= eqation.length; ++j)
        { 
            b += eqation[j];
        }
    }
        if(evalExpr(readExpr(a),x,'x')==NAN 
            && evalExpr(readExpr(b),x,'x')==0
            ||evalExpr(readExpr(b),x,'x')==NAN && evalExpr(readExpr(a),x,'x')==0){

                    if(evalExpr(readExpr(a),x,'x')/evalExpr(readExpr(b),x,'x')<=INT_MAX)
                    {
                        return evalExpr(readExpr(a),x,'x')/evalExpr(readExpr(b),x,'x');
                    }
                    else if(evalExpr(readExpr(b),x,'x')/evalExpr(readExpr(a),x,'x')<=INT_MAX)
                    {
                       return evalExpr(readExpr(b),x,'x')/evalExpr(readExpr(a),x,'x');
                    }
                    else {
                        eqation="Not to find";
                    }
                
                ;  //เคส NAN * 0 หรือ 0*NAN
        }


    }



////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    else if (eqation[pos] != '/' && eqation[posM] !='-' && eqation[posMul] !='*' )
    {
            int posP = eqation.search('^');

            if (eqation[posP] == '^')
    {
        for (unsigned int i = 0; i < posP; ++i)
        {
            a += eqation[i];
        }
        for (unsigned int j = posP + 1; j <= eqation.length; ++j)
        {
            b += eqation[j];
        }
    }
        if(evalExpr(readExpr(a),x,'x')==NAN 
            && evalExpr(readExpr(b),x,'x')==0
                || evalExpr(readExpr(b),x,'x')==NAN 
                    && evalExpr(readExpr(a),x,'x')==0){
                        
                ;  //เคส NAN ^ 0 หรือ 0 ^ NAN
        }

        else if(evalExpr(readExpr(a),x,'x')==1
            && evalExpr(readExpr(b),x,'x')==NAN)
            {
                        
                ;  //เคส NAN ^ 0 หรือ 0 ^ NAN
        }


    }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


a=""; 
b="";

if( evalExpr(readExpr(eqation),x,'x')==NAN){
    Analys(eqation,a,b,x);
}
}
}

    