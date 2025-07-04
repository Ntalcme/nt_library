#ifndef NT_ERROR_H
#define NT_ERROR_H

typedef enum
{
    NT_SUCCESS = 0,
    NT_ERR_NULL_PTR,
    NT_ERR_ALLOC,
    NT_ERR_OUT_OF_BOUNDS,
    NT_ERR_INVALID_ARG,
    NT_ERR_WRITE_FAILED
} nt_status;

const char *nt_str_status(nt_status state);

#endif
