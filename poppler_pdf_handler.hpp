#pragma once

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-image.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-page-renderer.h>

class Poppler_Pdf_Handler
{
private:
	poppler::document *doc = nullptr;
	poppler::page *page = nullptr;
// Default constructor
public:
	poppler::document * load_pdf(std::string path);
	poppler::page * process_pdf();
	void create_image_from_pdf(std::string image_name);
};
