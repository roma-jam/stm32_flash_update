/*
 * main.c
 *
 *  Created on: 4 θώνÿ 2017 γ.
 *      Author: RomaJam
 */

#include "board/ST/stm32_pin.h"
#include "board.h"
#include "system.h"
#include "config.h"

#define RAM

#ifdef RAM
#include "flash_update_STM32L052K8.h"
#else
#include "f_upd_test.h"
#endif

#if (DFU_DEBUG)
#include "dbg.h"
#endif
#define FLASH_TARGET

int main(void)
{
    /* init small system */
    SYSTEM system;
    /* init board */
    board_init();

#if (DFU_DEBUG)
    /* inti debug */
    board_dbg_init();

    printf("STM32 flash update example, v %d.%d \n", VERSION >> 8, VERSION & 0xff);
    printf("CPU %d MHz\n", power_get_core_clock() / 1000000);
#endif // DFU_DEBUG

    /* wait 1 sec in case of exclude unaccessable programing device during */
    /* stuck when flash update function called */
    delay_ms(999);

    /* no reboot needed */
    system.reboot = false;

    /* enable LED */
    gpio_enable(B0, GPIO_MODE_OUT);
    pin_set(B0);

#ifdef RAM
    /* create ram buffer with function code on stack */
    uint8_t ram[FLASH_UPD_SIZE] = { 0 };
    memcpy(ram, __FLASH_UPD, FLASH_UPD_SIZE);
#endif

#if (DFU_DEBUG)
#if defined(RAM)
    printf("Update firmware from RAM...\n");
#else
    printf("Update firmware...\n");
#endif
#endif
    /* disable IRQ */
    __disable_irq();

#ifdef RAM
    /* ram function call from flash_update_XXX.c file */
    flash_upd_sram(ram, 0x08007000, 0x08000000, 128, false);
#else
    flash_update(0x08007000, 0x08000000, 2048);
#endif

    /* enable IRQ */
    __enable_irq();

#if (DFU_DEBUG)
    printf("OK\n");
#endif

    while(!system.reboot)
    {

    }
    /* reset if needed */
    for(;;);
}
