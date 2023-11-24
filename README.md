# daisy-rnbo-poc

This serves as a proof-of-concept for running RNBO exported patches on the [Electrosmith Daisy Seed](https://www.electro-smith.com/daisy) platform.

The compiled code exceeds the FLASH capacity but fits well within SRAM (approximately 130kB for basic applications using the Seed board). The audio IO functions properly; you simply need to switch to a float buffer instead of the default double (`-DRNBO_USE_FLOAT32`). I tested this with the vibrato example from the "RNBO Pedal Collection."

This project is a barebones implementation for the Seed, featuring a simple oscillator in `gen~` within the RNBO patch.

Since it targets SRAM, you must execute `make program-boot` first and then `make program-dfu` while the Seed's LED is in the "breathing" state. This will output a sweeping frequency ranging from 50Hz to 1kHz (frequency set via RNBO param). The signal is disturbed by playing `sin(2*x)` from a short `buffer~`. The LED will blink to indicate that some MIDI messages are coming from the RNBO midiout.

All the essential configurations are in the Makefile (-D flags), `compat` directory, and `main.cpp`. `-fexceptions` is obligatory, though it seems that no compiled code use exceptions, image does not run on Seed without it. 

`rnbo/*` and `rnbo_source.cpp` autogenerated and unaltered. `libDaisy` located in the submodule. Optional memory management is introduced in the memmgr directory for allocating RNBO buffers in SDRAM. However, this is optional, and you can use the regular heap; just adjust DaisyPlatform.h to call regular malloc/free or your custom memory manager.

With `-DRNBO_SIMPLEENGINE` flag defined, you don't need to compile `RNBO_Engine.cpp` and `RNBO_ParameterInterfaceAsync.cpp`. This setup employs a core engine and synchronous event processing that doesn't rely on threads or mutexes.

It's a straightforward and rudimentary example, intended to demonstrate that this setup can function without Linux or RTOS.
