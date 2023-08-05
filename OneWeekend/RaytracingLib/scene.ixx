module;

#include <cmath>
#include <memory>

export module RaytracingLib:scene;

import :algebra;
import :hittable;
import :material;
import :sphere;
import :ray;

// public view of the module
export namespace RaytracingLib {

    hittable_list random_scene() {
        using namespace std;

        hittable_list world;

        auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
        world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

        for (int a = -11; a < 11; a++) {
            for (int b = -11; b < 11; b++) {
                auto choose_mat = random_double();
                point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

                if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                    shared_ptr<material> sphere_material;

                    if (choose_mat < 0.8) {
                        // diffuse
                        auto albedo = color::random() * color::random();
                        sphere_material = make_shared<lambertian>(albedo);
                        world.add(make_shared<sphere>(center, 0.2, sphere_material));
                    }
                    else if (choose_mat < 0.95) {
                        // metal
                        auto albedo = color::random(0.5, 1);
                        auto fuzz = random_double(0, 0.5);
                        sphere_material = make_shared<metal>(albedo, fuzz);
                        world.add(make_shared<sphere>(center, 0.2, sphere_material));
                    }
                    else {
                        // glass
                        sphere_material = make_shared<dielectric>(1.5);
                        world.add(make_shared<sphere>(center, 0.2, sphere_material));
                    }
                }
            }
        }

        auto material1 = make_shared<dielectric>(1.5);
        world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

        auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
        world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

        auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
        world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

        return world;
    }
}
