#include "helpers.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Function definitions

int getMemoryIndex(uint32_t address) {
	if (address < 0x100 || address > 0x110 || (address - 0x100) % 4 != 0) return -1;
	return (address - 0x100) / 4;
}

void executeMOV(const string& dest, const string& src, uint32_t reg[8], uint32_t memory[5]) {
	if (dest.empty() || src.empty()) {
		cout << "Invalid Instruction." << endl;
		return;
	}

	int d = dest[1] - '0';
	if (src[0] == '#') {
		reg[d] = stoi(src.substr(1), nullptr, 0);
	}
	else if (src[0] == 'R') {
		reg[d] = reg[src[1] - '0'];
	}
	else {
		uint32_t addr = stoi(src, nullptr, 0);
		int idx = getMemoryIndex(addr);
		if (idx == -1) cout << "Invalid Instruction. Memory out-of-range." << endl;
		else reg[d] = memory[idx];
	}
}

void executeADD(const string& rd, const string& rs1, const string& rs2, uint32_t reg[8]) {
	if (rd.empty() || rs1.empty() || rs2.empty()) {
		cout << "Invalid Instruction." << endl;
		return;
	}
	int d = rd[1] - '0';
	if (rs1[0] != 'R') {
		cout << "Invalid Instruction." << endl;
		return;
	}
	int s1 = rs1[1] - '0';
	if (rs2[0] == '#') reg[d] = reg[s1] + stoi(rs2.substr(1), nullptr, 0);
	else if (rs2[0] == 'R') reg[d] = reg[s1] + reg[rs2[1] - '0'];
	else cout << "Invalid Instruction." << endl;
}

void executeSUB(const string& rd, const string& rs1, const string& rs2, uint32_t reg[8]) {
	if (rd.empty() || rs1.empty() || rs2.empty()) {
		cout << "Invalid Instruction." << endl;
		return;
	}
	int d = rd[1] - '0';
	if (rs1[0] != 'R') {
		cout << "Invalid Instruction." << endl;
		return;
	}
	int s1 = rs1[1] - '0';
	if (rs2[0] == '#') reg[d] = reg[s1] - stoi(rs2.substr(1), nullptr, 0);
	else if (rs2[0] == 'R') reg[d] = reg[s1] - reg[rs2[1] - '0'];
	else cout << "Invalid Instruction." << endl;
}

void executeAND(const string& rd, const string& rs1, const string& rs2, uint32_t reg[8]) {
	if (rd.empty() || rs1.empty() || rs2.empty() || rs1[0] != 'R' || rs2[0] != 'R') {
		cout << "Invalid Instruction." << endl;
		return;
	}
	int d = rd[1] - '0';
	int s1 = rs1[1] - '0';
	int s2 = rs2[1] - '0';
	reg[d] = reg[s1] & reg[s2];
}

void executeOR(const string& rd, const string& rs1, const string& rs2, uint32_t reg[8]) {
	if (rd.empty() || rs1.empty() || rs2.empty() || rs1[0] != 'R' || rs2[0] != 'R') {
		cout << "Invalid Instruction." << endl;
		return;
	}
	int d = rd[1] - '0';
	int s1 = rs1[1] - '0';
	int s2 = rs2[1] - '0';
	reg[d] = reg[s1] | reg[s2];
}

void executeXOR(const string& rd, const string& rs1, const string& rs2, uint32_t reg[8]) {
	if (rd.empty() || rs1.empty() || rs2.empty() || rs1[0] != 'R' || rs2[0] != 'R') {
		cout << "Invalid Instruction." << endl;
		return;
	}
	int d = rd[1] - '0';
	int s1 = rs1[1] - '0';
	int s2 = rs2[1] - '0';
	reg[d] = reg[s1] ^ reg[s2];
}

void executeLOAD(const string& rd, const string& addrStr, uint32_t reg[8], uint32_t memory[5]) {
	if (rd.empty() || addrStr.empty()) {
		cout << "Invalid Instruction." << endl;
		return;
	}
	int d = rd[1] - '0';
	uint32_t addr = stoi(addrStr, nullptr, 0);
	int idx = getMemoryIndex(addr);
	if (idx == -1) cout << "Invalid Instruction. Memory out-of-range." << endl;
	else reg[d] = memory[idx];
}

void executeSTORE(const string& rs, const string& addrStr, uint32_t reg[8], uint32_t memory[5]) {
	if (rs.empty() || addrStr.empty()) {
		cout << "Invalid Instruction." << endl;
		return;
	}
	int s = rs[1] - '0';
	uint32_t addr = stoi(addrStr, nullptr, 0);
	int idx = getMemoryIndex(addr);
	if (idx == -1) cout << "Invalid Instruction. Memory out-of-range." << endl;
	else memory[idx] = reg[s];
}

void executeCMP(const string& op1, const string& op2, uint32_t reg[8], int& Z) {
	if (op1.empty() || op2.empty()) {
		cout << "Invalid Instruction." << endl;
		return;
	}
	uint32_t val1 = 0, val2 = 0;
	if (op1[0] != 'R') {
		cout << "Invalid Instruction." << endl;
		return;
	}
	val1 = reg[op1[1] - '0'];
	if (op2[0] == '#') val2 = stoi(op2.substr(1), nullptr, 0);
	else if (op2[0] == 'R') val2 = reg[op2[1] - '0'];
	else val2 = stoi(op2, nullptr, 0);
	Z = ((val1 - val2) == 0) ? 1 : 0;
	cout << "Status flag: Z=" << Z << endl;
}

void executeBEQ(const string& label, int Z) {
	if (label.empty()) cout << "Invalid Instruction." << endl;
	else if (Z == 1) cout << "Branch will be taken to " << label << endl;
	else cout << "Branch will not be taken to " << label << endl;
}

void executeBNE(const string& label, int Z) {
	if (label.empty()) cout << "Invalid Instruction." << endl;
	else if (Z == 0) cout << "Branch will be taken to " << label << endl;
	else cout << "Branch will not be taken to " << label << endl;
}

void executeBAL(const string& label) {
	if (label.empty()) cout << "Invalid Instruction." << endl;
	else cout << "Branch will be taken to " << label << endl;

}
