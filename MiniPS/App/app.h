#pragma once
#include "View/MiniPS.h"
#include "Model/Model.h"
#include "ViewModel/ViewModel.h"
#include "Notification/Notification.h"
#include "Comman/Comman.h"

class App {
public:
    App(): view(new MiniPS), model(new Model), viewmodel(new ViewModel){
        viewmodel->bind(model);
        view->SetOpenFileCommand(viewmodel->GetOpenFileCommand());
        view->SetContrastCommand(viewmodel->GetContrastCommand());
        view->SetGaussianFilterCommand(viewmodel->GetGaussianFilterCommand());
        view->SetFilter1Command(viewmodel->GetFilter1Command());
        view->SetFilter2Command(viewmodel->GetFilter2Command());
        view->SetSaveFileCommand(viewmodel->GetSaveFileCommand());
        viewmodel->SetUpdateViewNotifier(view->GetUpdateViewSink());
        model->SetConvertImageFormatNotifier(viewmodel->GetConvertImageFormatSink());
        view->SetQImage(viewmodel->GetQImage_origin());
        view->SetObjQImage(viewmodel->GetQImage_changed());
        view->SetBackQImage(viewmodel->GetQImage_back());
        viewmodel->SetCvImage_origin(model->GetCvImage());
        viewmodel->SetCvImage_changed(model->GetCvImage_changed());
        viewmodel->SetCvImage_back(model->GetCvImage_back());


        view->SetUndoCommand(viewmodel->GetUndoCommand());
        view->SetFaceDetectCommand(viewmodel->GetFaceDetectCommand());
    }
    

private:
    std::shared_ptr<MiniPS> view;
    std::shared_ptr<Model> model;
    std::shared_ptr<ViewModel> viewmodel;

public:
    void show();
};