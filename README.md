<header>

<h1 class="text-center">
Assignment 1: emu, A MIPS Emulator
</h1>

</header>


















<p class="text-right text-muted"><small>
version: 1.6 
last updated: 2019-11-03 00:20:00
</small></p>

<h2>Aims</h2>

<ul>
<li>Understanding encoding of MIPS instructions
<li>Understanding semantics of MIPS instructions
<li>Generally building a concrete understanding of an example CPU
<li>Practising C, including bit operations
</ul>

<h2>Getting Started</h2>
<p>
Create a new directory for this assignment
called <code>emu</code>,
change to this directory,
and fetch the provided code
by running these commands:

<pre is="tty">
<kbd is="sh">mkdir emu</kbd>
<kbd is="sh">cd emu</kbd>
<kbd is="sh">1521 fetch emu</kbd>
</pre>




<h2>The Assignment</h2>
<p>
You have been given files which
provide code for <strong>emu</strong>, a MIPS emulator.

<p>
However, two important functions —
<em>print_instruction</em> and <em>execute_instruction</em> —
remain to be completed.
Your task is to implement these functions.

<h3>Part 1: implementing <em>print_instruction</em></h3>

<p>
The first part of the assignment is
to implement the function <code>print_instruction</code>
in <code>print_instruction.c</code>.
<code>print_instruction</code> is given
a MIPS instruction as a 32-bit unsigned integer value,
You need to add code to <code>print_instruction</code>
which prints out the assembler for the instruction.


<div class="highlight"><pre><span></span><span class="c1">// If you use C library functions add includes here.</span>

<span class="cp">#include</span> <span class="cpf">&quot;emu.h&quot;</span><span class="cp"></span>
<span class="cp">#include</span> <span class="cpf">&quot;ram.h&quot;</span><span class="cp"></span>
<span class="cp">#include</span> <span class="cpf">&quot;registers.h&quot;</span><span class="cp"></span>

<span class="cm">/*</span>
<span class="cm"> * print a MIPS instruction (no newline)</span>
<span class="cm"> * run reference implementation if unsure what to print</span>
<span class="cm"> */</span>
<span class="kt">void</span> <span class="nf">print_instruction</span><span class="p">(</span><span class="kt">uint32_t</span> <span class="n">instruction</span><span class="p">)</span> <span class="p">{</span>
    <span class="n">printf</span><span class="p">(</span><span class="s">&quot;add $3, $7, $5&quot;</span><span class="p">);</span> <span class="c1">// REPLACE ME WITH YOUR CODE</span>
<span class="p">}</span>

<span class="c1">// PUT YOUR FUNCTIONS HERE</span>
</pre></div>


<p>
For example, <code>print_instruction(0x00851820)</code> should print <code>add $3, $4, $5</code>.

<p>
Tables below describe how MIPS instructions are encoded.
There is also a reference implementation which you can use
if you are unclear what string should be printed for an instruction.

<p>
<strong>emu</strong> takes several command-line arguments.
The <code>-p</code> option indicates the rest of the command is
hexadecimal integers describing instructions
that <em>print_instruction</em> will be called on —
for example:

<pre is="tty">
<kbd is="sh">make</kbd>
dcc     emu.c ram.c registers.c execute_instruction.c print_instruction.c   -o emu
<kbd is="sh">./emu -p 0x00851820</kbd>
[00400024] 00851820 add $3, $4, $5
</pre>

<p>
The code you have been given prints
<code>[00400024] 00851820 </code>:
the first part is the address this instruction would be placed,
and the second part is the number passed.
Your code only needs to print <code>add $3, $4, $5</code>,
the instruction that value encodes.

<p>
<code>emu -p</code> will also accept assembler statements,
each of which it will convert to integers,
and <em>print_instruction</em> will be called on that result.
For example:

<pre is="tty">
<kbd is="sh">./emu -p 'add $3, $4, $5'</kbd>
[00400024] 00851820 add $3, $4, $5
</pre>

<p>
Remember to quote the assembler instructions, as in the above example.
This is needed because the <code>$</code> character
has a special meaning to the shell.

