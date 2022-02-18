#include "CalculatorWindow.h"
#include "Calculations.h"
#include <SFML/Graphics.hpp>


CalculatorWindow::CalculatorWindow():window(VideoMode(400, 560), "Kalkulator", Style::Close)
{
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);
    //initNumbers();
    initWindowButtons();
    initScreen();
    screenInput = "";
    if (!font.loadFromFile("font/OpenSans-Regular.ttf"))
    {
        // error...
    }
    screenOutput.setPosition(Vector2f(2, 25));
    screenOutput.setFont(font);
    screenOutput.setCharacterSize(40);
    screenOutput.setFillColor(Color::Black);
    
    lastScreenOutput.setPosition(Vector2f(2, 2));
    lastScreenOutput.setFont(font);
    lastScreenOutput.setCharacterSize(14);
    lastScreenOutput.setFillColor(Color::Black);
    //Dodawanie dozwolonych znaków z klawiatury do tablicy
    toa[0] = '0';
    toa[1] = '1';
    toa[2] = '2';
    toa[3] = '3';
    toa[4] = '4';
    toa[5] = '5';
    toa[6] = '6';
    toa[7] = '7';
    toa[8] = '8';
    toa[9] = '9';
    toa[10] = '+';
    toa[11] = '-';
    toa[12] = '*';
    toa[13] = '/';
    toa[14] = '.';
    toa[15] = '^';
    toa[16] = ')';
    toa[17] = '(';
    toa[18] = 'e';
    toa[19] = '!';
    equation.setExpression("");
}

void CalculatorWindow::calculatorLoop()
{
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            //Obs³uga interfejsu
            windowButtonsHover();
            equalButtonClicked();
            windowButtonsClicked();

            switch (event.type)
            {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                        // Using Ctrl + V to paste a string into SFML
                    if (event.key.control && event.key.code == Keyboard::V)
                    {
                        screenInput = Clipboard::getString();
                        screenOutput.setString(screenInput);
                    }
                            
                        // Using Ctrl + C to copy a string out of SFML
                    if (event.key.control && event.key.code == sf::Keyboard::C)
                    {
                        Clipboard::setString(screenInput);
                    }
                    break;

                case Event::TextEntered:
                    if (screenInput == "SYNTAX ERROR")
                    {
                        if (event.text.unicode == 8) //kasowanie ca³oœci
                        {
                            screenInput = "";
                            screenOutput.setString(screenInput);
                        }
                    }
                    else if (event.text.unicode == 8 && screenInput != "") //kasowanie backspace
                    {
                        screenInput.pop_back();
                        screenOutput.setString(screenInput);
                    }
                    else if (event.text.unicode == 8 && screenInput == "")
                    {
                        lastScreenOutput.setString(screenInput);
                    }
                    else if (event.text.unicode == '=') //jezeli "=" to oblicz i wyswietl      
                    {
                        equation.setExpression(screenInput);
                        lastScreenOutput.setString(screenInput);
                        if (equation.checkExpression())
                        {
                            equation.convertToRPN();
                            equation.calculateRPNExpression();
                            screenInput = equation.strResult();
                            screenOutput.setString(screenInput);
                        }
                        else
                        {
                            screenInput = "SYNTAX ERROR";
                            screenOutput.setString(screenInput);
                        }      
                    }
                    else if (find(begin(toa), end(toa), event.text.unicode) != end(toa))
                    {                               //inaczej sprawdz czy wcisniety przycisk jest prawidlowy
                        screenInput += event.text.unicode;
                        screenOutput.setString(screenInput);
                    }
                    if (screenInput.size() > 17)    //wyœwietlanie 17 ostatnich znaków wyra¿enia
                    {
                        screenOutput.setString(screenInput.substr(screenInput.size() - 17));
                    }
                    break;
            }
        }

        window.clear(Color::White);

        for (int i = 0; i < 30; i++)
        {
            windowButtons[i]->drawButton(window);
        }
     
        screen.drawButton(window);
        window.draw(screenOutput);
        window.draw(lastScreenOutput);

        window.display();

    }
}


void CalculatorWindow::initScreen()
{
    screen.buttonSize(Vector2f(400,80));
    screen.setPositions(Vector2f(0,0));
    screen.buttonColor(Color(200, 200, 200));
}

