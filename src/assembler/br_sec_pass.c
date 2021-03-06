#include "br_sec_pass.h"
#include "util/tokeniser.h"
#include "label_scanner.h"
#include "second_pass.h"
#include "string.h"

#define PIPELINE_OFFSET 8
#define SHIFT 2

void proc_br_instr(char* br_char, union decoded_instr *decoded) {
    decoded->br._id = 0x2;
    decoded->br._id2 = 0x2;

    decoded->br.cond = tokcond(br_char);

    char *label = tokbrlabel();

    uint32_t label_addr = get_label_address(label);
    uint32_t curr_addr = get_curr_instr_addr();

    int32_t offset = (label_addr - (curr_addr + PIPELINE_OFFSET)) >> SHIFT;

    decoded->br.offset = offset;
}
