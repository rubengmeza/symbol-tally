#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "tally.hpp"

class App
{
private:
	sf::RenderWindow window;
	bool should_quit_app;
	sf::Texture texture;
	Tally current_tally;

	std::vector<Tally> take_offs;
public:
	App();
	void run();
	void get_user_input(sf::Sprite &image, Tally tally, sf::View &view, sf::Vector2f &drag_offset, bool &dragging);
	void render(sf::Sprite &image, sf::View view);

	void load_image(std::string path);
	Tally create_take_off();
};
