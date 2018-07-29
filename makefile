shell:
	mkdir part out
	gcc -o part/shell.obj shell.c
	objcopy -O binary part/shell.obj out/shell
