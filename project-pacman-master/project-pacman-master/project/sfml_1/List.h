#pragma once
#include "Button.h"
#include "Settings.h"
class List
{
private:
	Settings settings;
	std::string string;
	sf::Font font;
	Button* selectedOption;
	std::vector<Button*>Options;
	bool click=false;

	float clicktimer=0.f;
	float maxclicktimer=1.f;
public:
	bool change=false;

public:
	//constructor / Destructor
		List(float x_pos,float y_pos,float width ,float height,std::string options[], unsigned noOFoptions,float gridSizef, unsigned activeButton = 0);
		~List();

	//Getters
		const bool changed()const;
		const unsigned short &getSelecteditemID()const;
		const bool Clicked() const;
		const bool getclicktime();

	//Update fuctions
		void updateClicktimer(const float& dt);
		void update(sf::Vector2f& mousePos, const float& dt, sf::RenderWindow& window);

	//Render Functions
		void render(sf::RenderTarget* target);
};

