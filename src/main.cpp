#include <string>
#include <iostream>
#include <exception>
#include <filesystem>

#include <boost/program_options.hpp>

#include <options.hpp>
#include <file_storage.hpp>

int main(int argc, char **argv)
{
    namespace po = boost::program_options;

    int position{};
    std::string requested_type{};
    std::filesystem::path output_path{};
    std::string storage_type{};

    po::options_description general_options("General Options");
    general_options.add_options()
        ("help,h", "show this help menu")
        ("list,l", "list of available storage types");

    po::options_description printing_options("Printing Options");
    printing_options.add_options()
        ("position,p", po::value<int>()->default_value(1), "position of passphrase on paper")
        ("output,o", po::value<std::string>(), "output to be written into")
        ("storage-type,t", po::value<std::string>()->default_value("file"), "storage type, use -l to see list");

    po::positional_options_description positional_options;
    positional_options.add("output", 1);

    po::options_description all_options;
    all_options.add(general_options).add(printing_options);

    po::variables_map variables_map;
    po::command_line_parser command_line_parser(argc, argv);
    command_line_parser.options(all_options).positional(positional_options);

    try
    {
        auto parsed_options = command_line_parser.run();
        po::store(parsed_options, variables_map);
    }
    catch (po::error const& exp)
    {
        std::cerr << exp.what() << std::endl;
        return 1;
    }

    if (variables_map.count("help"))
    {
        std::cerr << "Usage: " << argv[0] << " [options]\n";
        std::cerr << all_options << std::endl;
    }

    if (variables_map.count("list"))
    {
        int index{1};

        std::cout << "Available storage types:\n";

        for (auto&& type: sp::storage::available_storage_types())
            std::cout << "  " << index << ". " << type << std::endl;

        return 0;
    }

    if (variables_map.count("position"))
        position = variables_map["position"].as<int>();

    if (variables_map.count("output"))
        output_path = variables_map["output"].as<std::string>();

    if (variables_map.count("storage-type"))
        storage_type = variables_map["storage-type"].as<std::string>();

    std::string username;
    std::cout << "Usagename: ";
    std::cin >> username;
    std::cout << "Domain: ";
    std::string domain;
    std::cin >> domain;
    std::cout << "Passphrase: ";
    std::string passphrase;
    std::cin >> passphrase;

    sp::credentials keys = {domain, username, passphrase};

    try
    {
        sp::file_storage storage(output_path);
        storage.record(keys);
        storage.write(position);
    }
    catch (std::exception const& exp)
    {
        std::cerr << exp.what() << std::endl;
    }
}
