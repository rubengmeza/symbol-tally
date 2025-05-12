#include <print>
#include <iostream>
#include "../include/poppler_pdf_handler.hpp"

poppler::document * Poppler_Pdf_Handler::load_pdf(std::string path)
{
	doc = poppler::document::load_from_file(path);
    if (!doc) {
        delete doc;
    }
	else
	{
		std::println("Loaded PDF: {}", path);
	}

	return doc;

}

poppler::page * Poppler_Pdf_Handler::process_pdf()
{
	int target_page = 6;
	page = doc->create_page(target_page);
	
	return page;
}

void Poppler_Pdf_Handler::create_image_from_pdf(std::string image_name)
{
	poppler::page_renderer page_renderer;
    page_renderer.set_render_hint(poppler::page_renderer::antialiasing, true);
    page_renderer.set_render_hint(poppler::page_renderer::text_antialiasing, true);
    page_renderer.set_render_hint(poppler::page_renderer::text_hinting, true);

	std::println("Processing PDF...");
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

