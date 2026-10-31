# Snapshot regression tests

Build NEON with async GPU support. The pinned RetroArch test host is fetched on the first test build:

```sh
make -C tests/snapshots check \
  CORE=/absolute/path/to/pcsx_rearmed_libretro.so
```

On Windows use native Make, `SHELL=C:/msys64/usr/bin/sh.exe`,
`CC=C:/msys64/mingw64/bin/gcc.exe` and `PYTHON=C:/path/to/python.exe`.
Python 3 runs the suite. `OUTPUT` must be new (default `build/results`).

The generated original PS-X EXE runs through ReARMed's HLE loader. No game or
BIOS is needed; do not use Beetle's adjacent generated reset stub as its BIOS.

The three profiles are NEON 2x, native 1x, and 2x with GPU threading enabled.
Each checks 32 retained steps, actual guest VRAM reads, full RAM, normalized RGB,
repeated restores and independent release. Blending into retained pixels makes
an omitted enhanced restore observable: the 2x case fails, while fixed 1x does
not reach that operation. Missing native VRAM fails the guest read at both scales.

These are software continuation tests, executed on Windows x86_64. They do not
certify frontend scheduling, all renderer fields, memory-card commitment,
allocation failures or setting transitions.

## Test harness dependency

Only these explicit test targets fetch sources from RetroArch. Normal core
builds and gameplay do not download or use the test harness. `harness.lock.json`
pins a full commit and SHA-256 for each source file, including the matching
libretro header. The first `make harness`, `check` or `check-gpu` downloads
the sources into a shared user cache; later runs verify and reuse them.
The cache is under `%LOCALAPPDATA%/libretro/snapshot-tests` on Windows, or
`$XDG_CACHE_HOME/libretro/snapshot-tests` (`~/.cache` by default) elsewhere. Only targets supported by this core are available.

Use `OFFLINE=1` to require cached sources, or set
`TOOLS=/path/to/RetroArch/libretro-common/samples/snapshots` for local
development or an offline source checkout. `HARNESS_CACHE` selects another
cache directory. A local override intentionally bypasses the pin and fetching.
Updating the harness requires changing the revision and checksums together;
branch heads and tags are never used as dependency versions.
