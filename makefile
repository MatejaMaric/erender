cpprender: source/*
#cd object_files
	g++ -g -c source/*
#cd ..
	mv *\.o object_files/
	g++ object_files/* -o cpprender -lsfml-graphics -lsfml-window -lsfml-system
	rm source/*gch

run: cpprender
	./cpprender
