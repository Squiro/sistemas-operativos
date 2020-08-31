#!/bin/bash

# =========================== Encabezado =======================

# Nombre del script: ejercicio1.sh
# Número de ejercicio: 1
# Trabajo Práctico: 1
# Entrega: Primer entrega

# ==============================================================

# ------------------------ Integrantes ------------------------
# 
#		Nombre		|		Apellido		|		DNI
#					|						|

# -------------------------------------------------------------

ErrorS()
{
	echo "Error. La sintaxis del script es la siguiente:"
	echo "Para contar la cantidad de líneas de un archivo: $0 nombre_archivo L" # COMPLETAR
	echo "Para contar la cantidad de caracteres de un archivo: $0 nombre_archivo C" # COMPLETAR
	echo "Para contar la cantidad de caracteres de la línea más larga: $0 nombre_archivo M" # COMPLETAR
}

ErrorP()
{
	echo "Error. $1 no existe o no hay permiso de lectura para el mismo." # COMPLETAR
}
# Si la cantidad de parámetros es menor a 2, entonces se muestra un error de sintaxis
if test $# -lt 2; then
	ErrorS
fi

# Se chequea si el archivo existe y se tiene permiso de lectura para el mismo.
# Se niega el valor de salida del comando test. Si el valor de salida es falso, se niega
# y se ejecuta el bloque del if. Si es verdadero, se pasa al elif.
if ! test -r "$1" ; then
	ErrorP "$1"
# En cambio si el primer parámetro es un archivo regular que existe Y el segundo parámetro es L, C o M, entonces
elif test -f "$1" && (test $2 = "L" || test $2 = "C" || test $2 = "M"); then
# Si el segundo parámetro es una L, entonces asignamos a la variable res el resultado
# del comando wc (worcount)
	if test $2 = "L" ; then
		res=`wc -l "$1"`
		echo "La cantidad de líneas es: $res" # COMPLETAR
# Si $2 es una C, hacemos lo mismo pero con un diferente parámetro para wc
	elif test $2 = "C"; then
		res=`wc -m "$1"`
		echo "La cantidad de caracteres es: $res" # COMPLETAR
# Si $2 es una M, asignamos a la variable res la salida de wc -L $1
	elif test $2 = "M"; then
		res=`wc -L "$1"`
		echo "La cantidad de caracteres en la línea más larga es: $res" # COMPLETAR
	fi
# Si el segundo parámetro no es ninguno de los indicados, mostramos un error de sintaxis
else
	ErrorS
fi

# =========================== Respuestas =======================

# A) ¿Cuál es el objetivo de este script?
# El script se encarga de ejecutar el comando wc (worcount) con distintos parámetros sobre un archivo.
# El parámetro con el cual será ejecutado el comando wc depende del segundo parámetro que sea enviado al ejecutar
# este script. Luego de ejecutar el comando, se muestra un mensaje de salida que brinda información específica
# (tales como cantidad de líneas, número de carateres, y  cantidad de carácteres en la línea más larga) del archivo.

# B) ¿Qué parámetros recibe?
# Recibe el nombre (o ruta) de un archivo, y un segundo parámetro obligatorio que debe ser una de las siguientes
# letras: L, C, M.

# E) ¿Qué información brinda la variable “$#”? ¿Qué otras variables similares conocen? Explíquelas.
# $# es una variable especial de Bash que en términos simples nos brinda la cantidad de parámetros que
# han sido enviados al script.
# 
# Otras variables como $# son:
# $?: el valor de salida (exit value) del último comando ejecutado. 
#
# $_: el último parámetro del último comando ejecutado.
#
# $0: el nombre del script.
# 
# $@: devuelve todos los parámetros como un array.
#
# $*: devuelve todos los parámetros como una sola palabra (un string).
#
# $$: PID del proceso actual.
#
# $!: PID del último proceso hijo ejecutado en segundo plano.
#
# $IFS: (internal field separator) esta variable determina cuál es el caracter separador 
# de parámetros que Bash reconocerá para diferenciar los distintos parámetros que le sean
# enviados al invocar un script. 

# F) El manual de Bash dice lo siguiente acerca de los distintos tipos de comillas que pueden
# ser utilizadas: 
# 
# -Comillas simples: al encerrar caracteres en comillas simples ('), los mismos 
# preservan su valor literal dentro de las comillas. A su vez, no puede haber una comilla simple
# dentro de este espacio encerrado por comillas simples, incluso si "scapeamos" la comilla utilizando
# una contrabarra (\).
#
# -Comillas dobles: encerrar caracteres en comillas dobles (") preserva el valor literal de todos los caracteres
# dentro de las comillas, con la excepción de algunos caracteres especiales como $, `, \. Los caracteres $ y ` 
# retienen su significado especial dentro de comillas dobles. La contrabarra lo retiene solamente cuando es acompañado
# por alguno de los siguientes caracteres: $, `, ", \, o el caracter de nueva línea. Las contrabarras
# son removidas al ser acompañadas por alguno de los caracteres listados.

# =========================== Fin de archivo =======================