#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<vector>
#include<map>
#include"Animation.h"
class Ghost
{
private: 
	//Variables
	std::map<std::string,Animation> animations;

	sf::Texture idleTexture;
	sf::Texture runTexture;
	sf::Texture eattenTexture;

	

	//AI stuff
	enum ghoustdir { LEFT = 0, RIGHT, UP, DOWN };
	int ghost_dir = UP;
	
	float movementSpeed ;
	float gridSizef;

	sf::Texture texture;
	sf::FloatRect nextPos;
	sf::FloatRect ghostBounds;
	sf::FloatRect wallBounds;
	sf::FloatRect gateBounds;
	sf::FloatRect debuggerBounds;
	sf::CircleShape target;
	sf::Color color;
	
	float shortDir;
	float defult_dir;

	float D_left;
	float D_Right;
	float D_up;
	float D_Down;
	float D_invalid;

	sf::Vector2i left_point;
	sf::Vector2i Right_point;
	sf::Vector2i Up_point;
	sf::Vector2i Down_point;
	sf::Vector2i pos;

	//Mods stuff
	enum  GhoustsMod { CHASE = 0, SITT, RUN , EATEN , OUT ,START};
	int ghoustState = 5;

	sf::Clock RunTemp;
	 int runTimer;
	 sf::Time Runtime;
	
	bool chaseMood;

	//Orange_Ghost Special stuff
	bool inRange = false;
	bool test=false;
	sf::CircleShape range;

public:
	sf::Sprite ghost;
	sf::Clock Temp;

	int Timer = 0;
	sf::Time time;

public:
	Ghost(float &gridSizef, sf::Texture& texture, sf::Texture& runtexture, sf::Texture& eattentexture, sf::Color color);
	~Ghost();

	//Getters
	sf::Vector2f updatesemiDistance(sf::Vector2f semiPoint);
	int getGhostState();

	//Setters
	void resetGame();
	void setRedPos();
	void setPinkPos();
	void setOrangePos();
	void setCyanPos();


	//Initialisation functions
	void initAnimation(sf::Texture &idletexture, sf::Texture& runtexture, sf::Texture& eattentexture);
	void initTarget();
	void initRange();

	//Update functions
	//AI stuff
	void updatePoints();
	void updateinvalid(std::vector<sf::Sprite>walls,sf::Sprite wall);
	void updateGateCollision(std::vector<sf::Sprite>& gateParts);
	void updateDebugCollision(std::vector<sf::RectangleShape>& Debuggers);
	void updateDistances();
	void updateShortestDistance();
	void updateMovement(const float& dt,std::vector<sf::Sprite> walls, sf::RectangleShape tp1, sf::RectangleShape tp2);
	void updateAnimation(const float &dt);
	
	//Modes stuff
	void UpdateModes(std::vector<sf::CircleShape>&BigPoints, sf::Sprite& pacman,bool &paused,int*scoore);
	void updateRedGhost( sf::Sprite &packman, sf::RenderWindow& window);
	void updatePinkGhost(unsigned short& player_state, sf::Sprite& packman, sf::RenderWindow& window);
	void updateOrangeGhost(sf::Sprite& packman, sf::RenderWindow& window);
	void updateCyanGhost(unsigned short& player_state, sf::Sprite& packman, sf::RenderWindow& window, Ghost& plinky);
	
	void update(const float& dt, std::vector<sf::Sprite> walls, sf::Sprite wall, sf::RectangleShape tp1, sf::RectangleShape tp2, std::vector<sf::Sprite>& gateParts, std::vector<sf::RectangleShape>& Debuggers);

	//Render functions
	void render(sf::RenderTarget* target);
};

