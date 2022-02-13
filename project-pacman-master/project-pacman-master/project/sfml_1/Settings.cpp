#include "Settings.h"

Settings::Settings()
{
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullScreen = false;
	this->frameRateLimite = 240;
	this->resolutions = sf::VideoMode::getFullscreenModes();
	this->soundLevel = 100.f;
};
 void Settings::readFromFile(const std::string fileAdress)
{
	std::ifstream window_config;
	window_config.open(fileAdress);
	
	if (window_config.is_open())
	{
		std::getline(window_config, this->title);
		window_config >> this->resolution.width >> this->resolution.height;
		window_config >> this->fullScreen;
		window_config >> this->frameRateLimite;
		window_config >> this->soundLevel;
		window_config >> this->playWithArrows;

	}
	window_config.close();
}
 void Settings::writeOnFile(const std::string fileAdress)
{
	std::ofstream window_config;
	window_config.open(fileAdress);
	
	if (window_config.is_open())
	{
		window_config << this->title<<"\n";
		window_config << this->resolution.width << " " << this->resolution.height << "\n";
		window_config << this->fullScreen << "\n";
		window_config << this->frameRateLimite<<"\n";
		window_config << this->soundLevel << "\n";
		window_config << this->playWithArrows;

	}

	window_config.close();
};

