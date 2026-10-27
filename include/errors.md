# Error handling in VFS

Errors are defined in [VFS/include/errors.h](VFS/include/errors.h) and [VFS/lib/errors.c](VFS/lib/errors.c).

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
