#include "settingsState.h"

//Costructor / Destructor
	settingsState::settingsState(sf::RenderWindow* window, Settings& sittengs, std::map<std::string, int>* supportedKeys, std::stack<state*>* states):
		state(window, supportedKeys, states)
	{
		this->settings.readFromFile("Config/window_config.txt");

		this->Reselotions = sf::VideoMode::getFullscreenModes();
		this->initBG(*window);
		this->initsound();
		this->initBars(*window);
		this->initTexts();
		this->initButtons();
	}
	settingsState::~settingsState()
	{
		delete this->ReselutionBar;

			auto it = this->Buttons.begin();
		for (it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
		{
			delete it->second;
		}

		auto it_2 = this->Bars.begin();
		for (it_2 = this->Bars.begin(); it_2 != this->Bars.end(); ++it_2)
		{
			delete it_2->second;
		}
	}

//Getters
	const bool settingsState::changed() const
	{
		if (this->change == true)
			return true;

		return false;
	}

//initialisation functions
	void settingsState::initBG(sf::RenderWindow &window)
	{
		if(!this->BG_text.loadFromFile("Textures/temp.png"))
			 std::cout << "ERROR::SETTINGS::CAN_NOT_LOAD_BACKGROUND\n";

		this->bg.setTexture(&this->BG_text);
		this->bg.setSize(sf::Vector2f(float(this->settings.resolution.width), float(this->settings.resolution.height)));
	}
	void settingsState::initButtons()
	{
		this->Buttons["BACK"]=new Button(this->settings.soundLevel,112.f*this->gridSizef,56.f*this->gridSizef,9.f*this->gridSizef, 9.f * this->gridSizef,
										"Back",this->font,this->gridSizef,
										sf::Color::White,sf::Color::Yellow,sf::Color::Blue,
										sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
										sf::Color::White, sf::Color::Yellow, sf::Color::Blue);

		this->Buttons["ACCEPT"] = new Button(this->settings.soundLevel,84.f*this->gridSizef, 56.f* this->gridSizef, 9.f * this->gridSizef, 9.f * this->gridSizef,
	                                		"Accept", this->font,this->gridSizef,
											sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
											sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
								    		sf::Color::White, sf::Color::Yellow, sf::Color::Blue);

		this->Buttons["FULLSCREEN_CHECK_BOX"] = new Button(this->settings.soundLevel, 2.f*this->gridSizef,
														   15.5f * this->gridSizef,4.f*this->gridSizef, 4.f * this->gridSizef,
														   "", this->font, this->gridSizef,
														   sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
														   sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
														   sf::Color::White, sf::Color::Yellow, sf::Color::Blue);

		this->Buttons["PLAY_WITH_ARROWS"] = new Button(this->settings.soundLevel, 2.f * this->gridSizef,
														41.2f * this->gridSizef, 4.f * this->gridSizef, 4.f * this->gridSizef,
														"", this->font, this->gridSizef,
														sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
														sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
														sf::Color::White, sf::Color::Yellow, sf::Color::Blue);

		this->Buttons["PLAY_WITH_WASD"] = new Button(this->settings.soundLevel, 2.f * this->gridSizef,
														53.2f * this->gridSizef, 4.f * this->gridSizef, 4.f * this->gridSizef,
														"", this->font, this->gridSizef,
														sf::Color::White, sf::Color::Yellow, sf::Color::Blue,
														sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
														sf::Color::White, sf::Color::Yellow, sf::Color::Blue);
	}
	void settingsState::initTexts()
	{
		if (!this->font.loadFromFile("Font/28 Days Later2.ttf"))
			std::cout << "ERROR::SETTINGS::CANT_LOAD_FONT\n";

		this->Reselutiontext.setFont(this->font);
		this->Reselutiontext.setString("resolution");
		this->Reselutiontext.setCharacterSize(7*static_cast<unsigned int>(this->gridSizef));
		this->Reselutiontext.setFillColor(sf::Color::White);
		this->Reselutiontext.setPosition(sf::Vector2f(this->gridSizef, this->gridSizef));

		this->fullScreenText.setFont(this->font);
		this->fullScreenText.setString("FullScreen");
		this->fullScreenText.setCharacterSize(7* static_cast<unsigned int>(this->gridSizef));
		this->fullScreenText.setFillColor(sf::Color::White);
		this->fullScreenText.setPosition(sf::Vector2f(7.f* this->gridSizef, 14.f* this->gridSizef));

		this->playWithArrowsText.setFont(this->font);
		this->playWithArrowsText.setString("Play With Arrows");
		this->playWithArrowsText.setCharacterSize(7 * static_cast<unsigned int>(this->gridSizef));
		this->playWithArrowsText.setFillColor(sf::Color::White);
		this->playWithArrowsText.setPosition(sf::Vector2f(7.f * this->gridSizef, 40.f * this->gridSizef));

		this->playWithWASDText.setFont(this->font);
		this->playWithWASDText.setString("Play With WASD");
		this->playWithWASDText.setCharacterSize(7 * static_cast<unsigned int>(this->gridSizef));
		this->playWithWASDText.setFillColor(sf::Color::White);
		this->playWithWASDText.setPosition(sf::Vector2f(7.f * this->gridSizef, 52.f * this->gridSizef));

		this->checkSign_texture.loadFromFile("Textures/checkSign.png");

		this->checkSign.setTexture(&this-> checkSign_texture);
		this->checkSign.setSize(sf::Vector2f(4.f* this->gridSizef, 4.f* this->gridSizef));
		this->checkSign.setPosition(sf::Vector2f(2.f* this->gridSizef,
												 15.5f* this->gridSizef));

		this->playCheckSign.setTexture(&this->checkSign_texture);
		this->playCheckSign.setSize(sf::Vector2f(4.f * this->gridSizef, 4.f * this->gridSizef));

		if(this->settings.playWithArrows==true)
			this->playCheckSign.setPosition(sf::Vector2f(2.f * this->gridSizef,
				41.2 * this->gridSizef));
		else
			this->playCheckSign.setPosition(sf::Vector2f(2.f * this->gridSizef,
				53.2f * this->gridSizef));
	}
	void settingsState::initBars(sf::RenderWindow &window)
	{
		//Resolution Bar
		std::vector<std::string>Reselotions_string;

		for (auto& i : Reselotions)
		{
			Reselotions_string.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
		}
		this->ReselutionBar = new List(window.getSize().x-58.f*this->gridSizef, 2.f*this->gridSizef,
									   56.f*this->gridSizef, 6.f*this->gridSizef,
									   Reselotions_string.data(),Reselotions_string.size(),this->gridSizef);
	}
	void settingsState::initsound()
	{
		this->soundIcon.loadFromFile("Textures/sound.png");

		if (this->settings.soundLevel == 0)
			this->soundLevel = 9.f*this->gridSizef;
		if (this->settings.soundLevel == 25)
			this->soundLevel = 18.f * this->gridSizef;
		if (this->settings.soundLevel == 50)
			this->soundLevel = 29.125f * this->gridSizef;
		if (this->settings.soundLevel == 75)
			this->soundLevel = 40.75f * this->gridSizef;
		if (this->settings.soundLevel == 100)
			this->soundLevel = 51.f * this->gridSizef;

		std::cout << this->soundLevel << std::endl;

		this->Bars["SOUND_BAR"] = new Bar(6.5f * this->gridSizef, 28.f * this->gridSizef, 46.8f * this->gridSizef, 
										  4.7f * this->gridSizef, soundLevel,this->soundIcon,this->gridSizef,
							    		  sf::Color::White, sf::Color::Yellow, sf::Color::Black, sf::Color::Black, sf::Color(128,128,128,200));										
	}
	void settingsState::initkeysBind()
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
	void settingsState::updateChangedSettings()
	{
		this->setGridSize();
		this->initBG(*this->window);
		this->initButtons();
		this->initTexts();
		this->initsound();
		this->initBars(*this->window);
	}
	void settingsState::updateButtons()
	{
		if (this->Buttons["BACK"]->isPressed() && this->getClickable()||sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBind["CLOSE"])) && this->getClickable())
		{
			this->states->push(new MainmenuState(this->window, this->settings, this->supportedKeys, this->states));
		}
		if (this->Buttons["FULLSCREEN_CHECK_BOX"]->isPressed() && this->getClickable())
		{
			if (!this->settings.fullScreen)
			{
				std::cout << "FullScreen\n";
				this->settings.fullScreen = true;
				this->change = true;
			}
			else if (this->settings.fullScreen )
			{
				std::cout << "WindowMode\n";
				this->settings.fullScreen = false;
				this->change = true;
			}
		}
		if (this->Buttons["PLAY_WITH_ARROWS"]->isPressed() )
		{ 
			if (this->settings.playWithArrows == true)
				this->playCheckSign.setPosition(sf::Vector2f(2.f * this->gridSizef,
					41.2 * this->gridSizef));
			this->settings.playWithArrows = true;
		}
		if (this->Buttons["PLAY_WITH_WASD"]->isPressed() )
		{
			this->playCheckSign.setPosition(sf::Vector2f(2.f * this->gridSizef,
				53.2f * this->gridSizef));
			this->settings.playWithArrows = false;
		}
		this->defult.width = this->settings.resolution.width;
		this->defult.height = this->settings.resolution.height;
		if (this->Buttons["ACCEPT"]->isPressed())
		{
			if (this->Bars["SOUND_BAR"]->getlevle() < 9.125f * this->gridSizef)
				this->settings.soundLevel = 0;
			if (this->Bars["SOUND_BAR"]->getlevle() >= 9.125f * this->gridSizef && this->Bars["SOUND_BAR"]->getlevle() < 18.f * this->gridSizef)
				this->settings.soundLevel = 25;
			if (this->Bars["SOUND_BAR"]->getlevle() >= 18.f * this->gridSizef && this->Bars["SOUND_BAR"]->getlevle() < 29.125f * this->gridSizef)
				this->settings.soundLevel = 50;
			if (this->Bars["SOUND_BAR"]->getlevle() >= 29.125f * this->gridSizef && this->Bars["SOUND_BAR"]->getlevle() < 40.75f * this->gridSizef)
				this->settings.soundLevel = 75;
			if (this->Bars["SOUND_BAR"]->getlevle() >= 40.75f * this->gridSizef)
				this->settings.soundLevel = 100;

			if (this->ReselutionBar->changed())
				this->settings.resolution = this->Reselotions[this->ReselutionBar->getSelecteditemID()];
			else
				this->settings.resolution = this->defult;

			this->settings.writeOnFile("Config/window_config.txt");
		
			if (!this->settings.fullScreen)
				this->window->create(this->settings.resolution, this->settings.title, sf::Style::Default);
			else if (this->settings.fullScreen)
				this->window->create(this->settings.resolution, this->settings.title, sf::Style::Fullscreen | sf::Style::Titlebar);
			else
				this->window->create(this->defult, this->settings.title, sf::Style::Default);
	
			this->change = false;
			this->ReselutionBar->change = false;

			this->updateChangedSettings();
		}  
	}
	void settingsState::update(const float& dt, sf::Event event)
	{
		this->updateMousepos();
		this->updateTimer(dt);
		this->ReselutionBar->update(this->mousePosView,dt,*this->window);
		for (auto& i : this->Buttons)
		{
			i.second->update(this->mousePosView, *this->window,dt);
		}
		for (auto& i : this->Bars)
		{
			i.second->update(this->mousePosView);
		}
		this->updateButtons();
	}

//Render Funcions
	void settingsState::render(sf::RenderTarget* target)
	{
		if (!target)
			target= this->window;
	
		target->draw(this->bg);
		target->draw(this->Reselutiontext);
		target->draw(this->fullScreenText);
		target->draw(this->playWithArrowsText);
		target->draw(this->playWithWASDText);
		this->ReselutionBar->render(target);
		this->Buttons["FULLSCREEN_CHECK_BOX"]->setOutline(this->gridSizef);
		this->Buttons["PLAY_WITH_WASD"]->setOutline(this->gridSizef);
		this->Buttons["PLAY_WITH_ARROWS"]->setOutline(this->gridSizef);

		if (this->settings.fullScreen==true)
			target->draw(this->checkSign);

			target->draw(this->playCheckSign);
		for (auto& i : this->Buttons)
		{
			i.second->render(target);
		}
		for (auto& i : this->Bars)
		{
			i.second->render(target);
		}
	}
	