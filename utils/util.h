#ifndef _UTIL_H
#define _UTIL_H

typedef void * (*fn_result)();

fn_result set_fn(int n_fn, ...);

#endif /* _UTIL_H */