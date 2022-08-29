#include <file_storage.hpp>

using namespace sp;

file_storage::file_storage(std::filesystem::path const& storage_path)
    : storage_path{storage_path},
    storage_file{storage_path, std::ios::out|std::ios::trunc},
    line_height{12},
    buffer{}
{
    if (!storage_file.is_open())
        std::runtime_error("storage file could not open");
}

file_storage::~file_storage()
{
    if (storage_path.empty())
        std::cout << buffer.str();
    else
        storage_file << buffer.str();

    storage_file.close();
}

void file_storage::write(printing_type type, unsigned int position)
{
    switch (type)
    {
        case printing_type::write:
            if (request_credentials())
            {
                write_start();
                write_vertical_space(position);
                write_credentials(position);
                write_end();
            }
            break;
        case printing_type::wipe:
            {
                write_start();
                write_vertical_space(position);
                write_block();
                write_end();
            }
            break;
    }
}

void file_storage::write_batch(unsigned int position)
{
    write_start();
    write_vertical_space(position);

    while (request_credentials())
    {
        write_credentials(position++);
        clear();
    }

    write_end();
}

void file_storage::write_vertical_space(unsigned int index)
{
    if (--index > 0)
        buffer << R"(\vspace*{)" << index * line_height << "pt}\n";
}

void file_storage::write_start()
{
    buffer << R"(\documentclass[a4paper,oneside,)";
    buffer << line_height << R"(pt]{article})" << "\n";
    buffer << R"(\usepackage[utf8]{inputenc})" << "\n";
    buffer << R"(\begin{document})" << "\n";
    buffer << R"(\noindent)" << "\n";
    buffer << R"(\begin{flushleft})" << "\n";
}

void file_storage::write_end()
{
    buffer << R"(\end{flushleft})" << "\n";
    buffer << R"(\end{document})" << "\n";
}

void file_storage::write_block()
{
    buffer << R"(\leavevmode\xleaders\hbox{█}\hfill\kern0pt )" << "\n";
}

void file_storage::write_credentials(unsigned int index)
{
    buffer << R"(\expandafter\string\csname )";
    buffer << index << ". " << keys.username << "@" << keys.domain;
    buffer << R"( \endcsname)" << "\n";
    buffer << R"(\leavevmode\xleaders\hbox{-}\hfill\kern0pt )" << "\n";
    buffer << R"(\expandafter\string\csname )";
    buffer << keys.passphrase;
    buffer << R"( \endcsname\\)" << "\n";
}
