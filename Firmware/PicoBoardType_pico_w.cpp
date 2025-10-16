// Pinscape Pico - Pico W Board Type for official Pico W (RP2040+CYW43)
// Copyright 2024, 2025 Michael J Roberts / BSD-3-Clause license / NO WARRANTY
//
// This implements tyhe PicoBoardType interface for the Pico W RP2040 -
// the official base version of the board sold by Raspberry Pi.  This file
// is included in the build ONLY when PICO_BOARD is set to "pico_w" in the
// build configuration.


#include <pico/cyw43_arch.h>
#include "PicoBoardType.h"
#include "Pinscape.h"
#include "Logger.h"


// Additional target-board-specific intialization
void PicoBoardType::Init()
{
    // set up the CYW43 to access Pico W LED
    if (cyw43_arch_init()) {

        Log(LOG_ERROR, "Wi-Fi init failed\n");
    }
    else {
        Log(LOG_INFO, "Wi-Fi init success\n");
    }
}

// LED initialization
void PicoBoardType::LED::Init()
{
    // no additional initialization required
}

// LED write
void PicoBoardType::LED::Write(bool state)
{
    static bool     state_mem = false;
    static uint64_t time_mem = 0;

//    Log(LOG_INFO, "PicoBoardType::LED::Write(%d)\n", state);
    uint64_t t = time_us_64();
    if ((t - time_mem) > 5000000) {
        if (state_mem != state) {

            Log(LOG_INFO, "PicoBoardType::LED::Write(%d)\n", state);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state);
            state_mem = state;
        }
        time_mem = t;
    }
}

uint32_t PicoBoardType::LED::GetResetUSBBootMask()
{
    return 0;
}

