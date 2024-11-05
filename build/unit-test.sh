cd "`dirname $0`"

artifacts="artifacts"

if ! [ -d ./$artifacts ]; then
    mkdir $artifacts
fi

cd $artifacts

source_files=(
    '../../src/utils.c'
    '../../src/ainst-bin.c'
    '../../src/cinst-bin.c'
    '../../src/lexer.c'
    '../../src/parser.c'
    '../../src/symbols.c'
)
test_files=(
    '../../tests/test-entry.c'
    '../../tests/test.c'
    '../../tests/test-utils.c'
    '../../tests/test-ainst-bin.c'
    '../../tests/test-cinst-bin.c'
    '../../tests/test-lexer.c'
    '../../tests/test-parser.c'
    '../../tests/test-symbols.c'
)
files=("${source_files[@]}" "${test_files[@]}")

args=""

if [ -f ./_test ]; then
    rm _test
fi

for file in "${files[@]}"; do
    args+=$file' '
done

if clang -o _test $args; then
    ./_test
fi

