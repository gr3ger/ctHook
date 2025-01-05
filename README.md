A simple DLL that hooks into `setlocale` to force `en_US.UTF-8` for Chrono Trigger, this resolves the issue with prices not being properly displayed ingame unless you change your system locale.

# Usage
Inject the DLL with your favored tool, when testing I was using SpecialK, but anything that can dynamically load DLLs should work just fine.
