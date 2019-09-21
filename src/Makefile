CXX = g++
LINKFLAG = -ldl -lpthread -lrt -lopencv_core
INCFLAGS = -I"usr/include/opencv"
CXXFLAGS = -O3 --fast-math -msse2 

stl:
	$(CXX) -o stl stl.o $(LINKFLAG)
clean:
	rm stl
# .c.o:
# 	$(CXX) $(INCFLAGS) $< -o $@ -c $(CXXFLAGS)

# .cpp.o:
# 	$(CXX) $(INCFLAGS) $< -o $@ -c $(CXXFLAGS)

# .cc.o:
# 	$(CXX) $(INCFLAGS) $< -o $@ -c $(CXXFLAGS)

# g++ -o l1qc_test l1qc_test.o -ldl -lpthread -lrt -lopencv_core
# g++ -o stl stl.o -ldl -lpthread -lrt -lopencv_core