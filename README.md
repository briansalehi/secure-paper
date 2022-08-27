# Secure Paper

Print your passphrases on paper once at a time.  
Each passphrase would be printed in a lower position relative
to its previous passphrase on paper, so that the same paper
can be used to add new passphrases.

## Prerequisites

Following packages are required in order to make this script
work:

* make
* cmake
* gcc
* texlive-most
* gpg
* evince (any other pdf reader is also fine)

## Setup

First clone the source:

```sh
git clone https://github.com/briansalehi/secure-paper.git
```

Then configure the project:

```sh
cmake -S secure-paper -B secure-paper-build -D CMAKE_BUILD_TYPE:STRING=release
```

Then build the project:

```sh
cmake --build secure-paper-build --parallel
```

And finally install it for your own:

```sh
cmake --install secure-paper-build --prefix $HOME/.local
```

## Usage

secure-paper can be used in different ways, but the simplest form of
its usage is to only call it.

### Write to File

Run secure-paper executable to enter into an interactive environment
and then type your new passphrases, either by long options or short:

```sh
secure-paper --position 4 --output output.txt
secure-paper -p 4 -o output.txt
secure-paper -p 4 output.txt
```

Interactively, you will be asked for different questions which cannot
be passed to the program as arguments for security reasons:

* Domain
* Username
* Passphrase

These questions are required in order to print your credentials on
paper.

Results would be saved into the output, you can then print it later.

The output option can be omitted and its value can be independently
given to program.

### Write to Network (not implemented yet)

Aside from file, output can written directly into network.

This can useful when you have a printer on your network:

```sh
secure-paper --position 4 --storage-type network --output 192.168.1.23:515
secure-paper -p 4 -t network -o 192.168.1.23:515
secure-paper -p 4 -t network 192.168.1.23:515
```

The output option can be omitted and its value can be independently
given to program.

## License

This work is licensed under [MIT License](LICENSE.md).
