#include "state.h"
//Constructor / Destructor
	state::state(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states)
	{
		this->states = states;
		this->window = window;
		this->setGridSize();
		this->supportedKeys = supportedKeys;
		this->quit = false;
		this->paused = false;
	
	}
	state::~state()
	{
	
	}

//Setters
	void state::endState()
	{
		this->quit = true;
	}
	void state::setGridSize()
	{
		this->gridSizef = (float)window->getSize().x / 128.f;
	}
	void state::isPaused()
	{
		this->paused = true;
	}
	void state::unpasued()
	{
		this->paused = false;
	}

//Getters
	const bool& state::getQuit() const
	{
		return quit;
	}
	const bool state::getClickable()
	{
		if (this->keyTimer >= this->maxTimer)
		{
			this->keyTimer = 0.f;
			return true;
		}

		return false;
	}

//Update Functions
	void state::updateMousepos()
	{
		this->mousePosScreen = sf::Mouse::getPosition();
		this->mousePosWindow = sf::Mouse::getPosition(*this->window);
		this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	}
	void state::updateTimer(const float& dt)
	{
		if (this->keyTimer < this->maxTimer)
			this->keyTimer += 5.f * dt;
	}


	void state::endApplication(sf::RenderWindow* window)
	{
		this->window->close();
	}