## Report

### How to Run the Code
1. Make sure the files `makefile`, `main.cpp`, `helpers.cpp`, and `helpers.h` are in the same directory as your input file `pp2_input.txt`.  
2. Open a terminal and compile the program using:
   ```bash
   make
   ```
3. Run the executable:
   ```bash
   ./driver
   ```
4. The program will display each instruction being executed, followed by the current state of the **registers** and **memory** after every operation.

---

### Working Process
The program simulates a simplified CPU executing a list of assembly-style instructions.

1. **File Reading:**  
   The program opens `pp2_input.txt` and reads instructions line by line. Each line contains one instruction and its operands.

2. **Instruction Decoding:**  
   Each instruction is parsed into tokens (opcode and operands). The opcode determines which `execute` function to call — such as `executeADD`, `executeLOAD`, etc.

3. **Execution:**  
   Based on the instruction, registers and memory arrays are updated. For example, arithmetic instructions modify registers, while load/store operations move data between memory and registers.

4. **Display:**  
   After each instruction, the program prints the entire register and memory state so users can observe changes in real time.

---

### Logic and Functionality of Each Operation

| Instruction | Description | Logic |
|--------------|--------------|--------|
| **MOV Rd, Src** | Moves a constant or register value into a destination register. | `reg[Rd] = (isRegister(Src) ? reg[Src] : stoi(Src));` |
| **ADD Rd, Rs1, Rs2** | Adds two register values and stores the result in a destination register. | `reg[Rd] = reg[Rs1] + reg[Rs2];` |
| **SUB Rd, Rs1, Rs2** | Subtracts one register value from another. | `reg[Rd] = reg[Rs1] - reg[Rs2];` |
| **AND Rd, Rs1, Rs2** | Performs bitwise AND between two registers. | `reg[Rd] = reg[Rs1] & reg[Rs2];` |
| **OR Rd, Rs1, Rs2** | Performs bitwise OR between two registers. | `reg[Rd] = reg[Rs1] \| reg[Rs2];` |
| **XOR Rd, Rs1, Rs2** | Performs bitwise XOR between two registers. | `reg[Rd] = reg[Rs1] ^ reg[Rs2];` |
| **LOAD Rd, [addr]** | Loads a value from memory into a register. | `reg[Rd] = memory[getIndex(addr)];` |
| **STORE Rs, [addr]** | Stores a register value into memory. | `memory[getIndex(addr)] = reg[Rs];` |
| **CMP R1, R2** | Compares two registers and sets the zero flag `Z` if equal. | `Z = (reg[R1] == reg[R2]) ? 1 : 0;` |
| **BEQ label** | Branches if zero flag `Z` is 1. | Placeholder — prints branch attempt (no jump table implemented). |
| **BNE label** | Branches if zero flag `Z` is 0. | Placeholder — prints branch attempt. |
| **BAL label** | Always branches (unconditional). | Placeholder — prints branch attempt. |

---

### Test Cases and Expected Output

#### 1. MOV
**Input:**
```
MOV R1, 10
```
**Expected Output:**
```
R1 = 0xA
```

#### 2. ADD
**Input:**
```
MOV R1, 5
MOV R2, 7
ADD R3, R1, R2
```
**Expected Output:**
```
R3 = 0xC   (12 in decimal)
```

#### 3. SUB
**Input:**
```
MOV R1, 15
MOV R2, 5
SUB R3, R1, R2
```
**Expected Output:**
```
R3 = 0xA
```

#### 4. AND
**Input:**
```
MOV R1, 12
MOV R2, 10
AND R3, R1, R2
```
**Expected Output:**
```
R3 = 0x8
```

#### 5. OR
**Input:**
```
MOV R1, 4
MOV R2, 1
OR R3, R1, R2
```
**Expected Output:**
```
R3 = 0x5
```

#### 6. XOR
**Input:**
```
MOV R1, 7
MOV R2, 3
XOR R3, R1, R2
```
**Expected Output:**
```
R3 = 0x4
```

#### 7. LOAD / STORE
**Input:**
```
MOV R1, 9
STORE R1, 0x100
LOAD R2, 0x100
```
**Expected Output:**
```
Memory[0x100] = 9  
R2 = 9
```

#### 8. CMP / BEQ / BNE
**Input:**
```
MOV R1, 5
MOV R2, 5
CMP R1, R2
BEQ LABEL
```
**Expected Output:**
```
Z = 1  
BEQ triggered (branch condition true)
```

---

### Invalid or Error Cases

| Case | Example | Reason |
|------|----------|--------|
| Invalid Opcode | `FOO R1, R2` | The instruction is not recognized; program prints “Invalid Instruction.” |
| Invalid Operand Count | `ADD R1, R2` | Missing operand; results in incorrect parsing or undefined behavior. |
| Out-of-Range Memory Address | `LOAD R1, 0x120` | Memory array only supports addresses 0x100–0x110; this access is invalid. |
| Non-Integer Values | `MOV R1, ABC` | The program expects integers or register identifiers only. |

---

### Summary
This project successfully simulates the execution of a simplified instruction set processor.  
It demonstrates a clear flow of **instruction decoding**, **execution**, and **state visualization**, providing an accessible way to understand CPU fundamentals.
