/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2022 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef AINSTEIN_USD1_SRC_AINSTEIN_USD1_H_  // NOLINT
#define AINSTEIN_USD1_SRC_AINSTEIN_USD1_H_

#if defined(ARDUINO)
#include "Arduino.h"
#else
#include "core/core.h"
#endif

namespace bfs {

class AinsteinUsD1 {
 public:
  AinsteinUsD1() {}
  explicit AinsteinUsD1(HardwareSerial *bus) : bus_(bus) {}
  void Config(HardwareSerial *bus) {bus_ = bus;}
  bool Begin();
  bool Read();
  inline float alt_m() const {return alt_m_;}
  inline uint8_t snr() const {return snr_nd_;}

 private:
  /* Communication */
  static constexpr int16_t COMM_TIMEOUT_MS_ = 5000;
  static constexpr int32_t BAUD_ = 115200;
  HardwareSerial *bus_;
  elapsedMillis t_ms_;
  /* Data */
  uint8_t snr_nd_;
  int16_t alt_cm_;
  float alt_m_;
  static constexpr float cm2m = 1.0f / 100.0f;
  /* Parser */
  static constexpr uint8_t HEADER_ = 0xFE;
  static constexpr uint8_t VER_ = 0x02;
  static constexpr uint8_t HEADER_POS_ = 0;
  static constexpr uint8_t VER_POS_ = 1;
  static constexpr uint8_t ALT_LSB_POS_ = 2;
  static constexpr uint8_t ALT_MSB_POS_ = 3;
  static constexpr uint8_t SNR_POS_ = 4;
  static constexpr uint8_t CHK_POS_ = 5;
  uint8_t c_;
  uint8_t state_ = 0;
  uint8_t alt_lsb_, alt_msb_, snr_, chk_;
  uint8_t buf_[6];
};

}  // namespace bfs

#endif  // AINSTEIN_USD1_SRC_AINSTEIN_USD1_H_ NOLINT
