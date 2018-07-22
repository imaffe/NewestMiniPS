#include "Model/Model.h"
#include "Notification/Notification.h"
#include <iostream>




std::shared_ptr<cv::Mat> Model::GetCvImage(){
    return img_origin;
}
std::shared_ptr<cv::Mat> Model::GetCvImage_changed() {
    return img_changed;
}
std::shared_ptr<cv::Mat> Model::GetCvImage_back() {
    return img_back;
}
void Model::SetConvertImageFormatNotifier(std::shared_ptr<IPropertyNotification> _convertImageFormatNotifier) {
    convertImageFormatNotifier = _convertImageFormatNotifier;
}


bool Model::OpenFile(const std::string& path) {
	*img_origin = cv::imread(path);
	if (img_origin->empty()) {
		return 0;
	}
	else {
        *img_changed = cv::imread(path);
        cv::GaussianBlur(*img_origin, *img_back, cv::Size(55, 55), 0, 0, cv::BORDER_DEFAULT);
		convertImageFormatNotifier->OnPropertyChanged();
		return 1;
	}
}

bool Model::SaveFile(const std::string& path)
{
	bool success = cv::imwrite(path,*img_changed);
	if (success) {
		return 1;
		convertImageFormatNotifier->OnPropertyChanged();
	}
	else {
		return 0;
	}
}

void Model::Contrast(double contrast_value, double bright_value)
{
	for (int y = 0; y < img_origin->rows; y++)
	{
		for (int x = 0; x < img_origin->cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				img_changed->at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>((contrast_value*0.01)*(img_origin->at<cv::Vec3b>(y, x)[c]) + bright_value);
			}
		}
	}
	convertImageFormatNotifier->OnPropertyChanged();
}

void Model::GaussianFilter(cv::Size ksize, double sigmaX, double sigmaY, int borderType)
{
	cv::GaussianBlur(*img_origin, *img_changed, ksize, sigmaX, sigmaY, borderType);
	convertImageFormatNotifier->OnPropertyChanged();

}

void Model::BlurFilter(int depth, cv::Size ksize, cv::Point anchor, bool norm)
{
	cv::blur(*img_origin, *img_changed, ksize);
	convertImageFormatNotifier->OnPropertyChanged();
}

void Model::Filter_1_Past()
{
	int width = img_origin->cols;
	int height = img_origin->rows;
	for(int y=0; y < height; y++)
	{
		uchar* P0 = img_origin->ptr<uchar>(y);
		uchar* P1 = img_changed->ptr<uchar>(y);
		for (int x = 0; x<width; x++)
		{
			float B = P0[3 * x];
			float G = P0[3 * x + 1];
			float R = P0[3 * x + 2];
			float newB = 0.272*R + 0.534*G + 0.131*B;
			float newG = 0.349*R + 0.686*G + 0.168*B;
			float newR = 0.393*R + 0.769*G + 0.189*B;
			if (newB<0)newB = 0;
			if (newB>255)newB = 255;
			if (newG<0)newG = 0;
			if (newG>255)newG = 255;
			if (newR<0)newR = 0;
			if (newR>255)newR = 255;
			P1[3 * x] = (uchar)newB;
			P1[3 * x + 1] = (uchar)newG;
			P1[3 * x + 2] = (uchar)newR;
		}
	}
	convertImageFormatNotifier->OnPropertyChanged();
}

void Model::Filter_2_Black()
{
	int width = img_origin->cols;
	int height = img_origin->rows;
	for (int y = 0; y < height; y++)
	{
		uchar* P0 = img_origin->ptr<uchar>(y);
		uchar* P1 = img_changed->ptr<uchar>(y);
		for (int x = 0; x<width; x++)
		{
			float B = P0[3 * x];
			float G = P0[3 * x + 1];
			float R = P0[3 * x + 2];
			float newB = abs(B - G + B + R)*G / 256;
			float newG = abs(B - G + B + R)*R / 256;
			float newR = abs(G - B + G + R)*R / 256;
			if (newB<0)newB = 0;
			if (newB>255)newB = 255;
			if (newG<0)newG = 0;
			if (newG>255)newG = 255;
			if (newR<0)newR = 0;
			if (newR>255)newR = 255;
			P1[3 * x] = (uchar)newB;
			P1[3 * x + 1] = (uchar)newG;
			P1[3 * x + 2] = (uchar)newR;
		}
	}
	convertImageFormatNotifier->OnPropertyChanged();
}

void Model::FaceDetect() {
    using namespace cv;
    Mat img_gray, img_equalized, face;
    cvtColor(*img_origin, img_gray, cv::COLOR_BGR2GRAY);
    equalizeHist(img_gray, img_equalized);
    CascadeClassifier faces_cascade;
    faces_cascade.load("haarcascades//haarcascade_frontalface_alt.xml");
    std::vector<Rect> faces;
    faces_cascade.detectMultiScale(img_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
    Point text;
    for (int i = 0; i < faces.size(); i++) {
        if (faces[i].height > 0 && faces[i].width > 0) {
            face = img_gray(faces[i]);
            text = Point(faces[i].x, faces[i].y);
            rectangle(*img_changed, faces[i], cv::Scalar(255, 0, 0), 1, 8, 0);
        }
    }
    convertImageFormatNotifier->OnPropertyChanged();
}

void Model::Undo() {
    *img_changed = img_origin->clone();
    convertImageFormatNotifier->OnPropertyChanged();
}