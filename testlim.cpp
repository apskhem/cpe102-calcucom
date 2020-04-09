#include <iostream>
#include <cmath>
#include <string>

using namespace std;

string assignVar(string &, string);
void change(string &, string , string , string );
void finddivide(string, string &, string &);
double stodu(string );

int main()
{
   
    string eqation = "50*x*(2*x*x+2)^(2*x+1)/(x+9)^(20*x+30)";
    string x; 
    string a = "", b = "";

    finddivide(eqation, a, b);

    cout << "Eqation : " + a + "/" + b << endl;
    cout << "Computing Limits" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "PLESE Input value of x on eqation : " ;
    cin >> x;
    
    cout<<"When X Approach :"<<x<<"\n"<<" eqation ="<< assignVar(eqation,x)<<endl;

    string Base = "", Power = "", first = "";
    change(a, Base, Power, first);
    assignVar(a,x);
    //a=first+"*"+"pow(" +Base +"," +Power +")"+")";
    cout << "Top eqation : " + a << endl;
    change(b, Base, Power, first);
    assignVar(b,x);
    //b=first+"*"+"pow(" +Base +"," +Power +")"+")";
    cout << "Bottom eqation : " + b<<endl;

    
}
/*
for(unsigned int i=0;i<eqation.size();++i)
if(eqation[i]=='^'){
}*/

double stodu(string eqation ){
  ;
}

void change(string &eqation, string Base, string Power, string first)
{  

    int pos = eqation.find("^");
    int ONE = eqation.find("(");
  

    string FindP;
    FindP += eqation.substr(pos + 1);
    int end = pos + 1 + FindP.find(")");

    first += eqation.substr(0, ONE);


    if (eqation[pos] == '^')
    {
        for (unsigned int i = ONE; i <= pos - 1; ++i)
        {
            Base += eqation[i];
        }
        for (unsigned int j = pos + 1; j <= end; ++j)
        {
            Power += eqation[j];
        }
        // eqation="pow("+Base+","+Power+")";

        eqation = first + "pow(" + Base + "," + Power + ")" ;
    
    }
}
void finddivide(string eqation, string &a, string &b)
{

    int pos = eqation.find('/');
    if (eqation[pos] == '/')
    {
        for (unsigned int i = 0; i < pos; ++i)
        {
            a += eqation[i];
        }
        for (unsigned int j = pos + 1; j <= eqation.size(); ++j)
        {
            b += eqation[j];
        }
    }
}

string assignVar(string & eqation, string a)
{

    size_t found = eqation.find('x');
    if (found != std::string::npos)
    {
        //eqation.insert(found, a);    
    }
    //cout << "first 'x' found at: " << found << '\n';

    found = eqation.find('x', found + 1);
    if (found != std::string::npos)
    {
        eqation.insert(found + 1, a);
        eqation.erase(found,1);
        
    }
    // cout << "second 'x' found at: " <<found << '\n';

    found = eqation.find('x', found + 1);
    if (found != std::string::npos)
    {
        eqation.insert(found+1, a);
        eqation.erase(found,1);
      
    }
    // cout << "third 'x' found at: " << found << '\n';

    found = eqation.find('x', found + 1);
    if (found != std::string::npos)
    {
        eqation.insert(found+1, a);
        eqation.erase(found,1);
        
    }
    // cout << "Fourth 'x' found at: " << found << '\n';

    found = eqation.find('x', found + 1);
    if (found != std::string::npos)
    {
        eqation.insert(found+1, a);
        eqation.erase(found,1);
       
    }
    //cout << "Fifth 'x' found at: " << found << '\n';
     found = eqation.find('x', found + 1);
    if (found != std::string::npos)
    {
        eqation.insert(found+1, a);
        eqation.erase(found,1);
       
    }
    return eqation;
}

/*for(unsigned int N=0;N<eqation.size();++N)
if(eqation[N]=='x'){*/