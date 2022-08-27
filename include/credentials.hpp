#pragma once

#include <string>
#include <ostream>

namespace sp
{
struct credentials
{
    std::string domain;
    std::string username;
    std::string passphrase;
};
} // sp

