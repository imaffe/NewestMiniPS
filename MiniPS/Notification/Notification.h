#pragma once
#include "Comman/Comman.h"
#include "ViewModel/ViewModel.h"
#include "View/MiniPS.h"

class MiniPS;
class ViewModel;

class ConvertImageFormatNotification : public IPropertyNotification {
public:
    ConvertImageFormatNotification(std::shared_ptr<ViewModel>_viewmodel) : viewmodel(_viewmodel){}
    void OnPropertyChanged() {
        viewmodel->ConvertImageFormat();
    }
protected:
    std::shared_ptr<ViewModel> viewmodel;
};


class OpenFileCommandNotification : public ICommandNotification {

};

class UpdateViewNotification : public IPropertyNotification {
public:
    UpdateViewNotification(std::shared_ptr<MiniPS> _view) : view(_view){}
    void OnPropertyChanged() {
        view->ShowPicture();
        view->SetBackGround();
        view->ShowObjPicture();
    }
protected:
    std::shared_ptr<MiniPS> view;
};

