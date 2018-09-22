#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <dlfcn.h>

int main(int argc, char *argv[]) {
    int num_shlib = argc - 1;
    bool failed = false;
    void **p = malloc(num_shlib * sizeof(void *));
    for(int i = 0; i < num_shlib; i++) {
        p[i] = dlopen(argv[1], RTLD_NOW);
        if(p[i] == NULL) {
            puts(dlerror());
            failed = true;
        }
    }
    for(int i = num_shlib - 1; i >= 0; i--) {
        if(p[i] != NULL)
            dlclose(p);
    }
    return failed ? 1 : 0;
}
