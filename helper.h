#include <stdint.h>

// masks that can be used to extract part of an instruction
// e.g. FIVE1 => 0b11111
#define FIVE1 0x1F
#define SIX1 0x3F
#define ELEVEN1 0x7FF
#define SIXTEEN1 0xFFFF
#define TWENTYONE1 0x1FFFFF
#define TWENTYSIX1 0x3FFFFFF

int isAdd(uint32_t instruction);

int isSub(uint32_t instruction);

int isMul(uint32_t instruction);

int isAnd(uint32_t instruction);

int isOr(uint32_t instruction);

int isXor(uint32_t instruction);

int isSllv(uint32_t instruction);

int isSrlv(uint32_t instruction);

int isSlt(uint32_t instruction);

int isAddi(uint32_t instruction);

int isAndi(uint32_t instruction);

int isOri(uint32_t instruction);

int isXori(uint32_t instruction);

int isSll(uint32_t instruction);

int isSrl(uint32_t instruction);

int isSlti(uint32_t instruction);

int isLui(uint32_t instruction);

int isLb(uint32_t instruction);

int isLh(uint32_t instruction);

int isLw(uint32_t instruction);

int isSb(uint32_t instruction);

int isSh(uint32_t instruction);

int isSw(uint32_t instruction);

int isBeq(uint32_t instruction);

int isBne(uint32_t instruction);

int isBlez(uint32_t instruction);

int isBgtz(uint32_t instruction);

int isBltz(uint32_t instruction);

int isBgez(uint32_t instruction);

int isJ(uint32_t instruction);

int isJal(uint32_t instruction);

int isJr(uint32_t instruction);

int isSyscall(uint32_t instruction);
