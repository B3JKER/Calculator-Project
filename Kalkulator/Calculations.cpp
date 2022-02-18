#include "Calculations.h"
#include <stack>
#include <cmath>
#include <sstream> //do wyniku na string
#include <iomanip> //

Calculations::Calculations(string str)
{
	expression = str;
	result = 0;
	precision = 2;

	this->oper[0] = '/';
	this->oper[1] = '*';
	this->oper[2] = '^';
	this->oper[3] = '+';
	this->oper[4] = '.';
	this->oper[5] = ',';
	int x = 48;
	for (int i = 0; i < 10; i++)
	{
		this->digits[i] = x;
		x++;
	}
}

void Calculations::setExpression(string equation)
{
	this->expression = equation;
}

bool Calculations::checkExpression()
{
	//1. Sprawdzanie czy nawiasy siê zgadzaj¹ (liczba otwieraj¹cych i zamykaj¹cych)
	if (count(expression.begin(), expression.end(), '(') != count(expression.begin(), expression.end(), ')')) { return false; }
	//2. Sprawdzanie czy na pocz¹tku lub koñcu jest operator
	if (find(begin(oper), end(oper), expression[0]) != end(oper)) { return false; }
	//3. Sprawdzanie czy pierwszy znak jest cyfr¹, minusem lub otwieraj¹cym nawiasem
	if (expression[0] == '-' || expression[0] == '(' || find(begin(digits), end(digits), expression[0]) != end(digits)) { }
	else { return false; }
	//4. Sprawdzanie czy ostatni znak jest cyfr¹ lub zamykaj¹cym nawiasem lub '!'
	if (expression[expression.size()-1] == ')' || find(begin(digits), end(digits), expression[expression.size() - 1]) != end(digits) || expression[expression.size() - 1] == '!') { }
	else { return false; }
	//5.  Sprawdzanie nawiasów
	int checkb = 0; //zmienna do sprawdzenia czy nawiasy sie zgadzaja
	int lkropek = 0; //zmienna do sprawdzenia czy kropki w liczbie sie nie powtarzaja
	for (int i = 0; i < expression.size(); i++)
	{
		if (expression[i] == '('){ checkb++; }
		else if (expression[i] == ')' && checkb > 0) { checkb--;  }
		else if (expression[i] == ')' && checkb <= 0) { return false; }

		if (i == 0 || i == expression.size() - 1) //5.1 Sprawdzanie czy po '(' lub przed ')' wystêpuje operator bior¹c pod uwagê tylko poczatek i koniec wyra¿enia
		{
			if (expression[i] == '(' && (find(begin(oper), end(oper), expression[i + 1]) != end(oper) ||  expression[i + 1] == '.' || expression[i + 1] == '!')) { return false; }
			if (expression[i] == ')' && (find(begin(oper), end(oper), expression[i - 1]) != end(oper) || expression[i - 1] == '-'  || expression[i - 1] == '.')) { return false; }
		}

		if (i > 0 && i < expression.size()) //zabezpieczenie przed szukaniem poza zakresem tablicy
		{
			//5.1 Sprawdzanie czy po '(' lub przed ')' wystêpuje operator
			if (expression[i] == '(' && (find(begin(oper), end(oper), expression[i + 1]) != end(oper) || expression[i + 1] == '.' || expression[i + 1] == '!')) { return false; }
			if (expression[i] == ')' && (find(begin(oper), end(oper), expression[i - 1]) != end(oper) || expression[i - 1] == '-' || expression[i - 1] == '.')) { return false; }

			//5.2 Sprawdzanie czy przed '(' lub po ')' wystêpuje operator
			if (expression[i] == '(' && (find(begin(digits), end(digits), expression[i - 1]) != end(digits) || expression[i - 1] == '.' || expression[i - 1] == '!')){ return false; }
			if (expression[i] == ')' && (find(begin(digits), end(digits), expression[i + 1]) != end(digits) || expression[i + 1] == '.')){ return false; }


			//6. Sprawdzanie czy minusy wystêpuj¹ obok siebie i czy silnia za minusem
			if (expression[i] == '-' && (expression[i - 1] == '-' || expression[i + 1] == '-' || expression[i + 1] == '!'))
			{
				return false;
			}

			//7. Sprawdzenie czy operatory wystepuja kilkukrotnie
			if (find(begin(oper), end(oper), expression[i]) != end(oper) && 
			((find(begin(oper), end(oper), expression[i - 1]) != end(oper) || expression[i - 1] == '-' || find(begin(oper), end(oper), expression[i + 1]) != end(oper) || expression[i + 1] == '!')))
			{
				return false;
			}

			//8. Sprawdzanie czy '!' wystêpuj¹ obok siebie i czy minus przed silni¹
			if ((expression[i] == '!') && (expression[i - 1] == '!' || expression[i - 1] == '-' || expression[i + 1] == '!' ))
			{
				return false;
			}
		}
		
		//9. Sprawdzenie kropek
		
		if (expression[i] == '.' && find(begin(digits), end(digits), expression[i - 1]) != end(digits))
		{
			lkropek++;
			
		}
		else if(find(begin(digits), end(digits), expression[i]) != end(digits) && i < expression.size() - 1) {}
		else
		{
			if (lkropek > 1)
			{
				return false;
			}
			lkropek = 0;
		}
	}


	return true;
}


