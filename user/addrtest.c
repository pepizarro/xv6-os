
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {

    char *addr = (char *)0xFFFFFFFF;
    sbrk(4096);  // Reservar una página
    
    // Intentar proteger la nueva página
    if (mprotect(addr, 1) == -1) {
        printf("mprotect falló\n");
    }
    
    return 0;
}
