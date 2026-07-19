# About This Repo

Fork of the original WoVR mod by [ProjectMimer](https://github.com/ProjectMimer/WoVR), which received last update in April 2024. It aim is to clean up the code, fix some of the bugs present in the original mod, and, in the future, maybe even add few extra features.

Full credit goes to ProjectMimer for their original work.



## Installation

### Requirements
- Windows 10/11
- SteamVR installed via Steam
- A SteamVR-compatible VR headset
- World of Warcraft 3.3.5a client

### Install Steps
1. Build the project (see Building below), or download the latest `d3d9.dll` release.
2. Copy `d3d9.dll` into your WoW 3.3.5a game folder, next to `Wow.exe`.
3. The `openvr_api.dll` is required at runtime. It ships with SteamVR and is loaded automatically from the SteamVR installation path.
4. Create a `vr` folder inside your WoW game directory (e.g. `World of Warcraft 3.3.5a/vr/`).
5. Copy `config/actions.json` and `config/actions_touch.json` into that `vr` folder.
6. Launch SteamVR, then launch WoW normally. The game should detect the VR headset and start in VR mode.

### Configuration
VR settings can be tuned by editing the `config.txt` file inside the `vr` folder. Key options include:
- Snap turn degrees (horizontal and vertical)
- Specific ground and flying mounts for the random mount button (Left Stick Click)

## Building from Source

### Requirements
- Visual Studio Build Tools with MSVC v145 toolset (VS 2026) or later
- Windows 10 SDK (10.0.26100 or later)

### Build Steps
1. Clone the repository:
   ```
   git clone https://github.com/belx-dev/WoVR
   ```
2. Download the OpenVR SDK headers and library and place them in the `openvr/` folder:
   - `openvr/headers/openvr.h`
   - `openvr/lib/win32/openvr_api.lib`
3. Restore NuGet packages (Detours 4.0.1) or download manually into `packages/Detours.4.0.1/`.
4. Open `dxProxyWoVR.sln` in Visual Studio and build the Release|Win32 configuration, or build from the command line:
   ```
   MSBuild dxProxyWoVR.sln /p:Configuration=Release /p:Platform=x86
   ```
5. The output `d3d9.dll` will be placed in the `Release/` folder.

## Original Readme

WoVR aims to add VR support to 3.3.5a the last patch of the second expansion of the highly successful MMO initially launched in 2004.
This mod is a experimental release intended to be played seated with VR motion controllers.
Currently we do not have plans for active continued development, if there is enough support and interested from the community we could look into first person mount visibility and player character IK.

This software and code is provided as is, use at your own risk; we are not liable for damages caused.
For install instructions and support please visit our section on the [flat2vr.com](https://flat2vr.com) discord.

WoVR has been in on and off development for over ten years, it originally started development as a mod for the Oculus DK1 back in 2013.
In January 2024 after a 4 year long hiatus we decided to restart development from scratch with everything we learned from creating XIVR.
This mod not only converts the game to be playable with motion controllers but also aims to add quality of life improvements from FF14.

Supports unmodified, 4GB patched and lua unlocked executables.

• Features •

→ Frame Synchronized 3D, one in engine frame equals one 3D VR frame

→ 6 DOF head tracking

→ Playable in both first and third person

→ Floating UI, inside the game world with full occlusion, supporting all addons

→ Optional made for VR UI with multiple floating windows and UI elements attached to your hands and face (Available on the Flat2VR discord)

→ Head-tracked HRTF positional audio

→ Ray traced motion controlled targeting and interacting, point your controller at anything to interact with it be it a NPC, enemy or mining node

→ Ray traced motion controlled AOE attacks, attacks like the mages blizzard or hunters traps can be placed on the ground via motion controls

→ Motion controlled UI, the UI can be interacted with via pointing your controllers at it

→ Motion controlled movement (Onward locomotion) the forward direction your character moves is offset by where you are pointing your left hand

→ Motion controlled swimming and flying, your character will swim/fly up and down to exactly where your left hand is pointing

→ Analogue movement with 2 movement speeds, based on the games default speed and RP walk

→ Vertical and horizontal snap turning, the amount of degrees the camera moves can be user adjusted in the /vr/config.txt

→ Implemented FF14s "Legacy Movement" mode, your character will run in the direction your stick is pointing at full speed, even towards you without backpedaling

→ Implemented FF14s "Auto Face Target" option, using a action automatically turns you towards your target and executes it, this even works while running away from your target without
interrupting your movement

→ Internal high res rendering, the game will run at normal desktop resolutions while out putting to the headset at two times native res and in the correct aspect ratio

→ Implemented support for resolutions in the WTF file higher then the max resolution of your monitor (NOTE your mouse on the UI is limited to what's visible on your desktop)

→ Floating Windows 10 OSK.exe keyboard (requires the game to be launched with admin privileges)

→ VR optimized near and far clip, this allows you to lean in closer then ever before without objects disappearing

→ Many small tweaks to the engine for better VR support 


• Known Issues • 

Head-tracked leaning is not accurate on elevators, ships and zeppelins

Loading screens might cause the headset to flicker

Certain UI elements might be displayed with a black background

The made for VR UI will appear very low res on 1080p monitors

All actions will turn you towards your target even those where it is not desirable like blink

Some times map chunks that would not be visible on the desktop will be culled

You can not turn the camera using the right stick while using a flight path


• Credits • 

Mod Development: Streetrat & Marulu

VR UI: Marulu

Help with finding memory addresses: Emenzed

Testing: Falandorn


• Controls • 
EG = When either grip is held

LG = When left  grip is held

RG = When right grip is held


Left hand angle

→ Controls direction of movement, flying and swimming

Left Analogue Stick 

→ Character Movement

Left Trigger

→ Next Action Set

→LG→ Previous Action Set

Left Stick Click

→ Random Mount (a specific flying and ground mount can be set in config.txt)

→EG→ 1 Key

X Button

→ Esc key

→EG→ 2 Key　

Y Button

→ Toggles Map

→EG→ 3 Key


Right hand angle

→ Controls ray into world, used for targeting aiming and UI interaction

Right Analogue Stick 

→ Camera Controls (Snap turning)

→LG→ Camera Zoom

Right Trigger

→ Left click

→RG→ Right Click

Right Stick Click

→ Toggle between first and third person & camera recenter

→EG→ 0 Key

B Button

→ Selects next target

→EG→ 9 Key　

A Button

→ Jump

→EG→ 8 Key

