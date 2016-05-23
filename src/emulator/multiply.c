/***************************************************************************
 * FILE NAME: multiply.c                                                   *
 *                                                                         *
 * PURPOSE: Carries out multiply instruction of ARM11                      *
 *          Accesses the ARM11 state to manipulate registers               *
 ***************************************************************************/

#include "multiply.h"

/* This might need to be defined somewhere else to reduce reduncancy.
 * Maybe util/...? */
#define SIGN_BIT 1 << 31

static uint32_t mul_accumulate(uint32_t, uint32_t, uint32_t);
static uint32_t mul_normal(uint32_t, uint32_t);
static uint32_t check_zero(uint32_t);
static uint32_t check_neg(uint32_t);

/* Pre: (*instruction).cond evaluates to true */
void mul_exec(void* instruction) {
    struct mul_instr* instr;
    instr = (struct mul_instr*) instruction;

    /* TODO: Add set-condition flag behaviour */
    uint32_t m = get_register((*instr).rm);
    uint32_t n = get_register((*instr).rn);
    uint32_t s = get_register((*instr).rs);

    uint32_t result = ((*instr).acc) ? mul_accumulate(m, n, s)
                                     : mul_normal(m, s);

    set_register((*instr).dest, result);
}

/*
 * Function : mul_accumulate
 * -------------------------
 * Perform the arithmetic part of the multiply instruction, accumulate variant.
 * Note: The result is casted to a 32bit integer (4 words). This function
 * should be sufficient for the specification of the instruction.
 */
static uint32_t mul_accumulate(uint32_t m, uint32_t s, uint32_t n) {
    return m * s + n;
}

/*
 * Function : mul_normal
 * -------------------------
 * Perform the multiply instruction, non-accumulate variant.
 * Same note applies as for mul_accumulate.
 */
static uint32_t mul_normal(uint32_t m, uint32_t s) {
    return m * s;
}

/*
 * Function : check_zero
 * Satisfies the update conditions for the flag Z.
 * Returns the flag <-> result of multiply is zero.
 */
static uint32_t check_zero(uint32_t val) {
    return (val) ? 0 : CPSR_Z;
}

/*
 * Function : check_neg
 * Satisfies the update conditions for the flag N.
 * Returns the flag <-> result of multiply is zero.
 */
static uint32_t check_neg(uint32_t val) {
    return (val & SIGN_BIT) ? CPSR_N : 0;
}
