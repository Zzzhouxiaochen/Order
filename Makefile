FLAGS=-std=c++11 -L/usr/lib64/mysql -lmysqlclient -ljsoncpp -lpthread -g 


.PHONY:all all:db_test 
 
db_test:db_test.cc db.hpp  
	g++ db_test.cc -o db_test $(FLAGS) 

main:main.cc
	g++ main.cc -lpthread -std=c++11

.PHONY:clean 
clean:  
	rm db_test