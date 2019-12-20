# stm32_flash_update
STM32 Flash update function.

Small implementation of data update function in flash memory on stm32 microcontrollers.
This function could be used for flash update in bootloaders, data storage basen on flash and e.t.c.

Example of simple usage could be found in folder "flash_update_example".
Example of firmware update usage could be found in "usb_switch" project in current github profile.

Description of function:

int flash_update(unsigned int dst_addr, unsigned int src_addr, int bytes_to_copy, bool reset);

dst_addr 		- Address in FLASH where data shal be placed.
src_addr 		- Address in FLASH/SRAM from data shal be copyed.
bytes_to_copy 	- Numbers of bytes to copy. Could be 1 byte also. 
reset 			- Reset after copying completed.

* INFO 
When function perform 1 byte write to FLASH, other 3 bytes of word (32-bits) will be flushed to zero.


