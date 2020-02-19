#include "xed.hpp"
#include "Opcode.hpp"
#include <iomanip>

ifstream symStream; //symbol stream
ifstream objStream; //object stream
ofstream sicStream; //sic stream
ofstream lisStream; //list stream

/**
Function xed: reads the input files and copies the contents into vectors for storage
**/
void xed::StorageLoader()
{
    string filestr;
    while (objStream.good())
    {
        getline(objStream, filestr);
        objStor.push_back(filestr);
    }
    while (symStream.good())
    {
        getline(symStream, filestr);
        symStor.push_back(filestr);
    }

    int start = 2; //we need to start at 2 to ensure no out of bounds error
    for (start = 2; start < symStor.size()-1; start++)
    {
        if(symStor[start][0] != (char)NULL)
        {
         symbol.push_back(symStor[start].substr(0, 6));
         symValue.push_back((unsigned int)strtol(symStor[start].substr(8, 6).c_str(),NULL,16));
         symFlag.push_back((unsigned int)strtol(symStor[start].substr(16, 1).c_str(),NULL,16));     
        }
        else
        {
            start+=3;
      
            break;
        }
    }

    for (int i = start; i < symStor.size()-1; i++)
    {
        litName.push_back(symStor[i].substr(8, 6));
        litLength.push_back((int)strtol(symStor[start].substr(19, 1).c_str(), NULL, 16));
        litAddr.push_back((unsigned int)strtol(symStor[start].substr(24, 6).c_str(), NULL, 16));
    }
}

/**
Function xed: reads the object file and the symbol file
**/
void xed::readFile (char *objFile)
{
    objStream.open(objFile);
    if (!objStream.is_open())
    {
        cout << "ERROR: UNABLE TO OPEN <filename>.obj" << endl;
        return;
        //exit (EXIT_FAILURE);
    }

    string symFile = objFile;
    //symFile.erase(symFile.find_last_of("."));
    symFile.erase(symFile.find("."));
    symFile += ".sym";
    symStream.open(symFile.c_str());
    /*
    if (!symStream.is_open())
    {
        cout << "incorrect or no file found." << endl;
        exit (EXIT_FAILURE);
    }
    */
    string sicFile = symFile;
    //sicFile.erase(symFile.find_last_of("."));
    sicFile.erase(symFile.find("."));
    sicFile += ".sic";
    sicStream.open(sicFile.c_str());

    string lisFile = sicFile;
    //lisFile.erase(lisFile.find_last_of("."));
    lisFile.erase(symFile.find("."));
    lisFile += ".lis";
    lisStream.open(lisFile.c_str());

    StorageLoader();
/*
    objStream.close();
    symStream.close();
*/
}

/**
Function xed: analyze format 1 of the opcode
**/
void xed::format1 (Opcode code, int opcode, int row, int current)
{
    string opname = code.getInstruction(opcode);
    for (int i = 0; i < symValue.size()-1; i++)
    {
        if (currentAddr == symValue[i])
        {
            sicStream << setw(8) << left << symbol[i];
            lisStream << setw(8) << left << symbol[i];
            break;
        }
        else if (i+1 >= symValue.size()-1)
        {
            sicStream << "        " << setw(8) << left << opname;
            lisStream << "        " << setw(8) << left << opname;
        }
    }
    
    for (int i = 0; i < litName.size(); i++) 
    { 
        if (currentAddr == litAddr[i]) 
        {
            sicStream << setw(10) << left << litName[i] << endl;
            sicStream << setw(14) << right << "LTORG" << endl;
            lisStream << setw(10) << left << litName[i] << endl;
            lisStream << setw(14) << right << "LTORG" << endl;
            return;
        }
    }
}

