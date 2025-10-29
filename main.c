#include <stdio.h>

int main(){
  uint32_t* memory = (uint32_t*)0x100;
  uint32_t reg[5] = {0,0,0,0,0};
  FILE* fptr = fopen("pp2_input.txt", "r");
  if(fptr == NULL){
    printf("Failed opening file");
    return 1;
  }
  /*To parse each line, first split it at the first space to separate the **operator** from the rest of the line (the operands). Then, split the remaining part by **commas** to extract each operand, trimming any extra spaces around them. Store the operator and operands (and how many operands you found) in a structure or array so you can process them later. This approach works even when different instructions have different numbers of operands.*/

  return 0;
}
