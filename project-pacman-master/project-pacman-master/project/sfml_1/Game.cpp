#include "Game.h"
//Constructors/Destructors
	Game::Game()
	{
		this->initSettings();
		this->initWindow();
		this->initKeys();
		this->initState();
	};
	Game::~Game()
	{
		delete this->window;

		if (!this->states.empty())
		{
			delete this->states.top();
			this->states.pop();
		}
	}

//Functions

	//Initialisation Functions
		void Game::initSettings()
		{
			this->settings.readFromFile("Config/window_config.txt");
		};
		void Game::initWindow()
		{
			if(this->settings.fullScreen)
				this->window = new sf::RenderWindow (this->settings.resolution, this->settings.title,sf::Style::Fullscreen);
			else 
				this->window = new sf::RenderWindow(this->settings.resolution, this->settings.title, sf::Style::Close |sf::Style::Titlebar);

			this->window->setFramerateLimit(this->settings.frameRateLimite);
			this->window->setMouseCursorGrabbed(true);

		}
		void Game::initKeys()
		{
			std::fstream supported_Keys_read("Config/supported_Key.txt");
			if (supported_Keys_read.is_open())
			{
				std::string key = " ";
				int key_value = -1;
				while (supported_Keys_read >> key >> key_value)
				{
					this->supportedKeys[key] = key_value;
				}
			}
			supported_Keys_read.close();
		}
		void Game::initState()
		{
			this->states.push(new MainmenuState(this->window,this->settings,&this->supportedKeys,&states));
		}

	//Update Functions
		void Game::updateDT()
		{
			this->dt = this->dtClock.restart().asSeconds();
		}
		void Game::updatEvent()
		{
			while (this->window->pollEvent(this->event))
			{
				if (this->event.type == sf::Event::Closed)
				{
					this->window->close();
				}
			}
	
		}
		void Game::update()
		{
			this->updatEvent();

			if (!this->states.empty())
			{
				this->states.top()->update(this->dt,this->event);
				if (this->states.top()->getQuit())
				{
					delete this->states.top();
					this->states.pop();
				}
			}
		}

	//Render Functions
		void Game::render()
		{
			this->window->clear();

			if (!this->states.empty())
			{
				this->states.top()->render();
			}

			this->window->display();
		}


	void Game::run()
	{
		while (this->window->isOpen())
		{
			this->updateDT();
			this->update();
			this->render();
		}
	}