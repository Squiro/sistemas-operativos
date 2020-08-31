# =========================== Encabezado =======================

# Nombre del script: ejercicio2.ps1
# Número de ejercicio: 2
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
    Este script muestra aquellos procesos en ejecución que tengan más de una determinada cantidad de instancias.
.PARAMETER cantidad
    Este parámetro es obligatorio. Es la cantidad mínima de instancias que debe tener un proceso para que sea reportado.
.EXAMPLE 
    C:\PS> ejercicio2.ps1 -cantidad 2

    AcroRd32
    Discord
    Firefox
    GTAV-fitgirlrepack
    CrysisCODEX
    FIFA19-Skidrow
    TotallyNotAVirusTrustMeImADolphin
#>

Param (
    # Decimos que el parámetro pathsalida es el primero en ser enviado 
    # y que no es obligatorio enviarlo para invocar al script
    [Parameter(Position = 1, Mandatory = $true)]
    [int] $cantidad
)

# Tiene que ser >= 2
if ($cantidad -ge 2) {
    $procesosTable = @{}

    $listaproceso = Get-Process

    foreach($proceso in $listaproceso) {
        $nombre = $proceso.Name

        if ($procesosTable.ContainsKey($nombre) -eq $true)
        {
            $procesosTable[$nombre] = ($procesosTable[$nombre] + 1)
        }
        else {
            $procesosTable.Add($nombre, 1)            
        }        
    }

    Write-Host "Procesos que tienen $cantidad o mas instancias en ejecucion"

    foreach($key in $procesosTable.Keys) {
        if ($procesosTable[$key] -ge $cantidad) {
            Write-Host $key
        }
    }
}
else {
    Write-Host "El parámetro cantidad debe ser mayor a 1."
}
# =========================== Fin de archivo =======================