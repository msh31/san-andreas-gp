@echo off
:loop
sampctl p build
if errorlevel 1 goto end

echo.
echo Starting server... Press Ctrl+C to stop and rebuild
echo.

samp-server.exe

echo.
echo Server stopped. Press any key to rebuild and restart, or Ctrl+C to exit
pause > nul
goto loop

:end
echo Build failed!
pause
