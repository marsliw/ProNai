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
