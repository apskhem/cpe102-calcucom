#include<iostream>
#include<cmath>
#include<string>

using namespace std;

double xp(double,double,double); //-b+sqrt
double xn(double,double,double); //-b-sqrt

int main(){
	
	double a,b,c;
	double x1,x2;
	
	cout<<"Enter a b c : ";
	cin>>a>>b>>c;
	
	x1=xp(a,b,c);
	x2=xn(a,b,c);
	
	cout<<" x = "<<x1<<","<<x2<<endl;
	
}

double xp(double A,double B,double C){
	double ans1;
	double t1 = sqrt(pow(B,2)-(4*A*C));
	ans1=((-1*B)+t1)/2;
	
	return ans1;
}

double xn(double D,double E,double F){
	double ans2;
	double t1 = sqrt(pow(E,2)-(4*D*F));
	ans2=((-1*E)-t1)/2;
	
	return ans2;
}

