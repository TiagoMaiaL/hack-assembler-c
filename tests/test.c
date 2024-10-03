#include <stdio.h>
#include <string.h>

// Small library for performing assertions and running automated tests.

// TODO: Move these to a header file.
void tst_str_equals(char *a, char *b);
void tst_int_equals(int a, int b);

void tst_suite_begin(char *title);
void tst_suite_finish();
void tst_unit(char *message, void (*tst_func)());

static int tests_count;
static int failures_count;

void print_divider()
{
    printf("=============================\n");
}

void print_header(char *suite_title)
{
    printf("%s\n", suite_title);
    print_divider();
}

void print_footer()
{
    print_divider();
    printf("Total tests ran: %d\n", tests_count);
    printf("Number of assertion failures: %d\n", failures_count);
}

void tst_suite_begin(char *title)
{
    tests_count = 0;
    failures_count = 0;
    
    print_header(title);
}

void tst_suite_finish()
{
    print_footer();
}

void tst_unit(char *title, void (*tst_func)())
{
    int failures;

    failures = failures_count;

    printf("tst: %s\n", title);

    tst_func();

    if (failures < failures_count) {
        printf("FAILED \n");
    } else {
        printf("PASSED \n");
    }

    ++tests_count;

    printf("\n");
}

void tst_str_equals(char *a, char *b)
{
    if (strcmp(a, b) != 0) {
        printf("assertion failure: tst_str_equals(\"%s\", \"%s\")\n", a, b);
        ++failures_count;
    }
}

void tst_int_equals(int a, int b)
{
    if (a != b) {
        printf("assertion failure: tst_int_equals(%d, %d)\n", a, b);
        ++failures_count;
    }
}

void some_test()
{
    tst_str_equals("some", "some");
    tst_str_equals("not ", "the same");
}

void some_test_2()
{
    tst_int_equals(1, 1);
    tst_int_equals(2, 3);
}

void some_test_3()
{
    tst_int_equals(2, 2);
    tst_str_equals("ab", "ab");
}

int main()
{
    tst_suite_begin("Testing the test library"); 
    tst_unit("Some test 1", some_test);
    tst_unit("Some test 2", some_test_2);
    tst_unit("Some test 3", some_test_3);
    tst_suite_finish();
}
