#pragma once

#include <array>
#include <iostream>

#include <credentials.hpp>

namespace sp
{
class storage
{
public:
    enum class storage_type { file, network, unknown };
    enum class printing_type { write, wipe, strikethrough };

    inline static std::array<char const*, 1> available_storage_types()
    {
        std::array<char const*, 1> types;
        types[0] = "file";
        return types;
    }

    bool request_credentials();
    void clear();

    virtual void write(printing_type, unsigned int) = 0;

protected:
    credentials keys;
}; // storage
} // sp
