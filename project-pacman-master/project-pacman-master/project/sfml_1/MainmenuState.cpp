#include"MainmenuState.h"

//Render Functions
	MainmenuState::MainmenuState(sf::RenderWindow* window, Settings& settings, std::map<std::string, int>* supportedKeys, std::stack<state*>* states):
		state(window,supportedKeys,states)
	{
		this->settings.readFromFile("Config/window_config.txt");
		this->initkeysBind();
		this->initBackGround(*window);
		this->initFont();
		this->initButtons();

	
	}
	MainmenuState::MainmenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states):
		state(window, supportedKeys, states)
	{
		this->settings.readFromFile("Config/window_config.txt");
		this->initkeysBind();
		this->initBackGround(*window);
		this->initFont();
		this->initButtons();	
	}
	MainmenuState::~MainmenuState()
	{
		auto it = this->Buttons.begin();
		for (it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
		{
			delete it->second;
		}
	}

//Initilaisation functions
	void MainmenuState::initkeysBind()
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
	void MainmenuState::initBackGround(sf::RenderWindow& window)
	{
		this->backGroundtexture.loadFromFile("Textures/temp.png");
		this->backGround.setTexture(&this->backGroundtexture);
		this->backGround.setSize(sf::Vector2f(float(window.getSize().x),float(window.getSize().y)));
	}
	void MainmenuState::initFont()
	{
		this->font.loadFromFile("Font/28 Days Later.ttf");
	}
	void MainmenuState::initButtons()
	{
		this->Buttons["NEW_GAME"] = new Button(this->settings.soundLevel,5.6f*this->gridSizef, 4.7f * this->gridSizef, 37.5f * this->gridSizef, 6.5f * this->gridSizef,
												"new game", this->font,this->gridSizef,
												sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
												sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
												sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

		this->Buttons["BEST_SCOORE"] = new Button(this->settings.soundLevel, 5.6f * this->gridSizef, 16.4f * this->gridSizef, 45.f * this->gridSizef, 6.5f * this->gridSizef,
													"best scoore", this->font, this->gridSizef,
													sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
													sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
													sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

		this->Buttons["SETTINGS"] = new Button(this->settings.soundLevel, 6.5f * this->gridSizef, 28.f * this->gridSizef, 30.5f * this->gridSizef, 6.5f * this->gridSizef,
											   "settings", this->font, this->gridSizef,
											   sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
											   sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
											   sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

		this->Buttons["DEVELOPERS"] = new Button(this->settings.soundLevel, 6.5f * this->gridSizef, 40.f * this->gridSizef, 44.f * this->gridSizef, 6.5f * this->gridSizef,
									 		 "developers", this->font, this->gridSizef,
											 sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
											 sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
											 sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);

		this->Buttons["EXIT"] = new Button(this->settings.soundLevel, 6.5f * this->gridSizef, 51.5f * this->gridSizef, 16.5f * this->gridSizef, 6.5f * this->gridSizef,
										 "exit", this->font, this->gridSizef,
										 sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
										 sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
										 sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);
	}

//Update functions
	void MainmenuState::updateSounds()
	{
	}
	void MainmenuState::updateInput(const float& dt)
	{
		if (this->Buttons["NEW_GAME"]->isPressed())
			this->states->push(new GameState(this->window, this->supportedKeys, this->states));

		if (this->Buttons["BEST_SCOORE"]->isPressed())
			this->states->push(new BestScooreState(this->window, this->supportedKeys, this->states));

		if (this->Buttons["SETTINGS"]->isPressed())
			this->states->push(new settingsState(this->window, this->settings, this->supportedKeys, this->states));

		if (this->Buttons["DEVELOPERS"]->isPressed())
			this->states->push(new DevelopersState(this->window, this->supportedKeys, this->states));

		if (this->Buttons["EXIT"]->isPressed())
			this->endState();
	}
	void MainmenuState::updateButtons(const float &dt)
	{
		for (auto& button : this->Buttons)
		{
			button.second->update(this->mousePosView,*this->window,dt);
		}
	}
	void MainmenuState::update(const float& dt, sf::Event event)
	{
		this->updateSounds();
		this->updateMousepos();
		this->updateButtons(dt);
		this->updateInput(dt);
	}

//Render functions
	void MainmenuState::render(sf::RenderTarget* target)
	{
		if (!target)
			target=window;

		target->draw(this->backGround);
		this->renderButtons(target);
	}
	void MainmenuState::renderButtons(sf::RenderTarget* target)
	{
		for (auto& button : this->Buttons)
		{
			button.second->render(target);
			button.second->renderAnimation(target);
		}
	}


	void MainmenuState::endState()
	{
		this->endApplication(this->window);
	}
