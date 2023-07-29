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

    //fprintf(STMP.ll.fl, "; ModuleID = '%s.fn'\n"
    //        "source_filename = '%s.fn'\n"
    //        "target datalayout = 'e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128'\n"
    //        "target triple = 'x86_64-pc-linux-gnu'\n\n",
    //        mdna,
    //        mdna
    //    );

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

Str FnTypeS(FnType type) {
    if (type == FN_INT8)
        return "i8";
    else if (type == FN_INT16)
        return "i16";
    else if (type == FN_INT32)
        return "i32";
    else if (type == FN_UINT8)
        return "u8";
    else if (type == FN_UINT16)
        return "u16";
    else if (type == FN_UINT32)
        return "u32";
}

FnFuncType FnFuncTypeN(FnType ret, FnType* params) {
    int c = 0;
    while (true) {
        if (params[c] == FN_NULL) {
            break;
        }
        c++;
    }

    return (FnFuncType) {.ret = ret, .params = (FnType*) params, .len = c};
}

FnBlock FnBlockAppend(char** bls) {
    FnBlock tmp;
    for (int i = 0; i < MAX_BLOCKS_LENGHT; i++) {
        if (bls[i] == NULL) {
            break;
        }
        strcpy(tmp.blocks[i], bls[i]);
    }
    return tmp;
}

FnFunc FnFuncNew(Str name, FnFuncType type) {
    FnFunc tmp;
    tmp.ty = type;
    tmp.len = 0;
    tmp.cgn = malloc(sizeof(char) * 80);
    // Ex:            define i32 @name
    tmp.len += sprintf(tmp.cgn + tmp.len, "define %s @%s(", FnTypeS(type.ret), name);
    // Ex:            (i8 %a, i8 %b)
    if (type.len == 0)
        tmp.len += sprintf(tmp.cgn + tmp.len, ") {\nentry:\n");

    for (int i = 0; i < type.len; i++) {
        if (i == type.len - 1) {
            tmp.len += sprintf(tmp.cgn + tmp.len, "%s %%%d) {\nentry:\n", FnTypeS(type.params[i]), i);
            break;
        }
        tmp.len += sprintf(tmp.cgn + tmp.len, "%s %%%d, ", FnTypeS(type.params[i]), i);
    }
    return tmp;
}

void FnFuncRet(FnFunc* fn, int32_t ret) {
    fn->len += sprintf(fn->cgn + fn->len, "ret %s %d\n", FnTypeS(fn->ty.ret), ret);
}

void FnFuncRetLL(FnFunc* fn, int64_t ret) {
    fn->len += sprintf(fn->cgn + fn->len, "ret %s %d\n", FnTypeS(fn->ty.ret), ret);
}

void FnFuncRetExp(FnFunc* fn, Str exp) {
    fn->len += sprintf(fn->cgn + fn->len, "ret %s %%%s\n", FnTypeS(fn->ty.ret), exp);
}

void FnFuncAddBuilder(FnFunc* fn, FnType ty, Str nm, int32_t lf, int32_t rg) {
    fn->len += sprintf(fn->cgn + fn->len, "%%%s = add %s %d, %d\n", nm, FnTypeS(ty), lf, rg);
}

void FnFuncAddLLBuilder(FnFunc* fn, FnType ty, Str nm, int64_t lf, int64_t rg) {
    (void) fn;
    (void) ty;
    (void) nm;
    (void) lf;
    (void) rg;
}

void FnFuncMulBuilder(FnFunc* fn, FnType ty, Str nm, int32_t lf, int32_t rg) {
    (void) fn;
    (void) ty;
    (void) nm;
    (void) lf;
    (void) rg;
}

void FnFuncMulLLBuilder(FnFunc* fn, FnType ty, Str nm, int64_t lf, int64_t rg) {
    (void) fn;
    (void) ty;
    (void) nm;
    (void) lf;
    (void) rg;
}

void FnFuncDivBuilder(FnFunc* fn, FnType ty, Str nm, int32_t lf, int32_t rg) {
    (void) fn;
    (void) ty;
    (void) nm;
    (void) lf;
    (void) rg;
}

void FnFuncDivLLBuilder(FnFunc* fn, FnType ty, Str nm, int64_t lf, int64_t rg) {
    (void) fn;
    (void) ty;
    (void) nm;
    (void) lf;
    (void) rg;
}

void FnFuncSubBuilder(FnFunc* fn, FnType ty, Str nm, int32_t lf, int32_t rg) {
    (void) fn;
    (void) ty;
    (void) nm;
    (void) lf;
    (void) rg;
}

void FnFuncSubLLBuilder(FnFunc* fn, FnType ty, Str nm, int64_t lf, int64_t rg) {
    (void) fn;
    (void) ty;
    (void) nm;
    (void) lf;
    (void) rg;
}

void FnFuncEnd(FnFunc* fn) {
    fn->len += sprintf(fn->cgn + fn->len, "}\n ");
}

void FnFuncClose(FnFunc* fn) {
    free(fn->cgn);
}

void FnDestroy(FnState* fn) {
    fclose(fn->ll.fl);
    free(fn->module.val);
}
