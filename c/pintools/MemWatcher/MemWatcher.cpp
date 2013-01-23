/*BEGIN_LEGAL 
Intel Open Source License 

Copyright (c) 2002-2012 Intel Corporation. All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.  Neither the name of
the Intel Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without
specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */

/*! @file
 *  This is an example of the PIN tool that demonstrates some basic PIN APIs 
 *  and could serve as the starting point for developing your first PIN tool
 */

#include "pin.H"
#include <stdio.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <list>

/* ================================================================== */
// Global variables 
/* ================================================================== */
ADDRINT rangeStart = 0;
ADDRINT rangeEnd = 0;

// Just happens to be PnkBstrB.exe .data section
ADDRINT obfuscStart = 0x2A00C; // start offset (will be added to base)
ADDRINT obfuscEnd = 0x36F88;   // end offset (will be added to base)

//ADDRINT dataStart = 0x20000;
//ADDRINT dataEnd = 0x2A00C;
ADDRINT dataStart = 0;
ADDRINT dataEnd = 0;

FILE *outFile;

/* ===================================================================== */
// Command line switches
/* ===================================================================== */
KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE,  "pintool",
    "o", "", "specify file name for MemWatcher output");

/* ===================================================================== */
// Utilities
/* ===================================================================== */

/*!
 *  Print out help message.
 */
INT32 Usage()
{
    cerr << "This tool runs obfuscated parts of pnkbstrb.exe " << endl;
    cerr << KNOB_BASE::StringKnobSummary() << endl;

    return -1;
}

/* ===================================================================== */
// Instrumentation routines
/* ===================================================================== */
BOOL IsInRange(ADDRINT writeAddress)
{
	//fprintf(outFile, "IsInRange: !(0x%08x >= 0x%08x && 0x%08x <= 0x%08x) = %d\r\n", writeAddress, dataStart, writeAddress, dataEnd, !(writeAddress >= dataStart && writeAddress <= dataEnd));
	return (!(writeAddress >= dataStart && writeAddress <= dataEnd) == 0);
}

BOOL IsSelfCall(ADDRINT call)
{
	return (!(call == 0x42b2f3));
}
VOID
LogInstruction(THREADID threadID, ADDRINT address, const char * disasm)
{
	fprintf(outFile, "UN [%d] 0x%lx %s ;\r\n", 
			threadID, address, disasm);
}


VOID
LogMemoryRead(THREADID threadID, ADDRINT address, const char * disasm,
		ADDRINT readaddr, UINT32 size,
		const CONTEXT *ctx, void *data)
{
	std::list<REG> * registers = (std::list<REG> *) data;


	fprintf(outFile, "RD [%d] 0x%lx %s ; 0x%lx [%lx]",
			threadID, address, disasm, readaddr,
			(*(unsigned long *)readaddr) );

	fprintf(outFile, "{");
	for (std::list<REG>::iterator it = registers->begin();
			it != registers->end(); it++) {
		REG reg = (*it);
		std::string name = REG_StringShort(reg);
		ADDRINT value = 0;
		// value = PIN_GetContextReg(ctx, reg);

		fprintf(outFile, " %s:%lx ", name.c_str(), value);
	}
	fprintf(outFile, "}\r\n");
}

VOID
LogMemoryRead2(THREADID threadID, ADDRINT address, const char * disasm,
		ADDRINT readaddr, UINT32 size, ADDRINT readaddr2)
{
	fprintf(outFile, "RD [%d] 0x%lx %s ; 0x%lx [%lx], 0x%lx [%lx]\r\n",
			threadID,  address, disasm,
			 readaddr,  (*(unsigned long *)readaddr),
			 readaddr2, (*(unsigned long *)readaddr2));
}

VOID
LogMemoryWrite(THREADID threadID, ADDRINT address, const char * disasm,
		ADDRINT writeaddr, UINT32 size)
{
	fprintf(outFile, "WR [%d] 0x%lx %s ; 0x%lx [%lx] [%d]\r\n",
			threadID, address, disasm,
			writeaddr, (*(unsigned long *)writeaddr), size);
}

VOID 
LogDirectCall(THREADID threadID, ADDRINT address, const char * disasm)
{
	fprintf(outFile, "CL [%d] 0x%lx %s\r\n", threadID, address, disasm);
}

const char *
dumpInstruction(INS ins)
{
	ADDRINT address = INS_Address(ins);
	std::stringstream ss;

	// Generate instruction byte encoding
	for (size_t i=0;i<INS_Size(ins);i++)
	{
		ss << setfill('0') << setw(2) << hex << (((unsigned int) *(unsigned char*)(address + i)) & 0xFF) << " ";
	}

	for (size_t i=INS_Size(ins);i<8;i++)
	{
		ss << "   ";
	}

	// Generate diassembled string
	ss << INS_Disassemble(ins);

	return _strdup(ss.str().c_str());
}

