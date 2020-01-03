# CMIPS
[![CMIPS](https://img.shields.io/badge/GitHub-CMIPS-blue)](https://github.com/fongchinghinunsw/CMIPS)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)


<p>
Tables below describe how MIPS instructions are encoded.

<p>
<strong>CMIPS</strong> takes several command-line arguments.
The <code>-p</code> option indicates the rest of the command is
hexadecimal integers describing instructions
that <em>print_instruction</em> will be called on —
for example:

<pre is="tty">
<kbd is="sh">make</kbd>
gcc     mips.c ram.c registers.c execute_instruction.c print_instruction.c helper.c   -o mips
<kbd is="sh">./mips -p 0x00851820</kbd>
[00400024] 00851820 add $3, $4, $5
</pre>

<p>
<code>mips -p</code> will also accept assembler statements,
each of which it will convert to integers,
and <em>print_instruction</em> will be called on that result.
For example:

<pre is="tty">
<kbd is="sh">./mips -p 'add $3, $4, $5'</kbd>
[00400024] 00851820 add $3, $4, $5
</pre>

<p>
Remember to quote the assembler instructions, as in the above example.
This is needed because the <code>$</code> character
has a special meaning to the shell.

<p>
<strong>mips</strong> also has a <code>-P</code> option,
which takes a file of assembler statements,
converts them to integers,
and calls <em>print_instruction</em> for each integer, for example:

<pre is="tty">
<kbd is="sh">./mips -P print10.s</kbd>
[00400024] 34080001 ori $8, $0, 1
[00400028] 2901000B slti $1, $8, 11
[0040002C] 10200009 beq $1, $0, 9
[00400030] 00082020 add $4, $0, $8
[00400034] 34020001 ori $2, $0, 1
[00400038] 0000000C syscall
[0040003C] 3404000A ori $4, $0, 10
[00400040] 3402000B ori $2, $0, 11
[00400044] 0000000C syscall
[00400048] 21080001 addi $8, $8, 1
[0040004C] 0401FFF7 bgez $0, -9
[00400050] 03E00008 jr $31
</pre>

<p>
<strong>mips</strong> has a <code>-e</code> option,
will also accept assembler statements,
convert them to integers,
and calls <em>execute_instruction</em> for each integer,
then print the value of registers.
For example:

<pre is="tty">
<kbd is="sh">./mips -e 'add $4, $14, $12'</kbd>
R0  [$zero] = 00000000
R1  [$at] = 00000000
R2  [$v0] = 00000000
R3  [$v1] = 00000000
R4  [$a0] = 0000000A
R5  [$a1] = 00000000
R6  [$a2] = 00000000
R7  [$a3] = 00000000
R8  [$t0] = 00000000
R9  [$t1] = 00000001
R10 [$t2] = 00000002
R11 [$t3] = 00000003
R12 [$t4] = 00000004
R13 [$t5] = 00000005
R14 [$t6] = 00000006
R15 [$t7] = 00000007
R16 [$s0] = 00000000
R17 [$s1] = 00000000
R18 [$s2] = 00000000
R19 [$s3] = 00000000
R20 [$s4] = 00000000
R21 [$s5] = 00000000
R22 [$s6] = 00000000
R23 [$s7] = 00000000
R24 [$t8] = 00000000
R25 [$t9] = 00000000
R26 [$k0] = 00000000
R27 [$k1] = 00000000
R28 [$gp] = 10008000
R29 [$sp] = 7FFFF8E4
R30 [$fp] = 00000000
R31 [$ra] = 00400018
</pre>

<p>
Note that <strong>mips</strong> sets registers 9 to 16
to the values 1 through 7 before execution
to have convenient values available for testing single instructions.

<p>
<strong>mips</strong> also has a <code>-E</code> option,
which like <code>-P</code> takes a file of assembler statements,
converts them to integers,
and calls <em>execute_instruction</em> multiple times to execute them.
For example:

<pre is="tty">
<kbd is="sh">./mips -E sum_100_squares.s</kbd>
338350
</pre>

<p>
<strong>mips</strong> can also be run interactively:

<pre is="tty">
<kbd is="sh">./mips add_memory.s</kbd>
PC = [00400024] 34080011 ori $8, $0, 17
mips > <kbd>h</kbd>
In interactive mode, available commands are:
    s       step (execute one instruction)
    r       execute all remaining instructions
    q       quit
    h       this help message
    P       print Program
    R       print Registers
    D       print Data segment
    S       print Stack segment
    T       print Text segment
Entering nothing will re-send the previous command.

mips > <kbd>R</kbd>
R0  [$zero] = 00000000
R1  [$at] = 00000000
R2  [$v0] = 00000000
R3  [$v1] = 00000000
R4  [$a0] = 00000000
R5  [$a1] = 00000000
R6  [$a2] = 00000000
R7  [$a3] = 00000000
R8  [$t0] = 00000000
R9  [$t1] = 00000001
R10 [$t2] = 00000002
R11 [$t3] = 00000003
R12 [$t4] = 00000004
R13 [$t5] = 00000005
R14 [$t6] = 00000006
R15 [$t7] = 00000007
R16 [$s0] = 00000000
R17 [$s1] = 00000000
R18 [$s2] = 00000000
R19 [$s3] = 00000000
R20 [$s4] = 00000000
R21 [$s5] = 00000000
R22 [$s6] = 00000000
R23 [$s7] = 00000000
R24 [$t8] = 00000000
R25 [$t9] = 00000000
R26 [$k0] = 00000000
R27 [$k1] = 00000000
R28 [$gp] = 10008000
R29 [$sp] = 7FFFF8E4
R30 [$fp] = 00000000
R31 [$ra] = 00400018
PC = [00400024] 34080011 ori $8, $0, 17
mips > <kbd>s</kbd>
PC = [00400028] 3C011001 lui $1, 4097
mips > <kbd>s</kbd>
PC = [0040002C] AC280000 sw $8, 0($1)
mips > <kbd>D</kbd>
[10000000..1000FFFC] 00000000
[10010000] 00000011
[10010004] 00000019
[10010008] 0000002A
</pre>

<p>
The assembly files you have been given
will help you debug and test your <em>execution_instruction</em>.
In addition, autotests are available
to help with your testing:

<pre is="tty">
<kbd is="sh">1521 autotest mips part2</kbd>
...
</pre>

<p>
As before,
if you create extra <code>.c</code> or <code>.h</code> files,
you will need to supply them explicitly to autotest; for example:

<pre is="tty">
<kbd is="sh">1521 autotest mips part2 extra1.c extra2.c extra3.h</kbd>
...
</pre>


<h2>MIPS Architecture</h2>
<p>
You only need to implement the following subset of
instructions and system calls;
<strong>mips</strong> will only be tested on these.

<h3>MIPS Instructions</h3>
<p>
You need to implement only this subset of MIPS instructions:



<table class="table table-sm table-striped">
<thead>
<tr><th style="width:20%;">Assembler
    <th>Description
    <th>C
    <th>Bit Pattern
</thead>
<tbody>

<tr><th scope="row"><code>add $d, $s, $t</code>
    <td>add
    <td>d = s + t
    <td><code>000000ssssstttttddddd00000100000</code>

<tr><th scope="row"><code>sub $d, $s, $t</code>
    <td>subtract
    <td>d = s - t
    <td><code>000000ssssstttttddddd00000100010</code>

<tr><th scope="row"><code>mul $d, $s, $t</code>
    <td>multiply to low
    <td>d = s * t
    <td><code>011100ssssstttttddddd00000000010</code>

<tr><th scope="row"><code>and $d, $s, $t</code>
    <td>and
    <td>d = s & t
    <td><code>000000ssssstttttddddd00000100100</code>

<tr><th scope="row"><code>or $d, $s, $t</code>
    <td>or
    <td>d = s l t
    <td><code>000000ssssstttttddddd00000100101</code>

<tr><th scope="row"><code>xor $d, $s, $t</code>
    <td>xor
    <td>d = s ^ t
    <td><code>000000ssssstttttddddd00000100110</code>

<tr><th scope="row"><code>sllv $d, $t, $s</code>
    <td>shift left
    <td>d = t << s
    <td><code>000000ssssstttttddddd00000000100</code>

<tr><th scope="row"><code>srlv $d, $t, $s</code>
    <td>shift right
    <td>d = t >> s
    <td><code>000000ssssstttttddddd00000000110</code>

<tr><th scope="row"><code>slt $d, $s, $t</code>
    <td>set on less than
    <td>d = (s < t)
    <td><code>000000ssssstttttddddd00000101010</code>

<tr><th scope="row"><code>addi $t, $s, I</code>
    <td>add immediate
    <td>t = s + I
    <td><code>001000ssssstttttIIIIIIIIIIIIIIII</code>

<tr><th scope="row"><code>andi $t, $s, I</code>
    <td>and with immediate
    <td>t = s & I
    <td><code>001100ssssstttttIIIIIIIIIIIIIIII</code>

<tr><th scope="row"><code>ori $t, $s, I</code>
    <td>or with immediate
    <td>t = s l I
    <td><code>001101ssssstttttIIIIIIIIIIIIIIII</code>

<tr><th scope="row"><code>xori $t, $s, I</code>
    <td>xor with immediate
    <td>t = s ^ I
    <td><code>001110ssssstttttIIIIIIIIIIIIIIII</code>

<tr><th scope="row"><code>sll $d, $t, I</code>
    <td>shift left immediate
    <td>d = t << I
    <td><code>00000000000tttttdddddIIIII000000</code>

<tr><th scope="row"><code>srl $d, $t, I</code>
    <td>shift right immediate
    <td>d = t >> I
    <td><code>00000000000tttttdddddIIIII000010</code>

<tr><th scope="row"><code>slti $t, $s, I</code>
    <td>set on less than immediate
    <td>t = (s < I)
    <td><code>001010ssssstttttIIIIIIIIIIIIIIII</code>

<tr><th scope="row"><code>lui $t, I</code>
    <td>load upper immediate
    <td>t = I << 16
    <td><code>00111100000tttttIIIIIIIIIIIIIIII</code>

<tr><th scope="row"><code>lb $t, O($b)</code>
    <td>load byte
    <td>t = *(int8*)(b + O)
    <td><code>100000bbbbbtttttOOOOOOOOOOOOOOOO</code>

<tr><th scope="row"><code>lh $t, O($b)</code>
    <td>load half word
    <td>t = *(int16*)(b + O)
    <td><code>100001bbbbbtttttOOOOOOOOOOOOOOOO</code>

<tr><th scope="row"><code>lw $t, O($b)</code>
    <td>load word
    <td>t = *(int32*)(b + O)
    <td><code>100011bbbbbtttttOOOOOOOOOOOOOOOO</code>

<tr><th scope="row"><code>sb $t, O($b)</code>
    <td>store byte
    <td>*(uint8*)(b + O) = (t & 0xff)
    <td><code>101000bbbbbtttttOOOOOOOOOOOOOOOO</code>

<tr><th scope="row"><code>sh $t, O($b)</code>
    <td>store half
    <td>*(uint16*)(b + O) = (t & 0xffff)
    <td><code>101001bbbbbtttttOOOOOOOOOOOOOOOO</code>

<tr><th scope="row"><code>sw $t, O($b)</code>
    <td>store word
    <td>*(uint32*)(b + O) = t
    <td><code>101011bbbbbtttttOOOOOOOOOOOOOOOO</code>

<tr><th scope="row"><code>beq $s, $t, I</code>
    <td>branch on equal
    <td>if (s == t) PC += I<<2; else PC += 4;
    <td><code>000100ssssstttttIIIIIIIIIIIIIIII</code>

<tr><th scope="row"><code>bne $s, $t, I</code>
    <td>branch on not equal
    <td>if (s != t) PC += I<<2; else PC += 4;
    <td><code>000101ssssstttttIIIIIIIIIIIIIIII</code>

<tr><th scope="row"><code>blez $s, I</code>
    <td>branch less than or equal than zero
    <td>if (s <= 0) PC += I<<2; else PC += 4;
    <td><code>000110sssss00000IIIIIIIIIIIIIIII</code>

<tr><th scope="row"><code>bgtz $s, I</code>
    <td>branch greater than zero
    <td>if (s > 0) PC += I<<2; else PC += 4;
    <td><code>000111sssss00000IIIIIIIIIIIIIIII</code>

<tr><th scope="row"><code>bltz $s, I</code>
    <td>branch on less than zero
    <td>if (s < 0) PC += I<<2; else PC += 4;
    <td><code>000001sssss00000IIIIIIIIIIIIIIII</code>

<tr><th scope="row"><code>bgez $s, I</code>
    <td>branch on greater than or equal to zero
    <td>if (s >= 0) PC += I<<2; else PC += 4;
    <td><code>000001sssss00001IIIIIIIIIIIIIIII</code>

<tr><th scope="row"><code>j X</code>
    <td>jump
    <td>PC = (PC & 0xF0000000) | (X << 2)
    <td><code>000010XXXXXXXXXXXXXXXXXXXXXXXXXX</code>

<tr><th scope="row"><code>jal X</code>
    <td>jump and link
    <td>$ra = PC + 4; PC = (PC & 0xF0000000) | (X << 2)
    <td><code>000011XXXXXXXXXXXXXXXXXXXXXXXXXX</code>

<tr><th scope="row"><code>jr $s</code>
    <td>jump register
    <td>PC = s
    <td><code>000000sssss000000000000000001000</code>

<tr><th scope="row"><code>syscall</code>
    <td>system call
    <td>determined by $v0
    <td><code>00000000000000000000000000001100</code>

</tbody>
</table>

<p>
The instruction 'Bit Pattern' uniquely identifies each instruction:
<ul>
<li><code>0</code>: Literal bit zero
<li><code>1</code>: Literal bit one
<!-- <li><code>-</code>: Literal bit zero or one -->
<li><code>X</code>: Immediate, print as hex with '0x' prefix
<li><code>I</code>: Immediate, print as dec
<li><code>b</code>: Base register field (number is the N in $N)
<li><code>O</code>: Offset immediate, print as dec
<li>[lowercase letter]: Register field (number is the N in $N)
</ul>

<p>
Arithmetic instruction should assume
registers contain a signed 32-bit number.
Arithmetical instruction should not attempt
to stop overflows as a result of their operation.

<p>
Every instruction has a <code>PC += 4</code> after the operation,
except for instruction that directly change the program counter,
such as branches or jumps.

<h3>System Calls</h3>
<p>
You only need to implement this subset of system calls.



<table class="table table-sm table-striped">
<thead>
<tr><th style="width:10%;">Request
    <th>Description
    <th>Arguments
    <th>Results
</thead>

<tbody>

<tr><th scope="row">1
    <td>print integer
    <td>$a0 = integer to print
    <td>

<tr><th scope="row">4
    <td>print string
    <td>$a0 = address of NUL-terminated string to print
    <td>

<tr><th scope="row">5
    <td>read integer
    <td>
    <td>$v0 = integer read

<tr><th scope="row">8
    <td>read string
    <td>$a0 = address of input buffer<br />$a1 = maximum number of characters to read
    <td>

<tr><th scope="row">10
    <td>exit
    <td>
    <td>

<tr><th scope="row">11
    <td>print character
    <td>$a0 = character to print
    <td>

<tr><th scope="row">12
    <td>read character
    <td>
    <td>$v0 = character read

</tbody>
</table>

<p>
Read String should read bytes until a newline is read or <code>$a1 - 1</code> bytes
have been read.  It should fill the remainder of the buffer with zero bytes.
<p>
This means that a string will always be null-terminated
and that any spare space in the buffer will be filled with zero bytes.

<p>
Print Character should print the lowest 8 bits of <code>$a0</code>.
<p>
You do not have to implement error handling for syscalls.  You can assume a valid syscall number is supplied.
You can assume valid arguments are supplied.
You can assume any I/O (scanf, fgetc, fputc, fgets, printf) succeeds.


<h2>Assumptions and Clarifications</h2>

<p>
Like all good programmers,
you should make as few assumptions as possible.

<p>
You can assume that
your functions are given only valid instructions
as listed in the table above,
and that memory accesses are valid.

<p>
You do not have to implement
MIPS instructions, system calls, or features
which are not explicitly mentioned in the tables above.
In particular,
you do not have to implement or consider
delay slots or traps,
which are beyond the scope of this assignment

</body>
