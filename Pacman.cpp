#include"Pacman.h"

Pacman::Pacman()
{
	animation_over = 0;
	dead = 0;
	energizer_timer = 0;

	direction = 1;
	position.x=0, position.y=0;
	
}


bool Pacman::get_dead()
{
	return dead;
}
void Pacman::set_dead(bool i_dead)
{
	dead = i_dead;
}

unsigned short Pacman::get_energizer_timer()
{
	return energizer_timer;
}
void Pacman::set_energizer_timer(unsigned short energ_tim)
{
	energizer_timer = energ_tim;
}

bool Pacman::get_animation_over()
{
	return animation_over;
}
void Pacman::set_animation_over(bool an_tim)
{
	animation_over = an_tim;
}

void Pacman::reset()
{
	dead = 0;
	animation_over = 0;
	energizer_timer = 0;

	direction = 1;
	animation_timer = 0;

}
void Pacman::draw(bool i_victory, sf::RenderWindow& i_window) 
{
	unsigned char frame = static_cast<unsigned char>(floor(animation_timer / static_cast<float>(PACMAN_ANIMATION_SPEED)));// 0->24 /4

	sf::Sprite sprite;

	sf::Texture texture;

	sprite.setPosition(position.x, position.y);

	if (1 == dead || 1 == i_victory)
	{
		if (animation_timer < PACMAN_DEATH_FRAMES * PACMAN_ANIMATION_SPEED) // 12*4
		{
			animation_timer++;

			texture.loadFromFile("Resources/Images/PacmanDeath" + std::to_string(CELL_SIZE) + ".png");

			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(CELL_SIZE * frame, 0, CELL_SIZE, CELL_SIZE));

			i_window.draw(sprite);
		}
		else
		{
			//You can only die once.
			animation_over = 1;
		}
	}
	else
	{
		texture.loadFromFile("Resources/Images/Pacman" + std::to_string(CELL_SIZE) + ".png");

		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(CELL_SIZE * frame, CELL_SIZE * direction, CELL_SIZE, CELL_SIZE));

		i_window.draw(sprite);

		animation_timer = (1 + animation_timer) % (PACMAN_ANIMATION_FRAMES * PACMAN_ANIMATION_SPEED); // 6*4
	}
}
void Pacman::update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
	//анализ стен
	//проверка кнопок
	//изменение координат пакмана в зависимости от стен и направления
	//проход по тунелю
	//обработка таблеток и пилюли
	//обработка таймера энергии
	std::array<bool, 4> walls{};
	walls[0] = map_collision(CollectPellets::No, I_Use_Door::No_, PACMAN_SPEED + position.x, position.y, i_map);
	walls[1] = map_collision(CollectPellets::No, I_Use_Door::No_, position.x, position.y - PACMAN_SPEED, i_map);
	walls[2] = map_collision(CollectPellets::No, I_Use_Door::No_, position.x - PACMAN_SPEED, position.y, i_map);
	walls[3] = map_collision(CollectPellets::No, I_Use_Door::No_, position.x, PACMAN_SPEED + position.y, i_map);

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (0 == walls[0]) //You can't turn in this direction if there's a wall there.
		{
			direction = 0;// pacman moves right for default (it implements in the pacman class)
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (0 == walls[1])
		{
			direction = 1;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (0 == walls[2])
		{
			direction = 2;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (0 == walls[3])
		{
			direction = 3;
		}
	}

	if (0 == walls[direction])//if not  the button, then it's necessary check
	{
		switch (direction)
		{
		case 0:
		{
			position.x += PACMAN_SPEED;

			break;
		}
		case 1:
		{
			position.y -= PACMAN_SPEED;

			break;
		}
		case 2:
		{
			position.x -= PACMAN_SPEED;

			break;
		}
		case 3:
		{
			position.y += PACMAN_SPEED;
			break;
		}
		}
		//}
//////////////////////////////////////////////////////////////////boarder/////////
		if (-CELL_SIZE >= position.x)     //  -1|0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 | 21
			//    |                                                     |
		{
			position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
		}
		else if (CELL_SIZE * MAP_WIDTH <= position.x)
		{
			position.x = PACMAN_SPEED - CELL_SIZE;
		}
		/////////////////////////////////////////////////////////////////////////////////////


		if (1 == map_collision(1, 0, position.x, position.y, i_map)) //When Pacman eats an energizer...
		{
			//He becomes energized!
			energizer_timer = static_cast<unsigned short>(ENERGIZER_DURATION / pow(2, i_level));
		}
		else
		{
			energizer_timer = std::max(0, energizer_timer - 1);
			//energizer_timer = 0;
			/*template<class T>
				const T& max(const T & a, const T & b)
			{
				return (a < b) ? b : a;
			}*/
		}
	}
}

