#pragma once
#include"Button.h"
#include<stack>
#include"state.h"

class PauseMenuState
	
{
	//Variables
private:
	sf::RectangleShape backGround;
	std::map<std::string, Button*> Buttons;
	sf::Texture buttonArea_Text;
public:
	sf::RectangleShape buttonArea;
	sf::Font font;

public:
	//Functions

	//Costructor / Destructor
		PauseMenuState(sf::RenderWindow& window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states);
		~PauseMenuState();

	//initialisation functions
		void addButton(float &soundLevel,std::string Key, float x_pos, float y_pos, float width, float height, std::string text,float gridSizef);
		void initFont();
		void initBackGround(sf::RenderWindow& window);
		void initButtonArea(sf::RenderWindow& window);

	//Update Functions
		const bool isButtonPressed(const std::string key);
		void updateInput(const float& dt);
		void updateButtons(sf::Vector2f &mousePosView, sf::RenderWindow& window,const float &dt);
		void update(sf::Vector2f& mousePosView,sf::RenderWindow& window,const float &dt);

	//Render Functions
		void renderButtons(sf::RenderTarget* target );
		void render(sf::RenderTarget* target = nullptr);
};

