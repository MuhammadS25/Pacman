#include "Map.h"
//Constructor / Destructor
	Map::Map(sf::RenderWindow& window,float gridSizef)
	{
		this->gridSizef = gridSizef;
		this->scoore = 0;
		this->initBackGround(window);
		this->initWalls(&this->walls, this->wall, this->lvl_1_MapDraw);
		this->initPoints(&this->Points, this->point, this->lvl_1_MapDraw);
	}

//Initialisation functions
	void Map::initBackGround(sf::RenderWindow& window)
	{
		//this->WallPaper.setFillColor(sf::Color::Black);
		this->wallPapertexture.loadFromFile("Textures/map.png");
		this->WallPaper.setTexture(&this->wallPapertexture);
		this->WallPaper.setSize(sf::Vector2f(57.f*this->gridSizef, 63.f*this->gridSizef));
		this->WallPaper.setPosition(0.f,6.1f*this->gridSizef);
	}
	void Map::initWalls(std::vector<sf::Sprite>* walls, sf::Sprite wall, char map[100][100])
	{
		this->WallTexture.loadFromFile("Textures/Wall.png");
		wall.setTexture(this->WallTexture);
		wall.setScale(sf::Vector2f(.08f*this->gridSizef, .08f * this->gridSizef));

		this->gateTexture.loadFromFile("Textures/Wall - Copy.png");
		this->gate.setTexture(this->gateTexture);
		this->gate.setScale(sf::Vector2f(.08f * this->gridSizef, .08f * this->gridSizef));


		this->tp1.setSize(sf::Vector2f((float)this->gridSizef, (float)this->gridSizef));
		this->tp1.setFillColor(sf::Color::Transparent);

		this->tp2.setSize(sf::Vector2f((float)this->gridSizef, (float)this->gridSizef));
		this->tp2.setFillColor(sf::Color::Transparent);

		this->Debugger.setSize(sf::Vector2f((float)this->gridSizef, (float)this->gridSizef));
		this->Debugger.setFillColor(sf::Color::Transparent);

		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
			{
				if (map[j][i] == '1')
				{
					wall.setPosition((i+ 32 )* this->gridSizef, j * this->gridSizef);
					walls->push_back(wall);
				}
				if (map[j][i] == '2')
				{
					this->tp1.setPosition((i + 32) * this->gridSizef, j * this->gridSizef);
				}
				if (map[j][i] == '3')
				{
					this->tp2.setPosition((i + 32) * this->gridSizef, j * this->gridSizef);
				}
				if (map[j][i] == '-')
				{
					this->gate.setPosition((i + 32) * this->gridSizef, j * this->gridSizef);
					this->gateParts.push_back(this->gate);
				}
				if (map[j][i] == '6')
				{
					this->Debugger.setPosition((i + 32) * this->gridSizef, j * this->gridSizef);
					this->Debuggers.push_back(this->Debugger);
				}
			}
	}
	void Map::initPoints(std::vector<sf::Sprite>* points, sf::Sprite point, char map[100][100])
	{
		this->PointsTexture.loadFromFile("Textures/PointsTexture.png");
		point.setTexture(this->PointsTexture);
		point.setScale(sf::Vector2f(0.08f*this->gridSizef,0.08f*this->gridSizef));

		this->Bigpoint.setFillColor(sf::Color::White);
		this->Bigpoint.setRadius(this->gridSizef);

		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
			{
				if (map[j][i] == '*')
				{
					point.setPosition((i + 32) *  this->gridSizef, j *  this->gridSizef);
					points->push_back(point);
				}
				if (map[j][i] == '5')
				{
					this->Bigpoint.setPosition((i + 32) * this->gridSizef, j * this->gridSizef);
					this->BigPoints.push_back(Bigpoint);
				}
			}
	
	}

