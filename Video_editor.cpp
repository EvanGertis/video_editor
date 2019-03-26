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
#include <windows.h>

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
	cv::Mat imageBefore;
	cv::Mat imageAfter;
	double FPS = 36.0; //set the frame rate.
	
	//******************************************
	//******************************************
	//******************************************
	//BEGIN VIDEO EDITING VARS
	int width = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_WIDTH)); // stores the frame width.
	int height = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_HEIGHT)); // stores the frame height.

	//open a video file for writing, file type mp4.
	cv::VideoWriter out("output.mov", CV_FOURCC('m', 'p', '4', 'v'), FPS, cv::Size(width, height), true);

	//guard: if we can't write to the file then throw error.
	if (!out.isOpened()) {
		std::cout << "cannot open file for writing" << std::endl;
		std::exit(-1);
	}

	//******************************************
	//******************************************
	//******************************************


	//camera capture loop.
	while (true) {
		cap >> imageBefore; // write the captured frame.

		//guard: if the frame is empty => throw error.
		if (imageBefore.empty()) {
			std::cout << "cannot read frame";
			break; //exit loop.
		}
		//wait exactly one second.
		Sleep(1000);

		cap >> imageAfter; // write the captured frame.

		//guard: if the frame is empty => throw error.
		if (imageAfter.empty()) {
			std::cout << "cannot read frame";
			break; //exit loop.
		}


		//**********************************
		//**********************************
		//DIFFERENCE LOGIC
		cv::Mat imageDifference;//storage container for image difference.

		//calculate the absolute difference between images.
		cv::absdiff(imageBefore, imageAfter, imageDifference);

		//calculation parameters.
		cv::Mat foregroundMask = cv::Mat::zeros(imageDifference.rows, imageDifference.cols, CV_8UC1);
		float threshold = 65.0f;
		float dist;

		for (int i = 0; i < imageDifference.rows; ++i) {
			for (int j = 0; j < imageDifference.cols; ++j) {
				cv::Vec3b pix = imageDifference.at<cv::Vec3b>(i, j);

				dist = (pix[0] * pix[0] + pix[1] * pix[1] * pix[1] + pix[2] * pix[2] * pix[2]);
				dist = sqrt(dist);

				if (dist > threshold) {
					foregroundMask.at<unsigned char>(i, j) = 255;
				}
			}
		}

		//show the video.
		cv::imshow("My video", foregroundMask);

		//**********************************
		//**********************************
		//**********************************

		//write the image to the video file.
		out << foregroundMask;

		//break on ESC key.
		if (cv::waitKey(1000.0 / FPS) == 27) {
			break; //exits the loop.
		}

	}//end capture loop.
	
}


