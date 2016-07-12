# invoke SourceDir generated makefile for Button_Hwi.pem3
Button_Hwi.pem3: .libraries,Button_Hwi.pem3
.libraries,Button_Hwi.pem3: package/cfg/Button_Hwi_pem3.xdl
	$(MAKE) -f C:\Users\user\workspace_v6_1\Button_Hwi/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\user\workspace_v6_1\Button_Hwi/src/makefile.libs clean

