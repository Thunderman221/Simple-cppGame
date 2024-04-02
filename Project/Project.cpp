#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
// creating a window of 600 by 600 and 60 fps
sf::RenderWindow window(sf::VideoMode(600, 600), "Project");
    window.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("Calibri.ttf")) {
	
		std::cerr << "Failed to load font" << std::endl;
		return 1; 
	}

	//Text with key designations
	sf::Text text("F2 - New Game / Esc - Exit / Arrow Keys - Move Title", font, 20);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(5.f, 5.f);

	Game game;
	game.setPosition(50.f, 50.f);

    sf::Event event;
	int move_counter = 0; // Random walk counter

	while (window.isOpen())
	{
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {

				//  Sign the pressed key - perform the corresponding action
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::Left) game.Move(Direction::Left);
				if (event.key.code == sf::Keyboard::Right) game.Move(Direction::Right);
				if (event.key.code == sf::Keyboard::Up) game.Move(Direction::Up);
				if (event.key.code == sf::Keyboard::Down) game.Move(Direction::Down);
				// New Game
				if (event.key.code == sf::Keyboard::F2) {
					game.Init();
					move_counter = 100;
				}
			}
		}
		//If the move count is greater than zero, continue to shuffle the puzzle
		if (move_counter-- > 0) game.Move((Direction)(rand() % 4));

		// Performing the necessary drawing actions
		window.clear();
		window.draw(game);
		window.draw(text);
		window.display();
	}


}
