final.o: vec3.o Color.o Ray.o Camera.o hittable_list.o Perlin.o Texture.o Sphere.o Material.o MSphere.o AABB.o BVH.o AARect.o img8.cpp
	g++ vec3.o Color.o Ray.o Camera.o hittable_list.o Perlin.o Texture.o Sphere.o Material.o MSphere.o AABB.o BVH.o AARect.o img8.cpp

vec3.o: vec3.cpp
	g++ -c vec3.cpp

Color.o: Color.cpp vec3.o
	g++ -c Color.cpp

Ray.o: Ray.cpp Color.o
	g++ -c Ray.cpp

Camera.o : Camera.cpp vec3.o Ray.o
	g++ -c Camera.cpp

hittable_list.o: hittable_list.cpp
	g++ -c hittable_list.cpp

Perlin.o: Perlin.cpp vec3.o
	g++ -c Perlin.cpp

Texture.o: Texture.cpp Perlin.o
	g++ -c Texture.cpp

Sphere.o: Sphere.cpp vec3.o Ray.o
	g++ -c Sphere.cpp

Material.o: Material.cpp Texture.o
	g++ -c Material.cpp

MSphere.o: MSphere.cpp
	g++ -c MSphere.cpp

BVH.o: BVH.cpp hittable_list.o
	g++ -c BVH.cpp

AABB.o: AABB.cpp vec3.o Ray.o
	g++ -c AABB.cpp

AARect.o: AARect.cpp
	g++ -c AARect.cpp

clean:
	del *.o