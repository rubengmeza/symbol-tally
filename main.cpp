#include <print>
#include <iostream>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-image.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-page-renderer.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/hal/interface.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// @Temporary: globals bad
poppler::document *doc = nullptr;
std::string file_path = "landscape_plans.pdf";
poppler::page *page = nullptr;

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

poppler::document * load_pdf(std::string path)
{
	doc = poppler::document::load_from_file(file_path);
    if (!doc) {
        delete doc;
    }
	else
	{
		std::println("Loaded PDF: {}", file_path);
	}

	// PDF meta data
	//std::string pdf_title = doc->get_title().to_latin1();
	//int pdf_page_count = doc->pages();
	//std::println("Document title: {}", pdf_title);
	//std::println("Document page count: {}", pdf_page_count);
	
	return doc;

}

poppler::page * process_pdf()
{
	int target_page = 6;
	page = doc->create_page(target_page);

	
	return page;
}

void create_image_from_pdf(std::string image_name)
{
	poppler::page_renderer page_renderer;
    page_renderer.set_render_hint(poppler::page_renderer::antialiasing, true);
    page_renderer.set_render_hint(poppler::page_renderer::text_antialiasing, true);
    page_renderer.set_render_hint(poppler::page_renderer::text_hinting, true);

	// pass DPI to page renderer for higher resolution image
    poppler::image img = page_renderer.render_page(page, 300, 300);
    if (!img.is_valid()) {
		std::cerr << "failed to render" << std::endl;
    }

    if (!img.save(image_name, "png")) {
		std::cerr << "failed to save image" << std::endl;
    }
	else
	{
		std::println("Image saved as: {}", image_name);
	}
}

int main() 
{
	//doc = load_pdf(file_path);
	// extract a single page
	//page = process_pdf();
	// Save as a reference image for opencv.
	//create_image_from_pdf("planting.png");
	// find the template in the reference image.
	//match("planting.png", "clj_template_4.png");	

    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window", sf::Style::None, sf::State::Windowed);
	// TODO: Keybind to load the sprite for display
	sf::Texture texture("planting.png");
	sf::Sprite sprite(texture);

	while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(sprite);

        window.display();
    }
	
    return 0;
}
