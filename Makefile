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
raytrace: test.o Film.o Camera.o Direction.o Point.o Ray.o RayTracer.o Sample.o Sampler.o Scene.o Shape.o PointLight.o DirLight.o
	$(CC) $(CFLAGS) -o raytrace test.o Film.o Camera.o Direction.o Point.o Ray.o RayTracer.o Sample.o Sampler.o Scene.o Shape.o PointLight.o DirLight.o $(INCFLAGS) $(LDFLAGS) 
test.o: test.cpp Color.h Film.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c test.cpp
RayTracer.h: Scene.h
Intersect.h: Scene.h
Triangle.h: Shape.h
Sphere.h: Shape.h
Scene.o: Scene.cpp Ray.h RayTracer.h Sample.h Sampler.h Point.h Direction.h Color.h Film.h Camera.h Intersect.h Shape.h Triangle.h Sphere.h
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
RayTracer.o: RayTracer.cpp Scene.h Color.h Intersect.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c RayTracer.cpp
Sample.o: Sample.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sample.cpp
Sampler.o: Sampler.cpp Sample.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sampler.cpp
PointLight.o: PointLight.cpp Light.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c PointLight.cpp
DirLight.o: DirLight.cpp Light.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c DirLight.cpp
Shape.o: Shape.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c Shape.cpp
clean: 
	$(RM) *.o raytrace *.png


 
