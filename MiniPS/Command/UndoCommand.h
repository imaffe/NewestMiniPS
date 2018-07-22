#pragma once
#include "Comman/Comman.h"
#include "ViewModel/ViewModel.h"

class ViewModel;
class UndoCommand : public ICommandBase {
public:
    UndoCommand() {}
    UndoCommand(std::shared_ptr<ViewModel> _viewmodel) : viewmodel(_viewmodel) {}
    void SetParameter(const std::shared_ptr<ICommandParameter>& _param) {}
    void Exec() {
        viewmodel->Undo();
    }
protected:
    std::shared_ptr<ViewModel> viewmodel;
};