void xed::format2 (Opcode code, int opcode, int row, int current)
{
    string opname = code.getInstruction(opcode);
    for (int i = 0; i < symValue.size()-1; i++)
    {
        if (currentAddr == symValue[i])
        {
            sicStream << setw(8) << left << symbol[i];
            lisStream << setw(8) << left << symbol[i];
            break;
        }
        else if (i+1 >= symValue.size()-1) 
        {
            sicStream << "        " << setw(8) << left << opname;
            lisStream << "        " << setw(8) << left << opname;
        }
    }

    for (int i = 0; i < litName.size(); i++)
    {
        if (currentAddr == litAddr[i])
        {
            sicStream << setw(10) << left << litName[i] << endl;
            sicStream << setw(14) << right << "LTORG" << endl;
            lisStream << setw(10) << left << litName[i] << endl;
            lisStream << setw(14) << right << "LTORG" << endl;
            return;
        }
    }

    int register1 = (int)strtol(objStor[row].substr(current+2, 1).c_str(), NULL, 16);
    int register2 = (int)strtol(objStor[row].substr(current+3, 1).c_str(), NULL, 16);

    switch (register1) 
    {           
        case 0:
            sicStream << "A,";
            lisStream << "A,";
            break;
        case 1:
            sicStream << "X,";
            lisStream << "X,";
            break;
        case 2:
            sicStream << "L,";
            lisStream << "L,";
            break;
        case 3:
            sicStream << "B,";
            lisStream << "B,";
            break;
        case 4:
            sicStream << "S,";
            lisStream << "S,";
            break;
        case 5:
            sicStream << "T,";
            lisStream << "T,";
            break;
        case 6:
            sicStream << "F,";
            lisStream << "F,";
            break;
        default:
            break;
    }
    
    switch (register2) 
    {           
        case 0:
            sicStream << "A" << endl;
            lisStream << "A" << endl;
            break;
        case 1:
            sicStream << "X" << endl;
            lisStream << "X" << endl;
            break;
        case 2:
            sicStream << "L" << endl;
            lisStream << "L" << endl;
            break;
        case 3:
            sicStream << "B" << endl;
            lisStream << "B" << endl;
            break;
        case 4:
            sicStream << "S" << endl;
            lisStream << "S" << endl;
            break;
        case 5:
            sicStream << "T" << endl;
            lisStream << "T" << endl;
            break;
        case 6:
            sicStream << "F" << endl;
            lisStream << "F" << endl;
            break;
        default:
            break;
    }
}

