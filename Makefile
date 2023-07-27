# La variable CC indica el ejecutable para el compilador C (usualmente son gcc o clang)
CC=gcc
# La variable CFLAGS indica las banderas para el compilador C
CFLAGS=-Wall -Wextra -std=gnu99 -ggdb
# La variable LDLIBS indica las banderas para la parte del "loader", usualmente librerías "-lxxxx"
LDLIBS=

# Este sería el ejecutable, sus dependencias son los .o
minish: 	builtin_cd.o builtin_dir.o builtin_exit.o builtin_getenv.o builtin_gid.o builtin_help.o builtin_history.o builtin_lookup.o builtin_pid.o builtin_setenv.o builtin_status.o builtin_uid.o builtin_unsetenv.o ejecutar.o externo.o linea2argv.o minish.o wrappers.o deq-func.o builtin_copiar.o

# Acá van los .o, make sabe que cada .o depende del .c correspondiente, acá se agrega la dependencia al .h
builtin_cd.o : builtin.h
builtin_dir.o : builtin.h
builtin_exit.o : builtin.h
builtin_getenv.o : builtin.h
builtin_gid.o : builtin.h
builtin_help.o : builtin.h
builtin_history.o : builtin.h
builtin_lookup.o : builtin.h
builtin_pid.o : builtin.h
builtin_setenv.o : builtin.h
builtin_status.o : builtin.h
builtin_uid.o : builtin.h
builtin_unsetenv.o : builtin.h
builtin_copiar.o : builtin.h
ejecutar.o : minish.h
externo.o : minish.h
linea2argv.o : minish.h
minish.o : minish.h
wrappers.o : wrappers.h
deq-func.o : deq.h
