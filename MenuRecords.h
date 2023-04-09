#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include"Global.h"
#define Max_menu_records 5

class MenuRecords
{
public:
	MenuRecords(std::string str_1 = EMPTY_RECORD, std::string str_2 = EMPTY_RECORD, std::string str_3 = EMPTY_RECORD, std::string str_4 = EMPTY_RECORD, std::string str_5 = EMPTY_RECORD);


	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void analyze(std::string);
	void deleteRecord();

	std::string* getRecords();


	int MenuRecordsPressed();

	~MenuRecords();
	static int position;
private:
	//static int position;
	int MenuRecordsSelected;
	sf::Font font;
	std::string infoRecords[Max_menu_records] = { EMPTY_RECORD, EMPTY_RECORD ,EMPTY_RECORD ,EMPTY_RECORD ,EMPTY_RECORD };
	sf::Text textRecords[Max_menu_records];
};