# invoke SourceDir generated makefile for Clock_module.pem3
Clock_module.pem3: .libraries,Clock_module.pem3
.libraries,Clock_module.pem3: package/cfg/Clock_module_pem3.xdl
	$(MAKE) -f C:\Users\user\workspace_v6_1\Clock_module/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\user\workspace_v6_1\Clock_module/src/makefile.libs clean

