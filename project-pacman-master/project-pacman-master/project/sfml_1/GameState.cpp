#include "GameState.h"
//constructor / Destructor
	GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states) :
		state(window, supportedKeys,states),pausemenue(*window,supportedKeys,states),test(*window,this->gridSizef),packman(this->gridSizef,this->level)
	{
		this->settings.readFromFile("Config/window_config.txt");
		this->soundLevel = this->settings.soundLevel;
		this->initkeysBind();
		this->initSounds();
		this->initGhosts();
		this->readBestscoore();
		this->initTexts();

		this->bgText.loadFromFile("Textures/GameBG.png");
		this->bg.setTexture(&this->bgText);
		this->bg.setSize(sf::Vector2f(float(this->window->getSize().x),float(this->window->getSize().y)));

		this->deathTexture.loadFromFile("Textures/Death.png");
		this->deathAnimation.initVariables(&this->deathTexture,0, 2.f, sf::Vector2u(12, 1));

		this->pausemenue.addButton(this->settings.soundLevel,"Continue",
			this->pausemenue.buttonArea.getPosition().x+4.5f*this->gridSizef,
			this->pausemenue.buttonArea.getPosition().y+32.8f*this->gridSizef ,34*this->gridSizef,  6 * this->gridSizef,
			"continue",this->gridSizef);

		this->pausemenue.addButton(this->settings.soundLevel, "Quit",
			this->pausemenue.buttonArea.getPosition().x + this->pausemenue.buttonArea.getSize().x / 2 - 7.f * this->gridSizef,
			this->pausemenue.buttonArea.getPosition().y + 55.f * this->gridSizef, 15.f * this->gridSizef, 6.f * this->gridSizef,
			"quit", this->gridSizef);

		this->sounds["START_SOUND"].play();
	}
	GameState::~GameState()
	{
		auto it = this->ghosts.begin();
		for (it = this->ghosts.begin(); it != this->ghosts.end(); ++it)
		{
			delete it->second;
		}


	}
	

