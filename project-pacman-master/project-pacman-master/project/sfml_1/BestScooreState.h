#pragma once
#include "state.h"
#include"Button.h"
#include"Settings.h"
#include<fstream>
#include<string>
class BestScooreState :
	public state
{
private:
	Settings settings;
	sf::Texture bg_text;
	sf::RectangleShape bg;

	sf::Font bestScoorefont;
	sf::Font buttonFont;

	sf::RectangleShape container;
	sf::Text bestScooreText;
	sf::Text actuallBestScoore;
	Button* button;

	int bastScoore=0;
	std::string name;

public:
	//Constructor / Destructor
	BestScooreState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states);
	~BestScooreState();
	
	//Inintialisation functions
		void readBestScoore();

		void initkeysBind();
		void initBackground();
		void initContainer();
		void initFont();
		void initButton();

	//Update Functions
		void updateButton();
		void update(const float& dt, sf::Event event);

	//Render Functions
		void render(sf::RenderTarget* target = nullptr);
};

