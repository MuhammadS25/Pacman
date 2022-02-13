#include "PackMan.h"
//constructor / Destructor
PackMan::PackMan(float gridSizef,unsigned int &level)
{
	this->gridSizef = gridSizef;
	this->x_pos = 58.5f * gridSizef;
	this->y_pos = 49.f * gridSizef;
	this->initPacman(level);

}
PackMan::~PackMan()
{
}

//Getters
	void PackMan::returnPackmanPos()
{
	this->packman.setPosition(this->x_pos, this->y_pos);
}

//initialisazion functions
	void PackMan::initPacman( unsigned int& level)
	{
		this-> movementSpeed = 14.f*this->gridSizef;
		this->packman.setPosition(this->x_pos, this->y_pos); 
		this->PackManTexture.loadFromFile("Textures/pacman.png"); 
		this->packman.setScale(sf::Vector2f(0.225f*this->gridSizef,0.225f*this->gridSizef));
		this->pacmanMoveAnimation.initVariables(&this->PackManTexture,0, 0.05f, sf::Vector2u(3, 4));

	}

//Update functions
	void PackMan::updateAnimation(const float &dt)
	{
		this->packman.setTexture(this->PackManTexture);
		this->packman.setTextureRect(sf::IntRect(32,0,16,16));
		if (this->velocity.x > 0)
		{
			this->pacmanMoveAnimation.update(0,0,3, dt);
			
		}
		else if (this->velocity.x < 0)
		{
			this->pacmanMoveAnimation.update(1, 0, 3, dt);
		}
		else if (this->velocity.y < 0)
		{
			this->pacmanMoveAnimation.update(2, 0, 3, dt);
		}
		else if (this->velocity.y > 0)
		{
			this->pacmanMoveAnimation.update(3, 0, 3, dt);
		}
		this->packman.setTextureRect(this->pacmanMoveAnimation.uvRect);

	}
	void PackMan::updateMovement(const float&dt)
	{
		packman.move(this->velocity.x*this->movementSpeed*dt,this->velocity.y*this->movementSpeed*dt);
	}
	void PackMan::update(const float &dt)
	{

		this->updateMovement(dt);
		this->updateAnimation(dt);
	}

//Render functions
	void PackMan::render(sf::RenderTarget* target)
	{
		target->draw(this->packman);
	}

