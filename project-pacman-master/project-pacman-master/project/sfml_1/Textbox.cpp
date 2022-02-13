#include "Textbox.h"
//Contructor / Destructor
	Textbox::~Textbox()
	{
	}
	Textbox::Textbox( bool sel,  Vector2f pos, bool TrueorFalse, int lim, int& scoore,float &gridSizef)
	{
		this->gridSizef = gridSizef;
		this->scoore = scoore;
		this->Text_Cursor.loadFromSystem(sf::Cursor::Arrow);

		ifstream highScoore;
		std::string name;
		highScoore.open("Highest Score.txt");
		if (highScoore.is_open())
		{
			highScoore >>name>> this->BestScoore;
			std::cout << this->BestScoore;
		}
		highScoore.close();

		this->font.loadFromFile("Font/arial.ttf");

		textbox.setCharacterSize(static_cast<unsigned int>(4.7f * this->gridSizef));
		textbox.setFillColor(sf::Color::Black);
		isSlected = sel;

		textbox.setFont(font);
		hasLimit = TrueorFalse;
		limit = lim - 1;

		this->Rect.setSize(sf::Vector2f(48.7f * this->gridSizef, 4.7f * this->gridSizef));
		this->Rect.setOutlineThickness(0.3f * this->gridSizef);
		this->Rect.setOutlineColor(Color::White);
		this->Rect.setPosition(pos);

		this->textbox.setPosition(sf::Vector2f(this->Rect.getPosition().x ,this->Rect.getPosition().y-this->Rect.getSize().y/4 ));

		this->idleColor = sf::Color(128, 128, 128, 200);
		this->HoveredColor = sf::Color(255, 250, 250, 100);
		this->PressedColor = sf::Color(245, 255, 250, 100);


		if (sel)
			textbox.setString("");
		else
			textbox.setString("");
	}

//Setters
	void Textbox::setSelected(bool sel)
	{
		isSlected = sel;
		if (!sel)
		{
			string t = of_text.str();
			string newT = "";
			if (t.length() != 0)
			{
				for (unsigned int i = 0; i <= t.length() - 1; i++)
				{
					newT += t[i];
				}
			}
			textbox.setString(newT);
		}
	}

//Getters
	string Textbox::getText()
	{
		return of_text.str();
	}
	const bool Textbox::getClickable()
	{
		if (this->keyTimer >= this->maxTimer)
		{
			this->keyTimer = 0.f;
			return true;
		}

		return false;
	}
	const bool Textbox::ispressed() const
	{
		if (this->textbox_state == PRESSED)
			return true;

		return false;
	}

//Update Functions
	void Textbox::drawTo(sf::RenderTarget* target)
	{
		target->draw(this->Rect);
		target->draw(textbox);
	
	}
	void Textbox::typedOn(Event input)
	{
		if (this->isSlected==true)
		{
			int charTyped = input.text.unicode;
			if (charTyped < 128)
			{
				if (this->hasLimit==true)
				{
					if (of_text.str().length() <= limit)
					{
						inputLogic(charTyped);
					}
					else if (of_text.str().length() >= limit && charTyped == DELETE_KEY)
					{
						deleteLastChar();
					}
				}
				else inputLogic(charTyped);
			}


		}
	}
	void Textbox::updateTextbox(sf::Vector2f& mousePos,sf::RenderWindow&window)
	{
		this->textbox_state = IDLE;

		//Hover and Pressed state
		if (this->Rect.getGlobalBounds().contains(mousePos))
		{
			this->textbox_state = HOVERED;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->textbox_state = PRESSED;

			}
		}
		switch (this->textbox_state)
		{
		case IDLE:
			this->Text_Cursor.loadFromSystem(sf::Cursor::Arrow);
			this->Rect.setFillColor(this->idleColor);
			break;
		case HOVERED:
			this->Text_Cursor.loadFromSystem(sf::Cursor::Text);
			this->Rect.setFillColor(this->HoveredColor);
			break;
		case PRESSED:
			this->Text_Cursor.loadFromSystem(sf::Cursor::Text);
			this->Rect.setFillColor(this->PressedColor);
			break;
		default:
			this->Text_Cursor.loadFromSystem(sf::Cursor::Arrow);
			this->Rect.setFillColor(sf::Color::Green);
			break;
		}
		window.setMouseCursor(this->Text_Cursor);
	}
	void Textbox::update(sf::RenderWindow& window,sf::Event event,const float &dt,Button&button)
	{
		this->updateTimer(dt);

		if (this->ispressed())
			this->setSelected(true);
		else if (Keyboard::isKeyPressed(Keyboard::Escape))
			this->setSelected(false);

				if (event.type == Event::TextEntered&&this->getClickable())
					this->typedOn(event);
		
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)||button.isPressed())
					{
						if (this->scoore > this->BestScoore)
						{
							ofstream Score;
							Score.open("Highest Score.txt");

							if (Score.is_open())
							{
								Score << this->getText() << " " << this->scoore;
							}
							Score.close();
						}
					}
			this->selected(this->getSelected());
	}
	void Textbox::updateTimer(const float& dt)
	{
		if (this->keyTimer < this->maxTimer)
			this->keyTimer += 7.f * dt;
	}



