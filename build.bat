:: dont echo, dont echo the echo. https://youtu.be/Ee3EtYb8d1o?si=59PK5V42msxIO0-E&t=1355
@echo off 
:: clear screen
cls

:: make directory
::if not exist executables (
 ::   mkdir executables
::)

:: push directory
pushd  executables

:: the -Zi switch make it so debug info is generated as well https://youtu.be/Ee3EtYb8d1o?si=lO9-bJeU9AM2UzRI&t=2531
cl -Zi ..\%1 user32.lib Gdi32.lib
:: pop directory
popd