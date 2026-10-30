# Runtime snapshots

The optional version 2 snapshot interface preserves complete state for frontend
run-ahead and preemptive frames. Registration alone changes no prediction
settings; the frontend owns scheduling.

NEON retains machine state, memory cards, GPU commands/transfers, enhanced
pixels, scanout ownership and controller edges/samples. Queued rendering
finishes before capture/restore. Empty scratch is omitted; derived texture
caches are invalidated.

Ordinary savestates retain their format. Snapshot restoration avoids
compatibility repairs that alter timer/CD continuation. Reset, media,
controller, cheat and option changes invalidate snapshots. Rejected ordinary
loads retain recovery ownership; failure after mutation blocks execution,
memory and persistence until confirmed recovery or content reload.

Speculation suppresses rumble and disk writes. Canonical memory-card changes
are reconciled against a committed mirror. Failed sectors remain pending for
retry, including when replay cancels an earlier write.

Buffers are allocated only when the frontend acquires handles. At 2x on
Windows x64 each capture uses about 12.51 MiB, including enhanced planes, plus
about 4.5 MiB shared staging/card mirrors. Final release frees staging after
pending persistence succeeds.

Enhanced rendering refuses incomplete temporary serialization. Other renderers
retain their serialized prediction path. The experimental command needs API
review. `tests/snapshots` contains reproducible software tests.
