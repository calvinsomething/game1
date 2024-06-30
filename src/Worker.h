#pragma once

#include "pch.h"

class Worker
{
    std::thread thread;

  public:
    template <typename T, typename... Args> Worker(T (*fn)(Args...), Args &&...args) : thread(fn, args...)
    {
    }

    ~Worker()
    {
        thread.join();
    }
};
