#include <exception>

#include <options.hpp>
#include <file_storage.hpp>

void write_to_storage(sp::storage&);

int main(int argc, char **argv)
try
{
    sp::options options(argc, argv);

    if (!options.ready())
        return 0;

    switch (options.storage_type)
    {
        case sp::storage::storage_type::file:
            if (sp::file_storage file_storage(options.output); options.batch_mode)
                file_storage.write_batch(options.position);
            else
                file_storage.write(options.printing_type, options.position);
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
