#include"MainMenu.h"


MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("Resources/Font/ALGER.TTF"))
		std::cout << "No font is here" << std::endl;

	//Play
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::Blue);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(250, 200);

	//Records
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setString("Records");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(250, 300);

	//Exit
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::White);
	mainMenu[2].setString("Exit");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(250, 400);

	MainMenuSelected = 0;
}

MainMenu::~MainMenu()
{

}

void MainMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_main_menu; ++i)
		window.draw(mainMenu[i]);
}

void MainMenu::MoveUp()
{
	MainMenuSelected--;
	mainMenu[MainMenuSelected + 1].setFillColor(sf::Color::White);

	if (MainMenuSelected == -1)
		MainMenuSelected = Max_main_menu - 1;

	mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
}

void MainMenu::MoveDown()
{
	MainMenuSelected++;
	mainMenu[MainMenuSelected - 1].setFillColor(sf::Color::White);
	if (MainMenuSelected == Max_main_menu)
		MainMenuSelected = 0;

	mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);

}