<p>
<strong>emu</strong> also has a <code>-P</code> option,
which takes a file of assembler statements,
converts them to integers,
and calls <em>print_instruction</em> for each integer, for example:

<pre is="tty">
<kbd is="sh">./emu -P print10.s</kbd>
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
If you are uncertain what output is correct,
run the reference implementation on a CSE machine:

<pre is="tty">
<kbd is="sh">1521 emu -p 0x03E00008</kbd>
[00400024] 03E00008 jr $31
</pre>

<p>
The reference implementation can print (almost) all
MIPS instructions.

<p>
Instructions that print with a '!' after them can not be executed by the reference implementation,
and do not need to be printed or executed by your assignment code.

<p>
If you find a bug in the reference implementation,
please report it on the course forum.

<p>
The assembly files you have been given
will help you debug and test your <em>print_instruction</em>.
In addition, autotests are available
to help with your testing:

<pre is="tty">
<kbd is="sh">1521 autotest emu part1</kbd>
...
</pre>

<p>
If you create extra <code>.c</code> or <code>.h</code> files,
you will need to supply them explicitly to autotest; for example:

<pre is="tty">
<kbd is="sh">1521 autotest emu part1 extra1.c extra2.c extra3.h</kbd>
...
</pre>


<h3>Part 2: implementing <em>execute_instruction</em></h3>

<p>
The second part of the assignment is
to implement the function <code>execute_instruction</code>
in <code>execute_instruction.c</code>,
<code>execute_instruction</code> is given
a MIPS instruction as a 32-bit unsigned integer value,
You need to add code to <code>execute_instruction</code>
which implements the instruction.


<div class="highlight"><pre><span></span><span class="c1">// If you use C library functions add includes here.</span>

<span class="cp">#include</span> <span class="cpf">&quot;emu.h&quot;</span><span class="cp"></span>
<span class="cp">#include</span> <span class="cpf">&quot;ram.h&quot;</span><span class="cp"></span>
<span class="cp">#include</span> <span class="cpf">&quot;registers.h&quot;</span><span class="cp"></span>

<span class="cm">/**</span>
<span class="cm"> * execute a MIPS instruction</span>
<span class="cm"> *</span>
<span class="cm"> * This function should:</span>
<span class="cm"> *</span>
<span class="cm"> * get register values by calling `get_register(register_type register_number)`</span>
<span class="cm"> * change registers by calling `set_register(register_type register_number, uint32_t value)`</span>
<span class="cm"> *</span>
<span class="cm"> * get memory values by `calling get_byte(uint32_t address)`</span>
<span class="cm"> * changes memory by `set_byte(uint32_t address, uint8_t value)`</span>
<span class="cm"> *</span>
<span class="cm"> * updates program_counter to address of next instruction</span>
<span class="cm"> *</span>
<span class="cm"> * returns 1 if an exit syscall is executed, 0 otherwise</span>
<span class="cm"> */</span>
<span class="kt">int</span> <span class="nf">execute_instruction</span><span class="p">(</span><span class="kt">uint32_t</span> <span class="n">instruction</span><span class="p">,</span> <span class="kt">uint32_t</span> <span class="o">*</span><span class="n">program_counter</span><span class="p">)</span> <span class="p">{</span>
    <span class="c1">// example code to implement add $4, $14, $12</span>
    <span class="kt">uint32_t</span> <span class="n">x</span> <span class="o">=</span> <span class="n">get_register</span><span class="p">(</span><span class="mi">14</span><span class="p">);</span>
    <span class="kt">uint32_t</span> <span class="n">y</span> <span class="o">=</span> <span class="n">get_register</span><span class="p">(</span><span class="mi">12</span><span class="p">);</span>
    <span class="kt">uint32_t</span> <span class="n">sum</span> <span class="o">=</span> <span class="n">x</span> <span class="o">+</span> <span class="n">y</span><span class="p">;</span>
    <span class="n">set_register</span><span class="p">(</span><span class="mi">4</span><span class="p">,</span> <span class="n">sum</span><span class="p">);</span>

    <span class="c1">// Update program_counter to address of next instructions</span>
    <span class="c1">// Most instructions will simply do the following:</span>
    <span class="p">(</span><span class="o">*</span><span class="n">program_counter</span><span class="p">)</span> <span class="o">+=</span> <span class="mi">4</span><span class="p">;</span>
    <span class="c1">// Jump &amp; Branch instructions will do something different</span>

    <span class="c1">// 0 should be returned, unless an exit syscall is executed</span>
    <span class="k">return</span> <span class="mi">0</span><span class="p">;</span>
<span class="p">}</span>

