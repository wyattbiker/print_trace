/* This must be on top. */
#define _XOPEN_SOURCE 700

/* Paste this on the file you want to debug. */
#define UNW_LOCAL_ONLY
#include <cxxabi.h> // needed for abi::__cxa_demangle
#include <libunwind.h>
#include <memory>


void print_trace(int trace_depth = 10);

// Symbol name demangler
std::shared_ptr<char> demangle(const char *abiName) {
    int status;
    char *ret = abi::__cxa_demangle(abiName, 0, 0, &status);

    /* NOTE: must free() the returned char when done with it! */
    std::shared_ptr<char> retval;
    retval.reset((char *)ret, [](char *mem) { if (mem) free((void*)mem); });
    return retval;
}

void print_trace(int trace_depth) {
    char sym[256];
    unw_context_t context;
    unw_cursor_t cursor;
    unw_getcontext(&context);
    unw_init_local(&cursor, &context);
    int counter=0;
    while (unw_step(&cursor) > 0) {
        unw_word_t offset, pc;
        unw_get_reg(&cursor, UNW_REG_IP, &pc);
        if (pc == 0) {
            break;
        }
        if (trace_depth-- > 0) {
            printf("0x%lx: (%d) ", (unsigned long)pc, counter++);
            if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
                // printf(" (%s+0x%lx)\n", sym, (unsigned long)offset);  // raw print
                // Demangle symbol names
                std::shared_ptr<char> retval = demangle(sym);
                if (retval) {
                    printf(" %s\n", retval.get());
                } else {
                    printf(" %s\n", sym);
                }
            } else {
                printf(" -- error: unable to obtain symbol name for this frame\n");
            }
        }
    }
    puts("");
}

