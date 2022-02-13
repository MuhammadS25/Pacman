#pragma once
#include "state.h"
#include"Button.h"
#include"List.h"
#include"Settings.h"
#include"Bar.h"
#include"MainmenuState.h"
class settingsState :
	public state
{
private:
	//Variables
	Settings settings;
	sf::VideoMode defult;
	sf::Font font;


	sf::Text fullScreenText;
	sf::Text playWithArrowsText;
	sf::Text playWithWASDText;

	sf::RectangleShape checkSign;
	sf::RectangleShape playCheckSign;

	sf::Texture checkSign_texture;

	List *ReselutionBar;
	sf::Text Reselutiontext;
	std::vector<sf::VideoMode> Reselotions;

	std::map<std::string, Button*>Buttons; 

	std::map<std::string,Bar*> Bars;

	sf::RectangleShape bg;
	sf::Texture BG_text;
	sf::Texture soundIcon;

	float soundLevel;
	bool change = false;
public:
	//Costructor / Destructor
		settingsState(sf::RenderWindow* window,Settings&sittengs, std::map<std::string, int>* supportedKeys, std::stack<state*>* states);
		~settingsState();

	//getters
		const bool changed() const;

	//initialisation functions
		void initButtons();
		void initBG(sf::RenderWindow &window);
		void initTexts();
		void initBars(sf::RenderWindow &window);
		void initsound();
		void initkeysBind();
	
	 //Update Functions
		void updateChangedSettings();
		void updateButtons();
		void update(const float& dt, sf::Event event);

	 //Render Funcions
		void render(sf::RenderTarget* target = nullptr);
};

