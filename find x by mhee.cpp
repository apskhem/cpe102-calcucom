#include<iostream>
#include<cmath>
#include<string>
#include<windows.h>

using namespace std;

double x_one(double,double);//ax+b
double xp(double,double,double); //-b+sqrt(b^2-4ac)/2a
double xn(double,double,double); //-b-sqrt(b^2-4ac)/2a
double SDforx3(double,double,double,double);//ax^3+bx^2+cx+d
double SDforx4(double,double,double,double,double);//ax^4+bx^3+cx^2+dx+e
double SDforx5(double,double,double,double,double,double);//ax^5+bx^4+cx^3+dx^2+ex+f

int main(){
	
	cout<<"[1]ax+b"<<endl;
	cout<<"[2]ax^2+bx+c"<<endl;
	cout<<"[3]ax^3+bx^2+cx+d"<<endl;
	cout<<"[4]ax^4+bx^3+cx^2+dx+e"<<endl;
	cout<<"[5]ax^5+bx^4+cx^3+dx^2+ex+f"<<endl;
	
	int oneToFive;
	cout<<"Enter your selection : ";
	cin>>oneToFive;
	
	if(oneToFive==1){
		double a1,b1;
		double x_1;
		cout<<"Enter a b : ";
		cin>>a1>>b1;
		x_1=x_one(a1,b1);
		
		cout<<"x = "<<x_1<<endl;
	}
	
	else if(oneToFive==2){
		double a2,b2,c2;
		double x21,x22;
	
		cout<<"Enter a b c : ";
		cin>>a2>>b2>>c2;
	
		x21=xp(a2,b2,c2);
		x22=xn(a2,b2,c2);
	
		cout<<" x = "<<x21<<","<<x22<<endl;
	}
	else if(oneToFive==3){
		double a3,b3,c3,d3;
		cout<<"Enter a b c d: ";
		cin>>a3>>b3>>c3>>d3;
		
		SDforx3(a3,b3,c3,d3);
		
	}
	
	else if(oneToFive==4){
		
	}
	
	else if(oneToFive==5){
		
	}
	
	
	
	system("pause");
	system("cls");
	
	cout<<" _______   ___     ___        ____         ___     ___    ___   ___     "<<endl;
	cout<<"[__   __] [   ]   [   ]      [    ]       [   ]   [   ]  [   ] [   ]    "<<endl;
	cout<<"   [ ]    [   ]___[   ]     [  []  ]      [    ]  [   ]  [   ][   ]     "<<endl;
	cout<<"   [ ]    [           ]    [  [__]  ]     [     ] [   ]  [      ]      "<<endl;
	cout<<"   [ ]    [    ___    ]   [  ______  ]    [   ][ ][   ]  [      ]      "<<endl;
	cout<<"   [ ]    [   ]   [   ]  [  ]      [  ]   [   ] [     ]  [   ][   ]     "<<endl;
	cout<<"   [_]    [___]   [___] [__]        [__]  [___]  [____]  [___] [___]    "<<endl;
	
	
}

double x_one(double A1,double B1){
	double ans;
	ans=(-1*B1)/A1;
}
double xp(double A,double B,double C){
	double ans1;
	double t1 = sqrt(pow(B,2)-(4*A*C));
	ans1=((-1*B)+t1)/(2*A);
	
	return ans1;
}

double xn(double D,double E,double F){
	double ans2;
	double t1 = sqrt(pow(E,2)-(4*D*F));
	ans2=((-1*E)-t1)/(2*D);
	
	return ans2;
}

double SDforx3(double A3,double B3,double C3,double D3){
	
	double sum3=1;
	double count1=0;
	double count2=0;
	
	for(double i=0;i<1000;i+=1){
		
		double t31=A3;
		double t32=A3*i;
		double t33=t32+B3;
		double t34=t33*i;
		double t35=t34+C3;
		double t36=t35*i;
		double t37=t36+D3;
		
		sum3=t37;
		
	    if(sum3==0){
			break;
		}
		count1+=1;
	}
	
	for(double i=0;i>-1000;i-=1){
		
		double t31=A3;
		double t32=A3*i;
		double t33=t32+B3;
		double t34=t33*i;
		double t35=t34+C3;
		double t36=t35*i;
		double t37=t36+D3;
		
		sum3=t37;
	
		if(sum3==0){
			break;
		}
		count2-=1;	
		}
	
	if(count1==999){
		cout<<"x :"<<count2*(-1)<<",";
		
	}
	else if(count2==-999){
		if(count1!=999){
		 cout<<"x :"<<count1*(-1)<<",";
		 
		}
		cout<<"--------------------";
		cout<<"    CANNOT FIND     ";
		cout<<"--------------------";
	}
	
	
	
	if(count1==998){
		double num1=A3;
	    double num2=B3+A3*count2;
	    double num3=num2*count2+C3;
	    double xot1=xp(num1,num2,num3);
	    double xot2=xn(num1,num2,num3);
	    cout<<"count2 ="<<count2<<endl;
	    
	    cout<<num1<<" "<<num2<<" "<<num3<<endl<<endl;
	    
	    cout<<xot1<<","<<xot2<<endl;
	}
	else {
		double num1=A3;
	    double num2=B3+A3*count1;
	    double num3=num2*count1+C3;
	    double xot1=xp(num1,num2,num3);
	    double xot2=xn(num1,num2,num3);
	    cout<<"count1 ="<<count1<<endl;
	    
	    cout<<num1<<" "<<num2<<" "<<num3<<endl<<endl;
	    
	    cout<<xot1<<","<<xot2<<endl;
	}
	
	
	
	
}

