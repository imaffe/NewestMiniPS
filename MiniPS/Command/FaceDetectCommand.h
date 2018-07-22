#pragma once
#include "Comman/Comman.h"
#include "ViewModel/ViewModel.h"

class ViewModel;
class FaceDetectCommand : public ICommandBase {
public:
    FaceDetectCommand() {}
    FaceDetectCommand(std::shared_ptr<ViewModel> _viewmodel) : viewmodel(_viewmodel) {}
    void SetParameter(const std::shared_ptr<ICommandParameter>& _param) {}
    void Exec(){
        viewmodel->FaceDetect();
    }
protected:
    std::shared_ptr<ViewModel> viewmodel;
};
