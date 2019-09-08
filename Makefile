all:
	gcc backdoor.c -o backdoor 

clean:
	sudo rm -rf backdoor
