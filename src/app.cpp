#include <print>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "../include/app.hpp"

// Prevent keyboard events in main loop while typing in a tally name.
enum Mode
{
	TALLY,
	INPUT
};
Mode current_mode = Mode::TALLY;

// Basic app setup.
App::App() 
{
	window.create(sf::VideoMode({1200, 1000}), "Symbol Tally: Easy CD Take offs", sf::Style::None, sf::State::Windowed);

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2u windowSize = window.getSize();
	sf::Vector2i centeredPosition(desktop.size.x / 2 - windowSize.x / 2, desktop.size.y / 2 - windowSize.y / 2);
	window.setPosition(centeredPosition);

	should_quit_app = false;
}

void App::run()
{
	load_image("../example/planting.png"); // Load image as texture.
	sf::Sprite image(texture);

	// Image should be zoomed out completely when first opened.
	sf::FloatRect image_bounds = image.getGlobalBounds();
	sf::View view({image_bounds.size.x / 2, image_bounds.size.y / 2}, {image_bounds.size.x, image_bounds.size.y});

	print_usage();

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
		if (event->is<sf::Event::Closed>())
		{
			window.close();
			should_quit_app = true;
		}
		else if (const auto *key_press = event->getIf<sf::Event::KeyPressed>())
		{
			// Using Mode to prevent keyboard events while typing names of new take offs.
			if (current_mode == Mode::TALLY)
			{
				if (key_press->code == sf::Keyboard::Key::N)
				{
					current_mode = Mode::INPUT;
					create_take_off();
				}
				else if (key_press->code == sf::Keyboard::Key::S) 
				{
					if (take_offs.size() > 0)
					{
						Tally &current_tally = take_offs.back();
						current_tally.find_template_match("../example/planting.png", "../example/clj_template.png");
					}
					else 
					{
						std::println("You must create a new take off.");
						std::println("Press 'N' to start a new take off.");
					}
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
				else if (key_press->code == sf::Keyboard::Key::E) 
				{
					export_take_offs();
				}
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
				// Prevent tally incrementing when there aren't any take offs in the vector.
				if (take_offs.size() > 0)
				{
					Tally &current_tally = take_offs.back();
					current_tally.increment(window, mouse_button_pressed, current_tally);
				}
				else
				{
					std::println("You must create a new take off.");
					std::println("Press 'N' to start a new take off.");
				}

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

void App::print_usage()
{
	std::println("--------------Program Usage-----------------");
	std::println("");
	std::println("This is a simple take off program.");
	std::println("You can move the view with a click and drag motion. You can also zoom with the mouse scroll wheel.");
	std::println("");
	std::println("--------------------------------------------");
	std::println("");
	std::println("To begin counting material, press 'N'. This will create a new take off.");
	std::println("You will be prompted to enter a name for the take off. It is common practice to use the name found on the legend for clarity.");
	std::println("You can then begin counting the symbols for the specified material. Once all symbols have been marked, you can then press 'N' again to begin on the next take off.");
	std::println("When you have finished all your take offs, press 'E' to save and export your counted materials to the file.");
	std::println("");
	std::println("--------------------------------------------");
}

void App::load_image(std::string path)
{
	if (texture.loadFromFile(path))
	{
		std::println("Texture created from file: {}", path);
	}
	else
	{
		std::cerr << "Failed to create texture from file: " << path << std::endl;
		exit(EXIT_FAILURE);
	}
}

void App::create_take_off()
{
	std::string name;
	std::println("Enter name: ");
	std::cin >> name;
	
	Tally tally(name);
	take_offs.push_back(tally);

	// Reset mode to allow input events.
	current_mode = Mode::TALLY;
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

void App::export_take_offs()
{
	std::string file_name = "my_take_offs.txt";
	std::ofstream output_file;
	output_file.open(file_name);
	std::println("File created: {}", file_name);

	std::string name = "default";
	int count = 0;
	for (int i = 0; i < take_offs.size(); i++)
	{
		name = take_offs[i].get_name();
		count = take_offs[i].get_count();
		output_file << name << ": " << count << "\n";
	}

	std::println("Take offs exported to file {}.", file_name);
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

