#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ios>
#include <stdexcept>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;




string cascade_name = "haarcascades/haarcascade_frontalface_alt2.xml";


int imageWidth = 600;
int imageHeight = 600;

char key;


static void showDetections(const vector<Rect>& found, Mat& imageData) {

	for (size_t i = 0; i < found.size(); i++) {
		Rect r = found[i];
		cv::rectangle(imageData, r.tl(), r.br(), Scalar(64, 255, 64), 1);
	}
}

{

void faceDetect(){
	VideoCapture cap(CV_CAP_ANY);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, imageWidth);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, imageHeight);

	CascadeClassifier cascade_1;

	if (!cascade_1.load(cascade_name)){
		//printf("--(!)Blad. Sprawdz nazwe pliku xml klasyfikatora.\n");
		cout << "--(!)Blad. Sprawdz nazwe pliku xml klasyfikatora.\n";
		return;
	}

	if (!cap.isOpened())
		return;
	namedWindow("video capture", CV_WINDOW_AUTOSIZE);

	while (true)
	{
		Mat img;
		cap >> img;//pobranie orazu z kamery do obrazu Mat

		Mat croppedImage;

		//HAAR

		Mat img_gray;
		cvtColor(img, img_gray, COLOR_BGR2GRAY);

		vector<Rect> found_faces;
		vector<Rect> smooth_area;


		cascade_1.detectMultiScale(img_gray, found_faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

		smooth_area = found_faces;

		int kernel_size = 13;
		Mat kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);


		for (unsigned int i = 0; i < smooth_area.size(); ++i) {

			smooth_area.at(i).width = smooth_area.at(i).width / 2;

			int x_pos = smooth_area.at(i).x;
			int y_pos = smooth_area.at(i).y;
			int w = smooth_area.at(i).width;
			int h = smooth_area.at(i).height;

			croppedImage = img(smooth_area.at(i));

			Mat dstImage;


			filter2D(croppedImage, dstImage, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);

			dstImage.copyTo(img(cv::Rect(x_pos, y_pos, dstImage.cols, dstImage.rows)));
		}
	}