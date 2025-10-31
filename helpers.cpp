#include "helpers.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//Learned:
// - You can convert a char into an int using " [char] - '0';
// - substr(#) is used to start a string that starts from index #
// - stoi is used to do string to int

// Function definitions

int getMemoryIndex(uint32_t address) {
	//Checks if address is valid
	if (address < 0x100 || address > 0x110 || (address - 0x100) % 4 != 0) {
		return -1;
	}
	//returns Register index @ address
	return (address - 0x100) / 4;
}

bool executeMOV(const string& dest, const string& src, uint32_t reg[8], uint32_t memory[5]) {
	//Check not empty
	if (dest.empty() || src.empty()) {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	//Register index number
	int d = dest[1] - '0';

	//find out the kind of input
	if (src[0] == '#') {
		//#0x0000 inputs
		reg[d] = stoi(src.substr(1), nullptr, 0);
	}
	else if (src[0] == 'R') {
		//R0 inputs
		reg[d] = reg[src[1] - '0'];
	}
	else {
		//0x000 inputs
		uint32_t addr = stoi(src, nullptr, 0);
		int index = getMemoryIndex(addr);
		if (index == -1)
		{
			cout << "Invalid Instruction. Memory out-of-range." << endl;
			return false;
		}
		else {
			reg[d] = memory[index];
		}
	}
	return true;
}

bool executeADD(const string& rd, const string& rs1, const string& rs2, uint32_t reg[8]) {
	//Check not empty
	if (rd.empty() || rs1.empty() || rs2.empty()) {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	//Register index number
	int d = rd[1] - '0';
	if (rs1[0] != 'R') {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	int s1 = rs1[1] - '0';
	//find out the kind of input
	if (rs2[0] == '#') {
		//#0x0000 inputs
		reg[d] = reg[s1] + stoi(rs2.substr(1), nullptr, 0);
	}
	else if (rs2[0] == 'R') {
		//R0 inputs
		reg[d] = reg[s1] + reg[rs2[1] - '0'];
	}
	else {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	return true;
}

bool executeSUB(const string& rd, const string& rs1, const string& rs2, uint32_t reg[8]) {
	//Check not empty
	if (rd.empty() || rs1.empty() || rs2.empty()) {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	//Register index number
	int d = rd[1] - '0';
	if (rs1[0] != 'R') {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	int s1 = rs1[1] - '0';
	//find out the kind of input
	if (rs2[0] == '#') {
		//#0x0000 inputs
		reg[d] = reg[s1] - stoi(rs2.substr(1), nullptr, 0);
	}
	else if (rs2[0] == 'R') {
		//R0 inputs
		reg[d] = reg[s1] - reg[rs2[1] - '0'];
	}
	else {
		//0x000 inputs
		cout << "Invalid Instruction." << endl;
		return false;
	}
	return true;
}

bool executeAND(const string& rd, const string& rs1, const string& rs2, uint32_t reg[8]) {
	//Check not empty
	if (rd.empty() || rs1.empty() || rs2.empty() || rs1[0] != 'R' || rs2[0] != 'R') {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	//Register index number
	int d = rd[1] - '0';
	int s1 = rs1[1] - '0';
	int s2 = rs2[1] - '0';
	reg[d] = reg[s1] & reg[s2];
	return true;
}

bool executeOR(const string& rd, const string& rs1, const string& rs2, uint32_t reg[8]) {
	//Check not empty
	if (rd.empty() || rs1.empty() || rs2.empty() || rs1[0] != 'R' || rs2[0] != 'R') {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	//Register index number
	int d = rd[1] - '0';
	int s1 = rs1[1] - '0';
	int s2 = rs2[1] - '0';
	reg[d] = reg[s1] | reg[s2];
	return true;
}

bool executeXOR(const string& rd, const string& rs1, const string& rs2, uint32_t reg[8]) {
	//Check not empty
	if (rd.empty() || rs1.empty() || rs2.empty() || rs1[0] != 'R' || rs2[0] != 'R') {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	//Register index number
	int d = rd[1] - '0';
	int s1 = rs1[1] - '0';
	int s2 = rs2[1] - '0';
	reg[d] = reg[s1] ^ reg[s2];
	return true;
}

bool executeLOAD(const string& rd, const string& addrStr, uint32_t reg[8], uint32_t memory[5]) {
	//Check not empty
	if (rd.empty() || addrStr.empty()) {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	//Register index number
	int d = rd[1] - '0';
	uint32_t addr = stoi(addrStr, nullptr, 0);
	int idx = getMemoryIndex(addr);
	if (idx == -1) {
		cout << "Invalid Instruction. Memory out-of-range." << endl;
		return false;
	}
	else {
		reg[d] = memory[idx];
		return true;
	}
}

bool executeSTORE(const string& rs, const string& addrStr, uint32_t reg[8], uint32_t memory[5]) {
	// Check for missing operands
	if (rs.empty() || addrStr.empty()) {
		cout << "Invalid Instruction." << endl;
		return false;
	}

	// Validate source register format (must start with 'R')
	if (rs[0] != 'R' || rs.size() < 2 || !isdigit(rs[1])) {
		cout << "Invalid Instruction. Invalid register." << endl;
		return false;
	}

	int s = rs[1] - '0';
	if (s < 0 || s > 7) {
		cout << "Invalid Instruction. Register out-of-range." << endl;
		return false;
	}

	// Convert memory address (like "0x100") to index
	uint32_t addr = stoi(addrStr, nullptr, 0);
	int idx = getMemoryIndex(addr);

	if (idx == -1) {
		cout << "Invalid Instruction. Memory out-of-range." << endl;
		return false;
	}

	// Store register value into memory
	memory[idx] = reg[s];
	return true;
}


bool executeCMP(const string& op1, const string& op2, uint32_t reg[8], int& Z) {
	//Check not empty
	if (op1.empty() || op2.empty()) {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	uint32_t val1 = 0, val2 = 0;
	if (op1[0] != 'R') {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	val1 = reg[op1[1] - '0'];
	//find out the kind of input
	if (op2[0] == '#') {
		//#0x0000 inputs
		val2 = stoi(op2.substr(1), nullptr, 0);
	}
	else if (op2[0] == 'R') {
		//R0 inputs
		val2 = reg[op2[1] - '0'];
	}
	else {
		//0x000 inputs
		val2 = stoi(op2, nullptr, 0);
		Z = ((val1 - val2) == 0) ? 1 : 0;
		cout << "Status flag: Z=" << Z << endl;
	}
	return true;
}

bool executeBEQ(const string& label, int Z) {
	//Check not empty
	if (label.empty()) {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	else if (Z == 1) {
		cout << "Branch will be taken to " << label << endl;
	}
	else {
		cout << "Branch will not be taken to " << label << endl;
	}
	return true;
}

bool executeBNE(const string& label, int Z) {
	//Check not empty
	if (label.empty()) {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	else if (Z == 0) {
		cout << "Branch will be taken to " << label << endl;
	}
	else {
		cout << "Branch will not be taken to " << label << endl;
	}
	return true;
}

bool executeBAL(const string& label) {
	//Check not empty
	if (label.empty()) {
		cout << "Invalid Instruction." << endl;
		return false;
	}
	else {
		cout << "Branch will be taken to " << label << endl;
	}
	return true;
}
