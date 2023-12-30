# ----------------------------------------------------------------------------
# <copyright company="Michael Koster">
#   Copyright (c) Michael Koster. All rights reserved.
#   Licensed under the MIT License.
# </copyright>
# ----------------------------------------------------------------------------
# Creates the Sparse Package MSIX for Win32ConsoleCom
# ----------------------------------------------------------------------------

# Use the tools from the Windows 11 SDK
$windowsSdk = "${env:ProgramFiles(x86)}\Windows Kits\10\bin\10.0.22000.0\x64"
$makepri = Join-Path $windowsSdk -ChildPath "makepri.exe" 
$makeAppx = Join-Path $windowsSdk -ChildPath "MakeAppx.exe"
$signTool = Join-Path $windowsSdk -ChildPath "SignTool.exe"

# compile target paths
$scriptDir = Split-Path -Parent $PSCommandPath
$projectRoot = Join-Path $scriptDir -ChildPath "..\Win32Console.SparsePackage"
$msixTarget = Join-Path $scriptDir -ChildPath "..\x64\Debug\Win32ConsoleSparsePackage.msix"
$certFile = Join-Path $scriptDir -ChildPath "..\..\eng\DevCert.pfx"


# Generate resource pack
&$makePri new /ConfigXml $scriptDir\priconfig.xml /ProjectRoot $projectRoot /OutputFile $projectRoot /Overwrite

# Create the MSIX package
&$makeAppx pack /d $projectRoot /p $msixTarget /nv /o

# Sign the MSIX package
$credentials = Get-Credential -User "PFX File" -Message "Enter password for PFX file"
$BSTR = [System.Runtime.InteropServices.Marshal]::SecureStringToBSTR($credentials.Password)
$password = [System.Runtime.InteropServices.Marshal]::PtrToStringAuto($BSTR)
[Runtime.InteropServices.Marshal]::ZeroFreeBSTR($BSTR)
&$signTool sign /fd SHA256 /a /f $certFile /p $password $msixTarget