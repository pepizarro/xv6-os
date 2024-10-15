PD: ya había creado la rama y no tiene mi nombre.

### Nombre: Pedro Pizarro

# Tarea 2

- Para esta tarea se modificó el Makefile y se seleccionó solo 1 CPU.

Primero debemos agregar los atributos de `priority` y `boost` a la estructura de proceso.

![plot](./T2-1.png)

Luego debemos inicializar estas variables cuando entra un nuevo proceso al sistema, esto se puede hacer en la función `allocproc` en el archivo `proc.c`.
Pero primero debemos realizar las modificaciones correspondientes a las prioridades y boost de los otros procesos existentes, en esta imagen primero se hacen esas modificaciones, y luego se inicializan los atributos para el nuevo proceso:

![plot](./T2-allocproc.png)

A continuación debemos modificar el scheduler para que se tome prioridad a los procesos con un número menor en el atributo `priority`, esto se hace en la función `scheduler` en el archivo `proc.c`.

La lógica es inicializar una variable `lproc`, donde guardaremos el proceso que tenga la menor prioridad, y otra variable llamada `lowerp`, que almacenará la menor prioridad encontrada, luego haremos un loop por todos los procesos, y en caso de que encontremos un proceso con una prioridad menor (o en caso de que sea el primer proceso por el cual estamos iterando, por eso la variable `areProcesses`) almacenaremos el proceso en `lproc` y su prioridad en `lowerp`.

Luego, una vez que ya hayamos pasado por todos los procesos, haremos el context switch (si es que hay algún proceso "runnable") y ejecutaremos el proceso con la menor prioridad encontrada

![plot](./T2-scheduler.png)

Por último para el programa de prueba, cree un programa de usuario llamado `multiproc.c`, el cual ejecuta un for loop 20 veces y en cada iteración realiza un fork. Si el fork fue exitoso el proceso hijo entra en un loop infinito en el que imprime su pid y su prioridad y luego realiza un `sleep`, es importante notar que este sleep no es que espere la cantidad de "tiempo" que se ingrese como parámetro, de hecho esta función suelta la cpu, ya que dentro de esta función se encuentra una llamada al sistema llamada `sleep` también, que recibe una condición, la función que llamamos desde el programa de usuario le entrega la condición de que cuando pase x unidad de tiempo este proceso "despierte", es decir, que se ponga en estado **RUNNABLE** nuevamente.

Me gustaría destacar el caso que no utilicemos el sleep ya que demuestra que esta política de elegir el proceso con menor prioridad está con mucha falta de detalles y condiciones ya que no considera cosas como las interrupciones, por lo que en caso de que la CPU ingrese al proceso con menor prioridad, no hay ninguna condición que nos diga cuando debemos salir, por eso en la imagen a continuación se realiza la prueba sin el sleep:

![plot](./T2-multiproc.png)

En este caso el scheduler entra al proceso padre, crea su primer hijo, el que tiene PID: 4, luego entra al sleep (suelta la CPU) y el scheduler decide ejecutar el proceso hijo, por que tiene prioridad 0 y el padre 1 (solo sería ejecutable el padre si es que ya pasó la unidad de tiempo en la que está dormido). 

Debido a esto y a la naturaleza del proceso hijo, este proceso no suelta más la CPU, y como vemos en la imagen solo se ejecuta este proceso.

Como la llamada a sistema sleep el proceso sale del estado "RUNNABLE", por lo que no es considerado cuando el proceso debe elegir un scheduler, con esta lógica actual sin interrupciones (y usando el sleep) no es posible llegar a la política deseada, ya que cuando se elige un proceso por ejecutar se busca el que tenga menor prioridad, pero puede ocurrir que el proceso que tenga menor prioridad esté dormido y ni siquiera se evalúe, y luego cuando "despierte" sea ejecutado nuevamente.

Debido a esto se obtienen patrones no reconocibles como el siguiente:

![plot](./T2-fail.png)
