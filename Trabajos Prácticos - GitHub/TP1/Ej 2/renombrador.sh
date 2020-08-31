#!/bin/bash

# =========================== Encabezado =======================

# Nombre del script: renombrador.sh
# Número de ejercicio: 2
# Trabajo Práctico: 1
# Entrega: Segunda entrega

# ==============================================================

# ------------------------ Integrantes ------------------------
# 
#		Nombre		|		Apellido		|		DNI
#					|						|
# -------------------------------------------------------------

ErrorDir() 
{
	echo "Error, $1 no es un directorio, o no existe, o es inaccesible debido a permisos."
	exit 1
}

Ayuda()
{
	echo "Este script renombra los archivos que contengan un espacio en blanco, reemplazando dicho espacio\
por un underscore (_). Al finalizar su ejecución muestra la cantidad de archivos renombrados."
	echo "Modo de uso: $0 [PARAM] directorio"
	echo "El directorio ingresado puede ser dejado en blanco para utilizar el directorio actual."
	echo "Parámetros: "
	echo "-r: recursivo. Se realiza el renombrado de archivos del directorio actual y de todos los directorios contenidos dentro del mismo recursivamente."
	echo "-h, -help, -?: muestra este manual."
}

# Chequea que exista el directorio y setea la variable directory en caso de ser así. Si no existe el dir, tira error.

CheckDir() 
{
	# Chequeamos si el directorio que se recibió por parámetro está vacío
	# Si no lo está...
	if [ ! "$1" == "" ] ; then
		# Verificamos si el directorio existe
		if [ ! -d "$1" ] ; then
			ErrorDir "$1"
		fi
		# Si existe lo asignamos
		directory=$1
	fi
	
	# Si no, lo dejamos tal cual esta (valor de $PWD)
}

RenombrarRecursivo() 
{
	# Activamos globstar para que funcione la recursividad al hacer globbing
	shopt -s globstar
	Renombrar
}

Renombrar() 
{
	# Recorremos todos los archivos en el directorio
	contador=0
	for arch in "${directory}"/**; do
		# No sé si hay que renombrar directorios también.
		#if [ -d "$arch" ] ; then
		#	echo "$arch es un directorio"
		#fi
		if [ -f "$arch" ] ; then
			#echo ${arch##*/}
			# Removemos el path entero y solo nos quedamos con el nombre de archivo utilizando parameter expansion
			filename=${arch##*/}
			path=${arch%/*}
			# Removemos los espacios repetidos en el nombre del archivo
			nombreSinRepetidos=`echo "$filename" | tr -s ' '`
			# Removemos los espacios en blanco y los reemplazamos con un underscore
			nuevoNombre="${nombreSinRepetidos// /_}"
			if [ "$nuevoNombre" != "$filename" ] ; then
				# ¿Existe ya ese archivo? ¿Renombramos uno antes y quedan iguales de nombre ahora?
				if [ -f "$path/$nuevoNombre" ] ; then 
					# Usamos el comando find aclarandole que solo busque archivos que no sean directorios, y 
					# que tengan el nombre del archivo que da problemas. Usamos un pipe para usar el comando wordcount con la salida de find, y contamos
					# la cantidad de lineas de dicha salida. Find devuelve una línea por archivo encontrado.
					repetidos=`find -type f -name "$nuevoNombre" | wc -l`
					#Esto no es lo más elegante del mundo pero bueno
					nuevoNombre="$repetidos-$nuevoNombre"
				fi
				# Hacemos el cambio de nombre
				mv -i "$arch" "$path/$nuevoNombre"
				# Aumentamos el contador de archivos cambiados
				let contador=contador+1
			fi
		fi
	done
	shopt -s globstar
	echo "Fueron renombrados $contador archivos."
}

# Asignamos por defecto el directorio actual como el valor de la variable PWD
directory=$PWD

# La cantidad de parámetros minimos es 0, este script puede funcionar sin recibir parámetros,
# por lo que hacer una validación de 0 parámetros es algo trivial... ¿A qué se refiere con eso?

# Chequeamos si se recibió uno de los parámetros de ayuda

if [ "$1" == "-h" ] || [ "$1" == "-help" ] || [ "$1" == "-?" ] ; then 
	Ayuda
# Si se recibieron dos parámetros...
elif [ $# == 2 ] ; then 
	# Si el primero es un parámetro recursivo...
	if [ "$1" == "-r" ] ; then
		# Llamamos a CheckDir para chequear y setear el directorio en el que vamos a empezar renombrar, pásandole el segundo parámetro
		CheckDir "$2"
		RenombrarRecursivo
	# No reconocemos el parámetro enviado
	else
		echo "Error $1 no es reconocido como un parámetro."
		Ayuda
	fi
# Si solo recibimos un parámetro (o ningún), tenemos que fijarnos que sea un directorio
else
	if [ "$1" == "-r" ] ; then
		RenombrarRecursivo
	else
		CheckDir "$1"
		Renombrar
	fi

fi

# =========================== Fin de archivo =======================