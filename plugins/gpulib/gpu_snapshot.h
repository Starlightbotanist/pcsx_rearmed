#ifndef GPULIB_SNAPSHOT_H
#define GPULIB_SNAPSHOT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Process-local continuation state. Storage is owned by the caller; it is
 * valid only while renderer allocations and configuration are unchanged. */
void GPUsnapshot_sync(void);
void GPUsnapshot_sync_state(void);
size_t GPUsnapshot_size(void);
void GPUsnapshot_save(void *data);
int GPUsnapshot_valid(const void *data);
void GPUsnapshot_load(const void *data);

#ifdef __cplusplus
}
#endif

#endif
