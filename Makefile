NAME=erender
CXXFLAGS=-g -Wall
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX=g++

build: src/*
	$(CXX) $(CXXFLAGS) src/* -o $(NAME) $(LIBS)

run: $(NAME)
	./$(NAME)
