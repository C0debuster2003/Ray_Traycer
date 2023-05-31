final.o: vec3.o Color.o Ray.o Camera.o hittable_list.o Perlin.o Texture.o Sphere.o Material.o MSphere.o AABB.o BVH.o AARect.o box.o hittable.o constant_medium.o img12.cpp
	g++ vec3.o Color.o Ray.o Camera.o hittable_list.o Perlin.o Texture.o Sphere.o Material.o MSphere.o AABB.o BVH.o AARect.o box.o hittable.o constant_medium.o img12.cpp

vec3.o: vec3.cpp
	g++ -c vec3.cpp

Color.o: Color.cpp vec3.o
	g++ -c Color.cpp

Ray.o: Ray.cpp Color.o
	g++ -c Ray.cpp

Camera.o : Camera.cpp vec3.o Ray.o
	g++ -c Camera.cpp
AABB.o: AABB.cpp vec3.o Ray.o
	g++ -c AABB.cpp
hittable.o: hittable.cpp AABB.o Ray.o
	g++ -c hittable.cpp
hittable_list.o: hittable_list.cpp hittable.o
	g++ -c hittable_list.cpp

Perlin.o: Perlin.cpp vec3.o hittable.o
	g++ -c Perlin.cpp

Texture.o: Texture.cpp Perlin.o hittable.o
	g++ -c Texture.cpp

Sphere.o: Sphere.cpp vec3.o Ray.o hittable.o
	g++ -c Sphere.cpp

Material.o: Material.cpp Texture.o hittable.o
	g++ -c Material.cpp
constant_medium.o: constant_medium.cpp hittable.o Material.o Texture.o
	g++ -c constant_medium.cpp
MSphere.o: MSphere.cpp hittable.o
	g++ -c MSphere.cpp

BVH.o: BVH.cpp hittable_list.o hittable.o
	g++ -c BVH.cpp

AARect.o: AARect.cpp hittable.o
	g++ -c AARect.cpp

box.o: box.cpp AARect.o hittable.o
	g++ -c box.cpp
clean:
	del *.o
