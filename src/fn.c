#include "fn.h"

Str FnFormat(const Str text, ...) {
    static char buffers[MAX_TEXTFORMAT_BUFFERS][MAX_TEXT_BUFFER_LENGTH] = { 0 };
    static int index = 0;

    char *currentBuffer = buffers[index];
    memset(currentBuffer, 0, MAX_TEXT_BUFFER_LENGTH);

    va_list args;
    va_start(args, text);
    vsnprintf(currentBuffer, MAX_TEXT_BUFFER_LENGTH, text, args);
    va_end(args);

    index += 1;
    if (index >= MAX_TEXTFORMAT_BUFFERS) index = 0;

    return currentBuffer;
}

FnState FnInit(Str mdna, Str target) {
    FnState STMP;

    // LLVMOut
    STMP.ll.fln = mdna;
    STMP.ll.fl = fopen(FnFormat("%s.ll", mdna), "w");

    // LLVMModule
    STMP.module.module = mdna;
    STMP.module.target = target;
    STMP.module.val = malloc(sizeof(FnVal) * 20);

    return STMP;
}

void FnPInit(FnState* STMP, Str mdna, Str target) {
    // LLVMOut
    STMP->ll.fln = mdna;
    STMP->ll.fl = fopen(FnFormat("%s.ll", mdna), "w");

    // LLVMModule
    STMP->module.module = mdna;
    STMP->module.target = target;
    STMP->module.val = malloc(sizeof(FnVal) * 20);
}


void FnDestroy(FnState* fn) {
    fclose(fn->ll.fl);
    free(fn->module.val);
}
