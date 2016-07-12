# invoke SourceDir generated makefile for Timer_Hwi_swi.pem3
Timer_Hwi_swi.pem3: .libraries,Timer_Hwi_swi.pem3
.libraries,Timer_Hwi_swi.pem3: package/cfg/Timer_Hwi_swi_pem3.xdl
	$(MAKE) -f C:\Users\user\workspace_v6_1\Timer_Hwi_swi/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\user\workspace_v6_1\Timer_Hwi_swi/src/makefile.libs clean

