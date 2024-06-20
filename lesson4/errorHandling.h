#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include "windows.h"

struct ComException
{
    HRESULT const hr;
    ComException(HRESULT const value) : hr(value) {}
};
inline void HR(HRESULT const hr)
{
    if (S_OK != hr) throw ComException(hr);
}

#endif // !ERROR_HANDLING_H


