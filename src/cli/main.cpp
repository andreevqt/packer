#include <stdio.h>
#include <stdint.h>
#include "pe/pe.h"
using namespace PE;

// WIP
// would be awesome to add a wrapper class
enum Option
{
    OPTION_PRINT_INFO = 1 << 0,



};

static uint32_t g_options = 0;

// TODO: extract file name properly
void Usage(const char* name)
{
    fprintf(stderr, "Usage: %s [options] input_file [output_file]\n", name);
    fprintf(stderr, "\tOptions:\n");
    fprintf(stderr, "\t\t-i: out file info\n");
    // TODO: options
}

bool HasOpt(uint32_t opt)
{
    return !!(g_options & opt);

}

void SetOpt(uint32_t opt)
{
    if (!HasOpt(opt))
        g_options |= opt;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        Usage(argv[0]);
        return -1;
    }
    FILE* pFile = fopen(argv[1], "rb");
    if (!pFile)
    {
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        Usage(argv[0]);
        return -1;
    }

    PeBase* pPe = create(pFile);
    if (!pPe)
    {
        fprintf(stderr, "Failed to process executable %s. REASON: %s\n", argv[1], ErrToStr(GetErr()).c_str());
        Usage(argv[0]);
        return -1;
    }

    if (pPe)
        delete pPe;

    return 0;
}