/*
 * Author: Fong Ching Hin Stephen
 * Description: Contains functions that help to identify a MIPS instruction.
 */

#include <stdint.h>
#include "helper.h"

int isAdd(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t leastSig11bits = instruction & ELEVEN1;

  return (mostSig6bits == 0) && (leastSig11bits == 0b100000);
}

int isSub(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t leastSig11bits = instruction & ELEVEN1;

  return (mostSig6bits == 0) && (leastSig11bits == 0b100010);
}

int isMul(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t leastSig11bits = instruction & ELEVEN1;

  return (mostSig6bits == 0b11100) & (leastSig11bits == 0b10);
}

int isAnd(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t leastSig11bits = instruction & ELEVEN1;

  return (mostSig6bits == 0) && (leastSig11bits == 0b100100);
}

int isOr(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t leastSig11bits = instruction & ELEVEN1;

  return (mostSig6bits == 0) && (leastSig11bits == 0b100101);
}

int isXor(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t leastSig11bits = instruction & ELEVEN1;

  return (mostSig6bits == 0) && (leastSig11bits == 0b100110);
}

int isSllv(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t leastSig11bits = instruction & ELEVEN1;

  return (mostSig6bits == 0) && (leastSig11bits == 0b100);
}

int isSrlv(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t leastSig11bits = instruction & ELEVEN1;

  return (mostSig6bits == 0) && (leastSig11bits == 0b110);
}

int isSlt(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t leastSig11bits = instruction & ELEVEN1;

  return (mostSig6bits == 0) && (leastSig11bits == 0b101010);
}

int isAddi(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b1000;
}

int isAndi(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b1100;
}

int isOri(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b1101;
}

int isXori(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b1110;
}

int isSll(uint32_t instruction) {
  uint32_t mostSig11bits = instruction >> 21;
  uint32_t leastSig6bits = instruction & SIX1;

  return (mostSig11bits == 0) & (leastSig6bits == 0);
}

int isSrl(uint32_t instruction) {
  uint32_t mostSig11bits = instruction >> 21;
  uint32_t leastSig6bits = instruction & SIX1;

  return (mostSig11bits == 0) & (leastSig6bits == 0b10);
}

int isSlti(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b1010;
}

int isLui(uint32_t instruction) {
  uint32_t mostSig11bits = instruction >> 21;

  return mostSig11bits == 0b00111100000;
}

int isLb(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b100000;
}

int isLh(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b100001;
}

int isLw(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b100011;
}

int isSb(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b101000;
}

int isSh(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b101001;
}

int isSw(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b101011;
}

int isBeq(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b100;
}

int isBne(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b101;
}

int isBlez(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t f17thTo21stbits = (instruction >> 16)
                            & FIVE1;
  return (mostSig6bits == 0b110) && (f17thTo21stbits == 0);
}

int isBgtz(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t f17thTo21stbits = (instruction >> 16)
                            & FIVE1;
  return (mostSig6bits == 0b111) && (f17thTo21stbits == 0);
}

int isBltz(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t f17thTo21stbits = (instruction >> 16)
                            & FIVE1;
  return (mostSig6bits == 0b1) && (f17thTo21stbits == 0);
}

int isBgez(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t f17thTo21stbits = (instruction >> 16)
                            & FIVE1;
  return (mostSig6bits == 0b1) && (f17thTo21stbits == 0b1);
}

int isJ(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b10;
}

int isJal(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  return mostSig6bits == 0b11;
}

int isJr(uint32_t instruction) {
  uint32_t mostSig6bits = instruction >> 26;
  uint32_t leastSig21bits = instruction & TWENTYONE1;

  return (mostSig6bits == 0) & (leastSig21bits == 0b1000);
}

int isSyscall(uint32_t instruction) {
  return instruction == 0b1100;
}
