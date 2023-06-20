#include <storage.hpp>

using namespace sp;

bool storage::request_credentials()
{
    std::cout << "Username: ";
    std::cin >> keys.username;
    if (keys.username.empty())
    {
        std::cout << "\n";
        return false;
    }

    std::cout << "Domain: ";
    std::cin >> keys.domain;
    if (keys.domain.empty())
    {
        std::cout << "\n";
        return false;
    }

    std::cout << "Passphrase: ";
    std::cin >> keys.passphrase;
    if (keys.passphrase.empty())
    {
        std::cout << "\n";
        return false;
    }

    return true;
}

void storage::clear()
{
    keys.username.clear();
    keys.domain.clear();
    keys.passphrase.clear();
}
