#include "ViewModel/ViewModel.h"
#include "Model/Model.h"
#include "Command//OpenFileCommand.h"
#include "Command/ContrastCommand.h"
#include "Notification/Notification.h"
#include "Command/GaussianFilterCommand.h"
#include "Command/Filter1Command.h"
#include "Command/Filter2Command.h"
#include "Command/SaveFileCommand.h"
#include "Command/UndoCommand.h"
#include "Command/FaceDetectCommand.h"
#include <QtGui/QImage>

ViewModel::ViewModel() : qimg_origin(std::shared_ptr<QImage>(new(QImage)))
					, qimg_changed(std::shared_ptr<QImage>(new(QImage)))
					, qimg_back(std::shared_ptr<QImage>(new(QImage)))
					, cvimg_origin(std::shared_ptr<cv::Mat>(new (cv::Mat)))
					, cvimg_changed(std::shared_ptr<cv::Mat>(new (cv::Mat)))
					, cvimg_back(std::shared_ptr<cv::Mat>(new (cv::Mat)))
{
    openFileCommand = std::static_pointer_cast<OpenFileCommand> \
        (std::shared_ptr<OpenFileCommand>(new OpenFileCommand(std::shared_ptr<ViewModel>(this))));
    contrastCommand = std::static_pointer_cast<ContrastCommand>\
        (std::shared_ptr<ContrastCommand>(new ContrastCommand(std::shared_ptr<ViewModel>(this))));
    gaussianFilterCommand= std::static_pointer_cast<GaussianFilterCommand> \
        (std::shared_ptr<GaussianFilterCommand>(new GaussianFilterCommand(std::shared_ptr<ViewModel>(this))));
    filter1Command= std::static_pointer_cast<Filter1Command> \
        (std::shared_ptr<Filter1Command>(new Filter1Command(std::shared_ptr<ViewModel>(this))));
    filter2Command = std::static_pointer_cast<Filter2Command> \
        (std::shared_ptr<Filter2Command>(new Filter2Command(std::shared_ptr<ViewModel>(this))));
    saveFileCommand= std::static_pointer_cast<SaveFileCommand> \
        (std::shared_ptr<SaveFileCommand>(new SaveFileCommand(std::shared_ptr<ViewModel>(this))));
    faceDetectCommand = std::static_pointer_cast<FaceDetectCommand> \
        (std::shared_ptr<FaceDetectCommand>(new FaceDetectCommand(std::shared_ptr<ViewModel>(this))));
    
    
    
    
    undoCommand = std::static_pointer_cast<UndoCommand> \
        (std::shared_ptr<UndoCommand>(new UndoCommand(std::shared_ptr<ViewModel>(this))));



    convertImageFormatSink = std::static_pointer_cast<ConvertImageFormatNotification>(std::shared_ptr<ConvertImageFormatNotification>(new ConvertImageFormatNotification(std::shared_ptr<ViewModel>(this))));


}

void ViewModel::bind(std::shared_ptr<Model> model) {
    this->model = model;
}

void ViewModel::SetUpdateViewNotifier(std::shared_ptr<IPropertyNotification> _updateViewNotifier) {
    this->updateViewNotifier = _updateViewNotifier;
}

std::shared_ptr<IPropertyNotification> ViewModel::GetConvertImageFormatSink() {
    return convertImageFormatSink;
}

void ViewModel::ConvertImageFormat(){
    (*qimg_origin) = MatToQImage(*cvimg_origin);
	(*qimg_back) = MatToQImage(*cvimg_back);
	(*qimg_changed) = MatToQImage(*cvimg_changed);
    updateViewNotifier->OnPropertyChanged();
}

QImage ViewModel::MatToQImage(cv::Mat cvimg){
    cv::Mat tempimg;
    cv::cvtColor(cvimg, tempimg, cv::COLOR_BGR2RGB);
    QImage::Format format = QImage::Format_RGB888;
    return QImage(tempimg.data, tempimg.cols, tempimg.rows,
                static_cast<int>(tempimg.step), format).copy();
}


std::shared_ptr<QImage> ViewModel::GetQImage_origin()
{
	return qimg_origin;
}
void ViewModel::SetCvImage_origin(std::shared_ptr<cv::Mat> _cvimg)
{
	cvimg_origin = _cvimg;
}
std::shared_ptr<QImage> ViewModel::GetQImage_changed()
{
	return qimg_changed;
}
void ViewModel::SetCvImage_changed(std::shared_ptr<cv::Mat> _cvimg)
{
	cvimg_changed = _cvimg;
}
std::shared_ptr<QImage> ViewModel::GetQImage_back()
{
	return qimg_back;
}
void ViewModel::SetCvImage_back(std::shared_ptr<cv::Mat> _cvimg)
{
	cvimg_back = _cvimg;
}



void ViewModel::OpenFile(std::string& path) {
	model->OpenFile(path);
}
void ViewModel::Contrast(double contrast_value,double brightness_value)
{   
	model->Contrast(contrast_value,brightness_value);
}
void ViewModel::GaussianFilter()
{
	model->GaussianFilter(cv::Size(3,3),0, 0);
}
void ViewModel::SaveFile(std::string& path)
{
	model->SaveFile(path);
}
void ViewModel::Filter1()
{
	model->Filter_1_Past();
}
void ViewModel::Filter2()
{
	model->Filter_2_Black();
}
void ViewModel::FaceDetect() {
    model->FaceDetect();
}
void ViewModel::Undo()
{
    model->Undo();
}

std::shared_ptr<ICommandBase> ViewModel::GetOpenFileCommand() {
	return openFileCommand;
}
std::shared_ptr<ICommandBase> ViewModel::GetContrastCommand()
{
	return contrastCommand;
}
std::shared_ptr<ICommandBase> ViewModel::GetGaussianFilterCommand()
{
	return gaussianFilterCommand;
}
std::shared_ptr<ICommandBase> ViewModel::GetSaveFileCommand()
{
	return saveFileCommand;
}
std::shared_ptr<ICommandBase> ViewModel::GetFilter1Command()
{
	return filter1Command;
}
std::shared_ptr<ICommandBase> ViewModel::GetFilter2Command()
{
	return filter2Command;
}
std::shared_ptr<ICommandBase> ViewModel::GetFaceDetectCommand() {
    return faceDetectCommand;
}
std::shared_ptr<ICommandBase> ViewModel::GetUndoCommand()
{
    return undoCommand;
}