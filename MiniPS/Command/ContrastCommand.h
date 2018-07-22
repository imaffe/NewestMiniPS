#pragma once
#include "Comman/Comman.h"
#include "ViewModel/ViewModel.h"

class ViewModel;
class ContrastParameter : public ICommandParameter {
private:
    double conpara;
    double bripara;
public:
    ContrastParameter(double _conpara,double _bripara) {
        conpara = _conpara;
        bripara = _bripara;
    }
    double GetConPara() {
        return conpara;
    }
    double GetBriPara() {
        return bripara;
    }
};
class ContrastCommand : public ICommandBase {
public:
    ContrastCommand() {}
    ContrastCommand(std::shared_ptr<ViewModel> _viewmodel) : viewmodel(_viewmodel) {}
    void SetParameter(const std::shared_ptr<ICommandParameter>& _param) {
        Param = std::static_pointer_cast<ContrastParameter>(_param);
    }
    void Exec() {
        double con = Param->GetConPara();
        double bri = Param->GetBriPara();
        viewmodel->Contrast(con,bri);
    }
protected:
    std::shared_ptr<ViewModel> viewmodel;
    std::shared_ptr<ContrastParameter> Param;
};