#include "nt_status.h"

const char *nt_str_status(nt_status state)
{
    switch (state)
    {
    case NT_SUCCESS:
        return "Success";
    case NT_ERR_NULL_PTR:
        return "Null pointer";
    case NT_ERR_ALLOC:
        return "Allocation failed";
    case NT_ERR_OUT_OF_BOUNDS:
        return "Index out of bounds";
    case NT_ERR_INVALID_ARG:
        return "Invalid argument";
    case NT_ERR_WRITE_FAILED:
        return "Write operation failed";
    default:
        return "Unknown error";
    }
}
