#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

#include<fstream>
#include<sstream>
#include<string>
class Settings
{
public:
	//Variables 
	std::string title = "None";
	sf::VideoMode resolution;
	bool fullScreen=false;
	bool playWithArrows=false;
	unsigned frameRateLimite;
	std::vector<sf::VideoMode> resolutions;
	float soundLevel;
public:
	Settings();
	
	void readFromFile(const std::string fileAdress);
	void writeOnFile(const std::string fileAdress);
};

