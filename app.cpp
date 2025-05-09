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

	// Image should be zoomed out completely when first opened.
	sf::FloatRect image_bounds = image.getGlobalBounds();
	sf::View view({image_bounds.size.x / 2, image_bounds.size.y / 2}, {image_bounds.size.x, image_bounds.size.y});

	while (!should_quit_app)
	{
		get_user_input(image, view, last_mouse_position, is_dragging);
		render(image, view);
	}
}

void App::get_user_input(sf::Sprite &image, sf::View &view, sf::Vector2f &last_mouse_position, bool &is_dragging)
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
			if (key_press->code == sf::Keyboard::Key::N)
			{
				create_take_off();
			}
			// @DEBUGGING: 
			else if (key_press->code == sf::Keyboard::Key::T) 
			{
				std::println("Size of take_off list: {}", take_offs.size());
				int count = 0;
				for (auto &take_off : take_offs)
				{
					for (auto &mark_up : take_off.get_mark_ups())
					{
						count++;
					}

				}
				std::println("Size of mark_ups list: {}", count);
			}
			else if (key_press->code == sf::Keyboard::Key::P) 
			{
				print_take_offs();
			}
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
					is_dragging = true;
					// Offset is from top left corner of image.
					last_mouse_position = mouse_position;
				}
			}
			else if (mouse_button_pressed->button == sf::Mouse::Button::Right)
			{
				Tally &current_tally = take_offs.back();
				current_tally.increment(window, mouse_button_pressed, current_tally);
			}
		}
		else if (const auto *mouse_button_released = event->getIf<sf::Event::MouseButtonReleased>())
		{
			if (mouse_button_released->button == sf::Mouse::Button::Left)
			{
				is_dragging = false;
			}
		}
		else if (const auto *mouse_moved = event->getIf<sf::Event::MouseMoved>()) 
		{
			// Moving the image.
			sf::Vector2f mouse_position = window.mapPixelToCoords(mouse_moved->position);
			drag_image(view, is_dragging, last_mouse_position, mouse_position);
		}
		else if (const auto *mouse_wheel_scrolled = event->getIf<sf::Event::MouseWheelScrolled>())
		{
			if (mouse_wheel_scrolled->wheel == sf::Mouse::Wheel::Vertical)
			{
				zoom_image(view, mouse_wheel_scrolled);
			}
		}
	}
}

void App::render(sf::Sprite &image, sf::View view)
{
	window.clear(sf::Color::Black);
	window.setView(view);

	window.draw(image);
	for (auto &t : take_offs)
	{
		for (auto &m : t.get_mark_ups())
		{
			window.draw(m);
		}
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

void App::create_take_off()
{
	std::string name;
	std::println("Enter name: ");
	std::cin >> name;
	Tally tally(name);
	take_offs.push_back(tally);
} 

void App::print_take_offs()
{
	std::string name = "default";
	int count = 0;

	std::println("Take Offs");
	for (int i = 0; i < take_offs.size(); i++)
	{
		name = take_offs[i].get_name();
		count = take_offs[i].get_count();
		std::println("{}: {}", name, count);
	}
}

void App::drag_image(sf::View &view, bool is_dragging, const sf::Vector2f &last_mouse_position, const sf::Vector2f &mouse_position)
{
	if (is_dragging) 
	{
		auto delta = last_mouse_position - mouse_position;
		view.move(delta);
	}
}

void App::zoom_image(sf::View &view, const sf::Event::MouseWheelScrolled *mouse_wheel_scrolled)
{
	// These numbers pulled from sfml example.
	view.zoom(1.0f + mouse_wheel_scrolled->delta * 0.1f);
}

