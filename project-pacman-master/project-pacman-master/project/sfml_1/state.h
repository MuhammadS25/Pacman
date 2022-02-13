#pragma once
#include"Button.h"
#include<stack>

class state
{
protected:

//Variables
	sf::RenderWindow* window;
	bool quit;
	bool paused;

	float gridSizef ;
	float soundLevel;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBind;
	std::stack<state*>* states;

	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, sf::SoundBuffer> Buffers;
	
	float keyTimer = 0.f;
	float maxTimer = 1.f;

	//Functions
public:
	//Constructor / Destructor
		state(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<state*>* states);
		virtual ~state();

	//Setters
		void setGridSize();
		void isPaused();
		void unpasued();
		void endState();

	//Getters
		const bool& getQuit() const;
		const bool getClickable();

	//Initialisation Functions
		virtual void initkeysBind() = 0;

	//Update Functionns
		virtual void updateMousepos();
		void updateTimer(const float &dt);
		virtual void update(const float& dt, sf::Event event) = 0;

	//Render Functions
		virtual void render(sf::RenderTarget*target = nullptr) = 0;
	

	void endApplication(sf::RenderWindow*window);
};

