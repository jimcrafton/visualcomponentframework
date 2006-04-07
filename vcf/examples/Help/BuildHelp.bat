@echo on
@if NOT EXIST Help MKDIR Help
@if NOT EXIST "Help\Help App.chm" hhc "Help App.hhp"
@cls