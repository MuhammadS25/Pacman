#include "Bar.h"
//Contructor / Destructor
	Bar::Bar(float x_pos, float y_pos, float width,float height,float &buttonPos_x, sf::Texture iconTexture,float gridSizef,
		sf::Color idleColor, sf::Color HoveredColor, sf::Color pressedColor,
		sf::Color MovingBarColor, sf::Color backGroundColor)
	{
		this->Bar_state = IDLE;

		this->idleColor = idleColor;
		this->HoveredColor = HoveredColor;
		this->PressedColor = pressedColor;

		this->iconTexture = iconTexture;

		this->bar.setPosition(x_pos, y_pos);
		this->bar.setSize(sf::Vector2f(width, height));
		this->bar.setFillColor(backGroundColor);

		this->button.setRadius(height/2);
		this->button.setFillColor(idleColor);
		this->button.setOrigin(this->button.getRadius(), this->button.getRadius());
		this->button.setPosition(buttonPos_x, this->bar.getPosition().y+this->bar.getSize().y/2);

		this->MovingBar.setSize(sf::Vector2f(this->bar.getSize().x - (this->bar.getPosition().x + this->bar.getSize().x - this->button.getPosition().x),this->bar.getSize().y/4));
		this->MovingBar.setPosition(sf::Vector2f((float)this->bar.getPosition().x, float(this->bar.getPosition().y+this->bar.getSize().y/2 - this->MovingBar.getSize().y / 2)));
		this->MovingBar.setFillColor(MovingBarColor);

		this->icon.setTexture(&this->iconTexture);
		this->icon.setSize(sf::Vector2f(3.7f*gridSizef, 3.7f * gridSizef));
		this->icon.setPosition(this->bar.getPosition().x-this->icon.getSize().x-10.f,this->bar.getPosition().y);
	}
	Bar::~Bar()
	{
	}

//Getters
	const float Bar::getlevle()
	{
		return this->button.getPosition().x;
	}

//Update Functions
	void Bar::movable()
	{
		if (this->button.getPosition().x - this->button.getRadius() < this->bar.getPosition().x)
		{
			this->button.setPosition(sf::Vector2f(this->bar.getPosition().x+this->button.getRadius(),this->button.getPosition().y));
		}
		if (this->button.getPosition().x + this->button.getRadius() > this->bar.getPosition().x + this->bar.getSize().x)
		{
			this->button.setPosition(sf::Vector2f(this->bar.getPosition().x+this->bar.getSize().x-this->button.getRadius(),this->button.getPosition().y));
		}
	}
	void Bar::updateMovingBar(sf::Vector2f mousPos)
	{
		this->Bar_state = IDLE;

		if (this->bar.getGlobalBounds().contains(mousPos))
		{
			this->Bar_state = HOVERED;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->Bar_state = PRESSED;
			}

		}

		switch (this->Bar_state)
		{
		case IDLE:
			this->button.setFillColor(this->idleColor);
			break;
		case HOVERED:
			this->button.setFillColor(this->HoveredColor);
			break;
		case PRESSED:
		{	
			std::cout << this->button.getPosition().x<<std::endl;
			this->button.setFillColor(this->PressedColor);
		}
			break;
		default:
			break;
		}
	}
	void Bar::update(sf::Vector2f mousPos)
	{
		this->updateMovingBar(mousPos);
	
		if (this->Bar_state==PRESSED)
		{
			this->button.setPosition(sf::Vector2f(mousPos.x,this->button.getPosition().y));
			this->MovingBar.setSize(sf::Vector2f(this->bar.getSize().x-(this->bar.getPosition().x+this->bar.getSize().x-this->button.getPosition().x), this->bar.getSize().y / 4));
		}
		this->movable();
	}

//Render Functions
	void Bar::render(sf::RenderTarget* target)
	{
		target->draw(this->bar);
		target->draw(this->MovingBar);
		target->draw(this->button);
		target->draw(this->icon);
	}
