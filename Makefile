src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -Wall

prog: $(obj)
	$(CC) -g -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) myprog
