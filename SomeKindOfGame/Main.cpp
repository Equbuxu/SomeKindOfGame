#include <SFML/Graphics.hpp>
#include "Location.h"
#include "Room.h"
#include "LocManager.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(780, 600), "SomeKindOfGame", sf::Style::Titlebar | sf::Style::Close);
	sf::View view(sf::Vector2f(390, 300), sf::Vector2f(780, 600));

	window.setView(view);
	window.setFramerateLimit(60);

	sf::Image icon;
	icon.loadFromFile("icon.png");

	window.setIcon(32,32,icon.getPixelsPtr());


	LocManager manager;
	
	

	sf::Clock elapsed;
	sf::Time thetime;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		static int frameCounter = 0;
		static int fps = 0;
		frameCounter++;
		thetime = elapsed.getElapsedTime();
		if (thetime.asMilliseconds() > 999)
		{
			fps = frameCounter;
			frameCounter = 0;
			elapsed.restart();
			std::cout << fps << std::endl;
		}

		manager.Update();
		manager.Draw(window, view);

		window.display();
	}

	return 0;
}