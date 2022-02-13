#include "Ghost.h"
#include<iostream>
#include<cmath>

Ghost::Ghost(float &gridSizef, sf::Texture& texture, sf::Texture& runtexture, sf::Texture& eattentexture,sf::Color color)
{
	this->gridSizef = gridSizef;
	this->idleTexture = texture;
	this->runTexture = runtexture;
	this->eattenTexture = eattentexture;


	this->movementSpeed = 12.f * this->gridSizef;
	this->color = color;
	this->initAnimation(texture,runtexture,eattentexture);
	this->initTarget();
	this->initRange();
}
Ghost::~Ghost()
{
}

	//Getters 
		sf::Vector2f Ghost::updatesemiDistance(sf::Vector2f semiPoint)
	{
		return sf::Vector2f(this->ghost.getPosition().x + this->ghost.getGlobalBounds().width / 2.f - semiPoint.x,
			this->ghost.getPosition().y + this->ghost.getGlobalBounds().height / 2.f - semiPoint.y);
	}
		int Ghost::getGhostState()
		{
			return this->ghoustState;
		}

	//Setters
		void Ghost::resetGame()
		{
			this->ghoustState = START;

			this->Timer = 0;
			this->time = sf::seconds(0);

			this->runTimer = 10;
			this->Runtime = sf::seconds(10);

		}
		void Ghost::setRedPos()
		{
			this->ghost.setPosition(sf::Vector2f(58.f*this->gridSizef, 25.2f * this->gridSizef));
		}
		void Ghost::setPinkPos()
		{
			this->ghost.setPosition(54.2f * this->gridSizef, 31.f * this->gridSizef);
		}
		void Ghost::setOrangePos()
		{
			this->ghost.setPosition(58.f * this->gridSizef, 31.f * this->gridSizef);
		}
		void Ghost::setCyanPos()
		{
			this->ghost.setPosition(62.f * this->gridSizef, 31.f * this->gridSizef);
		}

	//Initialisation functions
		void Ghost::initAnimation(sf::Texture& idletexture, sf::Texture& runtexture, sf::Texture& eattentexture)
		{
			
			this->ghost.setScale(sf::Vector2f(0.245f * this->gridSizef, 0.245f * this->gridSizef));
				this->ghost.setTexture(this->idleTexture);
				this->ghost.setTextureRect(sf::IntRect(0, 1, 16, 16));

				this->animations["IDLE"].initVariables(&this->idleTexture,0, 0.08f, sf::Vector2u(2, 4));
				this->animations["RUN"].initVariables(&this->runTexture,0, 0.08f, sf::Vector2u(4, 1));	
		}
		void Ghost::initTarget()
		{
			this->target.setOrigin(this->target.getRadius(), this->target.getRadius());
			this->target.setFillColor(this->color);
			this->target.setRadius(0.3f * this->gridSizef);

		}
		void Ghost::initRange()
		{
			this->range.setRadius(16.f * gridSizef);
			this->range.setFillColor(sf::Color::Transparent);
			this->range.setOutlineThickness(0.1f * this->gridSizef);
			this->range.setOutlineColor(sf::Color(sf::Color(255, 165, 0)));
			this->range.setOrigin(this->range.getRadius(), this->range.getRadius());
		}
	

	//Update Functions

		//general update
			void Ghost::updatePoints()
			{
				this->left_point.x = (int(this->ghost.getPosition().x - ( this->gridSizef)));
				this->left_point.y = (int(this->ghost.getPosition().y + this->ghost.getGlobalBounds().height / 2.f));

				this->Right_point.x = (int(this->ghost.getPosition().x + this->ghost.getGlobalBounds().width + ( this->gridSizef)));
				this->Right_point.y = (int(this->ghost.getPosition().y + this->ghost.getGlobalBounds().height / 2.f));

				this->Up_point.x = (int(this->ghost.getPosition().x + this->ghost.getGlobalBounds().width / 2.f));
				this->Up_point.y = (int(this->ghost.getPosition().y - ( this->gridSizef)));

				this->Down_point.x = (int(this->ghost.getPosition().x + this->ghost.getGlobalBounds().width / 2.f));
				this->Down_point.y = (int(this->ghost.getPosition().y + this->ghost.getGlobalBounds().height  + ( this->gridSizef)));

			}
			void Ghost::updateDistances()
			{
					this->D_up= (pow(this->Up_point.x - this->target.getPosition().x , 2) +
					pow(this->Up_point.y - this->target.getPosition().y + this->target.getRadius(), 2));

				this->D_Down = (pow(this->Down_point.x - this->target.getPosition().x , 2) +
					pow(this->Down_point.y - this->target.getPosition().y + this->target.getRadius(), 2));

				this->D_left = (pow(this->left_point.x - this->target.getPosition().x , 2) +
					pow(this->left_point.y - this->target.getPosition().y + this->target.getRadius(), 2));

				this->D_Right = (pow(this->Right_point.x - this->target.getPosition().x, 2) +
					pow(this->Right_point.y - this->target.getPosition().y + this->target.getRadius(), 2));

				this->D_invalid = 0.f;
			}
			void Ghost::updateinvalid(std::vector<sf::Sprite> walls, sf::Sprite wall)
			{
				
				if(this->pos.x==-1)
						this->D_Right = 0;
				else if (this->pos.x == 1)
						this->D_left = 0;
				else if (this->pos.y == -1)
						this->D_Down = 0;
				else if (this->pos.y == 1)
						this->D_up = 0;
				
				for (auto& wall : walls)
				{
					this->ghostBounds = this->ghost.getGlobalBounds();
					this->wallBounds = wall.getGlobalBounds();

					this->nextPos = this->ghostBounds;
					this->nextPos.left += 0.5f*this->gridSizef*this->pos.x;
					this->nextPos.top += 0.5f*this->gridSizef*this->pos.y;

					if (this->nextPos.intersects(this->wallBounds))
					{
						//Top
						if (this->ghostBounds.top < this->wallBounds.top &&
							this->ghostBounds.top + this->ghostBounds.width < this->wallBounds.top + this->wallBounds.width &&
							this->ghostBounds.left<this->wallBounds.left + this->wallBounds.width &&
							this->ghostBounds.left + this->ghostBounds.width >this->wallBounds.left)
						{
							this->D_Down = 0;
						}
						//Bottom
						 if (this->ghostBounds.top > this->wallBounds.top&&
							this->ghostBounds.top + this->ghostBounds.width > this->wallBounds.top + this->wallBounds.width &&
							this->ghostBounds.left<this->wallBounds.left + this->wallBounds.width &&
							this->ghostBounds.left + this->ghostBounds.width >this->wallBounds.left)
						{
							this->D_up = 0;
						}
						//Left
						if (this->ghostBounds.left < this->wallBounds.left &&
							this->ghostBounds.left + this->ghostBounds.width < this->wallBounds.left + this->wallBounds.width &&
							this->ghostBounds.top<this->wallBounds.top + this->wallBounds.height &&
							this->ghostBounds.top + this->ghostBounds.height >this->wallBounds.top)
						{
							this->D_Right = 0;
						}
						//Right
						 if (this->ghostBounds.left > this->wallBounds.left&&
							this->ghostBounds.left + this->ghostBounds.width > this->wallBounds.left + this->wallBounds.width &&
							this->ghostBounds.top<this->wallBounds.top + this->wallBounds.height &&
							this->ghostBounds.top + this->ghostBounds.height >this->wallBounds.top)
						{
							this->D_left = 0;
						}
			
					}
				}
			}
			void Ghost::updateGateCollision(std::vector<sf::Sprite> &gateParts)
			{
				for (auto wall : gateParts)
				{
					this->ghostBounds = this->ghost.getGlobalBounds();
					this->gateBounds = wall.getGlobalBounds();

					this->nextPos = this->ghostBounds;
					this->nextPos.left += 0.5f*this->gridSizef * this->pos.x;
					this->nextPos.top += 0.5f*this->gridSizef * this->pos.y;

					if (this->nextPos.intersects(this->gateBounds))
					{
						//Top
						if (this->ghostBounds.top < this->gateBounds.top &&
							this->ghostBounds.top + this->ghostBounds.width < this->gateBounds.top + this->gateBounds.width &&
							this->ghostBounds.left<this->gateBounds.left + this->gateBounds.width &&
							this->ghostBounds.left + this->ghostBounds.width >this->gateBounds.left)
						{
							this->D_Down = 0;
						}
					}
				}
			}
			void Ghost::updateDebugCollision(std::vector<sf::RectangleShape>& Debuggers)
			{
				for (auto debugger : Debuggers)
				{
					this->ghostBounds = this->ghost.getGlobalBounds();
					this->debuggerBounds = debugger.getGlobalBounds();

					this->nextPos = this->ghostBounds;
					this->nextPos.left += 0.5f * this->gridSizef * this->pos.x;
					this->nextPos.top += 0.5f * this->gridSizef * this->pos.y;

					if (this->nextPos.intersects(this->debuggerBounds))
					{
						//Left
						if (this->ghostBounds.left < this->debuggerBounds.left &&
							this->ghostBounds.left + this->ghostBounds.width < this->debuggerBounds.left + this->debuggerBounds.width &&
							this->ghostBounds.top<this->debuggerBounds.top + this->debuggerBounds.height &&
							this->ghostBounds.top + this->ghostBounds.height >this->debuggerBounds.top)
						{
							this->D_Right = 0;
						}
						//Right
						if (this->ghostBounds.left > this->debuggerBounds.left&&
							this->ghostBounds.left + this->ghostBounds.width > this->debuggerBounds.left + this->debuggerBounds.width &&
							this->ghostBounds.top<this->debuggerBounds.top + this->debuggerBounds.height &&
							this->ghostBounds.top + this->ghostBounds.height >this->debuggerBounds.top)
						{
							this->D_left = 0;
						}
					}
				}
			}
			void Ghost::updateShortestDistance()
			{
				if (this->D_up != 0)
				{
					this->defult_dir = D_up;
				}
				else if (this->D_left != 0)
				{
					this->defult_dir = D_left;
				}
				else if (this->D_Down != 0)
				{
					this->defult_dir = D_Down;
				}
				else if (this->D_Right != 0)
				{
					this->defult_dir = D_Right;
				}


				if (this->D_up <= this->defult_dir && this->D_up != 0)
				{
					this->defult_dir = D_up;
				}
				if (this->D_left < this->defult_dir && this->D_left != 0)
				{
					this->defult_dir = D_left;
				}
				if (this->D_Down < this->defult_dir && this->D_Down != 0)
				{
					this->defult_dir = D_Down;
				}
				if (this->D_Right < this->defult_dir && this->D_Right != 0)
				{
					this->defult_dir = D_Right;
				}

				this->shortDir =defult_dir;

				if (this->shortDir == D_up)
					this->ghost_dir = UP;
				else  if (this->shortDir == D_Right)
					this->ghost_dir = RIGHT;
				else  if (this->shortDir == D_Down)
					this->ghost_dir = DOWN;
				else  if (this->shortDir == D_left)
					this->ghost_dir = LEFT;
			}
			void Ghost::updateMovement(const float& dt, std::vector<sf::Sprite> walls,sf::RectangleShape tp1, sf::RectangleShape tp2)
			{
	
				this->ghost.move(this->pos.x * this->movementSpeed * dt, this->pos.y * this->movementSpeed * dt);

				switch (this->ghost_dir)
				{
				case LEFT :
					this->pos.x = -1;
					this->pos.y = 0;
					break;
				case RIGHT :
					this->pos.x = 1;
					this->pos.y = 0;
					break;
				case UP:
					this->pos.x = 0;
					this->pos.y = -1;
					break;
				case DOWN:
					this->pos.x = 0;
					this->pos.y = 1;
					break;
				default:
					break;
				}

				if (this->ghost.getPosition().x + this->ghost.getGlobalBounds().width <= tp1.getPosition().x)
				{
					this->ghost.setPosition(float(tp2.getPosition().x + tp2.getGlobalBounds().width),
						float(this->ghost.getPosition().y));
				}
				else if (this->ghost.getPosition().x >=tp2.getPosition().x+tp2.getGlobalBounds().width )
				{
					this->ghost.setPosition(float(tp1.getPosition().x - this->ghost.getGlobalBounds().width),
						float(this->ghost.getPosition().y));
				}
			}
			void Ghost::updateAnimation(const float &dt)
			{
				if (this->ghoustState != RUN || this->ghoustState != EATEN)
				{
					this->ghost.setTexture(this->idleTexture);

					if (this->pos.x < 0)
						this->animations["IDLE"].update(1,0,2, dt);
					if (this->pos.x > 0)
						this->animations["IDLE"].update(0,0,2, dt);
					if (this->pos.y < 0)
						this->animations["IDLE"].update(2, 0, 2, dt);
					if (this->pos.y > 0)
						this->animations["IDLE"].update(3, 0, 2, dt);

					this->ghost.setTextureRect(this->animations["IDLE"].uvRect);
				}
				if (this->ghoustState == RUN)
				{
					if (this->runTimer <= 7)
					{
						this->ghost.setTexture(this->runTexture);
						this->animations["RUN"].update(0, 0, 2, dt);
						this->ghost.setTextureRect(this->animations["RUN"].uvRect);
					}
					else
					{
						this->ghost.setTexture(this->runTexture);
						this->animations["RUN"].update(0, 1, 3, dt);
						this->ghost.setTextureRect(this->animations["RUN"].uvRect);
					}
				}
				if (this->ghoustState == EATEN)
				{
					if (this->pos.x < 0)
					{
						this->ghost.setTexture(this->eattenTexture);
						this->ghost.setTextureRect(sf::IntRect(16, 0, 16, 16));
					}
					if (this->pos.x > 0)
					{
						this->ghost.setTexture(this->eattenTexture);
						this->ghost.setTextureRect(sf::IntRect(0, 0, 16, 16));
					}				
					if (this->pos.y < 0)
					{
						this->ghost.setTexture(this->eattenTexture);
						this->ghost.setTextureRect(sf::IntRect(32, 0, 16, 16));
					}
					if (this->pos.y > 0)
					{
						this->ghost.setTexture(this->eattenTexture);
						this->ghost.setTextureRect(sf::IntRect(48, 0, 16, 16));
					}
				}
			}
			void Ghost::update(const float& dt, std::vector<sf::Sprite> walls, sf::Sprite wall, sf::RectangleShape tp1, sf::RectangleShape tp2, std::vector<sf::Sprite>& gateParts, std::vector<sf::RectangleShape>& Debuggers)
			{
				this->updatePoints();
				this->updateDistances();
				this->updateinvalid(walls,wall);
				if (this->ghoustState != EATEN)
					this->updateGateCollision(gateParts);
				if (this->ghoustState == EATEN)
					this->updateDebugCollision(Debuggers);
				this->updateShortestDistance();
				this->updateMovement(dt, walls, tp1, tp2);
				this->updateAnimation(dt);
			}
		
		//Special update
			void Ghost::UpdateModes(std::vector<sf::CircleShape>& BigPoints, sf::Sprite& pacman, bool& paused,int*scoore)
			{
				if (paused == false)
				{
					this->time += this->Temp.getElapsedTime();
					this->Timer = static_cast<int>(this->time.asSeconds());
					this->Temp.restart();
				}
				if (this->ghoustState == CHASE || this->ghoustState == SITT || this->ghoustState == START)
				{
					this->runTimer = 0;
					this->Runtime = sf::seconds(0);
					this->RunTemp.restart();

					this->movementSpeed = 9.f*this->gridSizef;
					if (this->Timer <= 9)
					{

						this->ghoustState = START;
					}
					else if (this->Timer > 9 && this->Timer <= 10)
					{
						this->ghoustState = OUT;
						for (auto& bigpoint : BigPoints)
						{
							if (pacman.getGlobalBounds().intersects(bigpoint.getGlobalBounds()))
							{
								this->ghoustState = RUN;
							}
						}
					}
					else if (this->Timer > 11 && this->Timer <= 35 || this->Timer > 55 && this->Timer <= 85 || this->Timer > 95 && this->Timer <= 130 || this->Timer > 135 && this->Timer <= 175 || this->Timer > 180)
					{
						this->ghoustState = CHASE;
						this->chaseMood = true; 
						for (auto& bigpoint : BigPoints)
						{
							if (pacman.getGlobalBounds().intersects(bigpoint.getGlobalBounds()))
							{
								this->ghoustState = RUN;
							}
						}
					}
					else
					{
						this->ghoustState = SITT;
						this->chaseMood = false;
						for (auto& bigpoint : BigPoints)
						{
							if (pacman.getGlobalBounds().intersects(bigpoint.getGlobalBounds()))
							{
								this->ghoustState = RUN;
							}
						}
					}
					
				}

				else if (this->ghoustState == RUN)
				{
					this->movementSpeed = 7.f * this->gridSizef;
					this->Runtime += this->RunTemp.getElapsedTime();
					this->runTimer = static_cast<int>(this->Runtime.asSeconds());
					this->RunTemp.restart();
					for (auto& bigpoint : BigPoints)
					{
						if (pacman.getGlobalBounds().intersects(bigpoint.getGlobalBounds()))
						{
							this->runTimer = 0;
							this->Runtime = sf::seconds(0);
							this->RunTemp.restart();
						}
					}
					if (pacman.getGlobalBounds().intersects(this->ghost.getGlobalBounds()))
					{
						*scoore = *scoore + 100;
						this->ghoustState = EATEN;
					}
					if (this->runTimer >= 10)
					{
						this->runTimer = 0;
						this->Runtime = sf::seconds(0);
						if (this->chaseMood == true)
							this->ghoustState = CHASE;
						else
							this->ghoustState = SITT;
					}
				}

				else if (this->ghoustState == EATEN)
				{
					this->movementSpeed = 13.f * this->gridSizef;

					this->runTimer = 0;
					this->Runtime = sf::seconds(0);
					this->RunTemp.restart();
					if (this->ghost.getGlobalBounds().contains(this->target.getPosition()))
					{
						this->ghoustState = OUT;
					}
					for (auto& bigpoint : BigPoints)
					{
						if (pacman.getGlobalBounds().intersects(bigpoint.getGlobalBounds()))
						{
							this->ghoustState = RUN;
						}
					}
				}

				else if (this->ghoustState == OUT)
				{
				this->runTimer = 0;
				this->Runtime = sf::seconds(0);
				this->RunTemp.restart();
					for (auto& bigpoint : BigPoints)
					{
						if (pacman.getGlobalBounds().intersects(bigpoint.getGlobalBounds()))
						{
							this->ghoustState = RUN;
						}
					}
					if (this->ghost.getGlobalBounds().contains(this->target.getPosition()))
					{
						if (this->chaseMood == true)
							this->ghoustState = CHASE;
						else
							this->ghoustState = SITT;
					}
				}
			}
			void Ghost::updateRedGhost(sf::Sprite& packman, sf::RenderWindow& window)
			{
				sf::Vector2f pacmanPos = (sf::Vector2f(packman.getPosition().x + packman.getGlobalBounds().width / 2.f,
													   packman.getPosition().y + packman.getGlobalBounds().height / 2.f));
				switch (this->ghoustState)
				{
				case START:
					this->target.setPosition(pacmanPos);
					break;
				case CHASE:
					this->target.setPosition(pacmanPos);
					break;
				case SITT:
					this->target.setPosition(80.5f*this->gridSizef,10.f*this->gridSizef);
					break;
				case RUN:
					this->target.setPosition(sf::Vector2f(float(rand() % window.getSize().x), float(rand() % window.getSize().y)));
					break;
				case EATEN:
					this->target.setPosition(60.2f * this->gridSizef, 32.f * this->gridSizef);
					break;
				case OUT:
					this->target.setPosition(60.3f * this->gridSizef, 25.6f * this->gridSizef);
					break;
				default:
					break;
				}
			}
			void Ghost::updatePinkGhost(unsigned short& player_state, sf::Sprite& packman, sf::RenderWindow& window)
			{
				sf::Vector2f pinkTarget;

				switch (player_state)
				{
				case 0:
					pinkTarget.x = packman.getPosition().x - (8 * this->gridSizef);
					pinkTarget.y = packman.getPosition().y + packman.getGlobalBounds().height / 2.f;
					break;
				case 1:
					pinkTarget.x = packman.getPosition().x + (8 * this->gridSizef);
					pinkTarget.y = packman.getPosition().y + packman.getGlobalBounds().height / 2.f;
					break;
				case 2:
					pinkTarget.x = packman.getPosition().x + packman.getGlobalBounds().width / 2.f;
					pinkTarget.y = packman.getPosition().y - (8 * this->gridSizef) ;
					break;
				case 3:
					pinkTarget.x = packman.getPosition().x + packman.getGlobalBounds().width / 2.f;
					pinkTarget.y = packman.getPosition().y + (8 * this->gridSizef);
					break;
				}

				switch (this->ghoustState)
				{
				case START:
					if (this->ghost.getGlobalBounds().intersects(this->target.getGlobalBounds()) && this->target.getPosition().y == 35.5f * this->gridSizef)
						this->test = true;
					if (this->ghost.getGlobalBounds().intersects(this->target.getGlobalBounds()) && this->target.getPosition().y == 29.8f * this->gridSizef)
							this->test = false;

						if(this->test==true)
							this->target.setPosition(55.f * this->gridSizef, 29.8f * this->gridSizef);
						else
							this->target.setPosition(55.f * this->gridSizef, 35.5f * this->gridSizef);

					break;
				case CHASE:
					this->target.setPosition(pinkTarget);
					break;
				case SITT:
					this->target.setPosition(40.f * this->gridSizef, 10.f * this->gridSizef);
					break;
				case RUN:
					this->target.setPosition(sf::Vector2f(float(rand() % window.getSize().x), float(rand() % window.getSize().y)));
					break;
				case EATEN:
					this->target.setPosition(60.2f * this->gridSizef, 32.f * this->gridSizef);
					break;
				case OUT:
					this->target.setPosition(60.3f * this->gridSizef, 25.6f * this->gridSizef);
					break;
				default:
					break;
				}

			}
			void Ghost::updateOrangeGhost(sf::Sprite& packman, sf::RenderWindow& window)
			{
				sf::Vector2f pacmanPos = (sf::Vector2f(packman.getPosition().x + packman.getGlobalBounds().width / 2.f,
					packman.getPosition().y + packman.getGlobalBounds().height / 2.f));

				this->range.setPosition(pacmanPos);

				if (abs(this->updatesemiDistance(pacmanPos).x) - (this->range.getRadius() + this->ghost.getGlobalBounds().width/2.f) < 0 &&
					abs(this->updatesemiDistance(pacmanPos).y) - (this->range.getRadius() + this->ghost.getGlobalBounds().height/2.f) < 0)
					this->inRange = true;
				else
					this->inRange = false;

				switch (this->ghoustState)
				{
				case START:
					if (this->ghost.getGlobalBounds().intersects(this->target.getGlobalBounds()) && this->target.getPosition().y == 35.5f * this->gridSizef)
						this->test = true;
					if (this->ghost.getGlobalBounds().intersects(this->target.getGlobalBounds()) && this->target.getPosition().y == 29.8f * this->gridSizef)
						this->test = false;

					if (this->test == true)
						this->target.setPosition(60.f * this->gridSizef, 29.8f * this->gridSizef);
					else
						this->target.setPosition(60.f * this->gridSizef, 35.5f * this->gridSizef);

					break;
				case CHASE:
					if(this->inRange==false)
						this->target.setPosition(pacmanPos);
					else 
						this->target.setPosition(55.f * this->gridSizef, 60.f * this->gridSizef);
					break;
				case SITT:
					this->target.setPosition(55.f * this->gridSizef, 60.f * this->gridSizef);
					break;
				case RUN:
					this->target.setPosition(sf::Vector2f(float(rand() % window.getSize().x),float( rand() % window.getSize().y)));
					break;
				case EATEN:
					this->target.setPosition(60.2f* this->gridSizef, 32.f * this->gridSizef);
					break;
				case OUT:
					this->target.setPosition(60.3f * this->gridSizef, 25.6f * this->gridSizef);
					break;
				default:
					break;
				}
			}
			void Ghost::updateCyanGhost(unsigned short& player_state, sf::Sprite& packman, sf::RenderWindow& window, Ghost& plinky)
			{
				sf::Vector2f semiTarget;

				switch (player_state)
				{
				case 0:
					semiTarget.x = packman.getPosition().x - (4 * this->gridSizef);
					semiTarget.y = packman.getPosition().y + packman.getGlobalBounds().height / 2.f;
					break;
				case 1:
					semiTarget.x = packman.getPosition().x + (4 * this->gridSizef);
					semiTarget.y = packman.getPosition().y + packman.getGlobalBounds().height / 2.f;
					break;
				case 2:
					semiTarget.x = packman.getPosition().x + packman.getGlobalBounds().width / 2.f;
					semiTarget.y = packman.getPosition().y - (4 * this->gridSizef);
					break;
				case 3:
					semiTarget.x = packman.getPosition().x + packman.getGlobalBounds().width / 2.f;
					semiTarget.y = packman.getPosition().y + (4 * this->gridSizef);
					break;
				}

				switch (this->ghoustState)
				{
				case START:
					if (this->ghost.getGlobalBounds().intersects(this->target.getGlobalBounds()) && this->target.getPosition().y == 35.5f * this->gridSizef)
						this->test = true;
					if (this->ghost.getGlobalBounds().intersects(this->target.getGlobalBounds()) && this->target.getPosition().y == 29.8f * this->gridSizef)
						this->test = false;

					if (this->test == true)
						this->target.setPosition(65.f * this->gridSizef, 29.8f * this->gridSizef);
					else
						this->target.setPosition(65.f * this->gridSizef, 35.5f * this->gridSizef);

					break;
				case CHASE:
					this->target.setPosition(semiTarget.x - plinky.updatesemiDistance(semiTarget).x,
						semiTarget.y - plinky.updatesemiDistance(semiTarget).y);
					break;
				case SITT:
					this->target.setPosition(65.f * this->gridSizef, 60.f * this->gridSizef);
					break;
				case RUN:
					this->target.setPosition(sf::Vector2f(float(rand() % window.getSize().x),float( rand() % window.getSize().y)));
					break;
				case EATEN:
					this->target.setPosition(60.2f* this->gridSizef, 32.f * this->gridSizef);
					break;
				case OUT:
					this->target.setPosition(60.3f * this->gridSizef, 25.6f * this->gridSizef);
					break;
				default:
					break;
				}

			}
	
	//Render Functions
			void Ghost::render(sf::RenderTarget* target)
		{
			target->draw(this->ghost);
		}
