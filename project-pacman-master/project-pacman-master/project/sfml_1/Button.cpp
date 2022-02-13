#include "Button.h"

//Constructor / Destructor
	Button::Button(float &soundLevel,float x_pos, float y_pos, float width, float height, std::string text, sf::Font font,float gridSizef
		, sf::Color idelColor, sf::Color hoverColor, sf::Color pressColor, sf::Color bg_idelColor, sf::Color bg_hoverColor, sf::Color bg_pressColor,
		sf::Color outline_idelColor, sf::Color outline_hoverColor, sf::Color outline_pressColor, unsigned short id )
	{
		this->gridSizef = gridSizef;
		this->ButtonState = BTN_idel;
		this->shape.setPosition(sf::Vector2f(x_pos, y_pos));
		this->shape.setSize(sf::Vector2f(width, height));
	
		this->font = font;
		this->text.setFont(this->font);
		this->text.setCharacterSize(5*static_cast<unsigned int>(gridSizef));
		this->text.setString(text);
		this->text.setPosition(sf::Vector2f(float(this->shape.getPosition().x + this->shape.getSize().x/2.f - this->text.getGlobalBounds().width/2.f) ,
											float(this->shape.getPosition().y + this->shape.getSize().y/2.f - this->text.getGlobalBounds().height/2.f-0.5*gridSizef)));

		this->idelColor = idelColor;
		this->hoverColor = hoverColor;
		this->pressColor = pressColor;

		this->outline_idelColor = outline_idelColor;
		this->outline_hoverColor = outline_hoverColor;
		this->outline_pressColor = outline_pressColor;

		this->bg_idelColor = bg_idelColor;
		this->bg_hoverColor = bg_hoverColor;
		this->bg_pressColor = bg_pressColor;

		this->text.setFillColor(this->idelColor);
		this->shape.setFillColor(sf::Color::Transparent);

		this->hoverdSound.loadFromFile("Sounds/hoverd_sound.wav");
		this->pressedSound.loadFromFile("Sounds/pressed_sound.wav");

		this->sound.setVolume(soundLevel);
		this->sound.setLoop(false);

		this->initAnimation(gridSizef);
	}

//Getters
	int Button::getenumstate()
	{
		return this->ButtonState;
	}
	bool Button::isPressed()
	{
		if (this->ButtonState == BTN_Pressed)
			return true;

		return false;
	}
	std::string Button::getText()
	{
		return this->text.getString();
	}
	const unsigned short &Button::getid()const
{
	return this->id;
}

//Setters
	void Button::setText(std::string text)
	{
		this->text.setString(text);
	}
	void Button::setid(const unsigned short id)
	{
		this->id = id;
	}

//Initialisation fuctions
	void Button::initAnimation(float gridSizef)
	{
		this->pacpic.loadFromFile("Textures/pacman.png");
		this->sprite.setScale(0.3f*this->gridSizef, 0.3f*this->gridSizef);
	

		this->animation.initVariables(&this->pacpic,0, 0.08f, sf::Vector2u(3, 4));
	}

//Update functions
	void Button::updateAnimation(const float &dt)
	{
		this->animation.update(0,0,3,dt);

		this->sprite.setPosition(this->shape.getPosition().x - this->sprite.getGlobalBounds().width-0.5f*this->gridSizef,
			this->shape.getPosition().y + this->shape.getSize().y / 2 - this->sprite.getGlobalBounds().height / 2);

		this->sprite.setTexture(this->pacpic);
		this->sprite.setTexture(this->pacpic);
		this->sprite.setTextureRect(this->animation.uvRect);
	}
	void Button::update(sf::Vector2f &mousePos,sf::RenderWindow &window,const float &dt)
	{
		//idel state
		this->ButtonState = BTN_idel;
		//Hover and Pressed state
		if (this->shape.getGlobalBounds().contains(mousePos))
		{
			this->ButtonState = BTN_hovered;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->ButtonState = BTN_Pressed;

			}
		}
		switch (this->ButtonState)
		{
		case BTN_idel:
			this->text.setFillColor(this->idelColor);
			this->shape.setFillColor(this->bg_idelColor);
			this->shape.setOutlineColor(this->outline_idelColor);
			break;
		case BTN_hovered:
			if (this->sound.getStatus() != this->sound.Playing)
				{
		    		this->sound.setBuffer(this->hoverdSound);
		       		this->sound.play();
	     		}
			this->text.setFillColor(this->hoverColor);
			this->shape.setFillColor(this->bg_hoverColor);
			this->shape.setOutlineColor(this->outline_hoverColor);
			this->updateAnimation(dt);
			break;
		case BTN_Pressed:
			this->text.setFillColor(this->pressColor);
			this->shape.setOutlineColor(this->outline_pressColor);
			this->shape.setFillColor(this->bg_pressColor);
			this->sound.setBuffer(this->pressedSound);
			this->sound.play();
			break;
		default:
			this->text.setFillColor(sf::Color::Red);
			this->shape.setFillColor(sf::Color::Green);
			break;
		}

	}

//Render Functions
	void Button::renderAnimation(sf::RenderTarget* target)
	{
		if (this->ButtonState == BTN_hovered)
		{
				target->draw(this->sprite);
		}
	}
	void Button::setOutline(float gridSizef)
	{
		this->shape.setOutlineThickness(0.5f*gridSizef);
	}
	void Button::render(sf::RenderTarget* target)
	{
		target->draw(this->shape);
		target->draw(this->text);
	}