C:
start /B SetTarg.bat
set location=C:\U4L\Snip\Controller
set projectname=ProjControllerQuick
set projectdirname=ProjControllerQuick
set configpostfix=Editor
set sniploc=C:\U4L\Snip
call %sniploc%\MyBuild.bat %projectname%%configpostfix% %location%\%projectdirname%\%projectname%
