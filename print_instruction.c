/*
 * Author: Fong Ching Hin Stephen
 */

#include "mips.h"
#include "ram.h"
#include "registers.h"
#include "helper.h"

/*
 * print a MIPS instruction (no newline)
 * run reference implementation if unsure what to print
 */
void print_instruction(uint32_t instruction) {

  if (isSyscall(instruction)) printf("syscall");

  // fxthToythbits means from xth bit to yth bit
  // 1st bit is the least significant bit.
  uint32_t f7thTo11stbits = (instruction >> 6) & FIVE1;
  uint32_t f12ndTo16thbits = (instruction >> 11)
                            & FIVE1;
  uint32_t f17thTo21stbits = (instruction >> 16)
                            & FIVE1;
  uint32_t f22ndTo26thbits = (instruction >> 21)
                            & FIVE1;
  int16_t leastSig16bits = instruction & SIXTEEN1;

  // These three instructions must be checked first, since
  // their most significant 11 bits are special (all zeros).
  if (isSll(instruction)) {
    printf("sll $%d, $%d, %d", f12ndTo16thbits,
           f17thTo21stbits, f7thTo11stbits);

  } else if (isSrl(instruction)) {
    printf("srl $%d, $%d, %d", f12ndTo16thbits,
           f17thTo21stbits, f7thTo11stbits);

  } else if (isLui(instruction)) {
    printf("lui $%d, %d", f17thTo21stbits, leastSig16bits);

  // Starting from here. Instructions' most significant 6 bits
  // are zeros. They must be checked after checking the above 3
  // instructions.
  } else if (isAdd(instruction)) {
    printf("add $%d, $%d, $%d", f12ndTo16thbits,
       f22ndTo26thbits, f17thTo21stbits);

  } else if (isSub(instruction)) {
    printf("sub $%d, $%d, $%d", f12ndTo16thbits,
       f22ndTo26thbits, f17thTo21stbits);

  } else if (isAnd(instruction)) {
    printf("and $%d, $%d, $%d", f12ndTo16thbits,
       f22ndTo26thbits, f17thTo21stbits);

  } else if (isOr(instruction)) {
    printf("or $%d, $%d, $%d", f12ndTo16thbits,
       f22ndTo26thbits, f17thTo21stbits);

  } else if (isXor(instruction)) {
    printf("xor $%d, $%d, $%d", f12ndTo16thbits,
       f22ndTo26thbits, f17thTo21stbits);

  } else if (isSllv(instruction)) {
    printf("sllv $%d, $%d, $%d", f12ndTo16thbits,
       f17thTo21stbits, f22ndTo26thbits);

  } else if (isSrlv(instruction)) {
    printf("srlv $%d, $%d, $%d", f12ndTo16thbits,
       f17thTo21stbits, f22ndTo26thbits);

  } else if (isSlt(instruction)) {
    printf("slt $%d, $%d, $%d", f12ndTo16thbits,
       f22ndTo26thbits, f17thTo21stbits);

  } else if (isJr(instruction)) {
    printf("jr $%d", f22ndTo26thbits);

  // Following functions has different most significant
  // 6 bits. Should be added last.
  } else if (isMul(instruction)) {
    printf("mul $%d, $%d, $%d", f12ndTo16thbits,
       f22ndTo26thbits, f17thTo21stbits);

  } else if (isAddi(instruction)) {
    printf("addi $%d, $%d, %d", f17thTo21stbits,
       f22ndTo26thbits, leastSig16bits);

  } else if (isAndi(instruction)) {
    printf("andi $%d, $%d, %d", f17thTo21stbits,
       f22ndTo26thbits, leastSig16bits);

  } else if (isOri(instruction)) {
    printf("ori $%d, $%d, %d", f17thTo21stbits,
       f22ndTo26thbits, leastSig16bits);

  } else if (isXori(instruction)) {
    printf("xori $%d, $%d, %d", f17thTo21stbits,
       f22ndTo26thbits, leastSig16bits);

  } else if (isSlti(instruction)) {
    printf("slti $%d, $%d, %d", f17thTo21stbits,
       f22ndTo26thbits, leastSig16bits);

  } else if (isLb(instruction)) {
    printf("lb $%d, %d($%d)", f17thTo21stbits, 
       leastSig16bits, f22ndTo26thbits);

  } else if (isLh(instruction)) {
    printf("lh $%d, %d($%d)", f17thTo21stbits,
       leastSig16bits, f22ndTo26thbits);

  } else if (isLw(instruction)) {
    printf("lw $%d, %d($%d)", f17thTo21stbits,
       leastSig16bits, f22ndTo26thbits);

  } else if (isSb(instruction)) {
    printf("sb $%d, %d($%d)", f17thTo21stbits,
       leastSig16bits, f22ndTo26thbits);

  } else if (isSh(instruction)) {
    printf("sh $%d, %d($%d)", f17thTo21stbits,
       leastSig16bits, f22ndTo26thbits);

  } else if (isSw(instruction)) {
    printf("sw $%d, %d($%d)", f17thTo21stbits,
       leastSig16bits, f22ndTo26thbits);

  } else if (isBeq(instruction)) {
    printf("beq $%d, $%d, %d", f22ndTo26thbits,
       f17thTo21stbits, leastSig16bits);

  } else if (isBne(instruction)) {
    printf("bne $%d, $%d, %d", f22ndTo26thbits,
       f17thTo21stbits, leastSig16bits);

  } else if (isBlez(instruction)) {
    printf("blez $%d, %d", f22ndTo26thbits,
       leastSig16bits);

  } else if (isBgtz(instruction)) {
    printf("bgtz $%d, %d", f22ndTo26thbits,
       leastSig16bits);

  } else if (isBltz(instruction)) {
    printf("bltz $%d, %d", f22ndTo26thbits,
       leastSig16bits);

  } else if (isBgez(instruction)) {
    printf("bgez $%d, %d", f22ndTo26thbits,
       leastSig16bits);

  } else if (isJ(instruction)) {
    printf("j 0x%X", instruction & TWENTYSIX1);

  } else if (isJal(instruction)) {
    printf("jal 0x%X", instruction & TWENTYSIX1);

  }
  return;
}
