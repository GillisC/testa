#include "testa.h"

static TestCase *tests_head = NULL;
bool __test_passed;

int total_tests = 0;
int passed_tests = 0;
int failed_tests = 0;
int total_assertions = 0;
int passed_assertions = 0;
int failed_assertions = 0;

void register_test(const char *test_name, TestFn fn) {
    TestCase *test_case = malloc(sizeof(TestCase));
    test_case->name = test_name;
    test_case->fn = fn;
    test_case->next = NULL;

    // if tests_head is null
    if (!tests_head) {
        tests_head = test_case;
    } 
    else {
        TestCase *previous = NULL;
        TestCase *current = tests_head;
        while (current) {
            previous = current;
            current = current->next;
        }
        // when we reached a null
        previous->next = test_case;
    }
    total_tests++;
}

void run_all_tests() {
    printf("Running  %d tests.\n", total_tests);
    printf("========================================\n");
    TestCase *current = tests_head;    
    while(current) {
        RUN_TEST(current->name, current->fn);
        current = current->next;
    }
    printf("============= Test Summary =============\n");
    printf("Total tests:      %d\n", total_tests);
    printf("Total assertions: %d\n", total_assertions);
    printf("Passed:           %d\n", passed_tests);
    printf("Failed:           %d\n", total_tests - passed_tests);
    printf("========================================\n");
}
