#pragma once

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

    virtual ~file_storage();

    void write(unsigned int position) override;

    void record(credentials const& secrets);

private:
    std::filesystem::path storage_path;
    std::ofstream storage_file;
};
} // sp
