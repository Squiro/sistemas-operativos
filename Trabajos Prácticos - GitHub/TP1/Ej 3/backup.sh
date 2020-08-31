#!/bin/bash

# =========================== Encabezado =======================

# Nombre del script: backup.sh
# Número de ejercicio: 3
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
	echo "Error: \"$1\" no es un directorio, o no existe, o es inaccesible debido a permisos."
	exit 1
}

Ayuda()
{
	echo "Este script administra la ejecución de un demonio encargado de crear backups de un directorio."
	echo "Modo de uso: $0 [PARAM] directorio dirbackup segundos"
	echo "Ejemplo: $0 -start ./carpetita /tmp/backup 1000"
	echo ""
	echo "Parámetros: "
	echo "-start: Inicia la ejecución del demonio, se solicita por parámetro el directorio a salvar, el\
 directorio donde guardar el backup y el intervalo de tiempo entre backups (expresado en\
 segundos)."
	echo "-stop: Finalizar el demonio"
	echo "-count: Indica la cantidad de archivos de backup hay en el directorio."
	echo "-clear: Limpia el directorio de backup, recibe por parámetro la cantidad de backup que\
 mantiene en la carpeta, siendo estos los últimos generados. Si no se recibe ningún parámetro se\
 toma el valor cero."
	echo "-play: El demonio crea el backup, en este instante."
}

Start() 
{
	if ! [ -f /tmp/daemonpid.txt ] ; then
		dirInicial="$1"
		dirFinal="$2"
		segundos="$3"

		# Si no existe el directorio de inicio, tiramos un error y terminamos el script
		if [ ! -d "$dirInicial" ] ; then 
			ErrorDir "$1"
		fi

		# Si no existe el final, lo creamos
		if [ ! -d "$dirFinal" ] ; then
			mkdir "$dirFinal"
			if  [ $? != 0 ] ; then
				echo "Error al intentar crear el directorio de destino. Asegúrese de ingresarlo correctamente."
			fi
		fi

		re="^[0-9]+$"
		if ! [[ "$segundos" =~ $re ]] ; then
			echo "Error: El parámetro que indica la cantidad de segundos no fue ingresado correctamente."
			exit 1
		fi

		# Creamos una variable de entorno que tenga el directorio de backup
		# Si todos los parámetros pasaron la validación... empezamos el script 
		./daemon.sh "$dirInicial" "$dirFinal" "$segundos" &
		echo "¡Demonio empezado!"
	else
		echo "Ya hay un demonio ejecutándose."
	fi
}

Clear() 
{
	getDaemonPid
	# Guardamos la cantidad recibida como parametro en un archivo de texto
	echo "$1" > /tmp/cantidad.txt
	# Mandamos la señal al hijo que está corriendo en background
	kill -10 $daemonpid
}

Stop() 
{
	getDaemonPid
	# Matamos al proceso en background
	kill -9 $daemonpid
	rm -f /tmp/daemonpid.txt
}

Count() 
{
	getDaemonPid
	# Le enviamos SIGUSR2 esperando que el proceso hijo la atrape
	kill -12 $daemonpid
}

Play()  
{
	getDaemonPid
	# Le enviamos una señal esperando que el proceso hijo la atrape
	kill -11 $daemonpid
}

getDaemonPid() 
{
	if [ ! -f /tmp/daemonpid.txt ] ; then
		echo "Error, debe comenzar el demonio antes de ejecutar este comando."
		exit 1
	fi

	daemonpid=`cat /tmp/daemonpid.txt`
}

# Chequeamos si se recibió uno de los parámetros de ayuda como primer parámetro

if [ "$1" == "-h" ] || [ "$1" == "-help" ] || [ "$1" == "-?" ] ; then 
	Ayuda
elif [ "$1" == "-start" ] ; then
	Start "$2" "$3" "$4"
elif [ "$1" == "-stop" ] ; then
	Stop
elif [ "$1" == "-clear" ] ; then
	Clear "$2"
elif [ "$1" == "-count" ] ; then 
	Count 
elif [ "$1" == "-play" ] ; then 
	Play
else
	echo "Error, no se específico ningún comando. Refierase a la ayuda para más info."
	echo ""
	Ayuda
fi

# =========================== Fin de archivo =======================