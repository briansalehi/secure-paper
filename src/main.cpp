#include <exception>

#include <options.hpp>
#include <file_storage.hpp>

void write_to_storage(sp::storage&);

int main(int argc, char **argv)
try
{
    sp::options options(argc, argv);

    if (options.ready())
    {
        switch (options.storage_type)
        {
            case sp::storage::storage_type::file:
                sp::file_storage file_storage(options.output);
                file_storage.request_credentials();
                file_storage.write(options.printing_type, options.position);
        }
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
}
