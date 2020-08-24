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
            std::cout << s << " " << hash << "\n";
            return hash;
        }
    };


    template <typename T>
    struct raw_memory_hash
    {
        std::size_t operator()(const T& obj) const noexcept
        {
            const char *const s = (const char *)&obj;
            auto hash = FowlerNollVoHash::hash_bytes(s, sizeof(T));
            std::cout << hash << "\n";
            return hash;
        }
    };

}

#endif // HASH_H
