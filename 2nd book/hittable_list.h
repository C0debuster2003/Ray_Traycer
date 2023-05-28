#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "AABB.h"

#include <memory>
#include <vector>
/*shared_ptr<type> is a pointer to some allocated type, with reference-counting semantics. Every time you
assign its value to another shared pointer (usually with a simple assignment), the reference count is
incremented. As shared pointers go out of scope (like at the end of a block or function), the reference
count is decremented. Once the count goes to zero, the object is deleted.*/

/*make_shared<thing>(thing_constructor_params ...) allocates a new instance of type thing, using the
constructor parameters. It returns a shared_ptr<thing>.*/
using std::make_shared;
using std::shared_ptr;

//only contains the declarations
//definitions are in a cpp file of the same name
class hittable_list : public hittable
{
public:
    hittable_list();
    hittable_list(shared_ptr<hittable> object);
    void clear();
    void add(shared_ptr<hittable> object);

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box)const override;

public:
    std::vector<shared_ptr<hittable>> objects;
};
#endif