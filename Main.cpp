#include<chrono>
#include<SFML/Graphics.hpp>
#include"Global.h"
#include<array>
#include<thread>
#include<ctime>
#include<iostream>
#include<Windows.h>
#include<fstream>
#include"DrawMap.h"
#include"MenuRecords.h"
#include<iostream>

#include"Pacman.h"
#include"Ghost.h"
#include"_1_Class_GhostManager.h"
#include"_1Class_SimpleObject.h"
#include"FillFileAfterRemove.h"
#include"AttentionWindow.h"
	
#include"ConvertSketch.h"
#include"MainMenu.h"
#include"GameCycle.h"
	
//std::string EMPTY_RECORD = "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";

void main()
{
	//sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Pac-Man", sf::Style::Close
	sf::RenderWindow MENU(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Main_Menu", sf::Style::Default);
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);
	//set background
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE));
	sf::Texture MainTexture;
	MainTexture.loadFromFile("Resources/Images/pacman_background.jpg");
	background.setTexture(&MainTexture);


	//photo to Records
	sf::RectangleShape Rbackground;
	Rbackground.setSize(sf::Vector2f(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE));
	sf::Texture RptionTexture;
	RptionTexture.loadFromFile("Resources/Images/Records_background.png");
	Rbackground.setTexture(&RptionTexture);




	sf::Text TextForOutput;
	sf::Font FontForOutput;
	if (!FontForOutput.loadFromFile("Resources/Font/ALGER.TTF"));

	TextForOutput.setFont(FontForOutput);
	TextForOutput.setFillColor(sf::Color::White);
	TextForOutput.setCharacterSize(FONT_HEIGHT);




	while (MENU.isOpen())
	{
		sf::Event event;

		if (MENU.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				MENU.close();
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					mainMenu.MoveUp();
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					mainMenu.MoveDown();
				}

				if (event.key.code == sf::Keyboard::Enter)
				{
					int x = mainMenu.MainMenuPressed();

					if (x == 0)
					{
						MENU.setVisible(false);

						GameCycle(MENU, FontForOutput, TextForOutput);
				
					}
					if (x == 1)
					{
						MENU.setVisible(false);
						MenuRecords MyListOfRecords;

						std::fstream Records;
						Records.open("Records/RECORDS.txt", std::fstream::in);


						sf::RenderWindow RECORDS(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "RECORDS");

						if (!Records.is_open())
						{
							Records.close();

							while (RECORDS.isOpen())
							{
								sf::Event Revent;

								if (RECORDS.pollEvent(Revent))
								{
									if (Revent.type == sf::Event::Closed)
									{
										RECORDS.close();
										MENU.setVisible(true);
									}
									if (Revent.type == sf::Event::KeyPressed)
									{
										if (Revent.key.code == sf::Keyboard::Escape)
										{
											RECORDS.close();
											MENU.setVisible(true);
										}
										if (Revent.key.code == sf::Keyboard::Up)
										{
											MyListOfRecords.MoveUp();
										}
										if (Revent.key.code == sf::Keyboard::Down)
										{
											MyListOfRecords.MoveDown();
										}
										if (Revent.key.code == sf::Keyboard::Delete)
										{
											MyListOfRecords.deleteRecord();
										}

									}
								}

								RECORDS.clear();
								RECORDS.draw(Rbackground);
								MyListOfRecords.draw(RECORDS);
								RECORDS.display();

							}
						}
						else
						{
							Records.seekp(0, ios::beg);

							while (!Records.eof())
							{
								std::string temp = "";

								std::getline(Records, temp, '\n');

								if (temp.compare("") == 0) { continue; }

								MyListOfRecords.analyze(temp);
							}
							MenuRecords::position = 0;

							Records.close();


							while (RECORDS.isOpen())
							{
								sf::Event Revent;
								if (RECORDS.pollEvent(Revent))
								{
									if (Revent.type == sf::Event::Closed)
									{
										FillFileAfterRemove(Records, MyListOfRecords);

										Records.close();

										RECORDS.close();
										MENU.setVisible(true);
									}

									if (Revent.type == sf::Event::KeyPressed)
									{
										if (Revent.key.code == sf::Keyboard::Escape)
										{
											FillFileAfterRemove(Records, MyListOfRecords);
												Records.close();

												RECORDS.close();
												MENU.setVisible(true);
										}

										if (Revent.key.code == sf::Keyboard::Up)
										{
											MyListOfRecords.MoveUp();
										}
										if (Revent.key.code == sf::Keyboard::Down)
										{
											MyListOfRecords.MoveDown();
										}
										if (Revent.key.code == sf::Keyboard::Delete)
										{
											MyListOfRecords.deleteRecord();
										}


									}
								}

								RECORDS.clear();
								RECORDS.draw(Rbackground);
								MyListOfRecords.draw(RECORDS);

								RECORDS.display();
							}
						}
					}
					if (x == 2)
					{
						MENU.close();
						break;
					}

				}


			}
			MENU.clear();
			MENU.draw(background);
			mainMenu.draw(MENU);
			MENU.display();
		}
	}


}
	
	
	