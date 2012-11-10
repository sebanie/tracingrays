CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
CFLAGS = -g -DGL_GLEXT_PROTOTYPES -DOSX
INCFLAGS = -I./glm-0.9.2.7 -I/usr/X11/include -I./include/
LDFLAGS = -framework GLUT -framework OpenGL -L./osxlib/ \
		-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
		-lGL -lGLU -lm -lstdc++ -lfreeimage
else
CFLAGS = -g -DGL_GLEXT_PROTOTYPES 
INCFLAGS = -I./glm-0.9.2.7 -I./include/ -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib \
		-L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lglut -lGLU -lGL -lX11 -lfreeimage
endif

RM = /bin/rm -f 
all: raytrace
raytrace: test.o Film.o Camera.o Direction.o Point.o Ray.o Sample.o Sampler.o Scene.o
	$(CC) $(CFLAGS) -o raytrace test.o Film.o Camera.o Direction.o Point.o Ray.o Sample.o Sampler.o Scene.o $(INCFLAGS) $(LDFLAGS) 
test.o: test.cpp Color.h Film.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c test.cpp
Intersect.h: Scene.h
Triangle.h: Shape.h
Scene.o: Scene.cpp Ray.h Sample.h Sampler.h Point.h Direction.h Color.h Film.h Camera.h Intersect.h Shape.h Triangle.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Scene.cpp 
Film.o: Film.cpp Film.h Color.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Film.cpp
Camera.o: Camera.cpp Camera.h Sample.h Ray.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Camera.cpp
Direction.o: Direction.cpp 
	$(CC) $(CFLAGS) $(INCFLAGS) -c Direction.cpp
Point.o: Point.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c Point.cpp
Ray.o: Ray.cpp Point.h Direction.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Ray.cpp
Sample.o: Sample.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sample.cpp
Sampler.o: Sampler.cpp Sample.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sampler.cpp
clean: 
	$(RM) *.o raytrace *.png


 
