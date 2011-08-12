#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Start format of an error message. */
#define MSG_START "%s:%d: error: "

/** Aborts the program with an error message.
 * The printed error message is prefixed with #MSG_START.
 * @param format Format of the error message.
 * @param ... format arguments
 */
#define abortWithMsg(format, ...) \
    do { \
        size_t fmtLen = strlen(MSG_START) + strlen(format) + 1 + 1; \
        char fmt[fmtLen]; \
        snprintf(fmt, fmtLen, "%s%s\n", MSG_START, format); \
        fprintf(stderr, fmt, __FILE__, __LINE__, __VA_ARGS__); \
        abort(); \
    } while (false)

/** The program name.
 * It is stored in a global variable by #main to make it available for #abortWithMsg anywhere in the program.
 */
const char *prgname;

/** Function pointer to benchmark functions.
 * @param num Number to pass to the benchmark function.
 * @return Result of the benchmark function.
 */
typedef uint_fast64_t(*fptr)(uint_fast64_t num);

/** An entry in the benchmark #functions table.
 * Entries in #functions should be declared using #defFunc for convenience.
 */
struct entry {

    /** The name of the function. */
    const char *name;

    /** The pointer to the function. */
    fptr func;
};

/** Declares an #entry in the #functions table.
 * @param name Name of the function.
 */
#define defFunc(name) { #name, name }

/** Benchmark function that recursively calculates a Fibonacci number.
 * @warning This function does not perform limits checks and thus does not detect overflows.
 * @param num Number of which to return the Fibonacci number.
 * @return Fibonacci number of \p num.
 */
uint_fast64_t fibo(uint_fast64_t num)
{
    switch (num) {
    case 0: return 0;
    case 1: return 1;
    default: return fibo(num - 1) + fibo(num - 2);
    }
}

/** Benchmark function that recursively calculates a factorial.
 * @warning This function does not perform limits checks and thus does not detect overflows.
 * @param num Number of which to return the factorial.
 * @return Factorial of \p num.
 */
uint_fast64_t fac(uint_fast64_t num)
{
    switch (num) {
    case 0: return 1;
    default: return num * fac(num - 1);
    }
}

/** Benchmark function that recursively calculates a triangle (Gauss sum).
 * @warning This function does not perform limits checks and thus does not detect overflows.
 * @param num Number of which to return the triangle (Gauss sum).
 * @return Triangle (Gauss sum) of \p num.
 */
uint_fast64_t triangle(uint_fast64_t num)
{
    switch (num) {
    case 0: return 0;
    default: return num + triangle(num - 1);
    }
}

/** Performance function pointer table. */
struct entry functions[] = {
    defFunc(fibo),
    defFunc(fac),
    defFunc(triangle),
};

/** Number of entries in #functions. */
#define NUM_FUNCTIONS (sizeof(functions) / sizeof(struct entry))

/** Parses a string to a uint_fast64_t.
 * If \p nptr is not a valid uint_fast64_t, the program is aborted with a corresponding error message.
 * @param nptr String to convert to uint_fast64_t.
 * @return number from parsing \p nptr.
 * @see strtoull for more information.
 */
uint_fast64_t parseLong(const char *nptr)
{
#define BASE 10
    char *endptr;
    uint_fast64_t num = strtoull(nptr, &endptr, BASE);
    if (!((*nptr != '\0') && (*endptr == '\0'))) {
        abortWithMsg("not a number: \"%s\"", nptr);
    }
    return num;
#undef BASE
}

/** Main program.
 *
 * If invoked without arguments, prints "hello, world".
 *
 * If invoked with two arguments, the first must be a supported function name, the second the numerical function argument.
 * That function then is invoked and the result printed.
 *
 * Any other use of arguments results in an error.
 *
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 * @return 0 in case of success, any other value indicates an error.
 */
int main(int argc, const char *argv[])
{
    prgname = argv[0];

    if (argc == 3) {
        uint_fast64_t num = parseLong(argv[2]);
        size_t index;
        const char *funcName = argv[1];
        for (index = 0; index < NUM_FUNCTIONS; index++) {
            if (0 == strcmp(functions[index].name, funcName)) {
                break;
            }
        }
        if (index >= NUM_FUNCTIONS) {
            abortWithMsg("function not supported: \"%s\"", funcName);
        }
        fptr fptr = functions[index].func;
        printf("%s(%lu) -> %lu\n", funcName, num, fptr(num));
    } else if (argc == 1) {
        printf("hello, world\n");
    } else {
        abortWithMsg("Wrong usage", "");
    }
    return 0;
}
