#include"GameCycle.h"


void GameCycle(sf::RenderWindow& MENU, sf::Font& FontForOutput, sf::Text& TextForOutput)
{
	bool IsPressToStart = false;

	sf::RenderWindow Play(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Pac-Man", sf::Style::Close);
	Play.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));


	bool game_won = 0;
	unsigned char level = 0;


	std::array<std::string, MAP_HEIGHT> map_sketch = {

		" ################### ",    //  -1|0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 | 21
		" #........#........# ",    //    |                                                     |
		" #o##.###.#.###.##o# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#   0   #.#    ",
		"#####.# ##=## #.#####",
		"     .  #123#  .     ",
		"#####.# ##### #.#####",
		"    #.#       #.#    ",
		" ####.# ##### #.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #o.#.....P.....#.o# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### "
	};
	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};

	std::array<SimpleObject::Position, 4> ghost_positions;
	GhostManager ghost_manager;
	Pacman pacman;



	map = convert_sketch(map_sketch, ghost_positions, pacman);// возвращает карту+ возвращает позицИИ призраков+ устанавливает позицИЮ пакмана
	ghost_manager.reset(level, ghost_positions);// (таймер на разбегание,cur_w=0 | (LONG_SCATTER_DURATION / pow(2, i_level))) ||+ у призрака movement_mode=0
	//присвоить позиции призракам, установить цель


	srand(static_cast<unsigned>(time(0)));
	std::chrono::time_point<std::chrono::steady_clock> previous_time = std::chrono::steady_clock::now();
	unsigned delta_time;

	sf::Event eventP;
	while (Play.isOpen())
	{
		if (0 == game_won && 0 == pacman.get_dead())
		{
			game_won = 1; // состояние того, что мы еще в процессе победы	СОЖРАЛИ ЛИ ВСЕ ТАБЛЕТКИ

			pacman.update(level, map); // level влияет на время действия таблетки
			ghost_manager.update(level, map, pacman);

			if (1 == pacman.get_dead())
			{
				game_won = 0;
				goto escapePelletChecking;
			}

			//We're checking every cell in the map.
			for (const std::array<Cell, MAP_HEIGHT>& column : map)
			{
				for (const Cell& cell : column)
				{
					if (Cell::Pellet == cell) //And if at least one of them has a pellet.
					{
						game_won = 0; //The game is not yet won.

						break;
					}
				}

				if (0 == game_won)
				{
					break;
				}
			}
		escapePelletChecking:

			if (1 == game_won)
			{
				pacman.set_animation_timer(0);
			}


		}

		else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //Restarting the game.
		{
			game_won = 0;

			if (1 == pacman.get_dead())
			{
				level = 0;
			}
			else
			{
				level++;
			}

			map = convert_sketch(map_sketch, ghost_positions, pacman);
			ghost_manager.reset(level, ghost_positions);
			pacman.reset();
			IsPressToStart = false;
		}

		{
			Play.clear();

			if (0 == game_won && 0 == pacman.get_dead())
			{
				draw_map(map, Play);
				ghost_manager.draw(GHOST_FLASH_START >= pacman.get_energizer_timer(), Play);

				TextForOutput.setString("Level : " + std::to_string(level));
				TextForOutput.setPosition(0, CELL_SIZE * MAP_HEIGHT);

				Play.draw(TextForOutput);
			}

			pacman.draw(game_won, Play);

			if (1 == pacman.get_animation_over())
			{
				if (1 == game_won)
				{
					TextForOutput.setString("Next  Level!");
					TextForOutput.setPosition((0.5f * (CELL_SIZE * MAP_WIDTH)) - 3 * CELL_SIZE, 0.5f * CELL_SIZE * MAP_HEIGHT);

					Play.draw(TextForOutput);

				}
				else
				{
					TextForOutput.setString("Game  over");
					TextForOutput.setPosition((0.5f * (CELL_SIZE * MAP_WIDTH)) - 3 * CELL_SIZE, 0.5f * CELL_SIZE * MAP_HEIGHT);

					Play.draw(TextForOutput);

				}
			}

			Play.display();

			if (!IsPressToStart)
			{
				sf::Event waitToStart;

				Play.pollEvent(waitToStart);
				while (waitToStart.type != sf::Event::KeyPressed)
				{
					Play.pollEvent(waitToStart);
				}
				IsPressToStart = true;
			}

		}

		delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		unsigned timeLeft = (delta_time <= FRAME_DURATION ? FRAME_DURATION - delta_time : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(timeLeft));
		previous_time = std::chrono::steady_clock::now();

		if (Play.pollEvent(eventP))// pool опрос 
		{
			if (eventP.type == sf::Event::Closed)
			{
				AttentionWindow(Play, MENU, FontForOutput);

			}

			if (eventP.type == sf::Event::KeyPressed)
			{
				if (eventP.key.code == sf::Keyboard::Escape)
				{
					AttentionWindow(Play, MENU, FontForOutput);
				}
			}


		}


		
	}
}