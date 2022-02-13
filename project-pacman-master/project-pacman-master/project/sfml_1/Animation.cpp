#include "Animation.h"
#include<iostream>
Animation::~Animation()
{
}

//Initialisation Functions
	void Animation::initVariables(sf::Texture* texture,  unsigned initcolume, float switchTime, sf::Vector2u imageCount)
	{
		this->switchTime = switchTime;
		this->imageCount = imageCount;
		this->totalTime = 0.f;
		this->currentImage.x = initcolume;

		this->uvRect.width = texture->getSize().x / imageCount.x;
		this->uvRect.height = texture->getSize().y / imageCount.y;
	}

//Update Functions
	void Animation::update(unsigned row, unsigned initcolume, unsigned endcolume, const float& dt)
	{
		this->currentImage.y = row;
		this->totalTime += dt;

		if (this->totalTime >= this->switchTime)
		{
			this->totalTime -= this->switchTime ;
			this->currentImage.x++;

			if (this->currentImage.x >= endcolume)
			{
				this->currentImage.x = initcolume;
				this->animationEnded = true;
			}
		}
		this->uvRect.left = this->uvRect.width * this->currentImage.x;
		this->uvRect.top = this->uvRect.height * this->currentImage.y;

	}
	void Animation::updatewithoutRepeat(unsigned row, const float& dt)
	{
		this->currentImage.y = row;
	
		this->totalTime += dt;
		if (this->totalTime >= this->switchTime&&this->animationEnded==false)
		{
			this->totalTime -= this->switchTime;
			this->currentImage.x++;

			if (this->currentImage.x >= this->imageCount.x)
				this->animationEnded = true;
			else
				this->animationEnded = false;

		}
		this->uvRect.left = this->uvRect.width * this->currentImage.x;
		this->uvRect.top = this->uvRect.height * this->currentImage.y;

	}
