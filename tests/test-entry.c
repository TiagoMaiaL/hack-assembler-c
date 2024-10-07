#include "test.h"
#include "test-ainst-bin.h"
#include "test-cinst-bin.h"
#include "test-utils.h"

int main()
{
    test_utils();
    test_ainst_translation();
    test_cinst_translation();

    // TODO: Return 1 if any error fails.
    // return tst_result();
    return 0;
}

