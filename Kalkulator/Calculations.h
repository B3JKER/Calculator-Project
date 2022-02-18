#pragma once
#include <string>
#include <cmath>
#include <vector>
#include <sstream> //do wyniku na string
#include <iomanip> //
using namespace std;

class Calculations
{
private:
	string expression;
	double result;
	char oper[6];
	int digits[10];
	ostringstream streamNumber; //do wyswietlenia wyniku w stringu
	int precision;
public:
	Calculations(string str = "");
	void setExpression(string equation);
	bool checkExpression();
	void convertToRPN();
	void calculateRPNExpression();
	string strResult();
	double doubleResult();
	int getPrecision();
	void setPrecision(int prec);
};