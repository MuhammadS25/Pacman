#pragma once
#include"SFML/Graphics.hpp"
class Animation
{
private:
	float switchTime;
	float totalTime;

	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

public:
	sf::IntRect uvRect;
	bool animationEnded = false;
public:
	~Animation();
	//Initialisation Functions
		void initVariables(sf::Texture* texture, unsigned initcolume, float switchTime, sf::Vector2u imageCount );

	//Update Functions
		void update(unsigned row, unsigned initcolume, unsigned endcolume,  const float& dt);
		void updatewithoutRepeat(unsigned row,  const float& dt);
	};