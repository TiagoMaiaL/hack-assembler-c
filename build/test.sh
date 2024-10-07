source_files=(
    '../src/utils.c'
    '../src/ainst-bin.c'
    '../src/cinst-bin.c'
)
test_files=(
    '../tests/test-entry.c'
    '../tests/test.c'
    '../tests/test-utils.c'
    '../tests/test-ainst-bin.c'
    '../tests/test-cinst-bin.c'
)
files=("${source_files[@]}" "${test_files[@]}")

args=""

for file in "${files[@]}"; do
    args+=$file' '
done

clang $args
