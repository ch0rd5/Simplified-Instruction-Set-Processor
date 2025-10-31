#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <cstdint>

int getMemoryIndex(uint32_t address);

// Instruction declarations
bool executeMOV(const std::string& dest, const std::string& src, uint32_t reg[8], uint32_t memory[5]);
bool executeADD(const std::string& rd, const std::string& rs1, const std::string& rs2, uint32_t reg[8]);
bool executeSUB(const std::string& rd, const std::string& rs1, const std::string& rs2, uint32_t reg[8]);
bool executeAND(const std::string& rd, const std::string& rs1, const std::string& rs2, uint32_t reg[8]);
bool executeOR(const std::string& rd, const std::string& rs1, const std::string& rs2, uint32_t reg[8]);
bool executeXOR(const std::string& rd, const std::string& rs1, const std::string& rs2, uint32_t reg[8]);
bool executeLOAD(const std::string& rd, const std::string& addrStr, uint32_t reg[8], uint32_t memory[5]);
bool executeSTORE(const std::string& rs, const std::string& addrStr, uint32_t reg[8], uint32_t memory[5]);
bool executeCMP(const std::string& op1, const std::string& op2, uint32_t reg[8], int& Z);
bool executeBEQ(const std::string& label, int Z);
bool executeBNE(const std::string& label, int Z);
bool executeBAL(const std::string& label);

#endif

