export module hittable;

import algebra;
import ray;

export struct hit_record {
    point3 p;
    vec3 normal;
    double t;
};

export class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};