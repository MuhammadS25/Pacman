#pragma once
#include "state.h"
#include"MainmenuState.h"
#include "PackMan.h"
#include"PauseMenuState.h"
#include "Map.h"
#include"Ghost.h"
#include"settingsState.h"
#include "Settings.h"
#include"Animation.h"
#include"EndState.h"
#include<sstream>
#include<cstdlib>
#include<fstream>
class GameState :
	public state
{
private:
	//Variables
		Settings settings;
		float soundLevel;

		sf::Texture bgText;
		sf::RectangleShape bg;

	//Winning and losing stuff
		short unsigned lives = 3;
		unsigned int level = 1;

		bool dead = false;

	//New Movement Stuff
		enum  PlayerState {LEFT_STATE=0,RIGHT_STATE,UP_STATE,DOWN_STATE};
		unsigned short player_state;

		sf::Text pausedText;
		float pausedText_width;
		float pausedText_height;
		sf::Text pausedText_line_2;
		float pausedText_line_2_width;

	//PackMan Stuff
		Animation deathAnimation;
		sf::Texture deathTexture;
		PackMan packman;
		PauseMenuState pausemenue;
		Map test;

	//Ghosts Stuff
		std::map<std::string, Ghost*>ghosts;
		std::map<std::string, sf::Texture>ghostsTextures;

	//Timer Stuff
		sf::Clock GameClock;
		sf::Time GameTimer;
		int GameTimer_int;

		sf::Clock ustoppableClock;
		sf::Time unstoppableTimer;
		int unstoppableTimer_int;
		int minents=0;
	//Texts Stuff
		sf::Font font;
		std::map<std::string, sf::Text> texts;
		std::string name;
		long long bestScoore;


	public:
	//constructor / Destructor
		GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states);
		~GameState();
	//functions

		//Initialisations 
			void initkeysBind();
			void initSounds();
			void initGhosts();
			void initTexts();
			void readBestscoore();

		//Update Functions
			void updatePacmandeath(const float &dt);
			void updatePacmanWin();
			void updateTexts();
			void updateGameTimer();
			void updateGhost(const float&dt);
			void updateInput(const float& dt);
			void updateButtons();
			void updatePackManInput( sf::Vector2f* Velocity);
			void update(const float& dt, sf::Event event);

		//Render
    		void render(sf::RenderTarget * target = nullptr);
};