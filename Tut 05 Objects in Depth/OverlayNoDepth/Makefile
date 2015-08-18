EXE=OverlapNoDepth
INCLUDE=-I../..
OBJ=*.cc ../../framework/*.cc
CXX_FLAG= -std=c++11

$(EXE):$(OBJ)
	g++ $(INCLUDE) $(OBJ) $(CXX_FLAG) -framework OpenGL -framework GLUT  -lglfw3 -o $@

clean:
	rm $(EXE)
