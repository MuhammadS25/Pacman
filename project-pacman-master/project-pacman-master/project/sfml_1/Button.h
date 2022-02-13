#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include"Animation.h"
#include<fstream>
#include<sstream>
#include<string>

class Button
{
private:
	//Variables
	enum Button_State { BTN_idel = 0, BTN_hovered, BTN_Pressed };
	unsigned short ButtonState;

	float gridSizef;
	unsigned short id ;

	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;

	sf::Color idelColor;
	sf::Color hoverColor;
	sf::Color pressColor;

	sf::Color bg_idelColor;
	sf::Color bg_hoverColor;
	sf::Color bg_pressColor;

	sf::Color outline_idelColor;
	sf::Color outline_hoverColor;
	sf::Color outline_pressColor;

	sf::Sound sound;
	sf::SoundBuffer hoverdSound;
	sf::SoundBuffer pressedSound;

	Animation animation;
	sf::Sprite sprite;
	sf::Texture pacpic;

	
public:
	//Constructor/Destructor
		Button(float& soundLevel,float x_pos, float y_pos, float width, float height, std::string text, sf::Font font, float gridSizef
			, sf::Color idelColor, sf::Color hoverColor, sf::Color pressColor, sf::Color bg_idelColor, sf::Color bg_hoverColor, sf::Color bg_pressColor,
			sf::Color outline_idelColor, sf::Color outline_hoverColor, sf::Color outline_pressColor, unsigned short id=0);

	//Function

	//Getters
		int getenumstate();
		bool isPressed();
		std::string getText();
		const unsigned short& getid() const;
	

	//setters
		void setText(std::string text);
		void setid(const unsigned short id);

	//initialisation functions
		void initAnimation(float gridSizef);

	//Update fuctions
		void updateAnimation(const float &dt);
		void update(sf::Vector2f &mousePos, sf::RenderWindow& window,const float &dt);

	//Render Functions
		void renderAnimation(sf::RenderTarget*target);
		void setOutline(float gridSizef);
		void render(sf::RenderTarget* target);
};

