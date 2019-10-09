CXX = g++
LINKFLAG = -ldl -lpthread -lrt -lopencv_core -lpython2.7
INCFLAGS = -std=c++11 -I"/usr/include/opencv" -I"/usr/include/python2.7"
CXXFLAGS = -O3 --fast-math -msse2 

stl:
	$(CXX) $(INCFLAGS) stl.cpp -o stl $(LINKFLAG)
clean:
	rm stl
again:
	make clean
	make stl
# .c.o:
# 	$(CXX) $(INCFLAGS) $< -o $@ -c $(CXXFLAGS)

# .cpp.o:
# 	$(CXX) $(INCFLAGS) $< -o $@ -c $(CXXFLAGS)

# .cc.o:
# 	$(CXX) $(INCFLAGS) $< -o $@ -c $(CXXFLAGS)

# g++ -o l1qc_test l1qc_test.o -ldl -lpthread -lrt -lopencv_core
# g++ -o stl stl.o -ldl -lpthread -lrt -lopencv_core