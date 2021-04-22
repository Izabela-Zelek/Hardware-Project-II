ECHO OFF
REM *************************************************************************
REM SAMPLE IF EDITING WITH ECLIPSE AND AVR PLUGIN INSTALLED 
REM THIS WAS SETUP WITH WINAVR, STARTER KIT PROJECT IS BASED ON AVR TOOLCHAIN
REM 
REM SET THE DEFAULT DIRECTORY
REM IF RUNNING FROM A USB STICK SET TO THE e.g. E: or F: depending on
REM directory location allocated on your computer
REM If the a network directory use e.g. N: or N:\uzebox
REM %cd% will default it to present working directory
REM
REM Ensure JAVA_HOME has been set within environmental settings
REM
REM *************************************************************************
SET DDIR=%cd%

REM *************************************************************************
REM Set HOME variable for EGIT
REM *************************************************************************
SET HOME=%USERPROFILE%

REM *************************************************************************
REM Set PATH
REM *************************************************************************
SET PATH=%PATH%;%JAVA_HOME%;
%DDIR%\devtools\WinAVR-20100110\bin;%DDIR%\devtools\WinAVR-20100110\utils\bin

REM *************************************************************************
REM Setup project directory and location of UZEBOX Kernel and required
REM include files
REM *************************************************************************
SET UZEBOX_PROJECTS=%DDIR%\projects
SET UZEBOX_EMULATOR_LOC=%DDIR%\devtools\uzem_win32-v2.0.0

REM *************************************************************************
REM Set Include PATHS
REM *************************************************************************
SET UZEBOX_KERNEL_DIR=%DDIR%/uzebox-master/kernel
SET "UZEBOX_KERNEL_DIR=%UZEBOX_KERNEL_DIR:\=/%"

SET AVR_INCLUDE_DIR=%DDIR%/devtools/WinAVR-20100110/avr/include
SET "AVR_INCLUDE_DIR=%AVR_INCLUDE_DIR:\=/%"

SET AVR_GCC_INCLUDE_DIR=%DDIR%/devtools/WinAVR-20100110/lib/gcc/avr/4.3.3/include
SET "AVR_GCC_INCLUDE_DIR=%AVR_GCC_INCLUDE_DIR:\=/%"

REM *************************************************************************
REM Registry Edit
REM *************************************************************************

REM REGEDIT4

REM ; @ECHO OFF
REM ; CLS
REM ; REGEDIT.EXE /S "%~f0"
REM ; EXIT

REM [HKEY_CURRENT_USER\Software\Test]
REM "val"="test"

REM *************************************************************************
REM Start eclipse and set workspace to location of UZEBOX projects
REM *************************************************************************
START %DDIR%\devtools\eclipse\eclipse.exe -data %UZEBOX_PROJECTS%

REM *************************************************************************
REM Start Emulator
REM *************************************************************************
REM SET DEBUG=-d
REM START %DDIR%\devtools\uzem_win32-v2.0.0\uzem.exe %UZEBOX_PROJECTS%\StarterKit\default\StarterKit.hex
REM *************************************************************************

ECHO ON
echo PATH
echo %PATH%
echo JAVA_HOME
echo %JAVA_HOME%
echo UZEBOX_PROJECTS
echo %UZEBOX_PROJECTS% 
echo UZEBOX_KERNEL_DIR 
echo %UZEBOX_KERNEL_DIR% 
echo AVR_INCLUDE_DIR 
echo %AVR_INCLUDE_DIR% 
echo AVR_GCC_INCLUDE_DIR
echo %AVR_GCC_INCLUDE_DIR%
ECHO OFF
