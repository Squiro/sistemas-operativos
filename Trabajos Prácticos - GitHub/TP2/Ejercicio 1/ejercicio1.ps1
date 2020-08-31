# =========================== Encabezado =======================

# Nombre del script: ejercicio1.ps1
# Número de ejercicio: 1
# Trabajo Práctico: 2
# Entrega: Primer entrega

# ==============================================================

# ------------------------ Integrantes ------------------------
# 
#		Nombre		|		Apellido		|		DNI
# -------------------------------------------------------------

# Param () se usa para definir parametros de entrada, cada uno separados por una coma.
# Podemos asignarles valores por defecto a estos parámetros, para que sean usados en caso de que al invocar el script 
# no se reciba ningún valor.
# Además utilizando [Parameter(...)] podemos especificar atributos para dicho parámetro, lo cuál modificará al mismo (e.g: 
# haciendo que este sea obligatorio o no).

Param (
    # Decimos que el parámetro pathsalida es el primero en ser enviado 
    # y que no es obligatorio enviarlo para invocar al script
    [Parameter(Position = 1, Mandatory = $false)]
    [String] $pathsalida = ".\procesos.txt ",
    [int] $cantidad = 3
)

# Chequeamos si existe el path de salida y guardamos el resultado en una variable
$existe = Test-Path $pathsalida

# En caso de que exista el path...
if ($existe -eq $true) {
    # Obtenemos la lista de procesos en ejecución
    $listaproceso = Get-Process
    # Por cada proceso en la lista de procesos...
    foreach ($proceso in $listaproceso) {
        # Aplicamos un formateo sobre la lista. Lo que hacemos es seleccionar solamente un par de atributos
        # que nos interesan del proceso. En este caso, tomamos las propiedades ID (el PID) y Name (el nombre)
        # y las redireccionamos al archivo de salida.
        $proceso | Format-List -Property Id,Name >> $pathsalida
    }
    # Recorremos solamente $cantidad procesos de la lista de procesos. Mostramos por pantalla
    # sus nombres y sus ID.
    for ($i = 0; $i -lt $cantidad ; $i++) {
        Write-Host $listaproceso[$i].Name - $listaproceso[$i].Id
    }
} else { # Si no existe el path de salida, mostramos un error
    Write-Host "El path no existe"
}

<#
    Respuestas: 

    1. ¿Cuál es el objetivo del script?

    El script cumple con dos objetivos. El primero es recorrer una lista de procesos activos al momento de ejecución del script,
    guardando sus ID y sus nombres en un archivo de salida. El segundo objetivo es mostrar por pantalla solo los $cantidad primeros procesos
    de esa lista, mostrando sus nombres y sus ID. 

    2. ¿Agregaría alguna otra validación a los parámetros?

    Que el parámetro de cantidad no sea mayor que la cantidad de procesos que hay en este momento (es decir, que los que están en la lista de procesos). 
    Así no recorremos innecesariamente procesos que no existen.
    
    3. ¿Qué sucede si se ejecuta el script sin ningún parámetro?

    Se utilizarían los valores predeterminado de los parámetros y el script se ejecutaría sin problemas.
#>
# =========================== Fin de archivo =======================