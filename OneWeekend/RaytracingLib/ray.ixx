export module RaytracingLib:ray;

import :algebra;

// public view of the module
export namespace RaytracingLib {

    class ray final {
    public:
        ray() = default;

        ray(const point3& origin, const vec3& direction)
            : orig(origin), dir(direction)
        {}

        point3 origin() const { return orig; }
        vec3 direction() const { return dir; }

        point3 at(double t) const {
            return orig + t * dir;
        }

    public:
        point3 orig;
        vec3 dir;
    };
}