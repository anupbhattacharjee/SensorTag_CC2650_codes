## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,em3 linker.cmd package/cfg/Timer_Hwi_swi_pem3.oem3

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/Timer_Hwi_swi_pem3.xdl
	$(SED) 's"^\"\(package/cfg/Timer_Hwi_swi_pem3cfg.cmd\)\"$""\"C:/Users/user/workspace_v6_1/Timer_Hwi_swi/Debug/configPkg/\1\""' package/cfg/Timer_Hwi_swi_pem3.xdl > $@
	-$(SETDATE) -r:max package/cfg/Timer_Hwi_swi_pem3.h compiler.opt compiler.opt.defs