void Calculations::calculateRPNExpression()
{
	stack <double> stos;
	string strnumber = "";
	double dbnumber = 0;
	double x, y, z;
	for (int i = 0; i < expression.size(); i++)
	{
		if (find(begin(digits), end(digits), expression[i]) != end(digits) || expression[i] == ',' || expression[i] == '.')
		{
			do
			{
				strnumber.push_back(expression[i]);
				i++;
			} while (expression[i] != ' ');
			i--;

			dbnumber = stod(strnumber);
			stos.push(dbnumber);
			dbnumber = 0;
			strnumber = "";
		}
		else if (find(begin(oper), end(oper), expression[i]) != end(oper) || expression[i] == '-')
		{

			x = stos.top(); stos.pop();
			y = stos.top(); stos.pop();
			switch (expression[i])
			{
			case '+':
				dbnumber = y + x;
				break;
			case '-':
				dbnumber = y - x;
				break;
			case '*':
				dbnumber = y * x;
				break;
			case '/':
				dbnumber = y / x;
				break;
			case '^':
				dbnumber = pow(y, x);
				break;
			}
			stos.push(dbnumber);
		}
		else if (expression[i] == 'n')
		{
			z = stos.top(); stos.pop();
			z = z * (-1);
			stos.push(z);
		}
		else if (expression[i] == '!')
		{
			z = stos.top(); stos.pop();
			double ret = 1;
			for (int i = 1; i <= z; i++)
			{
				ret *= i;
			}
			stos.push(ret);
		}
	}
	result = stos.top();
	
}

string Calculations::strResult()
{
	// Set Fixed -Point Notation
	streamNumber << fixed; //scientific do zapisu do jakiejs potegi, fixed do zwyklego
	// Set precision to 2 digits
	streamNumber << setprecision(precision);
	//Add double to stream
	streamNumber << result;
	// Get string from output string stream
	expression = streamNumber.str();
	//expression = to_string(dbnumber);
	streamNumber.str("");
	return expression;
}

double Calculations::doubleResult()
{
	return result;
}

int Calculations::getPrecision()
{
	return precision;
}

void Calculations::setPrecision(int prec)
{
	if (prec >= 0)
	{
		precision = prec;
	}
}

