#ifndef TESTA_H
#define TESTA_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef TESTA_USE_COLOR
#define TRY_COLOR(color) color
#else
#define TRY_COLOR(color) ""
#endif

#define COLOR_RESET "\x1b[0m"

#define GREEN_256 "\x1b[38;5;34m"
#define RED_256 "\x1b[38;5;160m"

extern bool __test_passed;
#define FAIL_TEST() __test_passed = false

extern int total_tests;
extern int failed_tests;

extern int total_assertions;
extern int passed_assertions;
extern int failed_assertions;

// macro that expands name into a void name() function
// it then creates the function register_##name which expands into
// register_name() the constructor attribute makes it so that the function is
// executed before entering main which in turn runs the register_test function
// which is a static function that takes a string and a function pointer and
// adds it to a global list of tests
#define TEST(name)                                                             \
    void name();                                                               \
    __attribute__((constructor)) void register_##name() {                      \
        register_test(#name, name);                                            \
    }                                                                          \
    void name()

// TODO add time stat
#define RUN_TEST(test_name, test_func)                                         \
    do {                                                                       \
        __test_passed = true;                                                  \
        test_func();                                                           \
        if (__test_passed) {                                                   \
            passed_tests++;                                                    \
            printf("[ " TRY_COLOR(GREEN_256) "PASS" TRY_COLOR(                 \
                       COLOR_RESET) " ] %s (%dms)\n",                          \
                   test_name, 0);                                              \
        } else {                                                               \
            printf("[ " TRY_COLOR(RED_256) "FAIL" TRY_COLOR(                   \
                       COLOR_RESET) " ] %s (%dms)\n",                          \
                   test_name, 0);                                              \
        }                                                                      \
    } while (0)

#define ASSERT_EQ_INT(a, b)                                                    \
    do {                                                                       \
        total_assertions++;                                                    \
        if (a != b) {                                                          \
            FAIL_TEST();                                                       \
            printf(                                                            \
                "%s:%d: Failure\nExpected equality of these values:\n  %d\n  " \
                "%d\n",                                                        \
                __FILE__, __LINE__, a, b);                                     \
        }                                                                      \
    } while (0)

#define ASSERT_EQ_FLOAT(a, b, epsilon)                                         \
    do {                                                                       \
        total_assertions++;                                                    \
        if (fabs((a) - (b)) > epsilon) {                                       \
            FAIL_TEST();                                                       \
            printf(                                                            \
                "%s:%d: Failure\nExpected equality of these values:\n  %f\n  " \
                "%f\n",                                                        \
                __FILE__, __LINE__, a, b);                                     \
        }                                                                      \
    } while (0)

#define ASSERT_EQ_DOUBLE(a, b, epsilon)                                        \
    do {                                                                       \
        total_assertions++;                                                    \
        if (fabs((a) - (b)) > epsilon) {                                       \
            FAIL_TEST();                                                       \
            printf(                                                            \
                "%s:%d: Failure\nExpected equality of these values:\n  %f\n  " \
                "%f\n",                                                        \
                __FILE__, __LINE__, a, b);                                     \
        }                                                                      \
    } while (0)

#define ASSERT_EQ_STR(a, b)                                                    \
    do {                                                                       \
        total_assertions++;                                                    \
        if (strcmp(a, b) != 0) {                                               \
            FAIL_TEST();                                                       \
            printf(                                                            \
                "%s:%d: Failure\nExpected equality of these values:\n  %s\n  " \
                "%s\n",                                                        \
                __FILE__, __LINE__, a, b);                                     \
        }                                                                      \
    } while (0)

#define ASSERT_EQ_CHAR(a, b)                                                   \
    do {                                                                       \
        total_assertions++;                                                    \
        if (a != b) {                                                          \
            FAIL_TEST();                                                       \
            printf(                                                            \
                "%s:%d: Failure\nExpected equality of these values:\n  %c\n  " \
                "%c\n",                                                        \
                __FILE__, __LINE__, a, b);                                     \
        }                                                                      \
    } while (0)

#define ASSERT_EQ_PTR(a, b)                                                    \
    do {                                                                       \
        total_assertions++;                                                    \
        if (a != b) {                                                          \
            FAIL_TEST();                                                       \
            printf(                                                            \
                "%s:%d: Failure\nExpected equality of these values:\n  %p\n  " \
                "%p\n",                                                        \
                __FILE__, __LINE__, a, b);                                     \
        }                                                                      \
    } while (0)

#define ASSERT_TRUE(a)                                                         \
    do {                                                                       \
        total_assertions++;                                                    \
        if (!a) {                                                              \
            FAIL_TEST();                                                       \
            printf(                                                            \
                "%s:%d: Failure\nExpected equality of these values:\n  %d\n  " \
                "true\n",                                                      \
                __FILE__, __LINE__, a);                                        \
        }                                                                      \
    } while (0)

#define ASSERT_FALSE(a)                                                        \
    do {                                                                       \
        total_assertions++;                                                    \
        if (a) {                                                               \
            FAIL_TEST();                                                       \
            printf(                                                            \
                "%s:%d: Failure\nExpected equality of these values:\n  %d\n  " \
                "false\n",                                                     \
                __FILE__, __LINE__, a);                                        \
        }                                                                      \
    } while (0)

// aliases any function pointer that has no arguments and returns void as a
// *TestFn
typedef void (*TestFn)(void);
// aliases any function pointer that has no arguments and returns void as a
// *TestFn
typedef void (*TestFn)(void);

// we store the tests in a linked list
typedef struct TestCase {
    const char *name;
    TestFn fn;
    struct TestCase *next;
} TestCase;

// registers a test to a global linked list of tests
void register_test(const char *test_name, TestFn fn);

// iterates and executes each test in the global linked list of tests
void run_all_tests();

#endif // TESTA_H
