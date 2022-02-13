#include "EndState.h"
 //Constructor / Destructon
	EndState::EndState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states,int& scoore):
		state(window,supportedKeys,states), textbox1(false,sf::Vector2f(37.5f * this->gridSizef,28.f * this->gridSizef),true, 10,scoore,this->gridSizef)
	{
		this->settings.readFromFile("Config/window_config.txt");

		this->initkeysBind();
		this->bg_text.loadFromFile("Textures/GameBG.png");
		this->bg.setTexture(&this->bg_text);
		this->bg.setSize(sf::Vector2f(float(this->window->getSize().x),float(this->window->getSize().y)));
		this->initFont();
		this->initButton();
	} 
	EndState::~EndState()
	{
		delete this->Donebutton;
		delete this->backbutton;
	}

//Initialisation Functions
	void EndState::initkeysBind()
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
	void EndState::initFont()
	{
		this->font.loadFromFile("Font/28 Days Later.ttf");
		this->uLost.setFont(this->font);
		this->uLost.setFillColor(sf::Color::White);
		this->uLost.setCharacterSize(static_cast < unsigned int>(9.4*this->gridSizef));
		this->uLost.setString("game over");
		this->uLost.setPosition(this->window->getSize().x / 2 - this->uLost.getGlobalBounds().width / 2, this->gridSizef);

		this->EnterURname.setFont(this->font);
		this->EnterURname.setFillColor(sf::Color::White);
		this->EnterURname.setCharacterSize(static_cast<unsigned int>(4.7f*this->gridSizef));
		this->EnterURname.setString("enter your name");
		this->EnterURname.setPosition(this->window->getSize().x / 2 - this->EnterURname.getGlobalBounds().width / 2, 18.7f*this->gridSizef);
	}
	void EndState::initButton()
	{
		this->Donebutton = new Button(this->settings.soundLevel, 37.5f * this->gridSizef, 37.5f * this->gridSizef, 18.7f * this->gridSizef, 4.7f * this->gridSizef, "done", this->font,
									this->gridSizef, sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
									sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
									sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

		this->backbutton = new Button(this->settings.soundLevel, 67.4f*this->gridSizef, 37.5f*this->gridSizef, 18.7f*this->gridSizef, 4.7f*this->gridSizef, "back", this->font,
									this->gridSizef, sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
									sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
									sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);
	}

//Update Functions
	void EndState::updatebutton()
	{
		if (this->Donebutton->isPressed())
		{
			this->back = true;
		}

		if (this->backbutton->isPressed()&&this->back==true)
		{
			this->states->push(new MainmenuState(this->window, this->supportedKeys, this->states));
		}
	}
	void EndState::update(const float& dt, sf::Event event)
	{
		this->updateMousepos();
		this->textbox1.updateTextbox(this->mousePosView,*this->window);
		this->textbox1.update(*this->window,event,dt,*this->Donebutton);
		this->Donebutton->update(this->mousePosView,*this->window,dt);
		this->backbutton->update(this->mousePosView,*this->window,dt);
		this->updatebutton();
	}

//Render Functions
	void EndState::render(sf::RenderTarget* target)
	{
		if (!target)
			target = this->window;

		target->draw(this->bg);
		target->draw(this->uLost);
		target->draw(this->EnterURname);
		this->Donebutton->render(target);
		this->backbutton->render(target);
		this->textbox1.drawTo(target);
	}