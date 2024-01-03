#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable.h"
#include "color.h"

class material
{
public:
    virtual ~material() = default;

    virtual bool scatter(const ray &in, const hit_record &rec, color &attenuation, ray &scattered) const = 0;
};

class lambertian : public material
{

private:
    color albedo;

public:
    lambertian(const color &a) : albedo(a) {}
    bool scatter(const ray &in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        vec3 scatter_direction = rec.normal + random_in_unit_sphere();

        // catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

class metal : public material
{
private:
    color albedo;

public:
    metal(const color &a) : albedo(a) {}
    bool scatter(const ray &in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        vec3 reflected = reflect(unit_vector(in.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return true;
    }
};
#endif // MATERIAL_H
