all:
	sudo cp ./get_proc_info.h /usr/include
	gcc -shared -fpic get_proc_info.c -o libget_proc_info.so
	sudo cp ./libget_proc_info.so /usr/lib
	gcc  wrapper.c -lget_proc_info -o wrapper
	./wrapper
	rm libget_proc_info.so
	rm wrapper
