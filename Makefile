src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -wall

prog: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) myprog
