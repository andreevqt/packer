#include "pe.h"

using namespace PE;

namespace {

TLS Error lastErr = ERR_SUCCESS;

}

Error PE::GetErr()
{
    return lastErr;
}

void PE::SetErr(Error err)
{
    lastErr = err;
}

PeBase* PE::create(FILE* file)
{
    Arch arch = PeBase::GetArch(file);

    if (arch == ARCH_UNKNOWN)
        return nullptr;

    if (arch == ARCH_X86)
        return new Pe_x86(file);

    // ARCH_X64 unsupported currently
    return nullptr;
}

std::string PE::ErrToStr(Error err)
{
    if (err == ERR_SUCCESS)
        return "ERR_SUCCESS";
    if (err == ERR_READ_DOS_HEADER)
        return "ERR_READ_DOS_HEADER";
    if (err == ERR_READ_NT_HEADER)
        return "ERR_READ_NT_HEADER";
    if (err == ERR_WRONG_DOS_MAGIC)
        return "ERR_WRONG_DOS_MAGIC";
    if (err == ERR_WRONG_NT_OPTIONAL_MAGIC)
        return "ERR_WRONG_NT_OPTIONAL_MAGIC";
    if (err == ERR_WRONG_NT_SIGNATURE)
        return " ERR_WRONG_NT_SIGNATURE";
    return "ERR_UNKNOWN";
}


void PE::PeBase::ReadDosHeader(FILE* file,PIMAGE_DOS_HEADER pDosHeader)
{
    if (!file)
        return;

    if (fread(pDosHeader, sizeof(IMAGE_DOS_HEADER), 1, file) < 1)
    {
        SetErr(ERR_READ_DOS_HEADER);
        return;
    }
    
    if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        SetErr(ERR_WRONG_DOS_MAGIC);
        return;
    }
}

// PeBase
PE::PeBase::PeBase(FILE* file)
{

}

PE::PeBase::~PeBase()
{
}

Arch PE::PeBase::GetArch(FILE* file)
{
    if (!file)
        return ARCH_UNKNOWN;

    IMAGE_DOS_HEADER dosHeader;

    ReadDosHeader(file, &dosHeader);
    if (GetErr() != ERR_SUCCESS)
        return ARCH_UNKNOWN;

    if (fseek(file, dosHeader.e_lfanew, SEEK_SET) != 0)
    {
        SetErr(ERR_READ_NT_HEADER);
        return ARCH_UNKNOWN;
    }

    IMAGE_NT_HEADERS32 ntHeaders;
    if (fread(&ntHeaders, sizeof(ntHeaders), 1, file) < 1)
    {
        SetErr(ERR_READ_NT_HEADER);
        return ARCH_UNKNOWN;
    }

    if (ntHeaders.Signature != IMAGE_NT_SIGNATURE)
    {
        SetErr(ERR_WRONG_NT_SIGNATURE);
        return ARCH_UNKNOWN;
    }

    if (ntHeaders.OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC && ntHeaders.OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        SetErr(ERR_WRONG_NT_OPTIONAL_MAGIC);
        return ARCH_UNKNOWN;
    }

    return ntHeaders.OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC ? ARCH_X86 : ARCH_X64;
}

// Pe_x86

PE::Pe_x86::Pe_x86(FILE* pFile) :
    PeBase(pFile)
{
}

PE::Pe_x86::~Pe_x86()
{
}

// Pe_x64

PE::Pe_x64::Pe_x64(FILE* pFile) :
    PeBase(pFile)
{
}

PE::Pe_x64::~Pe_x64()
{
}
