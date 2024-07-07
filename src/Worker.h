#pragma once

#include "pch.h"

class Worker
{
    std::thread thread;

  public:
    template <typename T, typename... Args> Worker(T (*fn)(Args...), Args &&...args) : thread(fn, std::forward(args)...)
    {
    }

    Worker(const Worker &) = delete;
    Worker operator=(const Worker &) = delete;
    Worker operator=(Worker &&) = delete;

    Worker(Worker &&other)
    {
        thread.swap(other.thread);
    };

    ~Worker()
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
};
