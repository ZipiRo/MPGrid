class Popup
{
private:
public:
    bool open = true;

    virtual void Init(ApplicationContext &context) {};
    virtual void Interface(ApplicationContext &context) = 0;
    virtual std::string GetName() = 0;
};

#include "LoadGridPopup.h"
#include "SaveGridPopup.h"
#include "ResizeGridPopup.h"
#include "GridColorThemesPopup.h"
#include "SetBackgroundPopup.h"
#include "ShowKeybindsPopup.h"