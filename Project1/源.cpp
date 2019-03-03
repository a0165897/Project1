#include <fstream>
#include <iostream>
#include "Ray.h"
#include "float.h"
#include "HitShap.h"
#include "Camera.h"

#include <ctime>
#include <random>
std::default_random_engine reng(time(nullptr));
std::uniform_real_distribution<double> uni_dist(0.0f, 1.0f);

using namespace std;

vec3 radom_unit_sphere()
{
	vec3 p;

	do
	{
		p = 2.0 * vec3(uni_dist(reng), uni_dist(reng), uni_dist(reng)) - vec3(1.0f, 1.0f, 1.0f);

	} while (p.squared_length() >= 1.0);

	return p;
}

vec3 color(const ray& r, hitable* world)
{
	hit_record rec;
	if (world->hit(r, 0.0f, DBL_MAX, rec))
	{
		vec3 target = rec.p + rec.normal + radom_unit_sphere();
		return 0.5f * color(ray(rec.p, target - rec.p), world);
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		double t = 0.5f * (unit_direction.y() + 1.0);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}

}


int main()
{
	int nx = 600;
	int ny = 300;
	int ns = 64;

	ofstream fout("image.ppm");
	fout << "P3\n" << nx << " " << ny << "\n255\n";
	cout << "äÖÈ¾ÖÐ¡£¡£¡£¡£" << endl;

	hitable *list[3];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable* world = new hitable_list(list, 2);

	camera cam;

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}

			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99f * col[0]);
			int ig = int(255.99f * col[1]);
			int ib = int(255.99f * col[2]);

			fout << ir << " " << ig << " " << ib << "\n";
		}
	}
	cout << "äÖÈ¾Íê±Ï" << endl;
	fout.close();
	//system("Pause");
}
