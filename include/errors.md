# Error handling in VFS

Errors are defined in [errors.h](errors.h) and [errors.c](../src/lib/errors.c).

errors are resolved by a single look up table that identifies the specific error handling fucntion to that spefic error.
```c
    static const ErrorInfo erro_info[ENUM_COUNT] = {}
```

errors are called globally from the set_erro() function.
```c
void set_error(Errors error, bool print_message_to_console) {
    if(print_message_to_console) {
        print_message(&erro_info[error]);
    }
// true prints message set at look up table.

/* 
    *more implementation.
 */
}

```
