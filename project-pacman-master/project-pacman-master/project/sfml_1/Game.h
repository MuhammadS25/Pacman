#pragma once
#include"MainmenuState.h"
#include "PackMan.h"
class Game
{   
private:
	//Variables
		Settings settings;
		sf::RenderWindow *window;
		sf::Event event;

		float dt;
		sf::Clock dtClock;
		std::stack <state*> states;
		std::map<std::string, int> supportedKeys;

	
		sf::Vector2f velocity;
public:
	//Constructors/Destructors
		Game();
		 ~Game();

	//Functions

private:
		//Initialisation Functions
			void initSettings();
			void initWindow();
			void initKeys();
			void initState();

		//Update Functions
			void updatEvent();
			void update();
			void updateDT();

		//Render Functions
			void render();

	public:
		void run();

};