#include <file_storage.hpp>

using namespace sp;

file_storage::file_storage(std::filesystem::path const& storage_path): storage_path{storage_path}
{
}

void file_storage::write(printing_type type, unsigned int position)
{
    buffer << R"(\documentclass{article})" << "\n";
    buffer << R"(\begin{document})" << "\n";
    buffer << R"(\noindent)" << "\n";

    for (int index = 1; index < position; ++index)
        buffer << index << R"(.\\)" << std::endl;

    buffer << R"(\expandafter\string\csname )";
    buffer << position << ". " << keys.username << "@" << keys.domain;
    buffer << R"( \endcsname)" << "\n";
    buffer << R"(\leavevmode\xleaders\hbox{-}\hfill\kern0pt )" << "\n";
    buffer << R"(\expandafter\string\csname )";
    buffer << keys.passphrase;
    buffer << R"( \endcsname)" << "\n";

    buffer << R"(\end{document})" << "\n";

    if (storage_path.empty())
    {
        std::cout << buffer.str();
    }
    else
    {
        std::ofstream storage_file(storage_path, std::ios::out|std::ios::trunc);

        if (!storage_file.is_open())
            std::runtime_error("storage file could not open");

        storage_file << buffer.str();
        storage_file.close();
    }
}
