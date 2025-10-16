// Pinscape Pico - Pico2 W Board Type for official Pico2 W (RP2350+CYW43)
// Copyright 2024, 2025 Michael J Roberts / BSD-3-Clause license / NO WARRANTY
//
// This implements tyhe PicoBoardType interface for the official Pico2 W
// (RP2350+CYW43) from Rasbperry Pi.  This file is included in the build when
// PICO_BOARD is set to "pico2_w" in the build configuration.


#include <pico/cyw43_arch.h>
#include "PicoBoardType.h"
#include "Pinscape.h"


// Additional target-board-specific intialization
void PicoBoardType::Init()
{
    // set up the CYW43 to access Pico2 W LED
    cyw43_arch_init();
}

// LED initialization
void PicoBoardType::LED::Init()
{
    // no additional initialization required
}

// LED write
void PicoBoardType::LED::Write(bool state)
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state);
}

uint32_t PicoBoardType::LED::GetResetUSBBootMask()
{
    return 0;
}

