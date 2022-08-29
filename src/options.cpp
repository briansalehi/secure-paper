#include <options.hpp>

using namespace sp;

options::options(int argc, char **argv)
    : command_line_parser(argc, argv),
    general_options("General Options"),
    printing_options("Printing Options"),
    program_name{argv[0]},
    batch_mode{false}
{
    general_options.add_options()
        ("help,h", "show this help menu")
        ("list,l", "list of available storage types");

    printing_options.add_options()
        ("batch,b", "batch mode, write multiple credentials")
        ("position,p", po::value<int>()->default_value(1),
             "position of passphrase on paper")
        ("output,o", po::value<std::string>(),
             "output to be written into")
        ("storage-type,t", po::value<std::string>()->default_value("file"),
             "storage type, use -l to see list")
        ("wipe,w", "wipe specified line");

    positional_options.add("output", 1);
    all_options.add(general_options).add(printing_options);
    command_line_parser.options(all_options).positional(positional_options);

    // these two lines throw exceptions
    auto parsed_options = command_line_parser.run();
    po::store(parsed_options, variables_map);
}

bool options::ready()
{
    bool operational = false;

    if (variables_map.count("help"))
    {
        std::cerr << "Usage: " << program_name << " [options]\n";
        std::cerr << all_options << std::endl;
        return false;
    }

    if (variables_map.count("list"))
    {
        int index{1};
        std::cout << "Available storage types:\n";
        for (auto&& type: sp::storage::available_storage_types())
            std::cout << "  " << index << ". " << type << std::endl;
        return false;
    }

    if (variables_map.count("storage-type"))
    {
        std::string requested_type = variables_map["storage-type"].as<std::string>();
        if (requested_type == "file")
            storage_type = storage::storage_type::file;
        else if (requested_type == "network")
            storage_type = storage::storage_type::network;
    }

    if (variables_map.count("output"))
    {
        output = variables_map["output"].as<std::string>();
    }

    if (variables_map.count("position"))
    {
        position = variables_map["position"].as<int>();
        printing_type = storage::printing_type::write;
        operational = true;
    }

    if (variables_map.count("wipe"))
    {
        printing_type = storage::printing_type::wipe;
        operational = true;
    }

    if (variables_map.count("batch"))
    {
        batch_mode = true;
        operational = true;
    }

    return operational;
}
