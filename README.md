# WoVR

VR support for World of Warcraft 3.3.5a (WotLK). Fork of [ProjectMimer/WoVR](https://github.com/ProjectMimer/WoVR) with bug fixes, performance improvements, and new features.

## Features

- 6DOF head tracking via SteamVR
- First and third person play
- Floating UI panel with full addon support
- HRTF positional audio
- Motion controller targeting and AOE placement
- Smooth/snap turning (configurable)
- Onward-style locomotion
- VR action bars with drag-and-drop spell placement
- Configurable button remapping
- SteamVR keyboard integration
- Camera rotation smoothing

## Requirements

- Windows 10/11
- SteamVR (installed via Steam)
- SteamVR-compatible VR headset (Quest, Vive, Index, etc.)
- Quest users: Meta Quest Link must be active before launching
- WoW 3.3.5a client (works with standard, 4GB patched, or lua unlocked executables)

## Installation

1. Close World of Warcraft if it is running.
2. Copy `d3d9.dll` and `openvr_api.dll` into your WoW 3.3.5a game folder (next to `Wow.exe`).
3. Copy the `vr` folder into your WoW 3.3.5a game folder.

The final structure should look like:

```
YourWoWFolder/
  Wow.exe
  d3d9.dll
  openvr_api.dll
  vr/
    config.txt
    actions.json
    actions_touch.json
    images/
      cursors.png
      keyboard_off.png
      keyboard_on.png
      occlusion_off.png
      occlusion_on.png
      swapgroup_off.png
      swapgroup_on.png
```

4. Start SteamVR.
5. Launch Wow.exe normally. The game starts in VR mode automatically.

## VRCore Addon

The `Interface/AddOns/VRCore` addon provides VR-specific UI elements. Copy the `Interface` folder into your WoW directory if it is not already there. The addon includes:

- Touch indicator overlays
- Draggable UI elements (chat, minimap, action bars)
- VR action bar with drag-and-drop spell placement
- UI element hide/show toggles

### VR Action Bars

1. Click the Divine Spirit icon in the toggle bar to open the VR action bar.
2. Drag spells from your spellbook onto the VR bar slots. Each drop also places the spell on the corresponding native action bar slot.
3. Click the toggle again to hide the bar.
4. Press VR controller buttons to cast spells via the native action bar.

Button mapping (configurable in `vr/config.txt`):

| Button | Action Bar Slot | Key |
|--------|----------------|-----|
| B | Slot 1 | `1` |
| X | Slot 2 | `2` |
| Y | Slot 3 | `3` |
| A | Slot 4 | `4` |
| B+ | Slot 5 | `5` |
| A+ | Slot 6 | `6` |
| X+ | Slot 7 | `7` |
| Y+ | Slot 8 | `8` |
| L | Slot 9 | `9` |
| R | Slot 0 | `0` |

(B+ means B while holding the grip bumper, etc.)

## Controls

| Input | Action |
|-------|--------|
| Left stick | Movement (atan2 facing) |
| Right stick | Camera rotation |
| Left trigger | Zoom/scroll |
| Right trigger (L) | Left click |
| Right trigger (R) | Right click |
| A | Jump |
| B | Next target |
| X | Escape |
| Y | Toggle map |
| Left stick click | Random mount / Target nearest |
| Right stick click | Toggle first/third person |
| Bumper + button | Secondary action (see action bar mapping above) |

## Configuration

Edit `vr/config.txt` to change settings. Changes take effect on next launch.

### Rendering
| Option | Default | Description |
|--------|---------|-------------|
| `uiOffsetScale` | `1.2` | Size of the floating UI panel |
| `uiOffsetZ` | `-160` | Distance of UI (more negative = further) |
| `uiOffsetY` | `0` | Vertical position of UI |
| `uiMultiplier` | `1` | UI render resolution |
| `gameMultiplier` | `1` | Game world render resolution |
| `rotationSmoothing` | `0` | Camera rotation smoothing (0 = off, 1 = max) |

### Turning
| Option | Default | Description |
|--------|---------|-------------|
| `snapRotateX` | `0` | Horizontal snap turn (0 = smooth, 1 = snap) |
| `snapRotateY` | `0` | Vertical snap turn (0 = smooth, 1 = snap) |
| `snapRotateAmountX` | `30` | Snap turn degrees horizontal |
| `snapRotateAmountY` | `30` | Snap turn degrees vertical |
| `smoothTurnSpeed` | `25` | Smooth turn speed (higher = slower) |

### Movement
| Option | Default | Description |
|--------|---------|-------------|
| `strafeMode` | `1` | Left stick walk direction (1 = always forward) |
| `hmdOnward` | `0` | Onward-style locomotion bitmask |

### Other
| Option | Default | Description |
|--------|---------|-------------|
| `ipdOffset` | `0` | Manual IPD offset in mm |
| `flyingMountID` | `0` | Flying mount display ID |
| `groundMountID` | `0` | Ground mount display ID |
| `disableControllers` | `0` | Disable VR controllers |
| `showBodyFPS` | `0` | Show FPS debug display |
| `OSK` | `1` | On-screen keyboard (requires admin) |

### Button Remapping
Buttons can be remapped by changing the action names in `config.txt`:

```
rightA: vr1
rightB: vr2
leftX: vr3
leftY: vr4
```

Available actions: `jump`, `mount`, `escape`, `tab`, `enter`, `backspace`, `space`, `vr1`-`vr12`, `none`.

Holding a bumper while pressing a button gives the secondary action (`vr7`-`vr12`).

## Building from Source

### Requirements
- Visual Studio Build Tools with MSVC v145 toolset (VS 2026) or later
- Windows 10 SDK (10.0.2610 or later)

### Steps
1. Clone the repository:
   ```
   git clone https://github.com/DinoCROTH/WoVR.git
   ```
2. The OpenVR SDK headers and library are included in the `openvr/` folder.
3. NuGet packages (Detours 4.0.1) restore automatically on build.
4. Build from the command line:
   ```
   MSBuild dxProxyWoVR.sln /p:Configuration=Release /p:Platform=x86
   ```
   Or open `dxProxyWoVR.sln` in Visual Studio and build Release|Win32.
5. The output `d3d9.dll` is placed in the `Release/` folder.

## Credits

- Original WoVR: [ProjectMimer](https://github.com/ProjectMimer/WoVR) (Streetrat & Marulu)
- VR UI: Marulu
- Memory addresses: Emenzed
- Testing: Falandorn
- Fork: [DinoCROTH](https://github.com/DinoCROTH/WoVR)

## License

Use at your own risk. Not liable for damages caused.
