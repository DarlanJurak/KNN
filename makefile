CC	=	gcc
CXX	=	g++
RM	=	rm -f

CXXFLAGS	=	-std=c++11



#Generates KNN exectuble file unifying class and main function object codes
knn: knn.o Sample.o
	$(CXX) knn.o Sample.o -o knn

#Generates KNN (main function) object code
knn.o: src/knn.cpp
	$(CXX) -c $(CXXFLAGS) src/knn.cpp

#Generates Sample (class) object code
Sample.o: src/Sample.cpp inc/Sample.hpp
	$(CXX) -c src/Sample.cpp

clean:
	$(RM) *.o knn