void Calculations::convertToRPN()
{
	char p0 = '(';
	char p1[3] = { '+','-',')' };
	char p2[3] = { '*','/','%' };
	char p3[1] = { '^' };
	char p4[1] = { '!' };

	stack <char> stos;
	string wyjscie = "";
	for (int i = 0; i < expression.size(); i++)
	{

		if (find(begin(digits), end(digits), expression[i]) != end(digits) || expression[i] == ',' || expression[i] == '.')
		{
			wyjscie += expression[i];
			continue;
		}
		if (wyjscie != "" && expression[i] != '(' && expression[i] != ')')
		{
			if (wyjscie.back() != ' ')
			{
				wyjscie += " ";
			}
		}
		if (expression[i] == '(')
		{
			stos.push(expression[i]);
		}
		else if (expression[i] == ')')
		{
			while (1)
			{
				if (stos.top() == '(')
				{
					stos.pop();
					break;
				}
				wyjscie += stos.top();
				stos.pop();
			}
		}
		//negacja gdy minus na pocz¹tku
		else if (i == 0 && expression[i] == '-')
		{
			stos.push('n');
		}
		//
		else if (find(begin(oper), end(oper), expression[i]) != end(oper) || expression[i] == '-' || expression[i] == '!')
		{
			//negacja
			if (expression[i] == '-' && find(begin(oper), end(oper), expression[i - 1]) != end(oper))
			{
				stos.push('n');
			}
			else if (expression[i] == '-' && expression[i - 1] == '(')
			{
				stos.push('n');
			}
			//
			else if (stos.empty())
			{
				stos.push(expression[i]);
			}
			else if (find(begin(p1), end(p1), expression[i]) != end(p1))
			{
				if (stos.top() == p0)
				{
					stos.push(expression[i]);
				}
				else
				{
					while (1)
					{
						wyjscie += stos.top();
						stos.pop();
						if (stos.empty() || stos.top() == p0)
						{ 
							stos.push(expression[i]);
							break; 
						}
					}
				}
			}
			else if (find(begin(p2), end(p2), expression[i]) != end(p2))
			{
				if (stos.top() == p0 || find(begin(p1), end(p1), stos.top()) != end(p1))
				{
					stos.push(expression[i]);
				}
				else
				{
					while (1)
					{
						wyjscie += stos.top();
						stos.pop();
						if (stos.empty() || stos.top() == p0 || find(begin(p1), end(p1), stos.top()) != end(p1))
						{
							stos.push(expression[i]);
							break;
						}
					}
				}
			}
			else if (find(begin(p3), end(p3), expression[i]) != end(p3))
			{
				if (stos.top() == p0 || find(begin(p1), end(p1), stos.top()) != end(p1) || find(begin(p2), end(p2), stos.top()) != end(p2))
				{
					stos.push(expression[i]);
				}
				else
				{
					while (1)
					{
						wyjscie += stos.top();
						stos.pop();
						if (stos.empty() || stos.top() == p0 || find(begin(p1), end(p1), stos.top()) != end(p1) || find(begin(p2), end(p2), stos.top()) != end(p2))
						{
							stos.push(expression[i]);
							break;
						}
					}
				}
			}
			else if (find(begin(p4), end(p4), expression[i]) != end(p4))
			{
				if (find(begin(p4), end(p4), stos.top()) != end(p4))
				{
					while (1)
					{
						wyjscie += stos.top();
						stos.pop();
						if (stos.empty() || stos.top() != p4[0])
						{
							stos.push(expression[i]);
							break;
						}
					}
				}
				else
				{
					stos.push(expression[i]);
				}
			}
		}
	}
	while (!stos.empty())
	{
		wyjscie += stos.top();
		stos.pop();
	}

	//Dodanie pozosta³ych " "
	for (int i = 0; i < wyjscie.size(); i++)
	{
		if (wyjscie[i] == ' ')
		{
			continue;
		}
		else if (find(begin(digits), end(digits), wyjscie[i]) != end(digits) || wyjscie[i] == '.')
		{
			if (find(begin(digits), end(digits), wyjscie[i + 1]) != end(digits) || wyjscie[i + 1] == '.' || wyjscie[i + 1] == ' ')
			{
			}
			else
			{
				i++;
				wyjscie.insert(i, " ");
				i--;
			}
		}
		else if(wyjscie[i + 1] != ' ')
		{
			i++;
			wyjscie.insert(i, " ");
			i--;
		}

	}

	this->expression = wyjscie;
}
