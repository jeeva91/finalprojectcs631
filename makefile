senddir: testsenddir.o senddir.o
	cc testsenddir.o senddir.o
senddir.o: senddir.c final.h
	cc -c senddir.c
testsenddir.o: testsenddir.c final.h
	cc -c testsenddir.c

sendfile: testsend.o sendfile.o
	cc testsend.o sendfile.o
testsend.o: testsend.c final.h
	cc -c testsend.c
sendfile.o: sendfile.c final.h
	cc -c sendfile.c
clean:
	rm *.o
