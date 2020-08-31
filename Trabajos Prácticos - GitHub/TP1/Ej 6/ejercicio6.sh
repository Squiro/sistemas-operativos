#!/bin/bash

# =========================== Encabezado =======================

# Nombre del script: ejercicio6.sh
# Número de ejercicio: 4
# Trabajo Práctico: 1
# Entrega: Primer entrega

# ==============================================================

# ------------------------ Integrantes ------------------------
# 
#		Nombre		|		Apellido		|		DNI
#					|						|
# -------------------------------------------------------------

ErrorDir() 
{
	echo "Error: \"$1\" no es un directorio, o no existe, o es inaccesible debido a permisos."
	Ayuda
	exit 1
}

Ayuda()
{
	echo "Este script muestra los 10 subdirectorios más grandes de un directorio pasado por parámetro. Se informa\
 el tamaño de los subdirectorios hoja (es decir, directorios que no contegan otros directorios dentro). Además, muestra\
 la cantidad de archivos dentro del directorio."
	echo "Modo de uso: $0 directorio"
	echo "Donde directorio significa la carpeta a analizar."
	echo "Ejemplo: $0 ./carpetita"
	echo ""
	echo "Parámetros: "
	echo "-h, -?, -help: muestra este mensaje de ayuda."
	echo "directorio: inicializa el script en dicho directorio"
}

Analizar() 
{
	if [ ! -d "$1" ] ; then
		ErrorDir "$1"
	fi


	echo "Tamaño de los subdirectorios hoja: "
	find "$1" -type d -links 2 -exec du -h {} \; -exec sh -c 'find "{}" -mindepth 1 -maxdepth 1 -type f | wc -l >> /tmp/filecount.txt' \; 2>&1 | grep -v 'Permission denied' > /tmp/sizes.txt
	
	awk 'BEGIN { OFS=" " } {
		getline line < "/tmp/filecount.txt"
		print $0, "-- Cantidad de archivos en el directorio: " line
	} ' /tmp/sizes.txt > /tmp/concat.txt

	sort -nr /tmp/concat.txt | head -n 10
}

rm -f /tmp/filecount.txt

# Chequeamos si se recibió uno de los parámetros de ayuda como primer parámetro

if [ "$1" == "-h" ] || [ "$1" == "-help" ] || [ "$1" == "-?" ] ; then 
	Ayuda
else
	Analizar "$1"
fi

# =========================== Fin de archivo =======================