/****************************************************************************** 
* Include Files * 
******************************************************************************/ 
// Standard header files
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/mman.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <unistd.h> 
#include <string.h> 
#include <math.h>
// Driver header file
#include <prussdrv.h>
#include <pruss_intc_mapping.h>	 
#include <math.h>

/****************************************************************************** 
* Local Macro Declarations * 
******************************************************************************/
#define PRU_NUM 	 0     

int main(void){

	unsigned int ret;
	//unsigned int i,value;

	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
	printf("\nINFO: Starting %s example.\r\n", "looplicht");
	// Initialize the PRU 
	prussdrv_init();
	// Open PRU Interrupt 
	ret = prussdrv_open(PRU_EVTOUT_0);
	if (ret)
	{
		printf("prussdrv_open open failed\n");
		return (ret);
	}
	

	// Get the interrupt initialized
	prussdrv_pruintc_init(&pruss_intc_initdata);

	//Execute example on PRU
	printf("\tINFO: Executing example.\r\n");
	prussdrv_exec_program(PRU_NUM, "./loper.bin");
	
        // for (i = 0; i < 100000; i++) {
        //         usleep(100);
	//	value=(sin(i*0.01)+1)*120+5;
	//	prussdrv_pru_write_memory(PRUSS0_PRU0_DATARAM, 0x00000040, &value, sizeof(unsigned int));
	//	printf("(%d)\n-> ",value);
        //}

        // Wait until PRU0 has finished execution
        printf("\tINFO: Waiting for HALT command.\r\n");
	
	prussdrv_pru_wait_event(PRU_EVTOUT_0);
	printf("\tINFO: PRU completed transfer.\r\n");
	prussdrv_pru_clear_event(PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);

	// Disable PRU and close memory mapping
	prussdrv_pru_disable(PRU_NUM);
	prussdrv_exit();
	return(0);
}




