#pragma once
#include <fvm/Pass.h>
#include <fvm/Utils/Cmdline.h>
#include "ISA/FISCISA.h"
#include "FISCPipelineConfigurator.cpp"
#include "../Memory/FISCMemoryModule.cpp"
#include <stdio.h>

class PipelineModule : public RunPass {

private:
	MemoryModule * memory; /* The main memory handle */

public:
	PipelineModule() : RunPass(2) {}

	enum PassRetcode init() {
		enum PassRetcode success = PASS_RET_OK;
		printf("- Initializing Pipeline\n");

		/* Fetch Memory Module Pass */
		if (!(memory = GET_PASS(MemoryModule))) {
			/* TODO: We were unable to find a MemoryModule pass!
			We cannot continue the execution of this pass */
			printf("\n>> ERROR: Could not fetch the Memory Module Pass!\n\n");
			success = PASS_RET_ERR;
		}

		return success;
	}

	enum PassRetcode finit() {
		printf("- Terminating Pipeline\n");
		return PASS_RET_OK;
	}

	enum PassRetcode run() {
		printf("\n>>>> Pipeline is running! <<<<");
		printf("\n- Memory contents:\n");
		
		int8_t byte = 0;
		uint32_t address = 0;
		
		while (byte != -1) {
			byte = (int8_t)memory->read(address, FISC_SZ_8, false);
			printf("\t- Address: 0x%x Data: 0x%x (%c)\n", address, byte, (char)byte);
			address++;
		}

		/* TODO:
			1-Fetch
			2-Decode
			3-Execute
			4-Memory Access
			5-Writeback
			
			6-Repeat
		*/
		
		return PASS_RET_OK;
	}

	enum PassRetcode watchdog() {
		return PASS_RET_OK;
	}
};
