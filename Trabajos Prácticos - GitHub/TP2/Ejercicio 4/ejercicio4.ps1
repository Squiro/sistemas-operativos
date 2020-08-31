# =========================== Encabezado =======================

# Nombre del script: ejercicio4.ps1
# Número de ejercicio: 4
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
    Permite comprimir, descomprimir, u obtener información sobre archivos ZIP.
.DESCRIPTION 
    Este script permite realizar las siguientes acciones sobre archivos ZIP:
    • Descompresión: Descomprime un archivo ZIP en un directorio pasado por parámetro.
    • Compresión: Comprime un directorio en un archivo ZIP.
    • Información: Muestra un listado con los nombres de los archivos, el peso y la relación de compresión, que se encuentran dentro de un archivo ZIP.
.PARAMETER pathzip
    Este parámetro es obligatorio. Es la ruta del archivo con el cual vamos a realizar alguna de las acciones.
.PARAMETER directorio
    Solo válido para los modos de compresión y descompresión. Indica el directorio a comprimir o el destino de la descompresión del archivo ZIP.
.PARAMETER descomprimir
    Indica que el modo a trabajar es el modo de descompresión.
.PARAMETER comprimir
    Indica que el modo a trabajar es el modo de compresión.
.PARAMETER informar
    Indica que el modo a trabajar es el modo de información.
.EXAMPLE 
    Para comprimir un directorio: 

    C:\PS> ejercicio4.ps1 -pathzip ./FotosDeGatos -comprimir -directorio ./backupDeLasFotosDeGatos/
.EXAMPLE 
    Para obtener información sobre un ZIP: 
    C:\PS> ejercicio4.ps1 -pathzip ./backupDeLasFotosDeGatos/FotosDeGatos.zip -informar
#>

Param (
    [Parameter(Position = 1, Mandatory = $true)]
    [ValidateNotNullOrEmpty()]
    [String] $pathzip,
    [Parameter(ParameterSetName="Unzip")]
    [Switch] $descomprimir,
    [Parameter(ParameterSetName="Zip")]
    [Switch] $comprimir,
    # Indicamos que el directorio es obligatorio para los parametersets zip y unzip
    [Parameter(Mandatory = $true, ParameterSetName="Zip")]
    [Parameter(Mandatory = $true, ParameterSetName="Unzip")]
    [String] $directorio,
    [Parameter(ParameterSetName="Informar")]
    [Switch] $informar
)
# Necesario para utilizar la clase zipfile
Add-Type -assembly "system.io.compression.filesystem"

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

function Descomprimir([String] $directorio) {
    if (ChequearDir($directorio)) {
        # Necesitamos hacer esto porque cuando enviamos un path no absoluto a un método de .NET
        # el mismo resuelve la dir del path en base al directorio de ejecución del proceso...
        $path = Resolve-Path $pathzip
        $directorio = Resolve-Path $directorio
        [IO.Compression.ZipFile]::ExtractToDirectory($path,$directorio)
        Write-Host "Archivo descomprimido en el directorio $directorio"
    }
}

function Comprimir([String] $directorio) {
    if (ChequearDir($directorio)) {
        $path = Resolve-Path $pathzip
        $directorio = Resolve-Path $directorio
        # Obtenemos el nombre de la carpeta donde estamos parados
        $filename = Split-Path $pathzip -Leaf
        # Y se lo añadimos al path del directorio, porque va a ser el nombre de nuestro archivo zip
        $directorio = "$directorio/$filename.zip"
        Write-Host $directorio

        try { 
            
            # Si queremos comprimir un directorio, y que el zip se guarde en el mismo directorio que estamos comprimiendo, tenemos
            # que hacer estos malabares
            [IO.Compression.ZipFile]::CreateFromDirectory($path,"$env:TEMP/$filename.zip")
            Move-Item "$env:TEMP/$filename.zip" $directorio -Force
            Write-Host "Archivo comprimido en el directorio $directorio"
        }
        catch [System.IO.IOException] {
            Write-Host $_
            Write-Host "Ocurrió un error del tipo IOException. ¿Ya existe al arhivo?"
        } 
    }
}

function Informar() {
    $currDir = Get-Location
    $dir = "$currDir$pathzip"
    [IO.Compression.ZipFile]::OpenRead($dir) | ForEach-Object { 
        $_.Entries | ForEach-Object {
           [long] $TotalCompressed = $null
           [long] $TotalSize = $null
       
           $TotalCompressed = $_.CompressedLength
           $TotalSize = $_.Length
          
           $obj = [pscustomobject]@{
                Archivo = $_
                PesoOrig = $TotalSize
                Ratio = "{0:P2}" -f (($TotalCompressed / $TotalSize))
           }
           $obj
       }
   } 
}

if (ChequearDir($pathzip)) {
    if ($descomprimir) {
        Descomprimir $directorio 
    } elseif ($comprimir) {
        Comprimir $directorio
    } elseif ($informar) {
        Informar
    }
    else {
        Write-Host "No se especifico ninguna accion."
    }
}
# =========================== Fin de archivo =======================