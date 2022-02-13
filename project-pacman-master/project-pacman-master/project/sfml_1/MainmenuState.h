#pragma once
#include"GameState.h"
#include"settingsState.h"
#include"Button.h"
#include"Settings.h"
#include"BestScooreState.h"
#include"DevelopersState.h"
class MainmenuState :
	public state
{
private:
	//Variabls
	Settings settings;
	sf::Font font;
	sf::RectangleShape backGround;
	sf::Texture backGroundtexture;
	
	std::map<std::string, Button*> Buttons;

public:
	//Constructor/Destructor
		MainmenuState(sf::RenderWindow* window,Settings&settings, std::map<std::string, int>* supportedKeys, std::stack<state*>* states);
		MainmenuState(sf::RenderWindow* window,std::map<std::string, int>* supportedKeys, std::stack<state*>* states);

	virtual ~MainmenuState();

	//Functions

		//initialisation
			void initkeysBind();
			void initBackGround(sf::RenderWindow& window);
			void initFont();
			void initButtons();

		//Update
			void updateSounds();
			void updateInput(const float& dt);
			void updateButtons(const float &dt);
			void update(const float& dt, sf::Event event);
	
		//Render
			void render(sf::RenderTarget* target = nullptr);
			void renderButtons(sf::RenderTarget* target = nullptr);
			void endState();
};


