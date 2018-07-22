#pragma once
#include "Comman/Comman.h"
#include "ViewModel/ViewModel.h"

class ViewModel;
class Filter1Command : public ICommandBase {
public:
    Filter1Command() {}
    Filter1Command(std::shared_ptr<ViewModel> _viewmodel) : viewmodel(_viewmodel) {}
    void SetParameter(const std::shared_ptr<ICommandParameter>& _param) {}
    void Exec() {
        viewmodel->Filter1();
    }
protected:
    std::shared_ptr<ViewModel> viewmodel;
};