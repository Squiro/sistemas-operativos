#*****************************************************
# Trabajo Practico Nº1
# Entrega Nº1
# Fecha 18/09/2019
#
# Ejercicio 5
# Nombre del script: Ejercicio5.sh
#
#*****************************************************
# Integrantes:
#
# Apellido y nombre                 DNI
#----------------------------------------------
#*****************************************************
# Realizar un script que emule el comportamiento del comando rm, pero utilizando el concepto de “papelera de reciclaje”, 
# es decir que, al borrar un archivo se tenga la posibilidad de recuperarlo en el futuro.
# El script tendrá las siguientes opciones:
# -l listar los archivos que contiene la papelera de reciclaje.
# -r [archivo] recuperar el archivo pasado por parámetro a su ubicación original.
# -e vaciar la papelera de reciclaje (eliminar definitivamente)
# Sin modificador para que elimine el archivo.
# La papelera debe estar alojada en el home del usuario que ejecuta el comando, en un directorio oculto.
# Nota: Tenga presente que archivos de diferentes directorios podrían tener el mismo nombre. 
# El script debe considerar estos casos.
#*****************************************************
#!/bin/bash

cantParametros=$#
IFS=''
param1="$1"
param2="$2"

dirPapelera=$HOME"/.papelera"

if ! [[ -d "$dirPapelera" ]]; then
		mkdir "$dirPapelera"
	fi

Help(){
	echo "**** MENU DE AYUDA ****"
	echo
	echo "Este script permite mover un archivo a una carpeta de reciclaje oculta, recuperarlo o borrarlo permanente"
	echo "ademas de mostrar el contenido de la carpeta misma"
	echo
	echo "Modo de empleo: $0 [OPCION] [RUTA]"
	echo
	echo "OPCIONES DISPONIBLES"
	echo -e "-l listar los archivos que contiene la papelera de reciclaje."
	echo -e "-r [archivo] recuperar el archivo pasado por parámetro a su ubicación original."
	echo -e "-e vaciar la papelera de reciclaje (eliminar definitivamente)"
	echo -e "Sin modificador para que elimine el archivo."
}

if [[ $cantParametros -eq 1  && ("$param1" == "-h" || "$param1" == "--help" || "$param1" == "-?") ]]; then
		Help
		exit 0
	fi

if [[ $cantParmetros -gt 2 ]]; then
	echo "ERROR: Cantidad de parametros equivocada"
	exit 1
fi


if [[ -f "$param1" ]]; then

	param1=$(realpath $param1)
	path_reformatted=$(dirname $param1 | tr "/" "~")

	filename=$(basename $param1 | tr "/" "~")
	new_filename=$path_reformatted'~'$filename
	

	if [ -f "$dirPapelera/$new_filename" ] ; then 
		repetidos=`find -type f -name "$new_filename" | wc -l`
		new_filename="$new_filename-$repetidos"
	fi

	mv $param1 $new_filename
	mv $new_filename $dirPapelera
	
else
	case "$param1" in

		-l)
			echo $(ls -A $dirPapelera | tr "~" "/")					
		;;

		-r)
			if [[ $cantParametros -eq 2 ]]; then
				filename=$(echo "$2" | tr "/" "~")
				
				for file in "$dirPapelera"/*
				do
					if [[ "$file" =~ "$filename" ]] ; then
						file=${file#"$dirPapelera"}
						aux=$(echo "$file" | tr "~" "/")
						arc="$dirPapelera/$file"
						mv "$arc" "$aux" 
					fi
				done

			else
				echo "Parametros invalidos"
				echo "Para mas ayuda --help"
				exit 2
			fi
		;;		

		-e)
			rm -rf $dirPapelera
			mkdir "$dirPapelera"
		;;
		
		*)
			echo "Parametros invalidos"
			echo "Para mas ayuda --help"
			exit 2
		;;

	esac
fi
