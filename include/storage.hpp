#pragma once

#include <array>

#include <credentials.hpp>

namespace sp
{
enum class storage_type { file };

class storage
{
public:
    inline static std::array<char const*, 1> available_storage_types()
    {
        std::array<char const*, 1> types;
        types[0] = "file";
        return types;
    }

    virtual void write(unsigned int position) = 0;

protected:
    credentials keys;
}; // storage
} // sp
