#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class button
{
private:
	RectangleShape shape;
	Font font;
	Text text;
public:
	bool isPressed;
	button(String s = "", Vector2f position = Vector2f(0.f, 0.f));
	void buttonSetText(String s);
	void buttonSetFont();
	void setPositions(Vector2f position);
	void drawButton(RenderWindow& window);
	void buttonSize(Vector2f position);
	void buttonColor(Color c);
	void buttonTextColor(Color c);
	bool contains(Vector2f position); //obs³uga myszki
	~button();
};