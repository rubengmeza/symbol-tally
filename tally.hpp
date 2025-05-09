#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Tally
{
private:
	sf::CircleShape mark_up; // @DUMB: Don't think this needs to be a member variable. Pushing copies into vector anyway...
	std::vector<sf::CircleShape> mark_ups;
	std::string name;
public:
	Tally();
	Tally(std::string name);

	void increment(sf::RenderWindow &window, const sf::Event::MouseButtonPressed *mouse_button_pressed, const Tally &current_tally);
	std::string get_name() const;
	std::vector<sf::CircleShape> get_mark_ups();
};
