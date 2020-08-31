# =========================== Encabezado =======================

# Nombre del script: ejercicio3.ps1
# Número de ejercicio: 3
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
    En base a un archivo CSV de entrada, mueve un listado de archivos a otros directorios.
.DESCRIPTION 
    En base a un archivo CSV (entrada) con los datos de origen y destino, mueve archivos de un directorio a otro y registra en un log con formato CSV (salida) 
    la hora en la que se movió cada uno de esos archivos.
.PARAMETER entrada
    Este parámetro es obligatorio. Es la ruta del archivo CSV de entrada donde están contenidos los archivos y la direcciones a ser movidos.
.PARAMETER salida
    Este parámetro es obligatorio. Es la ruta donde se guardará el archivo CSV de salida.
.EXAMPLE 
    C:\PS> ejercicio3.ps1 -entrada entrada.csv -salida salida.csv
#>

Param (
    [Parameter(Position = 1, Mandatory = $true)]
    [String] $entrada,
    [Parameter(Position = 2, Mandatory = $true)]
    [String] $salida
)

if (Test-Path "$entrada") {
    # Chequeamos que exista el path de salida 
    # No chequeamos si existe el archivo, porque eso lo creamos nosotros
    $salidaPath = Split-Path -Path "$salida"
    if ($salidaPath -eq "") {
        $existe = $true
    }
    else {
        $existe = Test-Path $salidaPath
    }

    if ($existe) {
        # Abrimos el archivo CSV
        $csvEntrada = Import-Csv -Path "$entrada"    
        foreach($line in $csvEntrada) 
        {
            # Get-Member obtiene los miembros, propiedades y métodos de los objetos. En este caso, obtenemos las propiedades.
            # Estas propiedades se traducen a las columnas del archivo csv. 
            $properties = $line | Get-Member -MemberType Properties

            # Por alguna razón las propiedades se ponen en orden inverso al orden de las columnas del CSV
            # Entonces el destino queda primero, y el origen ultimo
            $columna = $properties[0]
            $destino = $line | Select-Object -ExpandProperty $columna.Name
            $columna = $properties[1]
            $origen = $line | Select-Object -ExpandProperty $columna.Name
            
            # Movemos los archivos
            Move-Item $origen $destino
            # Obtenemos el nombre del archivo
            $filename = [System.IO.Path]::GetFileName($origen)
            # Obtenemos la fecha, especificando el formato
            $fecha = Get-Date -Format "dd/MM/yyyy"

            # Creamos un nuevo objeto de powershell que tenga como propiedades
            # el nombre de archivo y la fecha
            $obj = [pscustomobject]@{
                archivo = "$filename"       
                fecha  = $fecha         
            }
            # Añadimos el objeto al archivo de salida csv
            $obj | Export-Csv -Path "$salida" -Append
        } 
    }
    else {
        Write-Host "La ruta del archivo del salida no existe o no puede ser accedida."
    }    
}
else {
    Write-Host "El archivo de entrada no existe o no puede ser leido."
}


# =========================== Fin de archivo =======================