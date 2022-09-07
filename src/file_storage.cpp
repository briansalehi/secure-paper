#include <file_storage.hpp>

using namespace sp;

file_storage::file_storage(std::filesystem::path const& storage_path, unsigned int const index)
    : storage_path{storage_path},
    line_spacing{12},
    buffer{}
{
    this->storage_path.replace_extension("tex");
    storage_file.open(this->storage_path, std::ios::out|std::ios::trunc);

    if (!storage_file.is_open())
        std::runtime_error("storage file could not open");

    write_start(index);
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
            wipe_line();
        }
        break;
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

void file_storage::write_vertical_space(unsigned int index)
{
    unsigned int position = --index * line_spacing * 1.5;

    if (index > 0)
        buffer << "\n" << std::string(8, ' ') << R"(\vspace*{)" << position << "pt}\n";
}

void file_storage::write_start(unsigned int index)
{
    buffer << R"(\documentclass[a4paper,oneside,)";
    buffer << line_spacing << R"(pt]{article})" << "\n";
    buffer << R"(
\usepackage[utf8]{inputenc}
\usepackage{setspace}
\usepackage{xparse}
\onehalfspacing

\newcommand{\dashfill}{%
    \leavevmode\xleaders\hbox{-}\hfill\kern0pt
}

\NewDocumentCommand{\passphrase}{mv}{%
    \texttt{#1}~\dashfill~\texttt{#2}%
}

\begin{document})";

    if (index > 1)
        buffer << "\n" << std::string(4, ' ') << R"(\pagenumbering{gobble})";

    buffer << R"(
    \noindent
    \begin{flushleft})";
}

void file_storage::write_end()
{
    buffer << R"(
    \end{flushleft}
\end{document})" << std::endl;
}

void file_storage::wipe_line()
{
    buffer << "\n" << std::string(8, ' ') << R"(\leavevmode\xleaders\hbox{█}\hfill\kern0pt )";
}

void file_storage::write_credentials(unsigned int index)
{
    buffer << std::string(8, ' ') << R"(\passphrase)";
    buffer << "{" << index << ". " << keys.username << "@" << keys.domain << "}";
    buffer << "{" << keys.passphrase << "}";
}
