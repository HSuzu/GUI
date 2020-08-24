#pragma once

#ifndef SINGLETONFILE_H
#define SINGLETONFILE_H

#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>

#include "Hash.h"

template <typename T>
class SingletonFile {
public:
    using ptr = std::shared_ptr<T>;
protected:
    static
    std::unordered_map<
        const char *,
        std::shared_ptr<T>,
        Utils::hash<const char *>
    > _instances;

    const char *_filepath;
    SingletonFile(const char *filepath);
public:
    virtual ~SingletonFile() {}

    static std::shared_ptr<T> fromFile(const char *filepath);
    void releaseptr();
};

template <typename T>
std::unordered_map<
    const char *,
    std::shared_ptr<T>,
    Utils::hash<const char *>
> SingletonFile<T>::_instances;

template <typename T>
SingletonFile<T>::SingletonFile(const char *filepath) :
    _filepath(filepath)
{}

template <typename T>
std::shared_ptr<T> SingletonFile<T>::fromFile(const char *filepath)
{
    {
        auto instance = _instances.find(filepath);
        if(instance != _instances.end())
            return instance->second;
    }

    auto ret = _instances.emplace(filepath, new T(filepath));
    return ret.first->second;

}

template <typename T>
void SingletonFile<T>::releaseptr()
{
    _instances.erase(_filepath);
}
#endif // SINGLETONFILE_H
