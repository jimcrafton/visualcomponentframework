@echo off
@if exist HHCtrl.obj del HHCtrl.obj
@if exist HtmlHelp.lib del HtmlHelp.lib
@bcc32 -tWD -6 -v- -O2 -a8 -DWIN32;_LIB -c HHctrl.c 
@tlib HtmlHelp.lib /a HHCtrl.obj