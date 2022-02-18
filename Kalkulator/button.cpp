#include "button.h"

void button::buttonSetFont()
{
	if (!this->font.loadFromFile("font/OpenSans-Regular.ttf"))
	{
		// error...
	}
	this->text.setFont(font);
}

void button::setPositions(Vector2f position)
{
	this->shape.setPosition(position);
	this->text.setPosition(position.x+28, position.y+15);
}

void button::drawButton(RenderWindow& window)
{
	window.draw(this->shape);
	window.draw(this->text);
}

void button::buttonSize(Vector2f xy)
{
	this->shape.setSize(xy);
}

void button::buttonColor(Color c)
{
	this->shape.setFillColor(c);
}

void button::buttonTextColor(Color c)
{
	this->text.setFillColor(c);
}

bool button::contains(Vector2f xy)
{
	return shape.getGlobalBounds().contains(xy);
}


button::button(String string, Vector2f position)
{
	buttonSize(Vector2f(80.f, 80.f));//rozmiar przycisku
	buttonColor(Color(10,10,255));
	shape.setOutlineThickness(-1);
	//shape.setOutlineColor(Color::Black);
	buttonSetFont();
	buttonSetText(string);
	setPositions(position);
	isPressed = false;
}

void button::buttonSetText(String s)
{
	this->text.setCharacterSize(40);
	this->text.setString(s);
	this->text.setFillColor(Color::White);
}

button::~button()
{
}
