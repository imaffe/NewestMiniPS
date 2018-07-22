#pragma once
#include "Comman/Comman.h"
#include "ViewModel/ViewModel.h"

class ViewModel;
class GaussianFilterCommand : public ICommandBase {
public:
    GaussianFilterCommand() {}
    GaussianFilterCommand(std::shared_ptr<ViewModel> _viewmodel) : viewmodel(_viewmodel) {}
    void SetParameter(const std::shared_ptr<ICommandParameter>& _param) {}
    void Exec() {
        viewmodel->GaussianFilter();
    }
protected:
    std::shared_ptr<ViewModel> viewmodel;
};