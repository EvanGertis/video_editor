/*
File Name: Video_editor.cpp.
Author: Evan Gertis.
Date: 03/26/2019.
Purpose: Main entry point for my video editing program.
Credit: opencv opensource project.
License: None.
*/

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
	//open the camera.
	cv::VideoCapture cap(0);
	
	//guard: if the camera isn't available -> exit.
	if (!cap.isOpened()) {
		std::cout << "Unable to open camera." << std::endl;
		exit(-1);
	}

	//storage for the captured frame.
	cv::Mat image;
	double FPS = 24.0; //set the frame rate.
	
	//camera capture loop.
	while (true) {
		cap >> image; // write the captured frame.

		//guard: if the frame is empty => throw error.
		if (image.empty()) {
			std::cout << "cannot read frame";
			break; //exit loop.
		}

		//show the video.
		cv::imshow("My video", image);

		//break on ESC key.
		if (cv::waitKey(1000.0 / FPS) == 27) {
			break; //exits the loop.
		}

	}//end capture loop.
	
}


