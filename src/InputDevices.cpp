#include "InputDevices.h"

#include "Window.h"

InputDevices InputDevices::self;

InputDevices::Mouse &InputDevices::GetMouse()
{
    if (!self.registered)
    {
        self.register_mouse();
    }
    return self.mouse;
};

void InputDevices::register_mouse()
{
    RAWINPUTDEVICE riw = {};
    riw.usUsagePage = HID_USAGE_PAGE_GENERIC;
    riw.usUsage = HID_USAGE_GENERIC_MOUSE;

    THROW_IF_FAILED(RegisterRawInputDevices(&riw, 1, sizeof(riw)));
}
