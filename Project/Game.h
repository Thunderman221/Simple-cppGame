#pragma once
#include<SFML/Graphics.hpp>



const int SIZE = 4;                                //  Size of the playing field in tiles
const int ARRAY_SIZE = SIZE * SIZE;                // Array size
const int  FIELD_SIZE = 500;                       // Size of the playing field in pixels
const int CELL_SIZE = 120;                         // Plot size in pixels

enum class Direction { Left = 0, Right = 1, Up = 2, Down = 3 };

class Game : public sf::Drawable, public sf::Transformable
{
protected:
	int elements[ARRAY_SIZE];
	int empty_index;
	bool solved;
	sf::Font font;
public:
	Game();
	void Init();
	bool Check();
	void Move(Direction direction);
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;
};

