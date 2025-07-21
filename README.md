# Testa - Lightweight C Testing Framework
A minimal, header-and-source C testing framework designed for quick setup, simple unit tests, and clear output

## Features
- Easy-to-use macro-based test registration
- Automatic test discovery with constructor functions
- Simple `ASSERT_EQ` macros for common types (int, float, double, strings, char, pointers)
- Colored output support (optional, controlled via compile flag)
- Test pass/fail reporting with file and line info
- Summary of total tests, assertions, and failures
- Single header + source file implementation for easy integration

## Usage
### 1. Include the header
```c
#include "testa.h"
```
### 2. Write tests using the `TEST` macro
```c
TEST(test_addition) {
    ASSERT_EQ_INT(add(1, 2), 3);
}
```
### 3. Run tests
call `run_all_tests()` from your desired entry point:
```c
int main() {
    run_all_tests();

    return 0;
}
```

## Compilation
To use in another project simply compile them along your other files. 
Define `-DTESTA_USE_COLOR` for colored output.
Use provided `Makefile` to generate the example programs

## Assertions
The following assertion macros are currently supported:
- ASSERT_EQ_INT(expected, actual)
- ASSERT_EQ_DOUBLE(expected, actual)
- ASSERT_EQ_FLOAT(expected, actual)
- ASSERT_EQ_STR(expected, actual)
- ASSERT_EQ_CHAR(expected, actual)
- ASSERT_EQ_PTR(expected, actual)
- ASSERT_TRUE(boolean)
- ASSERT_FALSE(boolean)

## License
Use this code freely according to the MIT licence

## Example Output

