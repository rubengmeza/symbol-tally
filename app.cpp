#include <print>
#include <iostream>
#include "app.hpp"

App::App() 
{
	window.create(sf::VideoMode({800, 600}), "Symbol Tally: Simple CD Take offs", sf::Style::None, sf::State::Windowed);
	should_quit_app = false;
}

void App::run()
{
	load_image("planting.png"); // Load image as texture.
	sf::Sprite image(texture);

	Tally tally("plant");
	// Image should be zoomed out completely when first opened.
	sf::FloatRect image_bounds = image.getGlobalBounds();
	sf::View view({image_bounds.size.x / 2, image_bounds.size.y / 2}, {image_bounds.size.x, image_bounds.size.y});

	// Track if holding mouse button down.
	sf::Vector2f drag_offset;
	bool dragging = false;

	while (!should_quit_app)
	{
		get_user_input(image, tally, view, drag_offset, dragging);
		render(image, view);
	}
}

void App::get_user_input(sf::Sprite &image, Tally tally, sf::View &view, sf::Vector2f &drag_offset, bool &dragging)
{

	while (const std::optional event = window.pollEvent())
	{
		// @FEATURE: Reset view.
		if (event->is<sf::Event::Closed>())
		{
			window.close();
			should_quit_app = true;
		}
		else if (const auto *key_press = event->getIf<sf::Event::KeyPressed>())
		{
		}
		else if (const auto *mouse_button_pressed = event->getIf<sf::Event::MouseButtonPressed>())
		{
			if (mouse_button_pressed->button == sf::Mouse::Button::Left)
			{
				// Convert click position to float. 
				sf::Vector2f mouse_position = window.mapPixelToCoords(mouse_button_pressed->position);

				// Only work if mouse is on the image.
				if (image.getGlobalBounds().contains(mouse_position)) 
				{
					dragging = true;
					// Offset is from top left corner of image.
					drag_offset = mouse_position - image.getPosition();
				}
			}
			else if (mouse_button_pressed->button == sf::Mouse::Button::Right)
			{
				tally.increment(window, mouse_button_pressed);
				take_offs.push_back(tally);
			}
		}
		else if (const auto *mouse_button_released = event->getIf<sf::Event::MouseButtonReleased>())
		{
			if (mouse_button_released->button == sf::Mouse::Button::Left)
			{
				dragging = false;
			}
		}
		else if (const auto *mouse_moved = event->getIf<sf::Event::MouseMoved>()) 
		{
			if (dragging) 
			{
				sf::Vector2f mouse_position = window.mapPixelToCoords(mouse_moved->position);
				// @BETTER: This moves the image itself. May make more sense to move the camera instead? 
				// Make sure image follows mouse. 
				image.setPosition(mouse_position - drag_offset);
			}
		}
		else if (const auto *mouse_wheel_scrolled = event->getIf<sf::Event::MouseWheelScrolled>())
		{
			if (mouse_wheel_scrolled->wheel == sf::Mouse::Wheel::Vertical)
			{
				// change view when scrolling.
				view.zoom(1.0f + mouse_wheel_scrolled->delta * 0.1f);
			}
		}
	}
}

void App::render(sf::Sprite &image, sf::View view)
{
	window.clear(sf::Color::Black);
	window.setView(view);

	window.draw(image);
	for (auto t : take_offs)
	{
		window.draw(t.get_mark_up());
	}

	window.display();
}

// @RESILIENCE: If starting a new take off, will the user be able to just load another image? Or does this method imply restarting app to begin new project.
void App::load_image(std::string path)
{
	if (texture.loadFromFile(path))
	{
		std::println("Texture created from file: {}", path);
	}
	else
	{
		std::cerr << "Failed to create texture from file: " << path << std::endl;
	}
}
