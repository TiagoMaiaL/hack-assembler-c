cd "`dirname $0`"

artifacts="artifacts"

if ! [ -d ./$artifacts ]; then
    mkdir $artifacts
fi

cd $artifacts
rm -rf ./*

source_files=(
    '../../src/utils.c'
    '../../src/ainst-bin.c'
    '../../src/cinst-bin.c'
    '../../src/lexer.c'
    '../../src/parser.c'
    '../../src/symbols.c'
    '../../src/file.c'
    '../../src/main.c'
)
files=("${source_files[@]}")

args=""

if [ -f ./hasm ]; then
    rm hasm
    rm -rf *.dSYM
fi

for file in "${files[@]}"; do
    args+=$file' '
done

clang -g -Wall -o hasm $args
