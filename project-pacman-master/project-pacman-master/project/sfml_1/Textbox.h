#pragma once

#include<SFML\Graphics.hpp>
#include <iostream>
#include<sstream>
#include<fstream>
#include"Button.h"
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

using namespace sf;
using namespace std;

class Textbox
{
private:
	float gridSizef = 10.67f;

	enum TextboxState{IDLE=0,HOVERED,PRESSED};
	unsigned short textbox_state=0;

	Text textbox;
	sf::Font font;
	ostringstream of_text;
	RectangleShape Rect;
	bool isSlected = false, hasLimit = false, showCurser = false;
	unsigned int limit;
	Clock clock;

	sf::Color idleColor;
	sf::Color HoveredColor;
	sf::Color PressedColor;

	bool pressed = false;
	bool text = false;

	float keyTimer = 0.f;
	float maxTimer = 1.f;

	int scoore;
	int BestScoore;

	sf::RectangleShape bg;
	sf::Texture bg_text;

	sf::Cursor Text_Cursor;

public:
	~Textbox();
	Textbox( bool sel,  Vector2f pos, bool TrueorFalse, int lim,int&scoore,float &gridSizef);

	void setSelected(bool sel);
	string getText();
	void drawTo(sf::RenderTarget*target);
	void typedOn(Event event);
	void selected(bool sel)
	{
		sel = isSlected;

		if (sel)
		{
			if (clock.getElapsedTime() >= milliseconds(500))
			{
				clock.restart();
				showCurser = !showCurser;
				if (showCurser)
					textbox.setString(of_text.str() + "|");
				else
					textbox.setString(of_text.str());
			}

		}
	}
	bool getSelected()
	{
		return isSlected;
	}

	void updateTextbox(sf::Vector2f& mousePos,sf::RenderWindow&window);
	void update(sf::RenderWindow& window, sf::Event event, const float& dt,Button&button);
private:
	void updateTimer(const float& dt);
	const bool getClickable();

	const bool ispressed()const;
	//To make the text readable
	void inputLogic(int charTyped)
	{
		if (charTyped != DELETE_KEY && charTyped != ESCAPE_KEY && charTyped != ENTER_KEY)
			of_text << static_cast<char> (charTyped);
		else if (charTyped == DELETE_KEY)
		{
			if (of_text.str().length() > 0)
				deleteLastChar();
		}

		textbox.setString(of_text.str());

	}

	//To Delete The last char
	void deleteLastChar()
	{
		string t = of_text.str();
		string newT = "";
		for (unsigned int i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		of_text.str("");
		of_text << newT;

		textbox.setString(of_text.str() + "|");
	}
};

