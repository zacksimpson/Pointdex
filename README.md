# Pointdex

A CrossPoint-based Pokémon reading companion game for the Xteink X3. Turn real pages in your books and your lead Pokémon trains, wild Pokémon turn up, trainers challenge you, and you can work toward the gyms and the Pokédex.

## Credits
Pointdex exists because I've just chosen to mash a few existing wonderful open-source projects together. Very little is original to this repo. 
- [CrossPoint Reader 2.0.0](https://github.com/crosspoint-reader/crosspoint-reader/releases/tag/2.0.0) is the firmware and interface everything runs on.
- [padge01’s xteink-pokemon-game](https://github.com/padge01/xteink-pokemon-game) is the original reading-powered Pokémon companion, and the idea behind this project.
- [thebitsworld’s xteink-pokemon-game](https://github.com/thebitsworld/xteink-pokemon-game/tree/feat/reader-speed-1) iterated on that with the battles, trainers, gyms, items and moves.
However, both existing Pokémon projects are based on CrossInk, a fork of CrossPoint. This is where Pointdex differs (because I just personally prefer the UI from CrossPoint). 

## Branches

- `main`: the full game, with turn-based battles, wild encounters you fight and catch, road trainers, the eight Gym Leaders, the Elite Four, the Champion, a Trainer Card and a Hall of Fame.
- `no-battles`: the simpler original companion, with reading experience, levels, evolution, catching and the Pokédex, but no battles.

## What is here

The Pokémon game sits on top of stock CrossPoint 2.0.0 and keeps its interface and themes. Home shows a Pokémon strip with your lead Pokémon on the Classic, Lyra, Lyra Extended and RoundedRaff themes. If there is no room for the strip, the Pokémon row on Home gets a `!` when something is waiting.

Both branches also have a Time Left status bar item (chapter or book, Settings > Customize Status Bar) and Home layout fixes so the extra Pokémon row fits above the button hints.

> [!WARNING]
> **Only the Xteink X3 is a target.** It has not been tried on other devices like the X4 Classic or other ESP32 based devices.

## Art

The game's pictures are not in this repository. Species, item, trainer, badge and move-effect art come from the `xteink-pokemon-sd-card-assets.zip` attached to the [xteink-pokemon-game releases](https://github.com/thebitsworld/xteink-pokemon-game/releases). Unpack it so the files end up under `pokemon/` on the root of the SD card. Without it the game still runs, but without the pictures.

## Building

Install [PlatformIO](https://platformio.org) with the pioarduino platform pinned in `platformio.ini`, then:

```sh
pio run -e pokemon-x3
```

The image is `.pio/build/pokemon-x3/firmware.bin`. Flashing custom firmware is at your own risk. Back up your SD card first, and keep your Pokémon save files (`/.crosspoint/pokemon*.bin`), because the first run of `main` upgrades the save format and older builds cannot read it back. The notes in [CrossPoint's flashing docs](docs/crosspoint-readme.md) apply to this firmware as well.

The original CrossPoint Reader readme is kept at [docs/crosspoint-readme.md](docs/crosspoint-readme.md).
