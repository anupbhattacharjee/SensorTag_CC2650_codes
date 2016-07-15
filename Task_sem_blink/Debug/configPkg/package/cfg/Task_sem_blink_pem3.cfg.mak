# invoke SourceDir generated makefile for Task_sem_blink.pem3
Task_sem_blink.pem3: .libraries,Task_sem_blink.pem3
.libraries,Task_sem_blink.pem3: package/cfg/Task_sem_blink_pem3.xdl
	$(MAKE) -f C:\Users\user\workspace_v6_1\Task_sem_blink/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\user\workspace_v6_1\Task_sem_blink/src/makefile.libs clean

