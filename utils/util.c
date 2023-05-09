#include "util.h"

#include <stdlib.h>
#include <stdarg.h>

fn_result set_fn(int n_fn, ...)
{
    va_list v;
    va_start(v, n_fn);
    void *(*fn)() = NULL;
    for (int i = 0; i < n_fn; i++) {
        fn = va_arg(v, void *(*)());
        if (fn != NULL) {
            break;
        }
    }
    va_end(v);
    return fn;
}