void CalculatorWindow::initWindowButtons()
{
    this->windowButtons[0] = new button("0", Vector2f(80, 480));
    this->windowButtons[1] = new button("1", Vector2f(0, 400));
    this->windowButtons[2] = new button("2", Vector2f(80, 400));
    this->windowButtons[3] = new button("3", Vector2f(160, 400));
    this->windowButtons[4] = new button("4", Vector2f(0, 320));
    this->windowButtons[5] = new button("5", Vector2f(80, 320));
    this->windowButtons[6] = new button("6", Vector2f(160, 320));
    this->windowButtons[7] = new button("7", Vector2f(0, 240));
    this->windowButtons[8] = new button("8", Vector2f(80, 240));
    this->windowButtons[9] = new button("9", Vector2f(160, 240));
    this->windowButtons[10] = new button("+", Vector2f(240, 400));
    this->windowButtons[11] = new button("-", Vector2f(240, 320));
    this->windowButtons[12] = new button("*", Vector2f(240, 240));
    this->windowButtons[13] = new button("/", Vector2f(240, 160));
    this->windowButtons[14] = new button(".", Vector2f(160, 480));
    this->windowButtons[15] = new button("^", Vector2f(160, 160));
    this->windowButtons[16] = new button(")", Vector2f(80, 80));
    this->windowButtons[17] = new button("(", Vector2f(0, 80));
    this->windowButtons[18] = new button("e", Vector2f(0, 480));
    this->windowButtons[19] = new button("!", Vector2f(160, 80));
    this->windowButtons[20] = new button("pi", Vector2f(320, 160));
    this->windowButtons[21] = new button("=", Vector2f(240, 480));
    this->windowButtons[22] = new button("D", Vector2f(80, 160));
    this->windowButtons[23] = new button("C", Vector2f(0, 160));
    this->windowButtons[24] = new button("<-", Vector2f(240, 80));
    this->windowButtons[25] = new button("->", Vector2f(320, 80));
    this->windowButtons[26] = new button("", Vector2f(320, 240));
    this->windowButtons[27] = new button("", Vector2f(320, 320));
    this->windowButtons[28] = new button("", Vector2f(320, 400));
    this->windowButtons[29] = new button("", Vector2f(320, 480));

}

void CalculatorWindow::windowButtonsHover()
{
    for (int i = 0; i < 26; i++)
    {
        if (windowButtons[i]->contains(Vector2f(sf::Mouse::getPosition(window))))
        {
            windowButtons[i]->buttonColor(Color(100, 100, 255));
        }
        else
        {
            windowButtons[i]->buttonColor(Color(10, 10, 255));
        }
    }
}
void CalculatorWindow::windowButtonsClicked()
{
    for (int i = 0; i < 26; i++)
    {
        if (windowButtons[i]->contains(Vector2f(sf::Mouse::getPosition(window))))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                windowButtons[i]->buttonColor(Color::Red);
                if (windowButtons[i]->isPressed == false)
                {
                    if (i == 21) {}
                    else if (i == 18)//jezeli e
                    {
                        screenInput += "2.718281";
                        screenOutput.setString(screenInput);
                    }
                    else if (i == 20)//jezeli pi
                    {
                        screenInput += "3.141592";
                        screenOutput.setString(screenInput);
                    }
                    else if (i == 22)//jezeli wcisniety D
                    {
                        if (screenInput == "SYNTAX ERROR")
                        {
                            screenInput = "";
                            screenOutput.setString(screenInput);
                        }
                        else if(screenInput != "")
                        {
                            screenInput.pop_back();
                            screenOutput.setString(screenInput);
                        }
                    }
                    else if (i == 23)//jezeli wcisniety C
                    {
                        if (screenInput == "")
                        {
                            lastScreenOutput.setString(screenInput);
                        }
                        screenInput = "";
                        screenOutput.setString(screenInput);
                    }
                    else if (i == 24)// jezeli wcisniety <-
                    {
                        equation.setPrecision(equation.getPrecision() - 1);
                        screenInput = equation.strResult();
                        screenOutput.setString(screenInput);
                    }
                    else if (i == 25)// jezeli wcisniety ->
                    {
                        equation.setPrecision(equation.getPrecision() + 1);
                        screenInput = equation.strResult();
                        screenOutput.setString(screenInput);
                    }
                    else
                    {
                        screenInput += toa[i];
                        screenOutput.setString(screenInput);    
                    } 
                    windowButtons[i]->isPressed = true;
                }

            }
            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                windowButtons[i]->isPressed = false;
            }
        }
    }
}

void CalculatorWindow::equalButtonClicked()
{
    if (windowButtons[21]->contains(Vector2f(Mouse::getPosition(window))))
    {
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (windowButtons[21]->isPressed == false)
            {
                windowButtons[21]->buttonColor(Color::Red);
                equation.setExpression(screenInput);
                lastScreenOutput.setString(screenInput);
                if (equation.checkExpression())
                {
                    equation.convertToRPN();
                    equation.calculateRPNExpression();
                    screenInput = equation.strResult();
                    screenOutput.setString(screenInput);
                }
                else
                {
                    screenInput = "SYNTAX ERROR";
                    screenOutput.setString(screenInput);
                }
                windowButtons[21]->isPressed = true;
            }
        }
        else if (!Mouse::isButtonPressed(Mouse::Left))
        {
            windowButtons[21]->isPressed = false;
        }
    }
}