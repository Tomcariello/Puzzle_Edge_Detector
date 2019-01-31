// functions.h : include file for functions related to puzzle piece edge detection workflow

#pragma once

#include <string>
#include <iostream>
#include <filesystem>

// Include OpenCV Headers
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

// Declare all functions
void checkForPieces();
void getPiece();
void positionPiece();
void takePicture(string curImage);
void detectEdges(std::string filenameUnused);
void stopProcessing();

// Temporary variable to count the number of loops. Will be replaced when proper file reading is implemented.
// int loopCount = 0;

// Declare the path to the image directory
const std::string path = "../data";


// Check to see if there are any additional pieces    
void checkForPieces() {
	   
	// Iterate through the directory images. Process each image found.
	for (const auto & allFiles : fs::directory_iterator(path))
	{
		// Convert the current filename to a string
		const std::string fullPath = allFiles.path().string();

		// Call takePicture with the fullPath string
		takePicture(fullPath);
	}

	stopProcessing();
}

// Select a piece from the hopper
//void getPiece() {
//	positionPiece();
//};
//
//// Move piece into position beneath the camera
//void positionPiece() {
//	takePicture();
//}

// Take picture of puzzle piece
void takePicture(string curImage) {
	detectEdges(curImage);
}

// Run image processing
void detectEdges(std::string curImage) {

	// Declare the output variables. "Mat" is a OpenCV class which contains image data
	Mat blurredImage, cannyOutput, cdst, cdstP;

	// load the image based on the main function argument
	// To edit: Project --> Properties --> Debugging --> Command Arguments

	// This is an image path
	//string filename = "../data/IMG_3492.JPG";
	string filename = curImage; // This string appears to have quotes

	// Load the image into an openCV container ("Mat")
	Mat imageCV = imread(filename, IMREAD_GRAYSCALE);

	// Check if image is loaded fine
	if (imageCV.empty()) {
		printf(" Error opening image\n");
		printf(" Program Arguments: [image_name -- default %s] \n", "default_file");
		//return -1;
	}

	// Gaussian Blur the image
	GaussianBlur(imageCV, blurredImage, Size(9, 9), 0, 0);

	// Compute the mean with the computed mask
	Scalar computedMean = mean(imageCV);

	// Set threshold values based on the Mean
	int upperThreshold = 1.33 * computedMean[0];
	int lowerThreshold = .66 * computedMean[0];

	// Run Canny Edge detection	
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
	//imshow("Source", imageCV);
	//imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
	imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
	waitKey();

	bool isEdgePiece = false;

	if (isEdgePiece) {
		// Move to Bin 1
	}
	else {
		// Move to Bin 2
	}

	// Delete Image

	// Start this over again
	//checkForPieces();
}

// Shut this whole thing down
void stopProcessing() {
	std::cout << "All pieces have been sorted!\n";
	waitKey();
//	return 0;
}