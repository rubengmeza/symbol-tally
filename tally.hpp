#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Tally
{
private:
	sf::CircleShape mark_up;
	std::string name;
public:
	Tally();
	Tally(std::string name);

	void increment(sf::RenderWindow &window, const sf::Event::MouseButtonPressed *mouse_button_pressed);
	std::string get_name();
	sf::CircleShape get_mark_up();
};
