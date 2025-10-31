#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <cstdint>

int getMemoryIndex(uint32_t address);

// Instruction declarations
void executeMOV(const std::string& dest, const std::string& src, uint32_t reg[8], uint32_t memory[5]);
void executeADD(const std::string& rd, const std::string& rs1, const std::string& rs2, uint32_t reg[8]);
void executeSUB(const std::string& rd, const std::string& rs1, const std::string& rs2, uint32_t reg[8]);
void executeAND(const std::string& rd, const std::string& rs1, const std::string& rs2, uint32_t reg[8]);
void executeOR(const std::string& rd, const std::string& rs1, const std::string& rs2, uint32_t reg[8]);
void executeXOR(const std::string& rd, const std::string& rs1, const std::string& rs2, uint32_t reg[8]);
void executeLOAD(const std::string& rd, const std::string& addrStr, uint32_t reg[8], uint32_t memory[5]);
void executeSTORE(const std::string& rs, const std::string& addrStr, uint32_t reg[8], uint32_t memory[5]);
void executeCMP(const std::string& op1, const std::string& op2, uint32_t reg[8], int& Z);
void executeBEQ(const std::string& label, int Z);
void executeBNE(const std::string& label, int Z);
void executeBAL(const std::string& label);

#endif

