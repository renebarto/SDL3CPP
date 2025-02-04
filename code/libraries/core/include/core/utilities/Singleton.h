#pragma once

template <class T>
class Singleton
{
public:
    Singleton() = default;
    virtual ~Singleton() = default;

    static T &Get()
    {
        static T instance;
        return instance;
    }
};
