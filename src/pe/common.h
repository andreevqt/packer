#pragma once

#include <Windows.h>
#include <stdint.h>
#include <string>
#include <stdio.h>

#define ALIGN(t, x, a)          ALIGN_MASK(x, (t)(a)-1)
#define ALIGN_MASK(x, mask)     (((x) + (mask))&~(mask))

#if defined(_MSC_VER)
#define TLS __declspec(thread)
#elif defined(_GNU_C)
// TODO: gcc specific
#endif 


