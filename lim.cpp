#include<iostream>
#include<cmath>
#include <string>
using namespace std;



float assignVar(string);
void change(string & ,string &,string & ,string &);
void finddivide(string  ,string & ,string &);


int main(){
string eqation="2*(x)^(2*x+1)/(x+9)";
double x;
cout<<"Computing Limits"<<endl;
cout<<"-------------------------------------------"<<endl;
cout<<"PLESE Input value of x on eqation : "<<endl;
cin>>x;



string a="",b="";
finddivide(eqation,a,b);
cout<<"Eqation : "+a+"/"+b<<endl;




string Base="",Power="",first="";
change(a,Base,Power,first);
//a=first+"*"+"pow(" +Base +"," +Power +")"+")";
cout<<"ON : "+a<<endl;
change(b,Base,Power,first);
//b=first+"*"+"pow(" +Base +"," +Power +")"+")";
cout<<"Under : "+b;






}


void change(string &eqation ,string &Base,string &Power, string &first){
   
    int pos=eqation.find("^");
    int ONE=eqation.find("(");
    

    string FindP;
    FindP+=eqation.substr(pos+1);
    int end=pos+1+FindP.find(")"); 

    first+=eqation.substr(0,ONE);


 if(eqation[pos]=='^'){
        for(unsigned int i=ONE;i<=pos-1;++i){
            Base+=eqation[i];

        }
        for(unsigned int j=pos+1;j<=end;++j){
            Power+=eqation[j];
        }
       // eqation="pow("+Base+","+Power+")";
 
 eqation=first+"pow(" +Base +"," +Power +")"+")";
 

}
}
void finddivide(string eqation, string &a ,string &b){
   
    int pos=eqation.find('/');
    if(eqation[pos]=='/'){
        for(unsigned int i=0;i<pos;++i){
            a+=eqation[i];

        }
        for(unsigned int j=pos+1;j<=eqation.size();++j){
            b+=eqation[j];
        }
    }
    
}

float assignVar(string eqation ,double a){
   
for(unsigned int N=0;N<eqation.size();++N)
if(eqation[N]=='x'){

}

}