<span class="c1">// PUT EXTRA FUNCTIONS HERE</span>
</pre></div>


<p>
You implement instructions by appropriately calling the functions
<code>get_register</code>, <code>set_register</code>,
<code>get_byte</code> and <code>set_byte</code>.
<code>execute_instruction</code> must also update the program counter.

<p>
<strong>emu</strong> has a <code>-e</code> option,
will also accept assembler statements,
convert them to integers,
and calls <em>execute_instruction</em> for each integer,
then print the value of registers.
For example:

<pre is="tty">
<kbd is="sh">./emu -e 'add $4, $14, $12'</kbd>
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
Note that <strong>emu</strong> sets registers 9 to 16
to the values 1 through 7 before execution
to have convenient values available for testing single instructions.

<p>
<strong>emu</strong> also has a <code>-E</code> option,
which like <code>-P</code> takes a file of assembler statements,
converts them to integers,
and calls <em>execute_instruction</em> multiple times to execute them.
For example:

<pre is="tty">
<kbd is="sh">./emu -E sum_100_squares.s</kbd>
338350
</pre>

<p>
<strong>emu</strong> can also be run interactively:

<pre is="tty">
<kbd is="sh">./emu add_memory.s</kbd>
PC = [00400024] 34080011 ori $8, $0, 17
emu > <kbd>h</kbd>
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

emu > <kbd>R</kbd>
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
emu > <kbd>s</kbd>
PC = [00400028] 3C011001 lui $1, 4097
emu > <kbd>s</kbd>
PC = [0040002C] AC280000 sw $8, 0($1)
emu > <kbd>D</kbd>
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
<kbd is="sh">1521 autotest emu part2</kbd>
...
</pre>

<p>
As before,
if you create extra <code>.c</code> or <code>.h</code> files,
you will need to supply them explicitly to autotest; for example:

<pre is="tty">
<kbd is="sh">1521 autotest emu part2 extra1.c extra2.c extra3.h</kbd>
...
</pre>


<h2>MIPS Architecture</h2>
<p>
You only need to implement the following subset of
instructions and system calls;
<strong>emu</strong> will only be tested on these.

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
which are beyond the scope of this assignment.

<p>
If in doubt, match the output of the reference implementation.

<p>
You must submit <code>execute_instruction.c</code> and <code>print_instruction.c</code>.
You cannot not change the supplied files
(<code>emu.c</code>, <code>emu.h</code>,
 <code>ram.c</code>, <code>ram.h</code>,
 <code>registers.c</code>, and <code>registers.h</code>).
You may optionally submit extra <code>.c</code> or <code>.h</code> files;
if you do, add extra <code>.c</code> files
to your <code>emu.mk</code> to ensure your code compiles.
You may not submit other files.

<p>
Your submitted code must be C only.
You may call functions from the standard C library
(<abbr>e.g.</abbr>,
functions from <code>stdio.h</code>,
<code>stdlib.h</code>, <code>string.h</code>, etc.)
and the mathematics library (<code>math.h</code>).
You may use <code>assert.h</code>.

<p>
You may not submit code in other languages.
You may not use <code>system</code>
or other C functions to run external programs.
You may not use functions from other libraries;
in other words, you cannot use dcc's <code>-l</code> flag.

<p>
If you need clarification on
what you can and cannot use or do for this assignment,
ask in the class forum.

<p>
You are required to submit
intermediate versions of your assignment.
See below for details.

