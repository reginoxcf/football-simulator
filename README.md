# Football Simulator
Text-based random football league simulator (not yet accurate) based on attack and defense stats.

Steps to install (Windows)
----------------
1. Install the GNU GCC Compiler through [MSYS2](https://www.msys2.org/)
2. Check that GCC is installed by running:
   ```
   gcc --version
   g++ --version
   gdb --version
   ```
3. Navigate to the engine folder and then run:
   ```
   g++ -o generator generator.cpp&generator.exe
   g++ -o simulator simulator.cpp&simulator.exe
   ```
Known bugs
------------
- [ ] Standings table will break when stats overflow

Planned features
---------------
- [x] Make matchday-like fixtures instead of random ones
- [ ] Make engine more realistic
