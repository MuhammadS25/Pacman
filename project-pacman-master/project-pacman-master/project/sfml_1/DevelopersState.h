#pragma once
#include "state.h"
class DevelopersState :
	public state
{
private:
	sf::Texture bg_text;
	sf::RectangleShape bg;

	sf::Font font;
	sf::Text text;

	float moveSpeed;

	sf::Vector2i pos;
public:
	//Constructor / Destructor
		DevelopersState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states);
		~DevelopersState();

	//Initialisation Functions
		void initkeysBind();

	//Update Functions
		void update(const float& dt, sf::Event event);

	//Render Functions
		void render(sf::RenderTarget* target = nullptr);
};

