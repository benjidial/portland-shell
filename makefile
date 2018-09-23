shell:
	mkdir part out
	gcc -nostdinc -m32 -o part/shell.obj -c shell.c
	objcopy -j .text -O binary part/shell.obj out/shell

clean:
	rm -r part out
