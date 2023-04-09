#include"MenuRecords.h"


//std::string EMPTY_RECORD = "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";

MenuRecords::MenuRecords(std::string str_1, std::string str_2, std::string str_3, std::string str_4, std::string str_5)
{
	if (!font.loadFromFile("Resources/Font/ALGER.TTF"))
		std::cout << "No font is here" << std::endl;


	textRecords[0].setFont(font);
	textRecords[0].setFillColor(sf::Color::Blue);
	textRecords[0].setString(str_1);
	textRecords[0].setCharacterSize(30);
	textRecords[0].setPosition(10, 100);

	textRecords[1].setFont(font);
	textRecords[1].setFillColor(sf::Color::Black);
	textRecords[1].setString(str_2);
	textRecords[1].setCharacterSize(30);
	textRecords[1].setPosition(10, 200);

	textRecords[2].setFont(font);
	textRecords[2].setFillColor(sf::Color::Black);
	textRecords[2].setString(str_2);
	textRecords[2].setCharacterSize(30);
	textRecords[2].setPosition(10, 300);

	textRecords[3].setFont(font);
	textRecords[3].setFillColor(sf::Color::Black);
	textRecords[3].setString(str_2);
	textRecords[3].setCharacterSize(30);
	textRecords[3].setPosition(10, 400);

	textRecords[4].setFont(font);
	textRecords[4].setFillColor(sf::Color::Black);
	textRecords[4].setString(str_2);
	textRecords[4].setCharacterSize(30);
	textRecords[4].setPosition(10, 500);

	MenuRecordsSelected = 0;

}


void MenuRecords::analyze(std::string other)
{
	//static int position;
	textRecords[position].setString(other);
	infoRecords[position] = other;

	position++;

}

void MenuRecords::deleteRecord()
{
	//textRecords[MenuRecordsPressed()].setString("-------------------------------------");
	if (infoRecords[MenuRecordsPressed()].compare(EMPTY_RECORD) == 0)
	{
		return;
	}
	else
	{
		for (int i = MenuRecordsPressed() + 1; ; i++)
		{
			if (i < Max_menu_records)
			{
				infoRecords[i - 1] = infoRecords[i];
				textRecords[i - 1].setString(infoRecords[i - 1]);
			}
			else
			{
				infoRecords[i - 1] = EMPTY_RECORD;
				textRecords[i - 1].setString(infoRecords[i - 1]);
				break;
			}
		}

	}
}

std::string* MenuRecords::getRecords()
{
	return infoRecords;
}

MenuRecords::~MenuRecords()
{

}

void MenuRecords::draw(sf::RenderWindow& window_records)
{
	for (int i = 0; i < Max_menu_records; ++i)
		window_records.draw(textRecords[i]);
}

void MenuRecords::MoveUp()
{
	MenuRecordsSelected--;
	textRecords[MenuRecordsSelected + 1].setFillColor(sf::Color::Black);

	if (MenuRecordsSelected == -1)
		MenuRecordsSelected = Max_menu_records - 1;

	textRecords[MenuRecordsSelected].setFillColor(sf::Color::Blue);
}

void MenuRecords::MoveDown()
{
	MenuRecordsSelected++;
	textRecords[MenuRecordsSelected - 1].setFillColor(sf::Color::Black);
	if (MenuRecordsSelected == Max_menu_records)
		MenuRecordsSelected = 0;

	textRecords[MenuRecordsSelected].setFillColor(sf::Color::Blue);

}

int MenuRecords::MenuRecordsPressed()
{
	return MenuRecordsSelected;
}


int MenuRecords::position;