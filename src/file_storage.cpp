#include <file_storage.hpp>

using namespace sp;

file_storage::file_storage(std::filesystem::path const& storage_path): storage_path{storage_path}
{
    storage_file.open(storage_path, std::ios::out|std::ios::trunc);

    if (!storage_file.is_open())
        std::runtime_error("storage file could not open");
}

file_storage::~file_storage()
{
    if (storage_file.is_open())
        storage_file.close();
}

void file_storage::write(unsigned int position)
{
    storage_file << R"(\documentclass{article})" << std::endl;
    storage_file << R"(\begin{document})" << std::endl;

    for (unsigned int line = 1; line < position; ++line)
        storage_file << R"(\vspace{10px})" << std::endl;

    storage_file << keys.username;
    storage_file << "@" << keys.domain;
    storage_file << R"( \hfill )" << keys.passphrase;
    storage_file << std::endl;

    storage_file << R"(\end{document})" << std::endl;
}

void file_storage::record(credentials const& secrets)
{
    keys = secrets;
}
