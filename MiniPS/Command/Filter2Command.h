#pragma once
#include "Comman/Comman.h"
#include "ViewModel/ViewModel.h"

class ViewModel;
class Filter2Command : public ICommandBase {
public:
    Filter2Command() {}
    Filter2Command(std::shared_ptr<ViewModel> _viewmodel) : viewmodel(_viewmodel) {}
    void SetParameter(const std::shared_ptr<ICommandParameter>& _param) {}
    void Exec() {
        viewmodel->Filter2();
    }
protected:
    std::shared_ptr<ViewModel> viewmodel;
};