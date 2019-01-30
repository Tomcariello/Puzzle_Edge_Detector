// functions.h : include file for functions related to puzzle piece edge detection workflow

#pragma once

//#include <stdio.h>
//#include <tchar.h>
# include <iostream>
#include <string>

// Include OpenCV Headers
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

// Declare all functions
void checkForPieces();
void getPiece();
void positionPiece();
void takePicture();
void getImage();
void detectEdges(std::string filenameUnused);
void stopProcessing();

int loopCount = 0;


// Check to see if there are any additional pieces    
void checkForPieces() {
		
	std::cout << "Running checkForPieces...";

	if (loopCount == 0) {
		std::cout << "Piece found!\n";
		loopCount++;
		getPiece();
	}
	else {
		std::cout << "No pieces left.\n";
		stopProcessing();
	}
	
}

// Select a piece from the hopper
void getPiece() {
	positionPiece();
};

// Move piece into position beneath the camera
void positionPiece() {
	takePicture();
}

// Take picture of puzzle piece
void takePicture() {
	std::string image = "new_image";
	getImage();
}

// check folder for image namestring 
void getImage() {
	std::string filename = "filename";
	detectEdges(filename);
}

// Run image processing
void detectEdges(std::string filenameUnused) {

	// Declare the output variables. "Mat" is a OpenCV class which contains image data
	Mat blurredImage, cannyOutput, cdst, cdstP;

	// load the image based on the main function argument
	// To edit: Project --> Properties --> Debugging --> Command Arguments

	// This is a static image
	const char* filename = "../data/IMG_3512.JPG";

	// Load the image into an openCV container ("Mat")
	Mat imageCV = imread(filename, IMREAD_GRAYSCALE);

	// Check if image is loaded fine
	if (imageCV.empty()) {
		printf(" Error opening image\n");
		printf(" Program Arguments: [image_name -- default %s] \n", "default_file");
		//return -1;
	}
	// Loading Complete

	// Gaussian Blur the image
	GaussianBlur(imageCV, blurredImage, Size(9, 9), 0, 0);

	imshow("Blurred", blurredImage);

	// Compute the mean with the computed mask
	Scalar computedMean = mean(imageCV);

	int upperThreshold = 1.33 * computedMean[0];
	int lowerThreshold = .66 * computedMean[0];

	// Run Canny Edge detection	
	// Canny(inputArray, outputArray, double threshold 1, double threshold 2, aperture size)
	Canny(blurredImage, cannyOutput, 150, 50, 3);


	// Copy edges to the images that will display the results in BGR
	cvtColor(cannyOutput, cdst, COLOR_GRAY2BGR);
	cdstP = cdst.clone();

	// Standard Hough Line Transform
	// Will hold the results of the detection
	vector<Vec2f> lines;

	// Run the actual detection
	HoughLines(cannyOutput, lines, 1, CV_PI / 180, 150, 0, 0); 

	// Draw the lines
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
	}

	// Probabilistic Hough Line Transform
	// will hold the results of the detection
	vector<Vec4i> linesP;

	// Runs the actual detection
	HoughLinesP(cannyOutput, linesP, 1, CV_PI / 180, 50, 50, 10); 

	// Draw the lines
	for (size_t i = 0; i < linesP.size(); i++)
	{
		Vec4i l = linesP[i];
		line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}

	// Show results
	imshow("Source", imageCV);
	//imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
	imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);

	bool isEdgePiece = false;

	if (isEdgePiece) {
		// Move to Bin 1
	}
	else {
		// Move to Bin 2
	}

	// Delete Image

	// Start this over again
	checkForPieces();
}

// Shut this whole thing down
void stopProcessing() {
	std::cout << "All pieces have been sorted!\n";
	waitKey();
//	return 0;
}