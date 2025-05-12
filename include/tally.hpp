#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/hal/interface.h>

class Tally
{
private:
	sf::CircleShape mark_up; // @DUMB: Don't think this needs to be a member variable. Pushing copies into vector anyway...
	std::vector<sf::CircleShape> mark_ups;
	std::string name;
	int count;
public:
	Tally();
	Tally(std::string name);

	void increment(sf::RenderWindow &window, const sf::Event::MouseButtonPressed *mouse_button_pressed, const Tally &current_tally);
	void find_template_match(std::string filename, std::string templatename);
	void add_template_match(sf::Vector2f position);
	std::string get_name() const;
	int get_count() const;
	std::vector<sf::CircleShape> get_mark_ups();
};
