#include <storage.hpp>

using namespace sp;

void storage::request_credentials()
{
    std::cout << "Usagename: ";
    std::cin >> keys.username;

    std::cout << "Domain: ";
    std::cin >> keys.domain;

    std::cout << "Passphrase: ";
    std::cin >> keys.passphrase;
}
