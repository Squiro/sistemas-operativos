#!/bin/bash

dirInicial=$1
dirFinal=$2
segundos=$3
running=true

# > crea y sobrescribe
echo "$$" > /tmp/daemonpid.txt

# Redireccionamos el stdin
exec 0</dev/null
# Redireccionamos stdout y stderr
#exec 1>/dev/null
#exec 2>/dev/null

trap clear SIGUSR1

clear() 
{
    # Tenemos que leer la cantidad de archivos que quiere conservar
    cantidad=`cat /tmp/cantidad.txt`

    #Cantidad de archivos en el directorio, actualmente
    cantidadArch=`find "$dirFinal" -maxdepth 1 -mindepth 1 -type d | wc -l`
    ((cantidadArch++))
    #Cantidad de archivos a eliminar (hacemos un complemento)
    cantElim=$(($cantidadArch-$cantidad))
    
    if [ "$cantidad" == "" ] ; then
        cantElim=0
    fi

    # Agarramos todos los archivos del directorio y lo guardamos en un array
    files=("$dirFinal"/*)

    #if [ $cantidad != 0 ] ; then 
    #    let cantidad=cantidad-1
    #fi

    # Eliminamos esa cantidad de archivos
    for ((i=0;i<$cantElim;i++)); do
        #echo "${files[$i]}"
        rm -rf ${files[$i]}
    done
}

trap count SIGUSR2

# Cuenta la cantidad de backups hechos

count()
{
    # Ponemos maxdepth y mindepth para que no nos busque recursivamente los demás directorios
    # y para ignorar el directorio padre (.)
    cantidad=`find "$dirFinal" -maxdepth 1 -mindepth 1 -type d | wc -l`
    # Cuando el script atrapa la señal, el sleep anterior se corta, y el ciclo while vuelve a iterar, creando una carpeta nueva
    # Pero el find se ejcuta antes de esta iteración, por lo que encuentra una cantidad de carpetas menor a las que hay actualmente
    # Le aumentamos en uno la cantidad para que dé la cantidad "correcta"
    ((cantidad++))
    echo "La cantidad de archivos en el directorio de backups es: $cantidad"
}

trap play SIGSEGV 

# Genera un backup en este instante

play()
{
    echo "Creando backup ahora mismo"
    backup
}

backup() 
{
    fecha=`date +'%d-%m-%Y-%R:%S'`
    #mkdir "$dirFinal"/"$fecha"
    cp -r "$dirInicial" "$dirFinal/$fecha"
}

while $running; do 
    backup
    sleep $segundos & wait $!
done