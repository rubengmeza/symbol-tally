#include <print>
#include "../include/tally.hpp"

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
	mark_up.setOrigin({10, 10});
	sf::Vector2f mouse_position = window.mapPixelToCoords(mouse_button_pressed->position);
	mark_up.setPosition(mouse_position);
	mark_ups.push_back(mark_up);
	count++;
}

void Tally::find_template_match(std::string filename, std::string templatename)
{
	cv::Mat ref = cv::imread(filename);
	cv::Mat tpl = cv::imread(templatename);
    if (ref.empty() || tpl.empty())
    {
		std::println("Error reading file(s)!");
    }
	std::println("Searching for matches...");

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
			sf::Vector2f center(maxloc.x + tpl.cols / 2.0f, maxloc.y + tpl.rows / 2.0f);
			add_template_match(center);
			//cv::rectangle(ref, maxloc, cv::Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows), CV_RGB(0,255,0), 2);
			cv::floodFill(res, maxloc, 0); //mark drawn blob
        }
        else
            break;
    }

	//cv::imshow("final", ref);
	//cv::waitKey(0);
	
	// save marked up image
	//cv::imwrite("result.png", ref);
}

void Tally::add_template_match(sf::Vector2f position)
{
	std::println("Template match added to: {}", get_name());
	mark_up.setRadius(10);
	mark_up.setPointCount(30);
	mark_up.setFillColor(sf::Color::Red);
	mark_up.setOrigin({10, 10});
	mark_up.setPosition(position);
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
