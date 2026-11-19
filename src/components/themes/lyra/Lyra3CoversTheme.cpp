#include "Lyra3CoversTheme.h"

#include <GfxRenderer.h>
#include <HalStorage.h>

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include "RecentBooksStore.h"
#include "components/UITheme.h"
#include "components/icons/cover.h"
#include "fontIds.h"

// Internal constants
namespace {
constexpr int hPaddingInSelection = 8;
constexpr int cornerRadius = 6;
}  // namespace

int Lyra3CoversTheme::homeCoverThumbHeight(const GfxRenderer& renderer) const {
  const int tileWidth = (renderer.getScreenWidth() - 2 * Lyra3CoversMetrics::values.contentSidePadding) / 3;
  // Thumbs cover a (0.6*h, h) target box; in landscape the tile is wider than
  // 0.6 aspect, so request a taller thumb and let the draw crop vertically.
  return std::max(Lyra3CoversMetrics::values.homeCoverHeight, (tileWidth - 2 * hPaddingInSelection) * 5 / 3 + 2);
}

int Lyra3CoversTheme::coverHeightForTile(const GfxRenderer& renderer, const int tileHeight) {
  // top pad, gap and pad under the cover, then one title line
  const int below = 2 * hPaddingInSelection + 5 + renderer.getLineHeight(SMALL_FONT_ID);
  return std::clamp(tileHeight - below, 1, Lyra3CoversMetrics::values.homeCoverHeight);
}

void Lyra3CoversTheme::drawRecentBookCover(GfxRenderer& renderer, Rect rect, const std::vector<RecentBook>& recentBooks,
                                           const int selectorIndex, bool& coverRendered, bool& coverBufferStored,
                                           bool& bufferRestored, std::function<bool()> storeCoverBuffer) const {
  const int tileWidth = (rect.width - 2 * Lyra3CoversMetrics::values.contentSidePadding) / 3;
  const int tileY = rect.y;
  const bool hasContinueReading = !recentBooks.empty();
  const int coverH = coverHeightForTile(renderer, rect.height);
  // thumbs are made 0.6 * height wide, so the cover box is exactly that
  const int coverW = std::min(tileWidth - 2 * hPaddingInSelection, static_cast<int>(coverH * 0.6));
  const int sideW = (tileWidth - coverW) / 2;

  // Draw book card regardless, fill with message based on `hasContinueReading`
  // Draw cover image as background if available (inside the box)
  // Only load from SD on first render, then use stored buffer
  if (hasContinueReading) {
    if (!coverRendered) {
      for (int i = 0;
           i < std::min(static_cast<int>(recentBooks.size()), Lyra3CoversMetrics::values.homeRecentBooksCount); i++) {
        std::string coverPath = recentBooks[i].coverBmpPath;
        bool hasCover = true;
        const int tileX = rect.x + Lyra3CoversMetrics::values.contentSidePadding + tileWidth * i;
        const int coverX = tileX + sideW;
        const int coverY = tileY + hPaddingInSelection;
        if (coverPath.empty()) {
          hasCover = false;
        } else {
          // a thumb made at this exact height draws 1:1, else scale the full one until it exists
          std::string coverBmpPath = UITheme::getCoverThumbPath(coverPath, coverH);
          bool exactThumb = true;
          if (!Storage.exists(coverBmpPath.c_str())) {
            coverBmpPath = UITheme::getCoverThumbPath(coverPath, homeCoverThumbHeight(renderer));
            exactThumb = false;
          }

          // First time: load cover from SD and render
          HalFile file;
          if (Storage.openFileForRead("HOME", coverBmpPath, file)) {
            Bitmap bitmap(file);
            if (bitmap.parseHeaders() == BmpReaderError::Ok) {
              if (exactThumb) {
                drawCoverThumbFill(renderer, bitmap, Rect{coverX, coverY, coverW, coverH});
              } else {
                renderer.drawBitmap(bitmap, coverX, coverY, coverW, coverH);
              }
            } else {
              hasCover = false;
            }
            file.close();
          }
        }
        // Draw either way
        renderer.drawRect(coverX, coverY, coverW, coverH, true);

        if (!hasCover) {
          // Render empty cover
          renderer.fillRect(coverX, coverY + (coverH / 3), coverW, 2 * coverH / 3, true);
          renderer.drawIcon(CoverIcon, coverX + 24, coverY + 24, 32);
        }
      }

      coverBufferStored = storeCoverBuffer();
      coverRendered = coverBufferStored;  // Only consider it rendered if we successfully stored the buffer
    }

    for (int i = 0; i < std::min(static_cast<int>(recentBooks.size()), Lyra3CoversMetrics::values.homeRecentBooksCount);
         i++) {
      bool bookSelected = (selectorIndex == i);

      int tileX = rect.x + Lyra3CoversMetrics::values.contentSidePadding + tileWidth * i;

      const int maxLineWidth = tileWidth - 2 * hPaddingInSelection;

      auto titleLines = renderer.wrappedText(SMALL_FONT_ID, recentBooks[i].title.c_str(), maxLineWidth, 1);

      const int titleLineHeight = renderer.getLineHeight(SMALL_FONT_ID);
      const int dynamicBlockHeight = static_cast<int>(titleLines.size()) * titleLineHeight;
      // Add a little padding below the text inside the selection box just like the top padding (5 + hPaddingSelection)
      const int dynamicTitleBoxHeight = dynamicBlockHeight + hPaddingInSelection + 5;

      if (bookSelected) {
        // Draw selection box
        renderer.fillRoundedRect(tileX, tileY, tileWidth, hPaddingInSelection, cornerRadius, true, true, false, false,
                                 Color::LightGray);
        renderer.fillRectDither(tileX, tileY + hPaddingInSelection, sideW, coverH, Color::LightGray);
        renderer.fillRectDither(tileX + tileWidth - sideW, tileY + hPaddingInSelection, sideW, coverH,
                                Color::LightGray);
        renderer.fillRoundedRect(tileX, tileY + coverH + hPaddingInSelection, tileWidth, dynamicTitleBoxHeight,
                                 cornerRadius, false, false, true, true, Color::LightGray);
      }

      int currentY = tileY + coverH + hPaddingInSelection + 5;
      for (const auto& line : titleLines) {
        renderer.drawText(SMALL_FONT_ID, tileX + hPaddingInSelection, currentY, line.c_str(), true);
        currentY += titleLineHeight;
      }
    }
  } else {
    drawEmptyRecents(renderer, rect);
  }
}
