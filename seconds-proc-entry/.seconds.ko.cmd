savedcmd_/home/l3002/OSPractice/seconds-proc-entry/seconds.ko := ld -r -m elf_x86_64 -z noexecstack --no-warn-rwx-segments --build-id=sha1  -T scripts/module.lds -o /home/l3002/OSPractice/seconds-proc-entry/seconds.ko /home/l3002/OSPractice/seconds-proc-entry/seconds.o /home/l3002/OSPractice/seconds-proc-entry/seconds.mod.o;  make -f ./arch/x86/Makefile.postlink /home/l3002/OSPractice/seconds-proc-entry/seconds.ko
