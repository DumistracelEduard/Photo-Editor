#314CA_Dumistracel_Eduard_Costin
CC=gcc
CFLAGS=-Wall -Wextra -lm -std=c99

# define targets
TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c save.c default.c load.c select.c image_process.c rotate.c
	$(CC)  $(CFLAGS) image_editor.c save.c default.c load.c select.c image_process.c rotate.c -o image_editor -lm

pack:
	zip -FSr 3XYCA_FirstnameLastname_Tema1.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean