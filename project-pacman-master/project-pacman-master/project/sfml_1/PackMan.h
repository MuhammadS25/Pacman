#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

#include<fstream>
#include<sstream>
#include<string>
#include"Animation.h"
class PackMan 
{
private:
	//Variables
	enum PlayerState { LEFT_STATE = 0, RIGHT_STATE, UP_STATE, DOWN_STATE };
	unsigned short player_state;

	float movementSpeed = 150.f;

	float x_pos;
	float y_pos;

	 float gridSizef;
	 sf::Texture PackManTexture;
	 Animation pacmanMoveAnimation;

public:
	 sf::Vector2f velocity;
	 sf::Sprite packman;
	 sf::FloatRect nextPos;

public:
	//constructor / Destructor
	PackMan(float gridSizef, unsigned int& level);
	~PackMan();
	
	//Getters
		void returnPackmanPos();

	//initialisazion functions
		void initPacman(unsigned int& level);

	//Update functions
		void updateAnimation(const float &dt);
		void updateMovement(const float &dt);
		void update(const float& dt);

	//Render functions
		void render(sf::RenderTarget* target);
};

