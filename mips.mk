EXERCISES	+= mips
CLEAN_FILES	+= mips mips.o $(addsuffix .o, $(basename ${SRCS.mips}))
SRCS.mips	 = # mips.c  ##  for various reasons, this automatically appears
SRCS.mips	+= ram.c registers.c execute_instruction.c print_instruction.c
SRCS.mips	+= helper.c# <<< if you add C files, add them to the list here.

# Force only .c -> executable compilations (to preserve dcc analysis).
.SUFFIXES:
.SUFFIXES: .c

mips:			${SRCS.mips}
mips.o:			mips.c mips.h ram.h registers.h
ram.o:			ram.c mips.h ram.h
registers.o:		registers.c registers.h
execute_instruction.o:	execute_instruction.c mips.h
print_instruction.o:	print_instruction.c mips.h
helper.o:               helper.c helper.h
