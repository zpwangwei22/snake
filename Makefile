src=snake.c lib.c
obj=$(patsubst %.c, %.o, $(src))

cc=gcc

All:snake
snake:$(obj)
	$(cc) $^ -o $@
%.o:%.c
	$(cc) -c $< -o $@
clean:
	-rf -rm $(obj) snake

