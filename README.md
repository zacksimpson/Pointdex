# Pointdex

A reading-powered Pokémon companion for the Xteink X3 e-reader, built on [CrossPoint Reader](https://github.com/crosspoint-reader/crosspoint-reader) 2.0.0. Turn real pages in your books and your lead Pokémon trains, wild Pokémon turn up, trainers challenge you, and you can work toward the gyms and the Pokédex.

This is an unofficial, noncommercial fan project. It is not affiliated with or endorsed by Nintendo, Creatures Inc., GAME FREAK Inc., The Pokémon Company, Xteink, or the CrossPoint Reader project. See [NOTICE.md](NOTICE.md) for credits and rights.

## Branches

- `main`: the full game, with turn-based battles, wild encounters you fight and catch, road trainers, the eight Gym Leaders, the Elite Four, the Champion, a Trainer Card and a Hall of Fame.
- `no-battles`: the simpler original companion, with reading experience, levels, evolution, catching and the Pokédex, but no battles.

## What is here

The Pokémon game sits on top of stock CrossPoint 2.0.0 and keeps its interface and themes. Home shows a Pokémon strip with your lead Pokémon on the Classic, Lyra, Lyra three covers and RoundedRaff themes. If there is no room for the strip, the Pokémon row on Home gets a `!` when something is waiting.

Both branches also have a Time Left status bar item (chapter or book, Settings > Customise Status Bar) and Home layout fixes so the extra Pokémon row fits above the button hints.

Only the X3 is a target. It has not been tried on other devices, and the Nearby Sync, Applications, Game Boy and Bluetooth features of the projects this builds on are not included.

## Art

The game's pictures are not in this repository. Species, item, trainer, badge and move-effect art come from the `xteink-pokemon-sd-card-assets.zip` attached to the [xteink-pokemon-game releases](https://github.com/thebitsworld/xteink-pokemon-game/releases). Unpack it so the files end up under `pokemon/` on the root of the SD card. Without it the game still runs, but without the pictures.

## Building

Install [PlatformIO](https://platformio.org) with the pioarduino platform pinned in `platformio.ini`, then:

```sh
pio run -e pokemon-x3
```

The image is `.pio/build/pokemon-x3/firmware.bin`. Flashing custom firmware is at your own risk. Back up your SD card first, and keep your Pokémon save files (`/.crosspoint/pokemon*.bin`), because the first run of `main` upgrades the save format and older builds cannot read it back. The notes in [CrossPoint's flashing docs](docs/crosspoint-readme.md) apply to this firmware as well.

The original CrossPoint Reader readme is kept at [docs/crosspoint-readme.md](docs/crosspoint-readme.md).
