#pragma once
#include "button.h"
#include "Calculations.h"
class CalculatorWindow {
private:
	RenderWindow window;
	button screen;
	button* windowButtons[30];
	string screenInput;
	Text screenOutput;
	Text lastScreenOutput;
	Font font;
	char toa[21];	//table of allowed characters in ASCII code
	Calculations equation;
public:
	CalculatorWindow();
	void calculatorLoop();
	void initScreen();
	void initWindowButtons();
	void windowButtonsHover();
	void windowButtonsClicked();
	void equalButtonClicked();
};