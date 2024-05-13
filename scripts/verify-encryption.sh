#!/usr/bin/env bash

base="${1:-$PWD}"

warning() { tput bold; tput setaf 3; echo $@; tput sgr0; }
success() { tput bold; tput setaf 2; echo $@; tput sgr0; }
fail()    { tput bold; tput setaf 1; echo $@; tput sgr0; }
check()
{
    local path="$1"
    local already_checked="$2"
    local file_type

    file_type="$(file --mime-type "$path" | awk '{FS=":"} {print $2}')"

    echo -n "$path "
    case "$file_type" in
        text/plain)
            if grep -q 'BEGIN PGP MESSAGE' "$path"
            then
                begin_line="$(grep -n 'BEGIN PGP MESSAGE' "$path" | awk -F: '{print $1}')"

                if [ "${already_checked:-0}" -eq 0 ]
                then
                    warning "recovering"
                    cp "${path}" "${path}_backup"
                    sed -i "1,$((--begin_line))d" "$path"
                    check "$path" 1
                else
                    mv "${path}_backup" "${path}"
                    fail "cannot recover automatically"
                fi
            else
                fail "not encrypted"
            fi
            ;;
        application/pgp-encrypted)
            [ -f "${path}_backup" ] && rm "${path}_backup"
            if gpg --verify "$path" 2>/dev/null
            then
                success "ok"
            else
                fail "not verified"
            fi
            ;;
        application/pdf)
            warning "exposable file"
            ;;
        *)
            fail "unknown type"
            ;;
    esac
}

for path in $(find "$base" -maxdepth 1 -readable -type f)
do
    check "$path"
done
