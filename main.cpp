#include <print>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/hal/interface.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "poppler_pdf_handler.hpp"
#include "tally.hpp"

int match(std::string filename, std::string templatename)
{
	cv::Mat ref = cv::imread(filename);
	cv::Mat tpl = cv::imread(templatename);
    if (ref.empty() || tpl.empty())
    {
		std::println("Error reading file(s)!");
        return -1;
    }

	//cv::imshow("file", ref);
	//cv::imshow("template", tpl);

	// matchTemplate use: from samples at github.
	cv::Mat res_32f(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1);
	cv::matchTemplate(ref, tpl, res_32f, cv::TM_CCOEFF_NORMED);

	cv::Mat res;
    res_32f.convertTo(res, CV_8U, 255.0);
	//cv::imshow("result", res);

    int size = ((tpl.cols + tpl.rows) / 4) * 2 + 1; //force size to be odd
	cv::adaptiveThreshold(res, res, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, size, -128);
	//cv::imshow("result_thresh", res);

    while (true) 
    {
        double minval, maxval, threshold = 0.8;
		cv::Point minloc, maxloc;
        minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

        if (maxval >= threshold)
        {
			cv::rectangle(ref, maxloc, cv::Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows), CV_RGB(0,255,0), 2);
			cv::floodFill(res, maxloc, 0); //mark drawn blob
        }
        else
            break;
    }

	//cv::imshow("final", ref);
	//cv::waitKey(0);
	
	// save marked up image
	cv::imwrite("result.png", ref);

    return 0;
}



int main() 
{
	// Convert PDF to an image for manipulation
	//Poppler_Pdf_Handler pdf_handler;
	//pdf_handler.load_pdf("landscape_plans.pdf");
	//pdf_handler.process_pdf();
	//pdf_handler.create_image_from_pdf("planting.png");

	// TODO: OpenCV stuff
	// find the template in the reference image.
	//match("planting.png", "clj_template_4.png");	

    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window", sf::Style::None, sf::State::Windowed);
	// TODO: Keybind to load the sprite for display
	sf::Texture texture("planting.png");
	sf::Sprite sprite(texture);
	// show entire image when opened.
	sf::FloatRect sprite_bounds = sprite.getGlobalBounds();
	sf::View view({sprite_bounds.size.x / 2, sprite_bounds.size.y / 2}, {sprite_bounds.size.x, sprite_bounds.size.y});
	// Track if holding mouse button down.
	sf::Vector2f drag_offset;
	bool dragging = false;

	Tally tally("plant");
	// @QUESTIONABLE: Can this container be pointers? or references? 
	std::vector<Tally> take_offs;

	while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
			// @FEATURE: Reset view.
            if (event->is<sf::Event::Closed>())
			{
                window.close();
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
                    if (sprite.getGlobalBounds().contains(mouse_position)) {
                        dragging = true;
						// Offset is from top left corner of image.
                        drag_offset = mouse_position - sprite.getPosition();
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
					sprite.setPosition(mouse_position - drag_offset);
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
        window.clear(sf::Color::Black);

		window.setView(view);

        window.draw(sprite);
		for (auto t : take_offs)
		{
			window.draw(t.get_mark_up());
		}


        window.display();
    }
	
    return 0;
}
