#pragma once
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



void GameCycle(sf::RenderWindow& MENU, sf::Font& FontForOutput, sf::Text& TextForOutput);