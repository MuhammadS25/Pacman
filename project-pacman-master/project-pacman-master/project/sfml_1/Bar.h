#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

#include<fstream>
#include<sstream>
#include<string>

class Bar
{
private:
	enum BarState{IDLE=0,HOVERED,PRESSED};
	short Bar_state;

	
	sf::RectangleShape MovingBar;
	sf::CircleShape button;
	sf::RectangleShape icon;
	sf::Texture iconTexture;

	sf::Color idleColor;
	sf::Color HoveredColor;
	sf::Color PressedColor;

	sf::Color Bar_Color;
	sf::Color Moving_bar_color;

public:
	sf::RectangleShape bar;

public:
	//Constructor / Destructor
		Bar(float x_pos,float y_pos,float width,float height,float &buttonPos_x,sf::Texture iconTexture, float gridSizef,
			sf::Color idleColor,sf::Color HoveredColor,sf::Color pressedColor,
			sf::Color MovingBarColor,sf::Color backGroundColor);
		~Bar();

	//Getters
		const float getlevle();

	//Update Functions
		void movable();
		void updateMovingBar(sf::Vector2f mousPos);
		void update(sf::Vector2f mousPos);

	//Render Functions
		void render(sf::RenderTarget *target);
};

