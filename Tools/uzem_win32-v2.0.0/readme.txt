Uzem Uzebox emulator v2.0.0
-----------------------------------
Uzem is a multi-platform emulator for the Uzebox. It is currently a command line tool.

Usage:
uzem [OPTIONS] GAMEFILE<*.HEX | *.UZE>

Command line options:

--help -h           Show this help screen
--nosound  -n       Disable sound playback
--fullscreen -f     Enable full screen
--swrenderer -w     Use SDL software renderer (probably faster on older computers
--novsync -v        Disables VSYNC (does not apply to software renderer
--mouse -m          Start with emulated mouse enabled
--2p -2             Start with snes 2p mode enabled
--sd -s <path>      Specify a content path for the SD card emulation. If not specified, it mounts the directory in which the .HEX/.UZE resides.
--eeprom -e <file>  Use following filename for EEPRROM data (default is eeprom.bin)
--boot -b           Bootloader mode.  Changes start address to 0xF000
--gdbserver -d      Debug mode. Start the built-in gdb support
--port -t <port>    Port used by gdb (default 1284)
--capture -c        Captures gamepads data to file (GAMEFILE.cap)
--loadcap -l        Load and replays controllers data from capture file
--synchelp -z       Displays and logs information to help troubleshooting HSYNC timing issues
--record -r         Record a movie in mp4/720p(60fps) format. (ffmpeg executable must be in the same directory as uzem or in the system path)
	

Keyboard control:
F1   Display help
F5   Debugger resume execution (if compiled with DISAM switch)
F9   Debugger halt execution (if compiled with DISAM switch)
F10  Debugger single step (if compiled with DISAM switch)
0    AVCORE Baseboard power switch
1/2  Adjust left edge lock
3/4  Adjust top edge lock
5    Toggle NES/SNES 1p/SNES 2p/SNES mouse mode (default is SNES pad)
6    Mouse sensitivity scale factor
7    Re-map joystick
Esc  Quit emulator

            Up Down Left Right A B X Y Start Sel LShldr RShldr
NES:        ----arrow keys---- a s     Enter Tab              
SNES 1p:    ----arrow keys---- a s x z Enter Tab LShift RShift
  2p P1:     w   s    a    d   f g r t   z    x     q      e  
  2p P2:     i   k    j    l   ; ' p [   n    m     u      o

For complete usage and build info see the wiki page:
http://uzebox.org/wiki/index.php?title=Emulator

----------------------------------------

Changes for V2.0.0
-Code ported to SDL2
-Improved refresh rate from 30hz to 60hz
-Rewrite of the CPU decoder core for massive speed improvements
-Rewrite of the line renderer for speed improvements
-Added support for movie capture (requires ffmpeg)
-Improvements to the SD emulation
-Many other improvements and bug fixes


Changes for V1.3.2:
-Fixed issue that prevented clean exit at command line under windows
-Added feature to capture/playback controller buttons (snes mouse not yet supported)
-Implemented the watchdog timer to support the true random generator

Changes for V1.3:
-Uzem now updates the screen at 60hz (field rate) instead of 30hz (frame rate).
-Added frame rate stabilisation code
-Code cleanup and various small speed optimization
-Removed thread update code
-Bug fix: Null pointers when mounting sd card directpry on Linux

Changes for V1.20:
-Bug fix: added stting.h import in SDEmulator.h to fix compile issue under Linux
-Added preliminary support for Uzebox keyboard. For details see: http://uzebox.org/wiki/index.php?title=Uzebox_Keyboard

Changes for V1.19.1:
-Bug fix: Initial seek was ignored
-Bug fix: Can't read past 64k. FAT was not filled with cluster chain.
-Changed cluster size to a more standard 32k
