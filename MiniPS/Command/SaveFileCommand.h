#pragma once
#include "Comman/Comman.h"
#include "ViewModel/ViewModel.h"

class ViewModel;
class SPathParameter : public ICommandParameter {
private:
    std::string path;
public:
    SPathParameter(std::string _path) : path(_path) {}
    std::string GetPath() {
        return path;
    }
};

class SaveFileCommand : public ICommandBase {
public:
    SaveFileCommand() {}
    SaveFileCommand(std::shared_ptr<ViewModel> _viewmodel) : viewmodel(_viewmodel) {}
    void SetParameter(const std::shared_ptr<ICommandParameter>& _param) {
        pathParam = std::static_pointer_cast<SPathParameter>(_param);
    }
    void Exec() {
        std::string path = pathParam->GetPath();
        viewmodel->SaveFile(path);
    }
protected:
    std::shared_ptr<ViewModel> viewmodel;
    std::shared_ptr<SPathParameter> pathParam;
};
