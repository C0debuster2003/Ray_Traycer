#pragma once
#include"rt_weekend.h"
#include"hittable.h"
#include"hittable_list.h"
#include<vector>
using namespace std;

class bvh_node:public hittable{
    public:
        bvh_node();
        bvh_node(const hittable_list& list, double time0, double time1);
        bvh_node(const vector<shared_ptr<hittable>>& src_objects, size_t start, size_t end, double time0, double time1);
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

    public:
        shared_ptr<hittable> left;
        shared_ptr<hittable> right;
        aabb box; 
};
inline bool box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b, int axis) {
    aabb box_a;
    aabb box_b;

    if (!a->bounding_box(0,0, box_a) || !b->bounding_box(0,0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.min().e[axis] < box_b.min().e[axis];
}
bool box_x_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b);
bool box_y_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b);
bool box_z_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b);