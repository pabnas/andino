// BSD 3-Clause License
//
// Copyright (c) 2026, Ekumen Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include "pwm_out_rp2040.h"

#if defined(ARDUINO_ARCH_RP2040)

#include <Arduino.h>

namespace andino {

namespace {

// Ensure we configure the global PWM settings (frequency and resolution) only
// once, even if multiple PwmOutRp2040 instances are created.
bool g_pwm_configured = false;

}  // namespace

void PwmOutRp2040::begin() const {
  pinMode(gpio_pin_, OUTPUT);

  if (!g_pwm_configured) {
    // Configure 20 kHz PWM globally for the Arduino-pico core.
    analogWriteFreq(20000);
    // Use 8-bit resolution so the firmware's 0-255 range maps directly.
    analogWriteResolution(8);
    g_pwm_configured = true;
  }

  write(0);
}

void PwmOutRp2040::write(int value) const {
  if (value < 0) {
    value = 0;
  } else if (value > 255) {
    value = 255;
  }

  analogWrite(gpio_pin_, value);
}

}  // namespace andino

#endif  // ARDUINO_ARCH_RP2040
