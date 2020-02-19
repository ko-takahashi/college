#include <vector>
#include "OpCode.h"

using namespace std;

#include "Dasm.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>.obj" << endl;
        exit(EXIT_FAILURE);
    }
    Dasm *disassembler = new Dasm;
    disassembler->openFiles(*(argv+1));
    disassembler->disassemble();
    
    return 0;
}