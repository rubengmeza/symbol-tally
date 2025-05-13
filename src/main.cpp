#include <print>
#include <iostream>
//#include "../include/poppler_pdf_handler.hpp"

#include "../include/app.hpp"

// Poppler does not play nice with windows. Disabled for turn in purposes. Image already generated and app will work as intended.
int main() 
{
	// Convert PDF to an image for manipulation
	//Poppler_Pdf_Handler pdf_handler;
	//pdf_handler.load_pdf("../example/landscape_plans.pdf");
	//pdf_handler.process_pdf();
	//pdf_handler.create_image_from_pdf("../example/planting.png");

	App app;
	app.run();

	
    return 0;
}
