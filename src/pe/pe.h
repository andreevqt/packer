#pragma once
#include "common.h"

#if defined (_WIN32) 
#   if defined(pe_EXPORTS)
#       define  PE_EXPORT __declspec(dllexport)
#   elif defined(USE_STATIC_LIB)
#       define  PE_EXPORT 
#   else
#       define  PE_EXPORT __declspec(dllimport)
#   endif 
#else 
#   define PE_EXPORT
#endif

namespace PE {

enum Arch
{
    ARCH_X86 = 0,
    ARCH_X64,
    ARCH_UNSUPPORTED,
    ARCH_UNKNOWN
};

enum Error
{
    ERR_SUCCESS = 0,
    ERR_READ_DOS_HEADER,
    ERR_READ_NT_HEADER,
    ERR_WRONG_DOS_MAGIC,
    ERR_WRONG_NT_OPTIONAL_MAGIC,
    ERR_WRONG_NT_SIGNATURE,
    ERR_UNKNOWN
};

// abstract base class
class PE_EXPORT PeBase
{
public:
    PeBase(FILE* file);
    PeBase(const PeBase& peBase) = delete;

public:
    virtual ~PeBase();

    // some static methods
    static Arch GetArch(FILE* file);
    static void ReadDosHeader(FILE* file, PIMAGE_DOS_HEADER dosHeader);

private:

};

// deriviates
class PE_EXPORT Pe_x86 : public PeBase 
{
public:
    Pe_x86(FILE* file);
    Pe_x86(const Pe_x86&) = delete;
    ~Pe_x86();
};

class PE_EXPORT Pe_x64 : public PeBase 
{
public:
    Pe_x64(FILE* file);
    Pe_x64(const Pe_x64&) = delete;
    ~Pe_x64();

};

PE_EXPORT PeBase* create(FILE* file);

Error GetErr();
void SetErr(Error err);
std::string ErrToStr(Error err);

} //!PE