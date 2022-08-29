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
    virtual ~file_storage();

    void write(printing_type, unsigned int) override;
    void write_batch(unsigned int);

private:
    void write_vertical_space(unsigned int);
    void write_credentials(unsigned int);
    void write_start();
    void write_end();
    void write_block();

private:
    std::filesystem::path storage_path;
    std::ofstream storage_file;
    std::ostringstream buffer;
    int line_height;
};
} // sp
