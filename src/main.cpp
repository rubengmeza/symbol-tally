#include <print>
#include <iostream>
#include "../include/poppler_pdf_handler.hpp"

#include "../include/app.hpp"

int main() 
{
	// Convert PDF to an image for manipulation
	Poppler_Pdf_Handler pdf_handler;
	pdf_handler.load_pdf("example/landscape_plans.pdf");
	pdf_handler.process_pdf();
	pdf_handler.create_image_from_pdf("example/planting.png");

	// TODO: OpenCV stuff
	// find the template in the reference image.
	//match("planting.png", "clj_template_4.png");	

	App app;
	app.run();

	
    return 0;
}
