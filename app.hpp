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

	std::vector<Tally> take_offs;

	// Track if holding mouse button down.
	sf::Vector2f last_mouse_position;
	bool is_dragging = false;
public:
	App();
	void run();
	void get_user_input(sf::Sprite &image, sf::View &view, sf::Vector2f &last_mouse_position, bool &is_dragging);
	void render(sf::Sprite &image, sf::View view);

	// Image stuff.
	void load_image(std::string path);
	void drag_image(sf::View &view, bool is_dragging, const sf::Vector2f &last_mouse_position, const sf::Vector2f &mouse_position);
	void zoom_image(sf::View &view, const sf::Event::MouseWheelScrolled *mouse_wheel_scrolled);

	void create_take_off();
	void print_take_offs();
};