//Update functions
	void Map::updateWallCollision(sf::Sprite* sprite, std::vector<sf::Sprite> walls, sf::Sprite wall, sf::Vector2f* Velocity,sf::FloatRect nextPos,sf::Sound&move_sound)
	{
		for (auto &wall : walls)
		{
			sf::FloatRect playerBoundes = sprite->getGlobalBounds();
			sf::FloatRect wallBoundes = wall.getGlobalBounds();
			nextPos = playerBoundes;
			nextPos.left += 0.5*this->gridSizef*Velocity->x;
			nextPos.top += 0.5*this->gridSizef*Velocity->y;

			if (nextPos.intersects(wallBoundes))
			{
				//Top
				if (playerBoundes.top < wallBoundes.top &&
					playerBoundes.top + playerBoundes.width < wallBoundes.top + wallBoundes.width &&
					playerBoundes.left<wallBoundes.left + wallBoundes.width &&
					playerBoundes.left + playerBoundes.width >wallBoundes.left)
				{
					Velocity->y = 0.f;
					sprite->setPosition(playerBoundes.left, wallBoundes.top - playerBoundes.height);
				}
				//Bottom
				else if (playerBoundes.top > wallBoundes.top&&
					playerBoundes.top + playerBoundes.width > wallBoundes.top + wallBoundes.width &&
					playerBoundes.left<wallBoundes.left + wallBoundes.width &&
					playerBoundes.left + playerBoundes.width >wallBoundes.left)
				{
					Velocity->y = 0.f;
					sprite->setPosition(playerBoundes.left, wallBoundes.top + wallBoundes.height);
				}
				//Left
				if (playerBoundes.left < wallBoundes.left &&
					playerBoundes.left + playerBoundes.width < wallBoundes.left + wallBoundes.width &&
					playerBoundes.top<wallBoundes.top + wallBoundes.height &&
					playerBoundes.top + playerBoundes.height >wallBoundes.top)
				{
					Velocity->x = 0.f;
					sprite->setPosition(wallBoundes.left - playerBoundes.width, playerBoundes.top);
				}
				//Right
				else if (playerBoundes.left > wallBoundes.left&&
					playerBoundes.left + playerBoundes.width > wallBoundes.left + wallBoundes.width &&
					playerBoundes.top<wallBoundes.top + wallBoundes.height &&
					playerBoundes.top + playerBoundes.height >wallBoundes.top)
				{
					Velocity->x = 0.f;
					sprite->setPosition(wallBoundes.left + wallBoundes.width, playerBoundes.top);
				}
			}

		}
		if(Velocity->x==0&&Velocity->y==0)
			move_sound.stop();
		else
		{
			if (move_sound.getStatus() != move_sound.Playing)
				move_sound.play();
		}

		if (sprite->getPosition().x + sprite->getGlobalBounds().width <= this->tp1.getPosition().x)
		{
			sprite->setPosition(float(this->tp2.getPosition().x + this->tp2.getGlobalBounds().width),
				float(sprite->getPosition().y));
		}
		else if (sprite->getPosition().x > this->tp2.getPosition().x + sprite->getGlobalBounds().width)
		{
			sprite->setPosition(float(this->tp1.getPosition().x - sprite->getGlobalBounds().width),
				float(sprite->getPosition().y));
		}
	}
	void Map::updateGateCollision(sf::Sprite* sprite, std::vector<sf::Sprite> walls, sf::Sprite wall, sf::Vector2f* Velocity, sf::FloatRect nextPos)
	{
		for (auto& gate : this->gateParts)
		{
			sf::FloatRect playerBoundes = sprite->getGlobalBounds();
			sf::FloatRect wallBoundes = wall.getGlobalBounds();
			nextPos = playerBoundes;
			nextPos.left += 2 * Velocity->x;
			nextPos.top += 2 * Velocity->y;

			if (nextPos.intersects(wallBoundes))
			{
				//Top
				if (playerBoundes.top < wallBoundes.top &&
					playerBoundes.top + playerBoundes.width < wallBoundes.top + wallBoundes.width &&
					playerBoundes.left<wallBoundes.left + wallBoundes.width &&
					playerBoundes.left + playerBoundes.width >wallBoundes.left)
				{
					Velocity->y = 0.f;
					sprite->setPosition(playerBoundes.left, wallBoundes.top - playerBoundes.height);
				}
			}
		}
	}
	void Map::updatePointCollision(std::vector<sf::Sprite>* points, sf::Sprite point, sf::Sprite packman , sf::Sound &eat_1_sound, sf::Sound &eat_2_sound, unsigned int* level)
	{
		int i = 0;
	
		for (auto point : *points)
		{
			if (point.getGlobalBounds().contains(packman.getPosition().x+packman.getGlobalBounds().width/2.f,packman.getPosition().y+packman.getGlobalBounds().height/2.f))
			{
				this->pointseaten++;
				this->scoore += 10 ;
				points->erase(points->begin() + i);

				if (this->pointseaten < 200)
						eat_1_sound.play();
				else
						eat_2_sound.play();
			
				if (this->pointseaten >= 250)
				{
					*level = *level + 1;
					this->pointseaten = 0;
					this->initPoints(&this->Points, this->point, this->lvl_1_MapDraw);
					this->won = true;
				}
				else
					this->won = false;
			}
			i++;

		}
		int j = 0;
		for (auto bigpoints : this->BigPoints)
		{
			if (bigpoints.getGlobalBounds().intersects(packman.getGlobalBounds()))
			{
				this->BigPoints.erase(this->BigPoints.begin() + j);
				this->scoore += 20;
			}
			j++;
		}
	}
	void Map::update(sf::Sprite* sprite, sf::Vector2f* Velocity, sf::FloatRect nextPos, sf::Sound &eat_1_sound, sf::Sound &eat_2_sound, sf::Sound& move_sound, unsigned int* level)
	{
		this->updateGateCollision(sprite, this->gateParts, this->gate, Velocity, nextPos);
		this->updateWallCollision(sprite,this->walls,this->wall,Velocity,nextPos,move_sound);
		this->updatePointCollision(&this->Points, this->point,*sprite,eat_1_sound,eat_2_sound,level);
	}

//Render functions
	void Map::RenderwallPaper(sf::RenderTarget* target)
	{
		target->draw(this->WallPaper);
	}
	void Map::renderWalls(sf::RenderTarget* target, std::vector<sf::Sprite> walls)
	{
		for (auto &wall : walls)
		{
			target->draw(wall);
		}
		for (auto& gate : this->gateParts)
		{
			target->draw(gate);
		}

		target->draw(this->tp1);
		target->draw(this->tp2);
	}
	void Map::renderPoints(sf::RenderTarget* target, std::vector<sf::Sprite> points)
	{
		for (auto &point : points)
		{
			target->draw(point);
		}
		for (auto& Bigpoint : this->BigPoints)
		{
			target->draw(Bigpoint);
		}
	}
	void Map::render(sf::RenderTarget* target,bool paused)
	{
	
		this->renderWalls(target, this->walls);
		if(!paused)
		this->renderPoints(target,this->Points);
	
	}
