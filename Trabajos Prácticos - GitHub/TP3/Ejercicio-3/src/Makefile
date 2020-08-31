# directorio de includes
IDIR=../include
# directorio donde se guardarán los archivos .o
ODIR=obj

# Compilador a usar
CC = gcc 
# Flags del Compilador
CFLAGS=-pthread -I$(IDIR) 

# includes, dependencias
_DEPS=funciones.h
# Sintaxis: $(patsubst pattern, replacement, text)
# Halla palabras separadas por whitespaces en TEXT que coincidan con un PATTERN
# y las reemplaza con REPLACEMENT
# En este caso, matcheamos cualquier (%) texto, y usamos ese match para reemplazar el texto de 
# ahi con $(IDIR)/%
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Lo mismo que arriba #hacerConsultas.o leerResultado.o
_OBJ=ejercicio3.o funciones.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Definimos una regla. Las reglas tienen el siguiente formato:
# archivosTarget: prerequisitos
#				receta 

# También utilizamos variables o macros predefinidas de make, como
# $@: nombre del archivo target de la regla
# $<: primero de los prerequisitos

# Lo que hace esta regla es crear un archivo .o por cada archivo .c que tengamos en el directorio. Esto es para que
# los cambios que aplicamos en el código fuente se vean reflajados en el programa objeto antes de que este sea compilado
# definitivamente 

$(ODIR)/%.o: ./%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#$(OBJ): $(ODIR)/%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

# Utilizamos la variable predefinida $^, que hace referencia a los nombres de todos los prerequisitos, con espacios
# en cada uno de ellos. Esto es conveniente para compilar más de un archivo a la vez

#$(BIN): %: %.c
#	$(CC) -o $@ $^ $(CFLAGS) 

ejercicio3: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 


# Un target phony no hace referencia al nombre de un archivo... solo hace referencia
# a un nombre
.PHONY: clean

clean: 
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~