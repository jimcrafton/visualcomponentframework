REM CommandInterpreter: $(COMSPEC)
bcc32 -tWD -tWM -c SimpleDLL.cpp
ilink32 -aa -tpd -Gn -Gi c0d32.obj SimpleDLL.obj,SimpleDLL.so,,import32.lib cw32mti.lib,simpledll.def,
cls
