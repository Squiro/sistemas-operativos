#!/bin/bash

# =========================== Encabezado =======================

# Nombre del script: ejercicio4.sh
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
	echo "Este script cuenta la cantidad de líneas totales de código y la cantidad de comentarios que hay los archivos\
de un directorio especificado. A su vez, muestra la cantidad de archivos analizados y el porcentaje de líneas de código\
y comentarios basado en esa cantidad."
	echo "Modo de uso: $0 directorio extension"
	echo "Donde directorio significa la carpeta a analizar y extensión la extensión de los archivos de código."
	echo "Ejemplo: $0 ./carpetita cpp"
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

	# Activamos globstar para que funcione la recursividad al hacer globbing
	shopt -s globstar
	cantArch=0
	for arch in "${1}"**/*."$2"; do
		((cantArch++))
		# Chequeamos que sea un fichero y no un directorio
		if [ -f "$arch" ] ; then
			lineas=0
			comentarios=0
			codeAndSingleComm='^[[:blank:]]*[^[:blank:]]+.*\/\/.*'
			singleComment='^[[:blank:]]*\/\/.*'
			multiCommentStart='^[[:blank:]]*\/\*.*'
			multiCommentEnd='.*(\*\/)$'
			multiline=false

			echo "Analizando archivo: $arch"
			


			while IFS= read -r line;
			do
				# Si no está activado el flag multilinea
				if ! [ $multiline = true ]; then				
					# Cuenta líneas de código que tienen comentarios de una línea al final
					# e.g:    print("asd"); // prints asd
					if [[ $line =~ $codeAndSingleComm ]]; then
						((lineas++))
						((comentarios++))
					# Cuenta comentarios de una línea
					elif [[ $line =~ $singleComment ]]; then
						((comentarios++))
					# Si encontramos el inicio de un comentario multilinea, activamos el flag
					# Y sumamos uno al contador de comentarios
					elif [[ $line =~ $multiCommentStart ]]; then
						multiline=true
						((comentarios++))
						# Nos fijamos si encontramos el fin de un commentario multilinea
						if [[ $line =~ $multiCommentEnd ]]; then
							multiline=false
						fi
					else
						# Incrementamos contador de líneas si no se cumple ninguna otra condición
						((lineas++))
					fi
				# Si está activado el flag	
				else
					# Nos fijamos si encontramos el fin de un commentario multilinea
					if [[ $line =~ $multiCommentEnd ]]; then
						multiline=false
					fi
					((comentarios++))
				fi
			done < <(grep "" "$arch")

			total=$((lineas + comentarios))

			porcentajeLineas=`bc -l <<< "scale=2; ($lineas/$total)*100"`
			porcentajeComm=`bc -l <<< "scale=2; ($comentarios/$total)*100"`

			echo "Cantidad de lineas totales: $lineas - Porcentaje: $porcentajeLineas"
			echo "Cantidad de comentarios totales: $comentarios - Porcentaje: $porcentajeComm"
			echo ""
		fi
	done
	echo "Cantidad de archivos analizados: $cantArch"
	# Desactivamos globstar
	shopt -u globstar	

}

# Chequeamos si se recibió uno de los parámetros de ayuda como primer parámetro

if [ "$1" == "-h" ] || [ "$1" == "-help" ] || [ "$1" == "-?" ] ; then 
	Ayuda
else
	Analizar "$1" "$2"
fi

# =========================== Fin de archivo =======================