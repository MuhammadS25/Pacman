#pragma once
#include"state.h"
#include"Textbox.h"
#include"MainmenuState.h"
#include"Settings.h"
class EndState:
	public state
{
private:
	Settings settings;
	Textbox textbox1;
	Button *Donebutton;
	Button *backbutton;
	sf::RectangleShape bg;
	sf::Texture bg_text;

	sf::Text uLost;
	sf::Text EnterURname;
	sf::Font font;
	sf::Text i;
	bool back = false;

public:
	//Constructor / Destructor
		EndState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states,int &scoore);
		~EndState();

	//Initialisation Functions
		void initkeysBind();
		void initFont();
		void initButton();

	//Update Functions
		void updatebutton();
		void update(const float& dt, sf::Event event);

	//Render Functions
		void render(sf::RenderTarget* target = nullptr);
};

