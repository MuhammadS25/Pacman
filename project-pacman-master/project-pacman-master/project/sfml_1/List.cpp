#include "List.h"

//constructor / Destructor
	List::List(float x_pos, float y_pos, float width, float height, std::string options[], unsigned noOFoptions,float gridSizef, unsigned activeButton)
	{
		if (!this->font.loadFromFile("Font/28 Days Later2.ttf"))
			std::cout << "ERROR::CANT LOAD FONT \n";

		this->settings.readFromFile("Config/window_config.txt");

		this->selectedOption = new Button(this->settings.soundLevel,
			x_pos, y_pos,
			width, height,
			std::to_string(this->settings.resolution.width)+"x"+std::to_string(this->settings.resolution.height), this->font,gridSizef,
			sf::Color::Black, sf::Color::Yellow, sf::Color::Blue,
			sf::Color(128, 128, 128,200), sf::Color(255, 250, 250, 100), sf::Color(245, 255, 250, 100),
			sf::Color::White, sf::Color::White, sf::Color::White);

		for (unsigned int i = 0; i < noOFoptions; i++)
		{
			this->Options.push_back(new Button(this->settings.soundLevel,
				x_pos,y_pos+((i+1)*height),
				width,height,
				options[i], this->font, gridSizef,
				sf::Color::Black, sf::Color::Yellow, sf::Color::Blue,
				sf::Color(128, 128, 128, 200), sf::Color(255, 250, 250, 100), sf::Color(245, 255, 250, 100),
				sf::Color::White, sf::Color::White, sf::Color::White,
				i));
			this->Options[i]->setid(i);
		}
		this->selectedOption->setOutline(gridSizef);
	}
	List::~List()
	{
		delete this->selectedOption;
		for (auto& i : this->Options)
			delete i;
	}

//Setters
	const bool List::changed() const
	{
		if (this->change == true)
			return true;

		return false;
	}
	const unsigned short &List::getSelecteditemID()const
	{
		return this->selectedOption->getid();
	}

//Getters
	const bool List::Clicked() const
	{
		return this->click;
	}
	const bool List::getclicktime()
	{
		if (this->clicktimer >= this->maxclicktimer)
		{
			this->clicktimer = 0.f;
			return true;
		}
			return false;
	}


//Update fuctions
	void List::updateClicktimer(const float& dt)
	{
		if (this->clicktimer < this->maxclicktimer)
			this->clicktimer += 5.f * dt;
	}
	void List::update(sf::Vector2f& mousePos,const float &dt,sf::RenderWindow&window)
	{
		this->selectedOption->update(mousePos,window,dt);
		this->updateClicktimer(dt);

		if (this->selectedOption->isPressed()&&this->getclicktime())
		{
			if (this->Clicked())
				this->click = false;
			else
				this->click = true;
		}

		if (this->Clicked())
		{
			for (auto& i : this->Options)
			{
				i->update(mousePos,window,dt);
				if (i->isPressed() && this->getclicktime())
				{
					this->click = false;
					this->selectedOption->setText(i->getText());
					this->selectedOption->setid(i->getid());
					this->change = true;
				}
			}
		}
	}

//Render Functions
	void List::render(sf::RenderTarget* target)
	{
		this->selectedOption->render(target);
		if (this->Clicked())
		{
			for (auto& i : this->Options)
			{
				i->render(target);
			}
		}
	}
