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
    explicit file_storage(std::filesystem::path const&, unsigned int const);
    virtual ~file_storage();

    void write(printing_type, unsigned int) override;
    void write_batch(unsigned int);

private:
    void write_vertical_space(unsigned int);
    void write_credentials(unsigned int);
    void write_start(bool const);
    void write_end();
    void wipe_line();

private:
    std::filesystem::path storage_path;
    std::ofstream storage_file;
    std::ostringstream buffer;
    int line_spacing;
};
} // sp
