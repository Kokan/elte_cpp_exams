echo off
set errorlevel=

for %%s in (../*.cpp) do (
	
	echo|set /p=compile %%s
	
	del /F /Q a.exe  > NUL 2>&1
	g++ -Wall -o a.exe ../%%s > NUL 2>&1
	
	if not exist a.exe echo ......NOK
	if     exist a.exe echo ......OK
	
	if     exist a.exe (
		a.exe
	)

)

del /F /Q a.exe  > NUL 2>&1