int xed::format3 (Opcode code, int opcode, int row, int current)
{
    string opname = code.getInstruction(opcode);
    bool nixbpe[6];
    int flagSection = (int)strtol(objStor[row].substr(current+1, 2).c_str(), NULL, 16);
    for (int i = 0; i < 6; i++) //set flags bits for nixbpe
    {
        if((flagSection >> (5-i) & 1) == true)
            nixbpe[i] = 1;
        else
            nixbpe[i] = 0;
    }          
        

    unsigned int instruc = (unsigned int)strtol(objStor[row].substr(current, 2*(3+nixbpe[5])).c_str(), NULL, 16);
    
    for (int i = 0; i < symValue.size()-1; i++) 
    { 
        if (currentAddr == symValue[i]) 
        {
            sicStream << setw(8) << left << symbol[i];
            lisStream << setw(8) << left << symbol[i];
            //break;
        }
        else if (i+1 >= symValue.size()-1) 
        {
            sicStream << "        ";
            lisStream << "        ";
        }
    }

    for (int i = 0; i < litName.size(); i++)
    {
        if (currentAddr == litAddr[i])
        {
            int literal = (int)strtol(objStor[row].substr(current+(2*(3+nixbpe[5])), litLength[i]).c_str(), NULL, 16);
            sicStream << (nixbpe[5] ? "+":" "); //insert a "+" if extended format
            sicStream << setw(7) << opname << setw(10) << left << litName[i] << endl;
            sicStream << setw(14) << right << "LTORG" << endl;
            lisStream << (nixbpe[5] ? "+":" "); //insert a "+" if extended format
            lisStream << setw(7) << left << opname << setw(10) << left << litName[i];
            lisStream << setfill('0') << right << setw(2*(3+nixbpe[5])) << instruc << setfill(' ') << endl;
            lisStream << setfill('0') << setw(4) << right << currentAddr << setfill(' ') << "  ";
            lisStream << setw(14) << right << "LTORG" << "            " << literal << endl;
            return (3 + (litLength[i]/2));
        }
    }

    sicStream << (nixbpe[5] ? "+":" "); //insert a "+" if extended format
    lisStream << (nixbpe[5] ? "+":" ");

    unsigned int TA = 0; //target address
    
    if (nixbpe[5]) 
    {                    //check for extended format and put displacement field into TA
        TA = (unsigned int)strtol(objStor[row].substr(current, 8).c_str(), NULL, 16);
        TA &= 0x000FFFFF;
    }
    else 
    {
        TA = (unsigned int)strtol(objStor[row].substr(current, 6).c_str(), NULL, 16);
        TA &= 0x000FFF;
    }
    
    if (nixbpe[3]) 
    {        //base relative
        TA += baseAddr;
    }
    else if (nixbpe[4]) 
    {   //PC relative
        TA += (currentAddr + 3);
    }
    
    if (opname == "J" || opname == "JEQ" || opname == "JGT" || opname == "JLT" || opname == "JSUB") 
    {
        TA &= (nixbpe[5] ? 0x000FFFFF:0x000FFF);
    }

    if (nixbpe[0] == nixbpe[1]) 
    {   // simple addressing
        sicStream << setw(8) << left << opname;
        lisStream << setw(8) << left << opname;
        
        for (int i = 0; i < symValue.size(); i++) 
        { //insert symbol name
            if (TA == symValue[i] && opname != "RSUB") 
            {
                sicStream << setw(9) << left << symbol[i] + (nixbpe[2] ? ",X":"") << endl;
                lisStream << setw(9) << left << symbol[i] + (nixbpe[2] ? ",X":"");
                break;
            }
        }
        if (opname == "RSUB") {
            sicStream << endl;
            lisStream << "         ";
        }
    }

    else if (nixbpe[0]) 
    {   //indirect addressing
        sicStream << setw(7) << left << opname << "@";
        lisStream << setw(7) << left << opname << "@";
        for (int i = 0; i < symValue.size(); i++) 
        { //insert symbol name
            if (TA == symValue[i] && opname != "RSUB") 
            {
                sicStream << setw(9) << left << symbol[i] + (nixbpe[2] ? ",X":"") << endl;
                lisStream << setw(9) << left << symbol[i] + (nixbpe[2] ? ",X":"");
                break;
            }
        }
    }

    else 
    {                  //immediate addressing`
        sicStream << setw(7) << left << opname << "#";
        lisStream << setw(7) << left << opname << "#";
        if (!nixbpe[5]) 
        {
            sicStream << TA << endl;
            lisStream << setw(9) << TA;
        }
    }

    if (opname == "LDB") 
    {
        baseAddr = TA;
        for (int i = 0; i < symValue.size(); i++) 
        { //check if symbol name should be inserted
            if (TA == symValue[i]) 
            {
                sicStream << setw(10) << left << symbol[i] << endl;
                sicStream << setw(17) << right << "BASE    " << symbol[i] << endl;
                lisStream << setw(9) << left << symbol[i];
                lisStream << setw(2*(3+nixbpe[5])) << setfill('0') << instruc << setfill(' ') << endl;
                lisStream << setfill('0') << setw(4) << right << currentAddr << setfill(' ') << "  ";
                lisStream << setw(17) << right << "BASE    " << symbol[i] << endl;
                return (3+nixbpe[5]);
            }
        }
    }

    lisStream << right << setfill('0') << setw(2*(3+nixbpe[5])) << instruc << setfill(' ') << endl;
    return (3+nixbpe[5]);
}

int xed::readInstruc(int row, int current)
{
    Opcode code = *new Opcode;
    //int opcode = (int)strtol(objStor[row].substr(current, 2).c_str(), NULL, 16);
    int opcode = code.getOpcode((int)strtol(objStor[row].substr(current, 2).c_str(), NULL, 16));
    int instrucLen = code.getFormat(opcode);
    lisStream << setfill('0') << setw(4) << right << currentAddr << setfill(' ') << "  ";     
    //print current address in listing file
    switch (instrucLen) 
    {
        case 1:
            format1(code, opcode, row, current);
            break;
        case 2:
            format2(code, opcode, row, current);
            break;
        case 3:
            instrucLen = format3(code, opcode, row, current);
            break;
        default:
            break;
    }
    return (instrucLen * 2);
}

void xed::header(int row)
{
    string last; //this is the last line
    string progName = objStor[row].substr(1, 6);
    stringstream ss;
    unsigned int progStart = (unsigned int)strtol(objStor[row].substr(7, 6).c_str(), NULL, 16);
    currentAddr = progStart;
    progLength = (unsigned int)strtol(objStor[row].substr(13, 6).c_str(), NULL, 16);
    ss << progStart;
    string address = ss.str();
    sicStream << setw(9) << left << progName << "START   " << address <<endl;
    lisStream << setbase(16) << uppercase << setw(4) << setfill('0') << currentAddr << setfill(' ') << "  ";
    lisStream << setw(9) << left << progName << "START   " << address <<endl;
}

