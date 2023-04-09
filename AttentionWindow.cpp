#include"AttentionWindow.h"


void AttentionWindow(sf::RenderWindow& Play, sf::RenderWindow& MENU, sf::Font& FontForOutput )
{


	sf::RenderWindow ATTENTION(sf::VideoMode(400, 80), "ATTENTION", sf::Style::Titlebar);

	sf::Text TextForOutput[3];

	for (int i = 0; i < 3; i++)
	{
		TextForOutput[i].setFont(FontForOutput);
		TextForOutput[i].setFillColor(sf::Color::White);
		TextForOutput[i].setCharacterSize(15);

	}
	TextForOutput[0].setString("If you quit, you will lose a possible record");
	TextForOutput[1].setString("Press   'SPACE'   to exit");
	TextForOutput[2].setString("Press any other button to continue");
	//sf::Font FontForOutput;
	//if (!FontForOutput.loadFromFile("Resources/Font/ALGER.TTF"));

	TextForOutput[0].setPosition(5, 15);
	TextForOutput[1].setPosition(5, 30);
	TextForOutput[2].setPosition(5, 45);

	while (ATTENTION.isOpen())
	{
		sf::Event eventA;
		if (ATTENTION.pollEvent(eventA))
		{

			if (eventA.type == sf::Event::KeyPressed)
			{
				if (eventA.key.code == sf::Keyboard::Space)
				{
					ATTENTION.close();
					Play.close();
					MENU.setVisible(true);
				}
				if (eventA.key.code != sf::Keyboard::Space)
				{
					ATTENTION.close();
				}

			}
		}

		ATTENTION.clear();
		for (int i = 0; i < 3; i++)
		{
			ATTENTION.draw(TextForOutput[i]);
		}
		ATTENTION.display();

	}
}