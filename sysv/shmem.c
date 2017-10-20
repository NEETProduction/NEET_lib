

#define _GNU_SOURCE

#ifndef DEBUG
	#define perror(format, ...)
	#define fprintf(stream, perror, ...)
#endif

#include "sysv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <errno.h>

#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <sys/types.h>
#include <sys/wait.h>

static const int key_generator_value = 2345;

int sysv_shmget(void **ret, char *tok, key_t shm_fixkey, size_t size, int user_mode)
{
	if(size < 0)
	{
		return -1;
	}

	key_t shm_key;

	if(tok != NULL)
	{
		if((shm_key = ftok(tok, key_generator_value)) < 0)
		{
			perror("Error getting shm_key\n");
			return -1;
		}
	}
	else
	{
		shm_key = shm_fixkey;
	}

	int shm_id;
	if((shm_id = shmget(shm_key, size, IPC_CREAT|IPC_EXCL|user_mode)) < 0)
	{
		if(errno != EEXIST)
		{
			fprintf(stderr, "Error occured! ERRNO : %d\n", errno);
			return -1;
		}
		
		if((shm_id = shmget(shm_key, 0, 0)) < 0)
		{
			perror("Error getting shared memory ID\n");
			return -1;
		}
	}

	if(!(*ret = shmat(shm_id, 0, 0)))	//error
	{
		perror("Error getting memory address\n");
		return -1;
	}


	return shm_id;

}

int sysv_shmfree(int shm_id)
{
	return shmctl(shm_id, IPC_RMID, NULL);
}
