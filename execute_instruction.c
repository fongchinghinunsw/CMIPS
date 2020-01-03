/*
 * Author: Fong Ching Hin Stephen
 */

#include <string.h>

#include "mips.h"
#include "helper.h"
#include "ram.h"
#include "registers.h"

/**
 * execute a MIPS instruction
 *
 * This function should:
 *
 * get register values by calling `get_register(register_type register_number)`
 * change registers by calling `set_register(register_type register_number, uint32_t value)`
 *
 * get memory values by `calling get_byte(uint32_t address)`
 * changes memory by `set_byte(uint32_t address, uint8_t value)`
 *
 * updates program_counter to address of next instruction
 *
 * returns 1 if an exit syscall is executed, 0 otherwise
 */
int execute_instruction(uint32_t instruction, uint32_t *program_counter) {

  if (isSyscall(instruction)) {
    int request = get_register(2);
    if (request == 1) {
      // print integer
      int32_t integer = get_register(4);
      printf("%d", integer);

    } else if (request == 4) {
      // print string
      uint32_t address = get_register(4);
      int ch;
      while ((ch = get_byte(address)) != '\0') {
        putchar(ch);
        address = address + 1;
      }

    } else if (request == 5) {
      // read integer
      int32_t result;
      scanf("%d", &result);
      set_register(2, result);

    } else if (request == 8) {
      // read string
      uint32_t address = get_register(4);
      uint32_t bufferSize = get_register(5);
      int ch;
      int count = 0;
      while ((ch = getchar()) != EOF &&
             count < bufferSize - 1) {
        set_byte(address + count, ch);
        count++;
        if (ch == '\n') {
          break;
        }
      }

      // pad remaining spaces with null terminator.
      while (count < bufferSize) {
        set_byte(address + count, '\0');
        count++;
      }

    } else if (request == 10) {
      // exit
      (*program_counter) += 4;
      return 1;

    } else if (request == 11) {
      // print character
      uint8_t ch = get_register(4);
      putchar(ch);

    } else if (request == 12) {
      // read character
      int ch = getchar();
      set_register(2, ch);

    }
  }

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
    uint32_t x = get_register(f17thTo21stbits);
    uint32_t result = x << f7thTo11stbits;
    set_register(f12ndTo16thbits, result);

  } else if (isSrl(instruction)) {
    uint32_t x = get_register(f17thTo21stbits);
    uint32_t result = x >> f7thTo11stbits;
    set_register(f12ndTo16thbits, result);

  } else if (isLui(instruction)) {
    uint32_t immediate = instruction & SIXTEEN1;

    uint32_t result = immediate << 16;
    set_register(f17thTo21stbits, result);

  // Starting from here. instructions' most significant 6 bits
  // are zeros, they must be checked after the above three
  // instructions.
  } else if (isAdd(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    uint32_t y = get_register(f17thTo21stbits);
    uint32_t result = x + y;
    set_register(f12ndTo16thbits, result);

  } else if (isSub(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    uint32_t y = get_register(f17thTo21stbits);
    uint32_t result = x - y;
    set_register(f12ndTo16thbits, result);

  } else if (isAnd(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    uint32_t y = get_register(f17thTo21stbits);
    uint32_t result = x & y;
    set_register(f12ndTo16thbits, result);

  } else if (isOr(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    uint32_t y = get_register(f17thTo21stbits);
    uint32_t result = x | y;
    set_register(f12ndTo16thbits, result);

  } else if (isXor(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    uint32_t y = get_register(f17thTo21stbits);
    uint32_t result = x ^ y;
    set_register(f12ndTo16thbits, result);

  } else if (isSllv(instruction)) {
    uint32_t x = get_register(f17thTo21stbits);
    uint32_t y = get_register(f22ndTo26thbits);
    uint32_t result = x << y;
    set_register(f12ndTo16thbits, result);

  } else if (isSrlv(instruction)) {
    uint32_t x = get_register(f17thTo21stbits);
    uint32_t y = get_register(f22ndTo26thbits);
    uint32_t result = x >> y;
    set_register(f12ndTo16thbits, result);

  } else if (isSlt(instruction)) {
    int32_t s = get_register(f22ndTo26thbits);
    int32_t t = get_register(f17thTo21stbits);
    uint32_t result = s < t;
    set_register(f12ndTo16thbits, result);

  } else if (isJr(instruction)) {
    (*program_counter) = get_register(f22ndTo26thbits);
    return 0;

  // Following functions has different most significant
  // 6 bits. Should be checked last.
  } else if (isMul(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    uint32_t y = get_register(f17thTo21stbits);
    uint32_t result = x * y;
    set_register(f12ndTo16thbits, result);

  } else if (isAddi(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    uint32_t result = x + leastSig16bits;
    set_register(f17thTo21stbits, result);

  } else if (isAndi(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    uint32_t result = x & leastSig16bits;
    set_register(f17thTo21stbits, result);

  } else if (isOri(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    uint32_t result = x | leastSig16bits;
    set_register(f17thTo21stbits, result);

  } else if (isXori(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    uint32_t result = x ^ leastSig16bits;
    set_register(f17thTo21stbits, result);

  } else if (isSlti(instruction)) {
    int32_t x = get_register(f22ndTo26thbits);
    uint32_t result = x < leastSig16bits;
    set_register(f17thTo21stbits, result);

  } else if (isLb(instruction)) {
    uint32_t address = get_register(f22ndTo26thbits);
    uint32_t result = get_byte(address +
                               leastSig16bits);
    set_register(f17thTo21stbits, (int8_t)result);

  } else if (isLh(instruction)) {
    uint32_t result = 0;
    uint32_t address = get_register(f22ndTo26thbits);
    for (int i = 0; i < 2; i++) {
      uint32_t byte = get_byte(address +
                   leastSig16bits + i);
      result = result | (byte << i * 8);
    }
    set_register(f17thTo21stbits, (int16_t)result);

  } else if (isLw(instruction)) {
    uint32_t result = 0;
    uint32_t address = get_register(f22ndTo26thbits);
    for (int i = 0; i < 4; i++) {
      uint32_t byte = get_byte(address +
                   leastSig16bits + i);
      result = result | (byte << i * 8);
    }
    set_register(f17thTo21stbits, (int32_t)result);

  } else if (isSb(instruction)) {
    uint32_t result = get_register(f17thTo21stbits);
    uint32_t address = get_register(f22ndTo26thbits);
    result = result & 0xff;
    set_byte(leastSig16bits + address, (uint8_t)result);
    
  } else if (isSh(instruction)) {
    uint32_t result = get_register(f17thTo21stbits);
    uint32_t address = get_register(f22ndTo26thbits);
    result = result & 0xffff;
    for (int i = 0; i < 2; i++) {
      set_byte(leastSig16bits + address + i,
               (uint8_t)(result >> 8 * i) & 0xff);
    }

  } else if (isSw(instruction)) {
    uint32_t result = get_register(f17thTo21stbits);
    uint32_t address = get_register(f22ndTo26thbits);
    for (int i = 0; i < 4; i++) {
      set_byte(leastSig16bits + address + i,
               (uint8_t)(result >> 8 * i) & 0xff);

    }

  } else if (isBeq(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    uint32_t y = get_register(f17thTo21stbits);
    if (x == y) {
      (*program_counter) += ((uint32_t)leastSig16bits << 2);
      return 0;
    }

  } else if (isBne(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    uint32_t y = get_register(f17thTo21stbits);
    if (x != y) {
      (*program_counter) += ((uint32_t)leastSig16bits << 2);
      return 0;
    }

  } else if (isBlez(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    if (x <= 0) {
      (*program_counter) += ((uint32_t)leastSig16bits << 2);
      return 0;
    }

  } else if (isBgtz(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    if (x > 0) {
      (*program_counter) += ((uint32_t)leastSig16bits << 2);
      return 0;
    }

  } else if (isBltz(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    if (x < 0) {
      (*program_counter) += ((uint32_t)leastSig16bits << 2);
      return 0;
    }

  } else if (isBgez(instruction)) {
    uint32_t x = get_register(f22ndTo26thbits);
    if (x >= 0) {
      (*program_counter) += ((uint32_t)leastSig16bits << 2);
      return 0;
    }

  } else if (isJ(instruction)) {
    (*program_counter) = ((*program_counter) & 0xF0000000) |
                         ((instruction & TWENTYSIX1) << 2);
    return 0;

  } else if (isJal(instruction)) {
    set_register(31, (*program_counter) + 4);
    (*program_counter) = ((*program_counter) & 0xF0000000) |
                         ((instruction & TWENTYSIX1) << 2);
    return 0;
  }

  (*program_counter) += 4;

  return 0;
}
