cd "`dirname $0`"

artifacts="artifacts"

if ! [ -d ./$artifacts ]; then
    mkdir $artifacts
fi

cd $artifacts

test_files=(
    '../test-files/Add.asm'
    '../test-files/Max.asm'
    '../test-files/Rect.asm'
    '../test-files/Pong.asm'
)
files=("${test_files[@]}")

if sh ../build.sh; then
    for file in "${files[@]}"; do
        output_file="`echo $file | cut -d "/" -f 3 | cut -d "." -f 1`.hack"
        echo $file $output_file
        ./hasm $file $output_file
    done
fi
