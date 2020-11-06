#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include <string.h>

typedef int (*RMType)(const char *args);

int unlink(const char *args)
{
    if(strstr(args, "FIX")){
        return EPERM;
    } else {
        RMType real_unlink = (RMType)dlsym(RTLD_NEXT, 'unlink');
        return real_unlink(args);
    }
}
