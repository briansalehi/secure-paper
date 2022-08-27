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

## Usage

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

Run secure-paper executable to enter into another prompt and
then type your new passphrases, either by long options or short:

```sh
$ secure-paper --position 4 --output list.txt
$ secure-paper -p 4 -o list.txt
> Domain: dummy domain
> Username: dummy username
> Passphrase: dummy passphrase
```

Results would be saved into the output, you can then print it later.

## License

This work is licensed under [MIT License](LICENSE.md).
