#include "fn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define write(X, Y) fprintf(stdout, X, Y)
#define writef(X, Y, Z) fprintf(X, Y, Z)

typedef struct {
    int argc;
    Str* argv;
} FnArg;

Str FnTarget() {
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
#elif __APPLE__ || __MACH__
    return "Mac OSX";
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Other";
#endif
}

Str FnArgGet(FnArg src, const Str find) {
    for (int i = 0; i < src.argc; i++) {
        if (strcmp(find, src.argv[i]) == 0) {
            return src.argv[i];
        }
    }

    return NULL;
}

Str FnArgAtr(FnArg src, const Str find, Str df) {
    for (int i = 0; i < src.argc; i++) {
        if (strcmp(find, src.argv[i]) == 0) {
            return src.argv[i + 1];
        }
    }

    return df;
}


int main(int argc, Str* argv) {
    FnArg arg = (FnArg) {argc, argv};
    FnState fn = FnInit(FnArgAtr(arg, "-o", "a.out"), FnArgAtr(arg, "-t", FnTarget()));

    FnType type[MAX_TYPE_PARAMS_LENGHT] = {FN_INT8, FN_INT16, FN_INT32, FNULL};
    FnFuncType fntype = FnFuncTypeN(FN_INT32, type);

    // FnBlock bls = (FnBlock) {{"entry", "exit"}};

    FnFunc func = FnFuncNew("add", fntype);

    FnDestroy(&fn);
    return 0;
}
