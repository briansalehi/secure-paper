#pragma once

#include <string>
#include <iostream>
#include <boost/program_options.hpp>

#include <storage.hpp>

namespace po = boost::program_options;

namespace sp
{
struct options
{
    options(int argc, char **argv);

    bool ready();

    po::positional_options_description positional_options;
    po::command_line_parser command_line_parser;
    po::options_description printing_options;
    po::options_description general_options;
    po::options_description all_options;
    po::variables_map variables_map;

    storage::printing_type printing_type;
    storage::storage_type storage_type;
    std::string program_name;
    std::string output;
    int position;
};
} // namespace sp
