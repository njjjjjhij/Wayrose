# cClydestales GUI 💜

A Geode C++ starter project inspired by the generated purple/neon GUI mockups.

## Target
- Geometry Dash 2.2081 (Windows + Android metadata)
- Geode 5.11.2
- Mod ID: `cClydestales.gui`

## What is in this project
- `resources/icon.png` — generated mascot/icon artwork.
- `resources/click-icon.png` — click-to-open button art (currently a copy of the icon artwork).
- `src/main.cpp` — main-menu icon, custom click GUI, 20 toggle rows, and Hack CBF code prompt.
- `mod.json` — metadata and saved settings for all 20 features.
- `CMakeLists.txt` — Geode SDK project setup.

## Hack CBF access code
When you tap **Hack CBF** while it is off, the GUI asks for a code. The code is `rezo1234`.
This is only a local UI gate, not a secure authentication system.

## Important: what works vs. what is unfinished
The icon, menu layout, settings toggles, and code prompt are implemented in source. The 20 settings currently store their on/off values, but most are UI placeholders. **CBF and Hack CBF do not yet change the game's input/collision logic.** In particular, the future-position prediction and delayed-valid-jump behavior requested for Hack CBF are not implemented. Do not treat this as a working CBF replacement yet.

This source has not been compiled or tested against an installed Geode SDK in this environment. API adjustments may be required by your exact SDK/toolchain.

## Build
1. Install the Geode SDK and CLI for Geode 5.11.2.
2. Set the `GEODE_SDK` environment variable to the SDK directory.
3. Open this folder in VS Code with the Geode extension, then configure/build with CMake or the Geode CLI.
4. Build separately for each target. A Windows binary cannot be installed on Android; use the Android toolchain for an Android package.

Official docs:
- https://docs.geode-sdk.org/mods/configuring/
- https://docs.geode-sdk.org/mods/resources/
- https://docs.geode-sdk.org/tutorials/popup/
