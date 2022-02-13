#include "BestScooreState.h"
//Constructor / Destructor
	BestScooreState::BestScooreState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states):
		state(window,supportedKeys,states)
	{
		this->settings.readFromFile("Config/window_config.txt");

		this->initkeysBind();
		this->readBestScoore();
		this->initBackground();
		this->initFont();
		this->initContainer();

		this->initButton();


	}
	BestScooreState::~BestScooreState()
	{
		delete this->button;
	}

//Initialisation Functions
	void BestScooreState::readBestScoore()
	{
		std::ifstream bestScoore;
		bestScoore.open("Highest Score.txt");

		if (bestScoore.is_open())
		{
			bestScoore >> this->name >> this->bastScoore;
		}
		bestScoore.close();
	}

	void BestScooreState::initkeysBind()
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
	void BestScooreState::initBackground()
	{
		this->bg_text.loadFromFile("Textures/temp.png");
		this->bg.setTexture(&this->bg_text);
		this->bg.setSize(sf::Vector2f(float(this->window->getSize().x),float( this->window->getSize().y)));
	}
	void BestScooreState::initContainer()
	{
		this->container.setFillColor(sf::Color(245, 255, 250, 100));
		this->container.setOutlineThickness(0.3f*this->gridSizef);
		this->container.setOutlineColor(sf::Color::Red);
		this->container.setPosition(this->actuallBestScoore.getPosition().x - 1.f * this->gridSizef, this->actuallBestScoore.getPosition().y + 1.f * this->gridSizef);
		this->container.setSize(sf::Vector2f(this->actuallBestScoore.getGlobalBounds().width + 3.f * this->gridSizef, this->actuallBestScoore.getGlobalBounds().height + 1.f * this->gridSizef));
	}
	void BestScooreState::initFont()
	{
		this->buttonFont.loadFromFile("Font/28 Days Later.ttf");
		this->bestScooreText.setFont(this->buttonFont);
		this->bestScooreText.setFillColor(sf::Color::White);
		this->bestScooreText.setCharacterSize(static_cast<unsigned int>(9.4f * this->gridSizef));
		this->bestScooreText.setString("best sccore");
		this->bestScooreText.setPosition(this->window->getSize().x / 2 - this->bestScooreText.getGlobalBounds().width / 2, 9.4f * this->gridSizef);

		this->bestScoorefont.loadFromFile("Font/arial.ttf");
		this->actuallBestScoore.setFont(this->bestScoorefont);
		this->actuallBestScoore.setFillColor(sf::Color::Black);
		this->actuallBestScoore.setCharacterSize(static_cast<unsigned int>(9.4f * this->gridSizef));
		this->actuallBestScoore.setString(this->name + " : " +std::to_string(this->bastScoore));
		this->actuallBestScoore.setPosition(this->window->getSize().x / 2 - this->actuallBestScoore.getGlobalBounds().width / 2, 28.f * this->gridSizef);
	}
	void BestScooreState::initButton()
	{
		this->button = new Button(this->settings.soundLevel,5.6f * this->gridSizef, 61.f * this->gridSizef, 16.f * this->gridSizef, 6.5f * this->gridSizef,
									"back", this->buttonFont, this->gridSizef,
									sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
									sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
									sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);
	}

//Update Functions
	void BestScooreState::updateButton()
	{
		if (this->button->isPressed() && this->getClickable() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBind["CLOSE"]))&&this->getClickable())
			this->endState();
	}
	void BestScooreState::update(const float& dt, sf::Event event)
	{
		this->updateMousepos();
		this->updateTimer(dt);
		this->button->update(this->mousePosView, *this->window,dt);
		this->updateButton();
	}

//Render Functions
	void BestScooreState::render(sf::RenderTarget* target)
	{
		if (!target)
			target = this->window;

		target->draw(this->bg);
		target->draw(this->bestScooreText);
		target->draw(this->container);
		target->draw(this->actuallBestScoore);
		this->button->render(target);
	}
