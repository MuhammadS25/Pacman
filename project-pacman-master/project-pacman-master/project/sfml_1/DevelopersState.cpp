#include "DevelopersState.h"
//Constructor / Destructor
	DevelopersState::DevelopersState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states):
		state(window,supportedKeys,states)
	{
		this->initkeysBind();
		this->bg_text.loadFromFile("Textures/GameBG.png");
		this->bg.setTexture(&this->bg_text);
		this->bg.setSize(sf::Vector2f(float(this->window->getSize().x),float( this->window->getSize().y)));

		this->font.loadFromFile("Font/28 Days Later2.ttf");
		this->text.setFont(this->font);
		this->text.setCharacterSize(25);
		this->text.setFillColor(sf::Color::White);
		this->text.setString("Mazen Mohammed\n\nMohammed Ibrahim\n\nMohammed Zien\n\nMohammed Ibrahim\n\nMohammed Ashraf\n\nMaher Ahmed");
		this->text.setPosition(this->window->getSize().x / 2 - this->text.getGlobalBounds().width / 2,
								this->window->getSize().y / 2 - this->text.getGlobalBounds().height / 2);

		this->moveSpeed = 9 * this->gridSizef;
		this->pos = sf::Vector2i(1, -1);
	}
	DevelopersState::~DevelopersState()
	{
	}

//Initialisation Functions
	void DevelopersState::initkeysBind()
	{
		std::fstream supported_Keys_read("Config/supported_Key_GameState.txt");
		if (supported_Keys_read.is_open())
		{
			std::string key = "";
			std::string key2 = "";
			while (supported_Keys_read >> key >> key2)
			{
				this->keyBind[key] = this->supportedKeys->at(key2);
			}
		}
		supported_Keys_read.close();
	}

//Update Functions
	void DevelopersState::update(const float& dt,sf::Event event)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBind["CLOSE"])))
			this->endState();

	

		if (this->text.getGlobalBounds().left <= 0 ||
			this->text.getGlobalBounds().left + this->text.getGlobalBounds().width >= this->window->getSize().x )
			this->pos.x *= -1;

		if(this->text.getGlobalBounds().top <= 0 ||
			this->text.getGlobalBounds().top + this->text.getGlobalBounds().height >= this->window->getSize().y)
			this->pos.y *= -1;

	
			this->text.move(this->moveSpeed * dt * pos.x, this->moveSpeed * dt * pos.y);
	}

//Render Functions
	void DevelopersState::render(sf::RenderTarget* target)
	{
		if (!target)
			target = window;

		target->draw(this->bg);
		target->draw(this->text);
	}
