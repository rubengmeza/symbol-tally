#include <print>
#include <iostream>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-image.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-page-renderer.h>

int main() 
{
	std::string file_path = "landscape_plans.pdf";
	poppler::document *doc = nullptr;
	doc = poppler::document::load_from_file(file_path);
    if (!doc) {
        delete doc;
    }
	else
	{
		std::println("Loaded PDF: {}", file_path);
	}

	std::string pdf_title = doc->get_title().to_latin1();
	int pdf_page_count = doc->pages();
	std::println("Document title: {}", pdf_title);
	std::println("Document page count: {}", pdf_page_count);

	// extract a single page
	int target_page = 6;
    poppler::page *page = nullptr;
	page = doc->create_page(target_page);

	poppler::page_renderer page_renderer;
    page_renderer.set_render_hint(poppler::page_renderer::antialiasing, true);
    page_renderer.set_render_hint(poppler::page_renderer::text_antialiasing, true);

    poppler::image img = page_renderer.render_page(page);
    if (!img.is_valid()) {
		std::cerr << "failed to render" << std::endl;
    }

    if (!img.save("planting.png", "png")) {
		std::cerr << "failed to save image" << std::endl;
    }

    return 0;
}

