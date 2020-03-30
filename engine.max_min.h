#ifndef MAX_MIN_H
#define MAX_MIN_H

double x_one(double, double);						   //ax+b
double xp(double, double, double);					   //-b+sqrt(b^2-4ac)/2a
double xn(double, double, double);					   //-b-sqrt(b^2-4ac)/2a
array<double> SDforx3(double, double, double, double); //ax^3+bx^2+cx+d
array<double> critical_x(string);

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
		count2 *= -1;
	

	else if (count2 == -999)
		count1 *= -1;
	
	else if (count1 == 999 && count2 == -999)
	{
		//cout << "    CANNOT FIND     ";

	}

	if (count1 == 999)
	{
		double num1 = A3;
		double num2 = B3 + A3 * count1;
		double num3 = num2 * count1 + C3;
		double xot1 = xp(num1, num2, num3);
		double xot2 = xn(num1, num2, num3);

		ans.push(count1);
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

		ans.push(count2);
		ans.push(xot1);
		ans.push(xot2);
	}
}


#endif