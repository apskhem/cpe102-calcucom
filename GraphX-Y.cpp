#include <iostream>
#include <cmath>

using namespace std;

double round(double number);
void CreateGraph(int *values, int size);

string axis = "- ", point = "o ", space = "  ";

int main()
{

  int size = 20;
  double step = (1.0 / 5);

  int *values = new int[size + size + 1];
  double Y;

  for (int i = 0; i < size + size + 1; ++i)
  {
    double x = (i - size);
    x = x * step; //Expanding

    Y = sqrt(4-pow(x,2)) ; // EQUATION

    Y = Y / step; //Expanding Size
    values[i] = round(Y);
  }

  CreateGraph(values, size); // cout << "TABLE GRAPH:"
  delete[] values;
}

void CreateGraph(int *values, int size) //Function TABLE Graph :
{

  for (int i = 0; i < size + size + 1; ++i)
  {
    cout << endl;
  }
  for (int i = 0; i < size; ++i)
  {

    for (int b = 0; b < size; ++b)
    {
      if (size - i == values[b])
        cout << point;
      else
        cout << space;
    }

    if (size - i == values[size])
      cout << point;
    else
      cout << axis;

    for (int b = 0; b < size; ++b)
    {
      if (size - i == values[b + size + 1])
        cout << point;
      else
        cout << space;
    }
    cout << endl;
  }

  for (int i = 0; i < size + size + 1; ++i)
  {
    if (0 == values[i])
      cout << point;
    else
      cout << axis;
  }
  cout << endl;

  for (int i = 0; i < size; ++i)
  {
    for (int b = 0; b < size; ++b)
    {
      if (0 - i - 1 == values[b])
        cout << point;
      else
        cout << space;
    }
    if (0 - i - 1 == values[size])
      cout << point;
    else
      cout << axis;

    for (int b = 0; b < size; ++b)
    {
      if (0 - i - 1 == values[b + size + 1])
        cout << point;
      else
        cout << space;
    }
    cout << endl;
  }
}

double round(double number)
{
  return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}
