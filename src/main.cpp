#include <exception>

#include <options.hpp>
#include <file_storage.hpp>

void write_to_storage(sp::storage&);

int main(int argc, char **argv)
try
{
    sp::options args(argc, argv);

    if (!args.ready())
        return 0;

    switch (args.storage_type)
    {
        case sp::storage::storage_type::file:
            if (sp::file_storage storage{args.output, args.position}; args.batch_mode)
                storage.write_batch(args.position);
            else
                storage.write(args.printing_type, args.position);
            break;
        case sp::storage::storage_type::network:
            throw std::invalid_argument("network type not implemented yet");
            break;
    }
}
catch (boost::program_options::error const& exp)
{
    std::cerr << exp.what() << std::endl;
    return 1;
}
catch (std::exception const& exp)
{
    std::cerr << exp.what() << std::endl;
    return 1;
}
