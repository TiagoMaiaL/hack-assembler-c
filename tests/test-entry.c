#include "test.h"
#include "test-ainst-bin.h"
#include "test-cinst-bin.h"
#include "test-lexer.h"
#include "test-utils.h"
#include "test-parser.h"
#include "test-symbols.h"

int main()
{
    test_utils();
    test_ainst_translation();
    test_cinst_translation();
    test_lexer();
    test_parser();
    test_symbols_table();

    // TODO: Return 1 if any error happens.
    // return tst_result();
    return 0;
}

