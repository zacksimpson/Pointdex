#pragma once

#include <GfxRenderer.h>

#include "MappedInputManager.h"
#include "components/UITheme.h"

// stand-in for the crossink touch header helper. the x3 has no touch, so the
// header is just the theme header and a back tap never fires.
namespace TouchHeaderBackButton {
inline int height(const ThemeMetrics& metrics, const MappedInputManager&) { return metrics.headerHeight; }
inline Rect headerRect(const GfxRenderer& renderer, const MappedInputManager&) {
  const auto& metrics = UITheme::getInstance().getMetrics();
  return Rect{0, metrics.topPadding, renderer.getScreenWidth(), metrics.headerHeight};
}
inline bool wasTapped(const MappedInputManager&, const GfxRenderer&) { return false; }
}  // namespace TouchHeaderBackButton

// no touch on this build, so a tap never lands
inline bool pokemonNoTap(int, int, int, int) { return false; }
