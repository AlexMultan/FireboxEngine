@echo off
vendor\bin\premake\premake5.exe gmake
if exist Build\gmake\compile_commands.json (
    copy /Y Build\gmake\compile_commands.json .
)
PAUSE