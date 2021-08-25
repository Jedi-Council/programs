@echo off

echo "Creating project %1 ..."

echo "Entering projects directory"
cd projects

echo "Creating folder structure" 
mkdir %1
cd %1

mkdir drivers
mkdir include
mkdir src
mkdir build

echo "Copying Makefile and configuration files from resources"
xcopy ..\..\resources\Makefile 
xcopy ..\..\resources\stm32f10x_conf.h .\include\ 
xcopy ..\..\resources\main.h .\include\ 
xcopy ..\..\resources\main.c .\src\ 

echo "leaving projects directory"
cd ..\..	

