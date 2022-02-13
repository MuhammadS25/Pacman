
#include "PauseMenuState.h"

//Costructor / Destructor
	PauseMenuState::PauseMenuState(sf::RenderWindow& window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states)
	{
		this->initFont();
		this->initBackGround(window);
		this->initButtonArea(window);
	
	}
	PauseMenuState::~PauseMenuState()
	{
		auto it = this->Buttons.begin();
		for (it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
		{
			delete it->second;
		}
	}

//Functions

//initialisation Functions
	void PauseMenuState::addButton(float &soundLevel,std::string Key, float x_pos, float y_pos,float width,float height, std::string text,float gridSizef)
	{
		this->Buttons[Key] = new Button(soundLevel,x_pos, y_pos, width, height,
			text, this->font,gridSizef,
			sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
			sf::Color(0,0,0,0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
			sf::Color::White, sf::Color::Yellow, sf::Color::Blue);
	}
	void PauseMenuState::initFont()
	{
		if (!this->font.loadFromFile("Font/28 Days Later.ttf"))
			std::cout << "ERROR::CANT LOAD FONT \n";
	}
	void PauseMenuState::initBackGround(sf::RenderWindow& window)
	{
		this->backGround.setSize(sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)));
		this->backGround.setFillColor(sf::Color(20, 20, 20, 100));
	}
	void PauseMenuState::initButtonArea(sf::RenderWindow& window)
	{
		this->buttonArea_Text.loadFromFile("Textures/pause.png");
		this->buttonArea.setTexture(&this->buttonArea_Text);
	  this->buttonArea.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x/3.f),
		static_cast<float>(window.getSize().y)));

	  this->buttonArea.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->buttonArea.getSize().x/1.7f, 0.f);

  
	 }
	const bool PauseMenuState::isButtonPressed(const std::string key)
	{
		return this->Buttons[key]->isPressed();
	}

//Update Functions
	void PauseMenuState::updateInput(const float& dt)
	{
	}
	void PauseMenuState::updateButtons(sf::Vector2f& mousePosView,sf::RenderWindow&window,const float &dt)
	{
		for (auto& it : this->Buttons)
		{
			it.second->update(mousePosView,window,dt);
		}	
	}
	void PauseMenuState::update(sf::Vector2f& mousePosView, sf::RenderWindow& window,const float &dt)
	{
		this->updateButtons( mousePosView,window,dt);
	}

//Render Functions
	void PauseMenuState::renderButtons(sf::RenderTarget* target)
	{
		for (auto i :this->Buttons)
		{
			i.second->render(target);
		}
	}
	void PauseMenuState::render(sf::RenderTarget* target)
	{
		target->draw(this->backGround);
		target->draw(this->buttonArea);
		this->renderButtons(target);

	}