void xed::text(int row)
{
    int textLength = (int)strtol(objStor[row].substr(7, 2).c_str(), NULL, 16);
    int current = 9;
    while (current < (2 * textLength + 9)) 
    {
        int objSize = readInstruc(row, current);
        currentAddr += (objSize/2);
        current += objSize;
    }

    for (int i = 0; i < symValue.size(); i++) 
    { //check for assembler directives
        if (currentAddr <= symValue[i]) 
        {    //symbol was not used in program, use "RESW" or "RESB" to allocate memory
            lisStream << setfill('0') << setw(4) << right << currentAddr << setfill(' ') << "  ";
            if ((currentAddr % 3) == 0) 
            {  // if divisible by 3, reserve word
                sicStream << setw(8) << left << symbol[i] << " RESW    ";
                lisStream << setw(8) << left << symbol[i] << " RESW    ";
                if (i+1 < symValue.size()) 
                {
                    sicStream << setw(8) << left << (symValue[i+1]-symValue[i])/3 << endl;
                    lisStream << setbase(10) << setw(8) << left << (symValue[i+1]-symValue[i])/3 << setbase(16) << endl;
                    currentAddr +=(symValue[i+1]-symValue[i]);
                }
                else 
                {
                    sicStream << setw(8) << left << (progLength-symValue[i])/3 << endl;
                    lisStream << setbase(10) << setw(8) << left << (progLength-symValue[i])/3 << setbase(16) << endl;
                    currentAddr += (progLength-symValue[i]);
                }
            }
            else 
            {
                sicStream << setw(8) << left << symbol[i] << " RESB    ";
                lisStream << setw(8) << left << symbol[i] << " RESB    ";
                if (i+1 < symValue.size()) 
                {
                    sicStream << setw(8) << left << (symValue[i+1]-symValue[i]) << endl;
                    lisStream << setbase(10) << setw(8) << left << (symValue[i+1]-symValue[i]) << setbase(16) << endl;
                    currentAddr += (symValue[i+1]-symValue[i])/3;
                }
                else 
                {
                    sicStream << setw(8) << left << (progLength-symValue[i]) << endl;
                    lisStream << setbase(10) << setw(8) << left << (progLength-symValue[i]) << setbase(16) << endl;
                    currentAddr += (progLength-symValue[i])/3;
                }
            }
        }
    }
}

void xed::modify (int row)
{
    unsigned int modAddress = (unsigned int)strtol(objStor[row].substr(1, 6).c_str(), NULL, 16);
    int modLength = (int)strtol(objStor[row].substr(7, 2).c_str(), NULL, 16);
    int i = 0;
    unsigned int address = 0;

    while (objStor[i][0] != 'T') 
    {   //find the first text record
        i++;
    }
    address = (unsigned int)strtol(objStor[i].substr(1, 6).c_str(), NULL, 16);  //store text start address

    while (address < modLength) 
    {   //find text record that contains the address to modify
        address += (unsigned int)strtol(objStor[i].substr(7, 2).c_str(), NULL, 16);
        i++;
    }

    i--;
    address -= (unsigned int)strtol(objStor[i].substr(7, 2).c_str(), NULL, 16);  //subtract the last text length that was added
    int position = 2 * (modAddress - address) + 10;
    objStor[i][position] += progLength;
}

void xed::endObjCode (int row)
{
    unsigned int endAddress = (unsigned int)strtol(objStor[row].substr(1, 6).c_str(), NULL, 16);
    for (int i = 0; i < symValue.size(); i++)
    { 
        //check the symbol table for address of first instruction
        if (endAddress == symValue[i]) 
        {
            sicStream << "        " << setw(8) << left << "END" << symbol[i] << endl;
            lisStream << "        " << setw(8) << left << "END" << symbol[i] << endl;
            break;
        }
    }
}  

void xed::disassemble()
{
    for (int i = 0; i < objStor.size(); i++) 
    {
        switch (objStor[i][0]) 
        {
            case 'H':
                header(i);
                break;
            case 'T':
                text(i);
                break;
            case 'M':
                modify(i);
                break;
            case 'E':
                endObjCode(i);
                break;
            default:
                break;
        }
    }
}