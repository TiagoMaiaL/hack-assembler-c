cd "`dirname $0`"

source_files=(
    '../src/utils.c'
    '../src/ainst-bin.c'
    '../src/cinst-bin.c'
    '../src/lexer.c'
)
test_files=(
    '../tests/test-entry.c'
    '../tests/test.c'
    '../tests/test-utils.c'
    '../tests/test-ainst-bin.c'
    '../tests/test-cinst-bin.c'
    '../tests/test-lexer.c'
)
files=("${source_files[@]}" "${test_files[@]}")

args=""

if [ -f ./_test ]; then
    echo "removing test file"
    rm _test
fi

for file in "${files[@]}"; do
    args+=$file' '
done

if clang -o _test $args; then
    ./_test
fi

