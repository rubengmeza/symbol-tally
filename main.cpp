#include <print>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/hal/interface.h>
#include "poppler_pdf_handler.hpp"

#include "app.hpp"

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

	App app;
	app.run();

	
    return 0;
}
