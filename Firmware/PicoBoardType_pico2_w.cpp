// Pinscape Pico - Pico2 W Board Type for official Pico2 W (RP2350+CYW43)
// Copyright 2024, 2025 Michael J Roberts / BSD-3-Clause license / NO WARRANTY
//
// This implements tyhe PicoBoardType interface for the official Pico2 W
// (RP2350+CYW43) from Rasbperry Pi.  This file is included in the build when
// PICO_BOARD is set to "pico2_w" in the build configuration.


#include <pico/cyw43_arch.h>
#include "PicoBoardType.h"
#include "Pinscape.h"
#include "Logger.h"


// Additional target-board-specific intialization
void PicoBoardType::Init()
{
    // no additional initialization required
}

// LED initialization
void PicoBoardType::LED::Init()
{
    // set up the CYW43 to access Pico2 W LED
    if (cyw43_arch_init()) {

        Log(LOG_ERROR, "CYW43 init failed\n");
    }
    else {

        // First call to `cyw43_arch_gpio_put()` is very long
        // Call it once before watchdog running
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
    }
}

// LED write
void PicoBoardType::LED::Write(bool state)
{
    static bool stateMem = false;

    if (stateMem != state) {

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state);
        stateMem = state;
    }
}

uint32_t PicoBoardType::LED::GetResetUSBBootMask()
{
    return 0;
}

