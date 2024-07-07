#pragma once

#include "pch.h"

class InputDevices
{
    static InputDevices self;

    InputDevices() = default;

    bool registered;

  public:
    InputDevices(const InputDevices &) = delete;
    InputDevices(InputDevices &&) = delete;
    InputDevices operator=(const InputDevices &) = delete;
    InputDevices operator=(InputDevices &&) = delete;

    struct Mouse
    {
        struct
        {
            short x;
            short y;
        } Delta;
        struct
        {
            short x;
            short y;
        } Position;

        bool left_button_down;
        bool right_button_down;
    };

    static Mouse &GetMouse();

    Mouse mouse = {};

  private:
    void register_mouse();
};
