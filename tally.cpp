#include <print>
#include "tally.hpp"

// Creates new tally with radius 5.
Tally::Tally(): name(" "), count(0)
{
	std::println("New tally created without a name.");
}

// Creates new tally with radius 5.
Tally::Tally(std::string name): name(name), count(0)
{
	std::println("New tally created with name: {}", name);
}

//@BETTER: Pass the mouse position instead of the actual event?
void Tally::increment(sf::RenderWindow &window, const sf::Event::MouseButtonPressed *mouse_button_pressed, const Tally &current_tally)
{
	std::println("Tally added to: {}", current_tally.get_name());
	mark_up.setRadius(10);
	mark_up.setPointCount(30);
	mark_up.setFillColor(sf::Color::Red);
	sf::Vector2f mouse_position = window.mapPixelToCoords(mouse_button_pressed->position);
	mark_up.setPosition(mouse_position);
	mark_ups.push_back(mark_up);
	count++;
}

std::string Tally::get_name() const
{
	return name;
}

int Tally::get_count() const
{
	return count;
}

std::vector<sf::CircleShape> Tally::get_mark_ups()
{
	return mark_ups;
}
