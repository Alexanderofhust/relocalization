#ifndef INC_1_HEADER_H
#define INC_1_HEADER_H

#include <array>
#include <vector>

namespace relocalization {

    class Relocalization {
    private:
        std::array<std::array<float, 3>, 50> stable_points;  // 一个50*3的float数组，用来存放50个点坐标
        int index;  // 当前数组中的点数

    public:
        Relocalization();  // 构造函数

        bool miss_detect(float x, float y, float z) const;  // 检测x值是否在-500到500，检测y值是否在-500到500，检测z值是否在-10到10，如果三个值都满足，则返回true，否则返回false

        void add_point(float x, float y, float z);  // 如果数组行数小于50，则添加新的点，否则删除数组的第一行，并将新的点添加到最后一行

        void Relocalize(float& current_x, float& current_y, float& current_z) const;  // 将数组的第一行赋给当前点，不进行数组更新
    };

    class AbruptChangeDetector {
    private:
        float lastX, lastY, lastZ; // 上一次的XYZ坐标值
        float threshold;          // 导数值的上限

    public:
        // 构造函数
        AbruptChangeDetector(float initX, float initY, float initZ, float initThreshold);

        // 检测导数是否过大的方法
        bool detectAbruptChange(float x, float y, float z);

        // 设置新的阈值
        void setThreshold(float newThreshold);

        // 获取当前阈值
        float getThreshold() const;
    };

}

#endif //INC_1_HEADER_H
