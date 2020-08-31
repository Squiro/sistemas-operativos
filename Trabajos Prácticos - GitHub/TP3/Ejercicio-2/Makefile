CC = gcc # Compilador a usar
CFLAGS=-I. # Flags: -I
OBJ=ejercicio2.o

# Definimos una regla. Las reglas tienen el siguiente formato:
# archivosTarget: prerequisitos
#				receta 

# En la regla utilizamos el wildcard %: que hace que...

# También utilizamos variables o macros predefinidas de make, como
# $@: nombre del archivo target de la regla
# $<: primero de los prerequisitos

# Lo que hace esta regla es crear un archivo .o por cada archivo .c que tengamos en el directorio. Esto es para que
# los cambios que aplicamos en el código fuente se vean reflajados en el programa objeto antes de que este sea compilado
# definitivamente 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Utilizamos la variable predefinida $^, que hace referencia a los nombres de todos los prerequisitos, con espacios
# en cada uno de ellos. Esto es conveniente para compilar más de un archivo a la vez

ejercicio2: $(OBJ)
	$(CC) -pthread -o $@ $^ $(CFLAGS)