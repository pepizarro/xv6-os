
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {

    /*char *addr = sbrk(0);  // Obtener la dirección actual del heap*/
    /*i = mprotect(addr, 1);*/
    /*printf("mprotect returned: %d\n", i);*/
    char *addr = sbrk(0);  // Obtener la dirección actual del heap
    sbrk(4096);  // Reservar una página
    // Intentar proteger la nueva página
    if (munprotect(addr, 1) == -1) {
        printf("munprotect falló\n");
    }
    // Intentar escribir en la página protegida

    char *ptr = addr;
    *ptr = 'A';  // Write 'A' to the allocated memory

    printf("escritura funcionó, valor: %c\n", *ptr);
    
    // ahora desactivamos la protección para la misma dirección
    if (mprotect(addr, 1) == -1) {
        printf("munprotect falló\n");
    }
    printf("intentando escribir..\n");
    *ptr = 'A';  // Esto no debería funcionar
    printf("Valor en la dirección: %c\n", *ptr);  // Verificar el valor
    

    return 0;
}
