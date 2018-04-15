CC	=	gcc
CXX	=	g++
RM	=	rm -f

CXXFLAGS	=	-std=c++11

#Generates KNN exectuble file unifying class and main function object codes
knn: knn.o Instance.o
	$(CXX) knn.o Instance.o -o knn

#Generates KNN (main function) object code
knn.o: src/knn.cpp
	$(CXX) -c $(CXXFLAGS) src/knn.cpp

#Generates Instance (class) object code
Instance.o: src/Instance.cpp inc/Instance.hpp
	$(CXX) -c src/Instance.cpp

clean:
	$(RM) *.o knn
