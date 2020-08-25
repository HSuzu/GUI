#pragma once

#ifndef HASH_H
#define HASH_H

#include <functional>
#include <climits>
#include <cstring>

#include <iostream>

#include "HashFunctions.h"

namespace Utils {

    template <typename T>
    struct hash
    {
        std::size_t operator()(const T& obj) const noexcept
        {
            auto fn = std::hash<T>{};
            return fn(obj);
        }
    };

    template <>
    struct hash<const char *>
    {
        std::size_t operator()(const char *const s) const noexcept
        {
            auto hash = FowlerNollVoHash::hash_bytes(s, std::strlen(s));
            return hash;
        }
    };


    template <typename T>
    struct raw_memory_hash
    {
        std::size_t operator()(const T& obj) const noexcept
        {
            const char *const s = (const char *)&obj;
            return FowlerNollVoHash::hash_bytes(s, sizeof(T));
        }
    };

}

#endif // HASH_H
