# =========================== Encabezado =======================

# Nombre del script: ejercicio6.ps1
# Número de ejercicio: 6
# Trabajo Práctico: 2
# Entrega: Primer entrega

# ==============================================================

# ------------------------ Integrantes ------------------------
# 
#		Nombre		|		Apellido		|		DNI
# -------------------------------------------------------------

<# 
.SYNOPSIS    
    Script que realiza la suma entre matrices o el producto escalar.
.DESCRIPTION
    Lee una matriz a través de un archivo de entrada. Realiza el producto escalar entre un entero que es recibido por parámetro. Guarda el resultado
    en un archivo de salida.
.PARAMETER entrada
    Ruta del archivo que contiene la matriz.
.PARAMETER salida
    Ruta de salida donde se guardará la matriz resultado.
.PARAMETER producto
    Número entero con el cual se realizará el producto escalar.
.PARAMETER suma
    Ruta al archivo que contiene la otra matriz para realizar la operación. Indica que se realizará una suma de matrices. 
.EXAMPLE 
    C:\PS> ejercicio6.ps1 -entrada <ruta> -salida <ruta> -producto 3
#>

Param (
    [Parameter(Mandatory=$true)]
    [ValidateNotNullOrEmpty()]
    [String] $entrada,
    [Parameter(Mandatory=$true)]
    [ValidateNotNullOrEmpty()]
    [String] $salida,
    [Parameter(ParameterSetName="Producto")]
    [int] $producto,
    [Parameter(ParameterSetName="Suma")]
    [String] $suma
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

function productoEscalar([String] $directorio) {
    if (ChequearDir($directorio) -and ChequearDir($salida)) {
        $matriz = Get-Content "$directorio" 
    
        foreach ($line in $matriz) {
            $arr = $line.Split('|')            

            for ($i = 0; $i -lt $arr.Count; $i++) {
                $arr[$i] = ([double] $arr[$i] * $producto)
            }

            $arr = $arr -join '|'
            $arr >> $salida
        }
    }
}

function sumarMatrices() {
    if (ChequearDir($entrada) -and ChequearDir($salida) -and ChequearDir($suma)) {
        $matriz1 = Get-Content "$entrada" 
        $matriz2 = Get-Content "$suma"
        # Si tienen la misma cantidad de filas y columnas
        if (($matriz1.Length -eq $matriz2.Length) -and ($matriz1[0].Split('|').Count -eq $matriz2[0].Split('|').Count)) {
            for ($i = 0; $i -lt $matriz1.Length; $i++) {
                $filaMat1 = $matriz1[$i].Split('|')
                $filaMat2 = $matriz2[$i].Split('|')

                for ($j = 0; $j -lt $filaMat1.Count; $j++) {
                    $filaMat1[$j] = [double] $filaMat1[$j] + [double] $filaMat2[$j]
                }

                $filaMat1 = $filaMat1 -join '|'
                $filaMat1 >> $salida            
            } 
        } else {
            Write-Host "Las matrices deben tener la misma cantidad de filas y columnas para ser sumadas"
        }
    }
}

if ($producto -ne $null) {
    productoEscalar $entrada
} elseif($suma -ne "") {
    sumarMatrices
}
else {
    Write-Host "No se especifico ninguna accion."
}

# =========================== Fin de archivo =======================