std::list<REG> *
listRegisters(INS ins)
{
	std::list<REG> *registers = new std::list<REG>;

	for (UINT32 i = 0; i < INS_OperandCount(ins); i++) {
		if (INS_OperandIsReg(ins, i)) {
			REG reg = INS_OperandReg(ins, i);
			registers->push_back(reg);
		}
	}

	return registers;
}

/* ===================================================================== */
// Analysis routines
/* ===================================================================== */

VOID ImageLoad(IMG img, VOID *v)
{
	fprintf(outFile, "Loading %s\r\nStart 0x%08x-0x%08x\r\n", IMG_Name(img).c_str(),IMG_LowAddress(img), IMG_HighAddress(img));
	if (IMG_Name(img).rfind("PnkBstrB.exe") == -1) 
	{
		return;
	}

	for(SEC section=IMG_SecHead(img); SEC_Valid(section); section = SEC_Next(section)) 
	{
		if (SEC_Name(section).compare(".data")) 
		{
			//dataStart = SEC_Address(section);
			//dataEnd = SEC_Address(section) + SEC_Size(section);
			obfuscStart += SEC_Address(section);
			obfuscEnd += SEC_Address(section) + SEC_Size(section);
			dataStart = IMG_LowAddress(img);
			dataEnd = IMG_HighAddress(img);
			//obfuscStart = IMG_LowAddress(img);
			//obfuscEnd = IMG_HighAddress(img);
			fprintf(outFile, ".data @ 0x%08x-0x%08x\r\n", dataStart, dataEnd);
			rangeStart = IMG_LowAddress(img);
			rangeEnd = IMG_HighAddress(img);
			fprintf(outFile, "obfuscation range @ 0x%08x-0x%08x\r\n", obfuscStart, obfuscEnd);
			return;
		}
	}
}

VOID Instruction(INS ins, VOID *v)
{
	const char * disasm = dumpInstruction(ins);
	UINT32 memOperands = INS_MemoryOperandCount(ins);
	ADDRINT loc = INS_Address(ins);
	if (loc >= obfuscStart && loc <= obfuscEnd)
	//if (loc >= rangeStart && loc <= rangeEnd)
	{
	//{
		if (INS_IsDirectCall(ins)) 
		{
			INS_InsertIfCall(ins,
				IPOINT_BEFORE,
				(AFUNPTR)IsSelfCall,
				IARG_INST_PTR,
				IARG_END);

			INS_InsertThenCall(ins,
					IPOINT_BEFORE,
					(AFUNPTR) LogDirectCall,
					// IARG_START,
					IARG_THREAD_ID, // thread ID of the executing thread
					IARG_INST_PTR, // address of instruction
					IARG_PTR, disasm, // disassembled string
					IARG_END);
					
		} 
		else if (INS_IsMemoryWrite(ins))
		{
			string mnemonic = INS_Mnemonic(ins);
			// don't want PUSH/POP instructions
			if (mnemonic.compare("PUSH") == 0 || mnemonic.compare("POP") == 0) 
			{
				return;
			}

			INS_InsertIfCall(ins, 
				IPOINT_BEFORE, 
				(AFUNPTR)IsInRange, 
				IARG_MEMORYWRITE_EA,
				IARG_END);
			// memory write instruction
			INS_InsertThenCall(ins,
				IPOINT_BEFORE,
				(AFUNPTR) LogMemoryWrite,
				// IARG_START,
				IARG_THREAD_ID, // thread ID of the executing thread
				IARG_INST_PTR, // address of instruction
				IARG_PTR, disasm, // disassembled string
				IARG_MEMORYWRITE_EA, // effective address being written
				IARG_MEMORYWRITE_SIZE, // num bytes writen
				IARG_END);
		
			
		}
	}
}

/*!
 * Print out analysis results.
 * This function is called when the application exits.
 * @param[in]   code            exit code of the application
 * @param[in]   v               value specified by the tool in the 
 *                              PIN_AddFiniFunction function call
 */
VOID Fini(INT32 code, VOID *v)
{
	fflush(outFile);
	fclose(outFile);
}

/*!
 * The main procedure of the tool.
 * This function is called when the application image is loaded but not yet started.
 * @param[in]   argc            total number of elements in the argv array
 * @param[in]   argv            array of command line arguments, 
 *                              including pin -t <toolname> -- ...
 */
int main(int argc, char *argv[])
{
    // Initialize PIN library. Print help message if -h(elp) is specified
    // in the command line or the command line is invalid 
	PIN_InitSymbols();
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }
    string fileName = KnobOutputFile.Value();

    outFile = fopen(fileName.c_str(), "wb+");
    // Register function to watch for image loads.
	IMG_AddInstrumentFunction(ImageLoad, 0);
	INS_AddInstrumentFunction(Instruction, 0);
    // Register function to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);
    // Start the program, never returns
    PIN_StartProgram();
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
