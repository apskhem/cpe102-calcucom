#ifndef MAX_MIN_H
#define MAX_MIN_H

double x_one(double, double);						   //ax+b
double xp(double, double, double);					   //-b+sqrt(b^2-4ac)/2a
double xn(double, double, double);					   //-b-sqrt(b^2-4ac)/2a
array<double> SDforx3(double, double, double, double); //ax^3+bx^2+cx+d
array<double> critical_x(string);
string findRelativeMinMax(array<string> terms, const char &var);

string findRelativeMinMax(array<string> terms, const char &var) {

    array<string> diffedTerms = readExpr(diffExpr(terms, var));

    array<factor> factors;
    double a = 0, b = 0, c = 0;
    
    for (unsigned short i = 0; i < diffedTerms.length-1; i++) {
        TermComponents tc(diffedTerms[i], var);

        // checks tc
        if (tc.factors.length != 1 && tc.factors.length != 0) error("only one factor per term in this mode is allowed");

        if (tc.factors[i].n != "1" || tc.factors[i].n != "2") error("power of n in this mode is maximum at 3", 3);

        if (!tc.factors.length) c = tc.a;
        else if (tc.factors[i].n == "1") b = tc.a;
        else if (tc.factors[i].n == "2") a = tc.a;

        factors.push(tc.factors[i]);
    }

    if (b*b-4*a*c < 0) error("imagine number is not allowed in this mode", 2);

    double c1 = (-b - sqrt(b*b-4*a*c)) / (2*a);
    double c2 = (-b + sqrt(b*b-4*a*c)) / (2*a);

    double p1 = evalExpr(terms, c1, var);
    double p2 = evalExpr(terms, c2, var);

    if (p1 > p2) { // swap
        double temp_c = c1;
        double temp_p = p1;

        c1 = c2;
        c2 = temp_c;

        p1 = p2;
        p2 = temp_p;
    }

    std::cout << "relative min is [" <<  p1 << ", " << c2 << "]\n";
    std::cout << "relative max is [" <<  p2 << ", " << c1 << "]\n";
}

array<double> critical_x(string equation)
{
	int option;
	array<string> term = readExpr(equation);
	array<double> x_value;

	for (unsigned i = 0; i < equation.length; i++)
	{
		if (equation[i] == '^')
			option = equation[i + 1];
	}

	if (option == 1)
	{
		double a1, b1;

		for (unsigned i = 0; i < option + 1; i++)
		{
			string power = term[i].slice(term[i].length - 1, term[i].length);
			if (power == "x")
				a1 = parseNum(term[i]);
			else
				b1 = parseNum(term[i]);
		}
		x_value.push(x_one(a1, b1));
	}

	else if (option == 2)
	{
		double a2, b2, c2;
		double x21, x22;

		for (unsigned i = 0; i < option + 1; i++)
		{
			string power = term[i].slice(term[i].length - 2, term[i].length);
			if (power == "^2")
				a2 = parseNum(term[i]);
			else if (power.includes("x"))
				b2 = parseNum(term[i]);
			else
				c2 = parseNum(term[i]);
		}
		x_value.push(xp(a2, b2, c2));
		x_value.push(xn(a2, b2, c2));
	}

	else if (option == 3)
	{
		double a3, b3, c3, d3;
		for (unsigned i = 0; i < option + 1; i++)
		{
			string power = term[i].slice(term[i].length - 2, term[i].length);

			if (power == "^3")
				a3 = parseNum(term[i]);
			else if (power == "^2")
				b3 = parseNum(term[i]);
			else if (power.includes("x"))
				c3 = parseNum(term[i]);
			else
				d3 = parseNum(term[i]);
		}

		x_value = SDforx3(a3, b3, c3, d3);
	}
}

double x_one(double A1, double B1)
{
	double ans;
	ans = (-1 * B1) / A1;
}

double xp(double A, double B, double C)
{
	double ans1;
	double t1 = sqrt(pow(B, 2) - (4 * A * C));
	ans1 = ((-1 * B) + t1) / (2 * A);

	return ans1;
}

double xn(double D, double E, double F)
{
	double ans2;
	double t1 = sqrt(pow(E, 2) - (4 * D * F));
	ans2 = ((-1 * E) - t1) / (2 * D);

	return ans2;
}

array<double> SDforx3(double A3, double B3, double C3, double D3)
{
	array<double> ans;
	double sum3 = 1;
	double count1 = 0;
	double count2 = 0;

	for (double i = 0; i < 1000; i += 1)
	{
		double t31 = A3;
		double t32 = A3 * i;
		double t33 = t32 + B3;
		double t34 = t33 * i;
		double t35 = t34 + C3;
		double t36 = t35 * i;
		double t37 = t36 + D3;

		sum3 = t37;

		if (sum3 == 0)
			break;
		count1 += 1;
	}

	for (double i = 0; i > -1000; i -= 1)
	{
		double t31 = A3;
		double t32 = A3 * i;
		double t33 = t32 + B3;
		double t34 = t33 * i;
		double t35 = t34 + C3;
		double t36 = t35 * i;
		double t37 = t36 + D3;

		sum3 = t37;

		if (sum3 == 0)
			break;
		count2 -= 1;
	}

	
	if (count1 == 999)
	{
		double num1 = A3;
		double num2 = B3 + A3 * count1;
		double num3 = num2 * count1 + C3;
		double xot1 = xp(num1, num2, num3);
		double xot2 = xn(num1, num2, num3);

		ans.push(count1*(-1));
		ans.push(xot1);
		ans.push(xot2);
	}

	else
	{
		double num1 = A3;
		double num2 = B3 + A3 * count2;
		double num3 = num2 * count2 + C3;

		double xot1 = xp(num1, num2, num3);
		double xot2 = xn(num1, num2, num3);

		ans.push(count2*(-1));
		ans.push(xot1);
		ans.push(xot2);
	}
	
	if (count1 == 999 && count2 == -999)
		error("CANNOT FIND");

	return ans;
}

#endif
