#include <file_storage.hpp>

using namespace sp;

file_storage::file_storage(std::filesystem::path const& storage_path, unsigned int const index)
    : storage_path{storage_path},
    line_spacing{12},
    buffer{}
{
    if (!this->storage_path.empty())
        this->storage_path.replace_extension("tex");

    storage_file.open(this->storage_path, std::ios::out|std::ios::trunc);

    if (!storage_file.is_open())
        std::runtime_error("storage file could not open");

    bool page_numbering = index == 1 ? true : false;

    write_start(page_numbering);
    write_vertical_space(index);
}

file_storage::~file_storage()
{
    write_end();

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
        {
            if (request_credentials())
                write_credentials(position);
        }
        break;
        case printing_type::wipe:
        {
            wipe_line(position);
        }
        break;
        case printing_type::strikethrough:
        {
            strikethrough_line(position);
        }
    }
}

void file_storage::write_batch(unsigned int position)
{
    while (request_credentials())
    {
        write_credentials(position++);
        clear();
        std::cout << "\n";
    }
}

void file_storage::write_horizontal_space(unsigned int index)
{
    unsigned int digit_count = std::to_string(index).length() * 10;

    if (index > 0)
        buffer << std::string(4, ' ') << R"(\hspace*{)" << digit_count << R"(pt})" << '\n';
}

void file_storage::write_vertical_space(unsigned int index)
{
    unsigned int position = --index * line_spacing * 1.4;

    if (index > 0)
        buffer << std::string(4, ' ') << R"(\vspace*{)" << position << "pt}" << '\n';
}

void file_storage::write_start(bool const page_numbering)
{
    buffer << R"(\documentclass[a4paper,oneside,)" << line_spacing;
    buffer << R"(pt]{article})" << '\n';
    buffer << R"(\usepackage[dvipsnames]{xcolor})" << '\n';
    buffer << R"(\usepackage{setspace})" << '\n';
    buffer << R"(\onehalfspacing)" << "\n\n";
    buffer << R"(\newcommand{\dashfill}{\leavevmode\xleaders\hbox{-}\hfill\kern0pt})" << '\n';
    buffer << R"(\NewDocumentCommand{\passphrase}{mv}{\texttt{#1}~\dashfill~\texttt{#2}\par})" << '\n';
    buffer << R"(\newcommand{\blackbox}[0]{\colorbox{Black}{X}})" << '\n';
    buffer << R"(\newcommand{\strikethrough}[0]{{-}})" << "\n\n";
    buffer << R"(\begin{document})" << '\n';

    if (page_numbering)
        buffer << R"(\pagenumbering{arabic})" << '\n';
    else
        buffer << R"(\pagenumbering{gobble})" << '\n';

    buffer << R"(\noindent)" << '\n';
    buffer << R"(\begin{flushleft})" << '\n';
}

void file_storage::write_end()
{
    buffer << R"(\end{flushleft})" << '\n';
    buffer << R"(\end{document})" << '\n';
}

void file_storage::wipe_line(unsigned int index)
{
    write_horizontal_space(index);
    buffer << R"(\leavevmode\xleaders\hbox{\blackbox}\hfill\kern0pt)" << '\n';
}

void file_storage::strikethrough_line(unsigned int index)
{
    write_horizontal_space(index);
    buffer << R"(\leavevmode\xleaders\hbox{\strikethrough}\hfill\kern0pt)" << '\n';
}

void file_storage::write_credentials(unsigned int index)
{
    buffer << std::string(4, ' ') << R"(\passphrase)";
    buffer << "{" << index << ". " << keys.username << "@" << keys.domain << "}";
    buffer << "{" << keys.passphrase << R"(})" << '\n';
}