<p>
Your program must not require extra compile options.
It must compile with <code>dcc *.c -o emu</code>,
and it will be run with <code>dcc</code> when marking.
Run-time errors from illegal C will cause your code to fail automarking.
<p>
If your program writes out debugging output,
it will fail automarking tests:
make sure you disable debugging output before submission.
<h2>Change Log</h2>
<dl class="row">
<dt class="col-3">
    Version 1.0<br />
    <small>(2019-10-15 16:59:59)</small>
  </dt>
  <dd class="col-9">
    <ul>
      <li>Initial release onto unsuspecting students.</li>
    </ul>
  </dd><dt class="col-3">
    Version 1.1<br />
    <small>(2019-10-25 18:10:00)</small>
  </dt>
  <dd class="col-9">
    <ul>
      <li>The reference implementation now uses a signed comparison for SLT.</li><li>The reference implementation now implements sign extension for LB and LH.</li><li>The reference implementation now prints a '!' after instructions not required by the assignment.</li>
    </ul>
  </dd><dt class="col-3">
    Version 1.2<br />
    <small>(2019-10-28 16:00:00)</small>
  </dt>
  <dd class="col-9">
    <ul>
      <li>The reference implementation now behaves more like SPIM with syscall 12.</li><li>Updated registers.[ch] to follow new c_check rules when possible</li>
    </ul>
  </dd><dt class="col-3">
    Version 1.3<br />
    <small>(2019-10-28 19:00:00)</small>
  </dt>
  <dd class="col-9">
    <ul>
      <li>The reference implementation now prints bitwise immediates as unsigned</li>
    </ul>
  </dd><dt class="col-3">
    Version 1.4<br />
    <small>(2019-10-29 08:00:00)</small>
  </dt>
  <dd class="col-9">
    <ul>
      <li>syscall handling clarified</li>
    </ul>
  </dd><dt class="col-3">
    Version 1.5<br />
    <small>(2019-10-29 11:30:00)</small>
  </dt>
  <dd class="col-9">
    <ul>
      <li>Fixed typo in registers.h</li>
    </ul>
  </dd><dt class="col-3">
    Version 1.6<br />
    <small>(2019-11-03 00:20:00)</small>
  </dt>
  <dd class="col-9">
    <ul>
      <li>The reference implementation now stops execution on SYSCALL 10</li>
    </ul>
  </dd>
</dl>








<p>
When you think your program is working,
you can use <code>autotest</code>
to run some simple automated tests:

<pre is="tty">
<kbd is="sh">1521 autotest emu</kbd>
</pre>



<section class="exercise ">
    <header><h3>Assessment</h3></header>
    


<h3>Submission</h3>
<p>
When you are finished working on the assignment,
you must submit your work by running <code>give</code>:


<pre is="tty">
<kbd is="sh">give cs1521 ass1_emu print_instruction.c execute_instruction.c <var>[other .c or .h files]</var></kbd>
</pre>


<p>
You must run <code>give</code> before <strong>Monday     4 November 21:59:59</strong>
to obtain the marks for this assignment.
Note that this is an individual exercise,
the work you submit with <code>give</code> must be entirely your own.

<p>
You can run <code>give</code> multiple times.
Only your last submission will be marked.

<p>
If you are working at home, you may find it more convenient
to upload your work via
<a href="https://cgi.cse.unsw.edu.au/~give/Student/give.php">give's web interface</a>.

<p>
You cannot obtain marks by e-mailing your code to tutors or lecturers.

<p>
You check the files you have submitted <a href="https://cgi.cse.unsw.edu.au/~cs1521/19T3/student/">here</a>.

<p>
Automarking will be run by the lecturer after the submission deadline,
using test cases different to those <code>autotest</code> runs for you.
(Hint: do your own testing as well as running <code>autotest</code>.)

<p>
Manual marking will be done by your tutor,
who will mark for style and readability,
as described in the <strong>Assessment</strong> section below.
After your tutor has assessed your work,
you can <a href="https://cgi.cse.unsw.edu.au/~cs1521/19T3/student/">view your results here</a>;
The resulting mark will also be available
<a href="https://cgi.cse.unsw.edu.au/~give/Student/sturec.php">via give's web interface</a>.




<h3>Due Date</h3>
<p>
This assignment is tentatively due <strong>Monday     4 November 21:59:59</strong>.
<p>
If your assignment is submitted after this date,
each hour it is late
reduces the maximum mark it can achieve by 2%.
For example,
if an assignment worth 74% was submitted 10 hours late,
the late submission would have no effect.
If the same assignment was submitted 15 hours late,
it would be awarded 70%,
the maximum mark it can achieve at that time.



