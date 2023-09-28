@echo off

if "%~1"=="" (
    echo error: save path is null!
    exit -1
)
if "%~2"=="" (
    echo error: audio extension is null!
    exit -2
)
if "%~3"=="" (
    echo error: url is null!
    exit -3
)

set path="%~1"
set ext=%~2
set url="%~3"

set size=50M
set count=1
set timeout=1

echo .......................................................................................
echo . Output path:.....................%path%
echo . Source URL:......................%url%
echo . Audio extension:................. %ext%
echo . Max source size:................. %size%
echo . Max count of sources:............ %count%
echo . Timeout:......................... %timeout%s
echo .......................................................................................

yt-dlp -o %path% --max-filesize %size% --max-downloads %count% --socket-timeout %timeout% --extract-audio --audio-format %ext%  %url%

:end