//Initialisation Functions
	void GameState::initkeysBind()
	{
		std::fstream supported_Keys_read;
		if (this->settings.playWithArrows == true)
			supported_Keys_read.open("Config/supported_Key_GameState.txt");
		else
			supported_Keys_read.open("Config/supported_Key_GameState _WASD.txt");

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
	void GameState::initSounds()
	{
		this->Buffers["START_SOUND"].loadFromFile("Sounds/start-game.wav");
		this->Buffers["MOVE_SOUND"].loadFromFile("Sounds/move_sound.wav");
		this->Buffers["EAT_SOUND_1"].loadFromFile("Sounds/chomp1.wav");
		this->Buffers["EAT_SOUND_2"].loadFromFile("Sounds/chomp2.wav");
		this->Buffers["DIE_SOUND"].loadFromFile("Sounds/pacman-lose.wav");

		this->sounds["START_SOUND"].setBuffer(this->Buffers["START_SOUND"]);
		this->sounds["MOVE_SOUND"].setBuffer(this->Buffers["MOVE_SOUND"]);
		this->sounds["EAT_SOUND_1"].setBuffer(this->Buffers["EAT_SOUND_1"]);
		this->sounds["EAT_SOUND_2"].setBuffer(this->Buffers["EAT_SOUND_2"]);
		this->sounds["DIE_SOUND"].setBuffer(this->Buffers["DIE_SOUND"]);

		for (auto& i : this->sounds)
		{
			i.second.setVolume(this->soundLevel);
		}
	}
	void GameState::initGhosts()
	{
		this->ghostsTextures["RED"].loadFromFile("Textures/redGhost.png");
		this->ghostsTextures["CYAN"].loadFromFile("Textures/cyanGhost.png");
		this->ghostsTextures["PINK"].loadFromFile("Textures/redGhost - Copy (2).png");
		this->ghostsTextures["ORANGE"].loadFromFile("Textures/orangeGhost.png");

		this->ghostsTextures["RUN"].loadFromFile("Textures/Run.png");
		this->ghostsTextures["EATTEN"].loadFromFile("Textures/Eatten.png");

		this->ghosts["PLINKY"] = new Ghost(this->gridSizef, this->ghostsTextures["RED"], this->ghostsTextures["RUN"], this->ghostsTextures["EATTEN"],sf::Color::Red);
		this->ghosts["PINKY"] = new Ghost(this->gridSizef, this->ghostsTextures["PINK"], this->ghostsTextures["RUN"], this->ghostsTextures["EATTEN"], sf::Color(255, 192, 203));
		this->ghosts["INKY"] = new Ghost(this->gridSizef, this->ghostsTextures["CYAN"], this->ghostsTextures["RUN"], this->ghostsTextures["EATTEN"], sf::Color::Cyan);
		this->ghosts["CLYDE"] = new Ghost(this->gridSizef, this->ghostsTextures["ORANGE"], this->ghostsTextures["RUN"], this->ghostsTextures["EATTEN"], sf::Color(255, 165, 0));

		this->ghosts["PLINKY"]->setRedPos();
		this->ghosts["PINKY"]->setPinkPos();
		this->ghosts["INKY"]->setCyanPos();
		this->ghosts["CLYDE"]->setOrangePos();
	}
	void GameState::initTexts()
	{
		this->font.loadFromFile("Font/arial.ttf");

		this->texts["TIMER"].setCharacterSize(static_cast<unsigned int>(2.8f*this->gridSizef));
		this->texts["TIMER"].setFillColor(sf::Color::White);
		this->texts["TIMER"].setFont(this->font);
		this->texts["TIMER"].setPosition(9.f * this->gridSizef, 9.f * this->gridSizef);

		this->texts["LIVES"].setCharacterSize(static_cast<unsigned int>(2.8f * this->gridSizef));
		this->texts["LIVES"].setFillColor(sf::Color::White);
		this->texts["LIVES"].setFont(this->font);
		this->texts["LIVES"].setPosition(9.f * this->gridSizef, 28.f * this->gridSizef);

		this->texts["SCOORE"].setCharacterSize(static_cast<unsigned int>(2.8f * this->gridSizef));
		this->texts["SCOORE"].setFillColor(sf::Color::White);
		this->texts["SCOORE"].setFont(this->font);
		this->texts["SCOORE"].setPosition(9.f * this->gridSizef, 47.f * this->gridSizef);

		this->texts["LEVEL"].setCharacterSize(static_cast<unsigned int>(2.8f * this->gridSizef));
		this->texts["LEVEL"].setFillColor(sf::Color::White);
		this->texts["LEVEL"].setFont(this->font);
		this->texts["LEVEL"].setPosition(103.f * this->gridSizef, 9.f * this->gridSizef);

		this->texts["BEST_SCOORE"].setCharacterSize(static_cast<unsigned int>(2.8f * this->gridSizef));
		this->texts["BEST_SCOORE"].setFillColor(sf::Color::White);
		this->texts["BEST_SCOORE"].setFont(this->font);
		this->texts["BEST_SCOORE"].setPosition(103.f * this->gridSizef, 28.f * this->gridSizef);
	}
	void GameState::readBestscoore()
	{
		std::ifstream bestScoore;
		bestScoore.open("Highest Score.txt");

		if (bestScoore.is_open())
		{
			bestScoore >> this->name >> this->bestScoore;
		}
		bestScoore.close();
	}

//Update Functions
	void GameState::updatePacmandeath(const float&dt)
	{
		for (auto& ghost : this->ghosts)
		{
			if (ghost.second->getGhostState()==0|| ghost.second->getGhostState() == 1|| ghost.second->getGhostState() == 4|| ghost.second->getGhostState() == 5)
			{
				if (this->packman.packman.getGlobalBounds().intersects(ghost.second->ghost.getGlobalBounds()))
				{
					this->sounds["DIE_SOUND"].play();
					
					this->packman.packman.setTexture(this->deathTexture);
					this->deathAnimation.updatewithoutRepeat(0, dt);
					this->packman.packman.setTextureRect(this->deathAnimation.uvRect);

						this->GameTimer = sf::seconds(1);
						this->GameTimer_int = 1;

						this->ghosts["PLINKY"]->resetGame();
						this->ghosts["PINKY"]->resetGame();
						this->ghosts["INKY"]->resetGame();
						this->ghosts["CLYDE"]->resetGame();

						this->player_state = LEFT_STATE;
						this->packman.packman.setPosition(58.5f * this->gridSizef, 49.f * this->gridSizef);

						this->ghosts["PLINKY"]->setRedPos();
						this->ghosts["PINKY"]->setPinkPos();
						this->ghosts["INKY"]->setCyanPos();
						this->ghosts["CLYDE"]->setOrangePos();

						if (this->lives > 0)
							this->lives--;
						else
						{
							this->states->push(new EndState(this->window, this->supportedKeys, this->states,this->test.scoore));
						}
						
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Insert))
			this->states->push(new EndState(this->window, this->supportedKeys, this->states, this->test.scoore));
	}
	void GameState::updatePacmanWin()
	{
		if (this->test.won == true)
		{
			this->sounds["START_SOUND"].play();
			this->GameTimer = sf::seconds(1);
			this->GameTimer_int = 1;

			this->ghosts["PLINKY"]->resetGame();
			this->ghosts["PINKY"]->resetGame();
			this->ghosts["INKY"]->resetGame();
			this->ghosts["CLYDE"]->resetGame();

			this->player_state = LEFT_STATE;
			this->packman.packman.setPosition(58.5f * this->gridSizef, 49.f * this->gridSizef);

			this->ghosts["PLINKY"]->setRedPos();
			this->ghosts["PINKY"]->setPinkPos();
			this->ghosts["INKY"]->setCyanPos();
			this->ghosts["CLYDE"]->setOrangePos();
		}
	}
	void GameState::updateTexts()
	{
		stringstream str_stream;
		stringstream lives_str_stream;
		stringstream Time_str_stream;
		stringstream Level_str_stream;

		str_stream << "Scoore\n" << this->test.scoore;
		lives_str_stream << "Lives\n" << this->lives;
		Time_str_stream << "Time\n" << std::to_string(this->minents) << ":" <<this->unstoppableTimer_int;
		Level_str_stream << "Level\n" << this->level;

		this->texts["SCOORE"].setString(str_stream.str());
		this->texts["LIVES"].setString(lives_str_stream.str());
		this->texts["TIMER"].setString(Time_str_stream.str());
		this->texts["LEVEL"].setString(Level_str_stream.str());
		this->texts["BEST_SCOORE"].setString("Best Scoore\n"+this->name+":"+std::to_string(this->bestScoore));

	}
	void GameState::updateGameTimer()
	{
		this->GameTimer += this->GameClock.getElapsedTime();
		this->GameTimer_int = static_cast<int>(this->GameTimer.asSeconds());
		this->GameClock.restart();

		this->unstoppableTimer += this->ustoppableClock.getElapsedTime();
		this->unstoppableTimer_int = static_cast<int>(this->unstoppableTimer.asSeconds());
		this->ustoppableClock.restart();
		if (this->unstoppableTimer_int > 59)
		{
			this->unstoppableTimer = sf::seconds(0);
			this->unstoppableTimer_int = 0;
			this->minents++;
		}
	}
	void GameState::updateGhost(const float& dt)
	{

		this->ghosts["PLINKY"]->updateRedGhost(this->packman.packman, *this->window);
		this->ghosts["PINKY"]->updatePinkGhost(this->player_state, this->packman.packman, *this->window);
		this->ghosts["CLYDE"]->updateOrangeGhost(this->packman.packman, *this->window);
		this->ghosts["INKY"]->updateCyanGhost(this->player_state, this->packman.packman, *this->window, *this->ghosts["PLINKY"]);

		for (auto& ghosts : this->ghosts)
		{
			ghosts.second->UpdateModes(this->test.BigPoints, this->packman.packman,this->paused,&this->test.scoore);
			ghosts.second->update(dt, this->test.walls, this->test.wall, this->test.tp1, this->test.tp2,this->test.gateParts,this->test.Debuggers);
		}
	}
	void GameState::updateInput(const float& dt)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBind.at("CLOSE")))&&this->paused &&this->getClickable())
		{
			this->unpasued();
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBind.at("CLOSE"))) && !this->paused && this->getClickable())
		{
			this->isPaused();
		}
	
	}
	void GameState::updateButtons()
	{
		if (this->pausemenue.isButtonPressed("Continue") && this->getClickable())
		{
			this->unpasued();
		}
		if (this->pausemenue.isButtonPressed("Quit")&&this->getClickable())
		{
			this->endState();
		}
	}
	void GameState::updatePackManInput(sf::Vector2f *Velocity)
	{
	
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBind.at("MOVE_LEFT"))))
			{
				this->player_state = LEFT_STATE;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBind.at("MOVE_RIGHT"))))
			{
				this->player_state = RIGHT_STATE;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBind.at("MOVE_UP"))))
			{
				this->player_state = UP_STATE;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBind.at("MOVE_DOWN"))))
			{
				this->player_state = DOWN_STATE;
			}
		
			switch (this->player_state)
			{
			case LEFT_STATE:
				Velocity->x = -1;
				break;
			case RIGHT_STATE:
				Velocity->x = 1;
				break;
			case UP_STATE:
				Velocity->y = -1;
				break;
			case DOWN_STATE:
				Velocity->y = 1;
				break;
			default:
				break;
			}
	}
	void GameState::update(const float& dt, sf::Event event)
	{
		this->updateMousepos();
		this->updateTimer(dt);
		this->updateInput(dt);
		this->updateGameTimer();
		if (!this->paused)
		{
			this->updatePacmandeath(dt);
			this->updatePacmanWin();
			this->updateTexts();

			this->test.won = false;
			if (this->GameTimer_int >= 4)
			{

				this->updateGhost(dt);
				this->updatePackManInput(&this->packman.velocity);
				this->test.update(&this->packman.packman, &this->packman.velocity, this->packman.nextPos,
					this->sounds["EAT_SOUND_1"], this->sounds["EAT_SOUND_2"], this->sounds["MOVE_SOUND"],&this->level);

				this->packman.update(dt);
			}
		}
		else
		{

			this->pausemenue.update(this->mousePosView,*this->window,dt);
			this->updateButtons();
		}
		
	}

//Render Functions
	void GameState::render(sf::RenderTarget* target)
	{
		if (!target)
			target = this->window;

		target->draw(this->bg);
		this->test.render(target, this->paused);
			if (this->paused)
			{
				this->pausemenue.render(target);
			}
			else
			{
				for (auto& ghost : this->ghosts)
				{
					ghost.second->render(target);
				}
				this->packman.render(target);

				for(auto& text:this->texts)
					target->draw(text.second);
				
			}
	}