<h2>Assessment Scheme</h2>
<p>
This assignment will contribute 13 marks to your final COMP1521 mark.
<p>
80% of the marks for assignment 1 will come
from the performance of your code on a large series of tests.
<p>
20% of the marks for assignment 1 will come from hand marking.
These marks will be awarded on the basis of
clarity, commenting, elegance and style.
In other words, you will be assessed on
how easy it is for a human to read and understand your program.

<p>
An indicative assessment scheme follows.
The lecturer may vary the assessment scheme
after inspecting the assignment submissions,
but it is likely to be broadly similar to the following:


<table class="table table-sm w-75 mx-auto">
<tbody>
<tr><th scope="row">HD (85+)
    <td>print_instructions and execute_instructions work; beautiful code
<tr><th scope="row">DN (75–84)
    <td>print_instructions and execute_instructions mostly work; good, clear code
<tr><th scope="row">CR (60–74)
    <td>print_instructions works
<tr><th scope="row">PS (50–59)
    <td>print_instructions partly works
<tr><th scope="row">0%
    <td>knowingly providing your work to anyone <br>
        and it is subsequently submitted (by anyone).
<tr><th scope="row">0 FL for <br> COMP1521
    <td>submitting any other person's work; this includes joint work.
<tr><th scope="row">academic <br> misconduct
    <td>submitting another person's work without their consent;<br>
        paying another person to do work for you.
</tbody>
</table>




<h3>Intermediate Versions of Work</h3>
<p>
You are required to submit intermediate versions of your assignment.
<p>
Every time you work on the assignment
and make some progress
you should copy your work to your CSE account
and submit it using the <code>give</code> command below.
It is fine if intermediate versions do not compile
or otherwise fail submission tests.
Only the final submitted version of your assignment will be marked.
<p>
All these intermediate versions of your work
will be placed in a Git repository
and made available to you via a web interface
at <code>https://gitlab.cse.unsw.edu.au/<var>z5555555</var>/19T3-comp1521-ass1_emu</code>
(replacing <i>z5555555</i> with your own zID).
This will allow you to retrieve earlier versions of your code if needed.



<h3>Attribution of Work</h3>

<p>
This is an individual assignment.

<p>
The work you submit must be entirely your own work,
apart from any exceptions explicitly included
in the assignment specification above.
Submission of work partially or completely derived from any other person
or jointly written with any other person is not permitted.

<p>
You are only permitted to request help with the assignment
in the course forum, help sessions,
or from the teaching staff (the lecturer(s) and tutors) of COMP1521.

<p>
Do not provide or show your assignment work to any other person
(including by posting it on the forum),
apart from the teaching staff of COMP1521.
If you knowingly provide or show your assignment work
to another person for any reason,
and work derived from it is submitted,
you may be penalized,
even if that work was submitted
without your knowledge or consent;
this may apply even if your work is submitted by
a third party unknown to you.
You will not be penalized
if your work is taken
without your consent or knowledge.

<p>
Submissions that violate these conditions will be penalised.
Penalties may include negative marks,
automatic failure of the course,
and possibly other academic discipline.
We are also required to report
acts of plagiarism or other student misconduct:
if students involved hold scholarships,
this may result in a loss of the scholarship.
This may also result in the loss of a student visa.

<p>
Assignment submissions will be examined,
both automatically and manually,
for such submissions.



    </section>  





</main>

<footer class="mt-3 pt-3 bg-dark text-center no-print">
<p class="text-muted">
<strong>COMP1521 19T3: Computer Systems Fundamentals</strong>
is brought to you by <br />
the <a href="https://www.cse.unsw.edu.au/">School of Computer Science and Engineering</a><br />
at the <a href="https://www.unsw.edu.au/">University of New South Wales</a>, Sydney.<br />
For all enquiries, please email the class account at
<a href="mailto:@cse.unsw.edu.au">cs1521@cse.unsw.edu.au</a><br />

<small>CRICOS Provider 00098G</small>
</p>


</footer>

</body>
