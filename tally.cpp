#include <print>
#include "tally.hpp"

// Creates new tally with radius 5.
Tally::Tally(): name(" ")
{
	std::println("New tally created without a name.");
}

// Creates new tally with radius 5.
Tally::Tally(std::string name): name(name)
{
	std::println("New tally created with name: {}", name);
}

void Tally::increment(sf::RenderWindow &window, const sf::Event::MouseButtonPressed *mouse_button_pressed)
{
	mark_up.setRadius(300);
	mark_up.setPointCount(30);
	mark_up.setFillColor(sf::Color::Red);
	sf::Vector2f mouse_position = window.mapPixelToCoords(mouse_button_pressed->position);
	mark_up.setPosition(mouse_position);
}

std::string Tally::get_name()
{
	return name;
}

sf::CircleShape Tally::get_mark_up()
{
	return mark_up;
}
