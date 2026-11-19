#pragma once

#include <algorithm>
#include <cstdint>

// rolling average of seconds per forward page turn, for the time left label.
// uses the uptime clock, so it works without a trusted wall clock.
class ReaderPace {
 public:
  void noteTurn(const bool forward, const bool succeeded) { pendingForward = forward && succeeded; }

  void onRenderComplete(const uint32_t nowMs) {
    if (pendingForward && hasAnchor) {
      const uint32_t elapsedMs = nowMs - anchorMs;
      if (elapsedMs >= MIN_PAGE_MS && elapsedMs <= MAX_PAGE_MS) {
        samples = std::min<uint8_t>(samples + 1, WINDOW);
        avgMs += (static_cast<float>(elapsedMs) - avgMs) / samples;
      }
    }
    anchorMs = nowMs;
    hasAnchor = true;
    pendingForward = false;
  }

  bool secondsPerPage(float& seconds) const {
    if (samples < MIN_SAMPLES) return false;
    seconds = avgMs / 1000.0f;
    return true;
  }

 private:
  static constexpr uint32_t MIN_PAGE_MS = 2000;
  static constexpr uint32_t MAX_PAGE_MS = 180000;
  static constexpr uint8_t WINDOW = 20;
  static constexpr uint8_t MIN_SAMPLES = 5;

  float avgMs = 0.0f;
  uint32_t anchorMs = 0;
  uint8_t samples = 0;
  bool hasAnchor = false;
  bool pendingForward = false;
};
