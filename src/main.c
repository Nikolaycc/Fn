#include "fn.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define write(X, Y) fprintf(stdout, X, Y)
#define writef(X, Y, Z) fprintf(X, Y, Z)

#define PWD getenv("PWD")

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
    return "x86_64-pc-linux-gnu";
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

void FnCompile(const FnState state) {
    //printf("[LLVM COMPILE] (%s/%s.ll): Starting...\n", PWD, state.ll.fln);
    //system("llc program.ll -o a.s");
    //printf("[LLVM COMPILE]: Succses\n");
    //system(FnFormat("gcc a.s -o %s", state.ll.fln));
    //system(FnFormat("ld -o %s/%s %s/%s.o -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc -melf_x86_64", PWD, state.ll.fln, PWD, state.ll.fln));
    //printf("[CC COMPILE]: Succses\n");;
    //system(FnFormat("rm -rfv %s/%s.ll %s/%s.o", PWD, state.ll.fln, PWD, state.ll.fln));
}

void FnInterp(const FnState state) {
    system(FnFormat("lli %s.ll", state.ll.fln));
}

int main(int argc, Str* argv) {
    FnArg arg = (FnArg) {argc, argv};
    Str iorc;
    bool cp = false;
    if (FnArgGet(arg, "-i") == NULL)
        cp = true;

    FnState fn = FnInit(FnArgAtr(arg, "-o", "a.out"), FnArgAtr(arg, "-t", FnTarget()));

    FnType type[MAX_TYPE_PARAMS_LENGHT] = {FNULL};
    FnFuncType fntype = FnFuncTypeN(FN_INT32, type);

    // FnBlock bls = (FnBlock) {{"entry", "exit"}};

    FnFunc func = FnFuncNew("main", fntype);
    FnFuncAddBuilder(&func, FN_INT32, "result", 5, 5);
    FnFuncRetExp(&func, "result");
    FnFuncEnd(&func);

    fprintf(fn.ll.fl, func.cgn, 0);

    if (cp == true)
        FnCompile(fn);
    else
        FnInterp(fn);

    char* sys = malloc(sizeof(char) * 35);
    sprintf(sys, "./llc/llcf %s.ll", fn.ll.fln);

    printf("%s\n", sys);
    system(sys);

    free(sys);
    FnDestroy(&fn);
    FnFuncClose(&func);
    return 0;
}
