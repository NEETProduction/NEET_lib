/*
Copyright 2017 Jeonghun Gong

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

int parent_process(int argc, char **argv);
int child_process(int argc, char **argv);

int main(int argc, char **argv)
{
	pid_t child_pid = fork();
	if(!child_pid)
	{
		return child_process(argc, argv);
	}

	parent_process(argc, argv);
	waitpid(child_pid, 0, 0);

	return 0;
}

int parent_process(int argc, char **argv)
{
	printf("Hello, Child! from parent\n");
	return 0;
}

int child_process(int argc, char**argv)
{
	printf("Hello, Parent! from child\n");
	return 0;
}
