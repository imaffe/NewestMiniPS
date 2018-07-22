#pragma once

#include <Comman/Comman.h>
#include <string>
#include <opencv2/opencv.hpp>
class Model
{
private:
    std::shared_ptr<cv::Mat> img_origin;
	std::shared_ptr<cv::Mat> img_changed;
	std::shared_ptr<cv::Mat> img_back;
    std::shared_ptr<IPropertyNotification> convertImageFormatNotifier;
public:

    Model() : img_origin(std::shared_ptr<cv::Mat>(new(cv::Mat)))
			, img_changed(std::shared_ptr<cv::Mat>(new(cv::Mat)))
			, img_back(std::shared_ptr<cv::Mat>(new(cv::Mat)))
	{}
    ~Model(){}

	void SetConvertImageFormatNotifier(std::shared_ptr<IPropertyNotification>);
    std::shared_ptr<cv::Mat> GetCvImage();
    std::shared_ptr<cv::Mat> GetCvImage_changed();
    std::shared_ptr<cv::Mat> GetCvImage_back();
	bool OpenFile(const std::string& path);
	bool SaveFile(const std::string& path);
	void Contrast(double contrast_value, double bright_value);
	void GaussianFilter(cv::Size ksize, double sigmaX, double sigmaY = 0, int borderType = cv::BORDER_DEFAULT);
	void BlurFilter(int depth, cv::Size ksize, cv::Point anchor, bool norm = true);
	void Filter_1_Past();
	void Filter_2_Black();
    
    void FaceDetect();
    
    void Undo();
};

