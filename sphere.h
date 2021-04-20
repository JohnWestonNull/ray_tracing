//
// Created by john on 2021/4/15.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include <utility>

#include "vec3.h"
#include "hittable.h"
class material;
class sphere : public hittable {
public:
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;

    sphere() = default;
    sphere(point3 c, double r, shared_ptr<material> m) : center(c), radius(r), mat_ptr(std::move(m)) {};

    bool hit(
            const ray &r, double t_min, double t_max, hit_record &rec
    ) const override;
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);
    // as early as possible
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    return true;
}

#endif //RAY_TRACING_SPHERE_H
