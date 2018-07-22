////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <vector>
#include <map>
#include <stack>

//types
typedef unsigned char     uchar;
typedef unsigned short    ushort;
typedef unsigned int      uint;
typedef unsigned __int64  uint64;
typedef __int64           int64;

//command

class ICommandParameter
{

};


class ICommandBase
{
public:
    virtual void SetParameter(const std::shared_ptr<ICommandParameter>& param) = 0;
    virtual void Exec() = 0;
};


//Notifications

class IPropertyNotification
{
public:
    virtual void OnPropertyChanged() = 0;
};

class ICommandNotification
{
public:
    virtual void OnCommandComplete(bool bOK) = 0;
};



