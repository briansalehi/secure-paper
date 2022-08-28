#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <storage.hpp>

namespace sp
{
class file_storage: public storage
{
public:
    explicit file_storage(std::filesystem::path const& storage_path);
    void write(printing_type type, unsigned int position) override;

private:
    std::filesystem::path storage_path;
    std::ostringstream buffer;
};
} // sp
