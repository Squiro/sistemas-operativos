# =========================== Encabezado =======================

# Nombre del script: ejercicio5.ps1
# Número de ejercicio: 5
# Trabajo Práctico: 2
# Entrega: Primer entrega

# ==============================================================

# ------------------------ Integrantes ------------------------
# 
#		Nombre		|		Apellido		|		DNI
#					|						|
# -------------------------------------------------------------

<# 
.SYNOPSIS
    Este script realiza las siguientes dos acciones cada terminado tiempo: 
    • Informar la cantidad de procesos que se encuentran corriendo en ese momento.
    • Indicar el tamaño de un directorio.
.DESCRIPTION 
    El script puede recibir los siguientes parámetros:
    • -Procesos: Parámetro que indica que se mostrará la cantidad de procesos corriendo al momento de ejecutar el script.
    • -Peso: Parámetro que indica que se mostrará el peso de un directorio.
    • -Directorio: Solo se puede usar si se pasó “-Peso”. Indica el directorio a evaluar.
.PARAMETER proceso
    Indica que el modo a trabajar es el modo de procesos.
.PARAMETER peso
    Indica que el modo a trabajar es el modo de peso.
.PARAMETER directorio
    Solo válido para el modo peso. Indica el directorio a mostrar información sobre su tamaño.
.EXAMPLE 
    Para obtener información sobre los procesos: 

    C:\PS> ejercicio5.ps1 -procesos
.EXAMPLE 
    Para obtener información sobre el tamaño de un directorio: 

    C:\PS> ejercicio5.ps1 -peso -directorio <ruta>
#>

Param (
    [Parameter(ParameterSetName="Procesos")]
    [Switch] $procesos,
    [Parameter(ParameterSetName="Peso")]
    [Switch] $peso,
    [Parameter(ParameterSetName="Peso", Mandatory=$true)]
    [String] $directorio
)

function ChequearDir([String] $dir) {
    if (!(Test-Path $dir)) {
        ErrorDir $dir
        return $false
    } else {
        return $true
    }
}

function ErrorDir([String] $dir) {
    Write-Host "Error, el directorio: $dir, no se existe o no puede ser leido."
}

function informarProcesos() {
    while ($true) {
        $cant = (Get-Service | Where-Object Status -eq "Running").Count
        Write-Host $cant
        Start-Sleep -s 10
    }

}

function informarPeso([String] $directorio) {
    if (ChequearDir($directorio)) {
        while ($true) {
            $cant = Get-ChildItem -path $directorio | Measure-Object -Sum Length | Select-Object Sum
            Write-Host $cant.Sum
            Start-Sleep -s 10
        }
    }
}


if ($procesos) {
    informarProcesos
} elseif($peso) {
    informarPeso($directorio)
}
else {
    Write-Host "No se especifico ninguna accion."
}

# =========================== Fin de archivo =======================