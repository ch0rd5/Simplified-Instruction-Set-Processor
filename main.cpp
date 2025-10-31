#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "helpers.h"

using namespace std;

int main() {
    uint32_t memory[5] = { 0 };
    uint32_t reg[8] = { 0 };
    int Z = 0;

    ifstream infile("pp2_input.txt");
    if (!infile) {
        cout << "Failed to open file." << endl;
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        replace(line.begin(), line.end(), ',', ' ');
        cout << line << endl;

        stringstream ss(line);
        string opcode;
        ss >> opcode;

        if (opcode == "MOV") {
            string dest, src; ss >> dest >> src;
            executeMOV(dest, src, reg, memory);
        }
        else if (opcode == "ADD") {
            string rd, rs1, rs2; ss >> rd >> rs1 >> rs2;
            executeADD(rd, rs1, rs2, reg);
        }
        else if (opcode == "SUB") {
            string rd, rs1, rs2; ss >> rd >> rs1 >> rs2;
            executeSUB(rd, rs1, rs2, reg);
        }
        else if (opcode == "AND") {
            string rd, rs1, rs2; ss >> rd >> rs1 >> rs2;
            executeAND(rd, rs1, rs2, reg);
        }
        else if (opcode == "OR") {
            string rd, rs1, rs2; ss >> rd >> rs1 >> rs2;
            executeOR(rd, rs1, rs2, reg);
        }
        else if (opcode == "XOR") {
            string rd, rs1, rs2; ss >> rd >> rs1 >> rs2;
            executeXOR(rd, rs1, rs2, reg);
        }
        else if (opcode == "LOAD") {
            string rd, addrStr; ss >> rd >> addrStr;
            executeLOAD(rd, addrStr, reg, memory);
        }
        else if (opcode == "STORE") {
            string rs, addrStr; ss >> rs >> addrStr;
            executeSTORE(rs, addrStr, reg, memory);
        }
        else if (opcode == "CMP") {
            string op1, op2; ss >> op1 >> op2;
            executeCMP(op1, op2, reg, Z);
        }
        else if (opcode == "BEQ") {
            string label; ss >> label;
            executeBEQ(label, Z);
        }
        else if (opcode == "BNE") {
            string label; ss >> label;
            executeBNE(label, Z);
        }
        else if (opcode == "BAL") {
            string label; ss >> label;
            executeBAL(label);
        }
        else cout << "Invalid Instruction." << endl;

        // Display
        cout << "Register array:" << endl;
        for (int i = 0; i < 8; i++) cout << "R" << i << "=0x" << hex << reg[i] << " " << endl;

        cout << "Memory array:" << endl;
        for (int i = 0; i < 5; i++) cout << (memory[i] ? "0x" + to_string(memory[i]) : "___") << (i != 4 ? "," : "");
        cout << endl << endl;
    }

    infile.close();
    return 0;
}
