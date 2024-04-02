#include "Game.h"
Game::Game() {
	// Loading font for rendering elements
	font.loadFromFile("calibri.ttf");
	Init();
}

void Game::Init() {
	// Fill the array of dies
	for (int i = 0; i < ARRAY_SIZE - 1; i++) elements[i] = i + 1;
	// Place an empty die in the lower right position
	empty_index = ARRAY_SIZE - 1;
	elements[empty_index] = 0; // Пустаю плашка имеет значение = 0
	solved = true;
}

bool Game::Check() {
	// Checking the assembly of the puzzle
	for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
		if (elements[i] > 0 && elements[i] != i + 1) return false;
	}
	return true;
}
 
void Game::Move(Direction direction) {
	// Calculate the row and column of an empty die
	int col = empty_index % SIZE;
	int row = empty_index / SIZE;

	// Checking whether the die can be moved and calculating the index of the moved die
	int move_index = -1;
	if (direction == Direction::Left && col < (SIZE - 1))move_index = empty_index + 1;
	if (direction == Direction::Right && col > 0) move_index = empty_index - 1;
	if (direction == Direction::Up && row < (SIZE - 1)) move_index = empty_index + SIZE;
	if (direction == Direction::Down && row > 0) move_index = empty_index - SIZE;

	// Moving a die in place of an empty die
	if (empty_index >= 0 && move_index >= 0) {
		int tmp = elements[empty_index];
		elements[empty_index] = elements[move_index];
		elements[move_index] = tmp;
		empty_index = move_index;
	}
	solved = Check();
}
void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	states.transform *= getTransform();
	sf::Color color = sf::Color(200, 100, 200);

	// Drawing of the playing field frame
	sf::RectangleShape shape(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);

	// Preparing the frame for rendering all strips
	shape.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	// Preparation of a text blank for drawing of bar numbers
	sf::Text text(" ", font, 52);

	for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
		shape.setOutlineColor(color);
		text.setFillColor(color);
		text.setString(std::to_string(elements[i]));
		if (solved) {
			// The solved puzzle is highlighted in a different color
			shape.setOutlineColor(sf::Color::Cyan);
			text.setFillColor(sf::Color::Cyan);
		}
		else if (elements[i] == i + 1) {
			//The numbers of the strips in their places are highlighted in a different color
			text.setFillColor(sf::Color::Green);
		}
		// Drawing of all strips, except for the empty one
		if (elements[i] > 0) {
			// Calculating the cloak position for rendering
			sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f);
			shape.setPosition(position);
			// The position of the text was selected manually
			text.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f);
			target.draw(shape, states);
			target.draw(text, states);
		}

		
	}
}
