#ifndef SYSV_H
#define SYSV_H

#include <sys/types.h>
#include <sys/ipc.h>

int sysv_shmget(void **ret, char *tok, key_t shm_fixkey, size_t size, int user_mode);
int sysv_shmfree(int shm_id);

#endif
