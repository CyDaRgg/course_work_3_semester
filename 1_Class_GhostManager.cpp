#include"_1_Class_GhostManager.h"

GhostManager::GhostManager():
	current_wave(0),
	wave_timer(LONG_SCATTER_DURATION),
	ghosts({ Ghost(0), Ghost(1), Ghost(2), Ghost(3) })
{

}

void GhostManager::update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman& i_pacman)
{
	//если съел, то то просто обработка призраков
	 //если нет, то контролирующиеся волны
	if (0 == i_pacman.get_energizer_timer()) //We won't update the wave timer when Pacman is energized.
	{
		if (0 == wave_timer)
		{
			if (7 > current_wave)
			{
				current_wave++;

				for (Ghost& ghost : ghosts)
				{                          // cur   mov_m
					ghost.switch_mode();   // 0->1  0->1     2n+1 || 1
				}
			}

			//I took the rules from the website.
			if (1 == current_wave % 2)  // на 1 3 5 7 волнах 
			{
				wave_timer = CHASE_DURATION; // 1024
			}
			else if (2 == current_wave) // на 2 
			{
				wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, i_level));// 512/2^level
			}
			else //4 6
			{
				wave_timer = static_cast<unsigned short>(SHORT_SCATTER_DURATION / pow(2, i_level));// 256/2^level
			}
		}
		else
		{
			wave_timer--;
		}
	}

	for (Ghost& ghost : ghosts)
	{
		if (1 == i_pacman.get_dead()) { continue; }
		ghost.update(i_level, i_map, ghosts[0], i_pacman);
	}
}
void GhostManager::draw(bool i_flash, sf::RenderWindow& i_window)
{
	for (Ghost& ghost : ghosts)
	{
		ghost.draw(i_flash, i_window);
	}
}
void GhostManager::reset(unsigned char i_level, const std::array<SimpleObject::Position, 4>& i_ghost_positions)
{
	current_wave = 0;

	//This is how we're increasing the difficulty.
	wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, i_level));

	for (unsigned char a = 0; a < 4; a++)
	{
		ghosts[a].set_position(i_ghost_positions[a].x, i_ghost_positions[a].y);
	}

	for (Ghost& ghost : ghosts)
	{
		//We use the blue ghost to get the location of the house and the red ghost to get the location of the exit.
		ghost.reset(ghosts[2].get_position(), ghosts[0].get_position());
	}
}
