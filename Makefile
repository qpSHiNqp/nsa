all:
	cd client; make
	cd server; make

client:
	cd client; make

server:
	cd server; make

clean:
	cd client; make clean
	cd server; make clean

