#include "header.h"
#include <iostream>
#include <cmath>

namespace relocalization {

    Relocalization::Relocalization() : index(0) {
        // 初始化数组
        for (auto &point: stable_points) {
            point.fill(0.0f);
        }
    }

    bool Relocalization::miss_detect(float x, float y, float z) const {
        // 检查点是否在指定范围内,给离群检测托底
        return (x >= -500 && x <= 500) &&
               (y >= -500 && y <= 500) &&
               (z >= -10 && z <= 10);
    }

    void Relocalization::add_point(float x, float y, float z) {
        if (index < 25) {
            stable_points[index][0] = x;
            stable_points[index][1] = y;
            stable_points[index][2] = z;
            index++;
        } else {
            // 移动数组元素，丢弃最早的点
            std::cout << "array is full,delete points: (" << stable_points[0][0] << ", " << stable_points[0][1] << ", "
                      << stable_points[0][2] << "), new points: (" << x << ", " << y << ", " << z << ")" << std::endl;

            for (int i = 0; i < 49; ++i) {
                stable_points[i] = stable_points[i + 1];
            }
            stable_points[49][0] = x;
            stable_points[49][1] = y;
            stable_points[49][2] = z;
        }
    }

    void Relocalization::Relocalize(float &current_x, float &current_y, float &current_z) const {
        if (index > 0) {
            current_x = stable_points[0][0];
            current_y = stable_points[0][1];
            current_z = stable_points[0][2];
        } else {
            // 如果没有点，可以设置默认值或抛出异常
            current_x = 0.0f;
            current_y = 0.0f;
            current_z = 0.0f;
        }
    }


    // 构造函数实现
    AbruptChangeDetector::AbruptChangeDetector(float initX, float initY, float initZ, float initThreshold)
            : lastX(initX), lastY(initY), lastZ(initZ), threshold(initThreshold) {}

// 检测导数是否过大的方法实现
    bool AbruptChangeDetector::detectAbruptChange(float x, float y, float z) {
        // 计算导数（变化率）
        float dx = x - lastX;
        float dy = y - lastY;
        float dz = z - lastZ;

        // 检查导数是否超过阈值
        if (std::fabs(dx) > threshold || std::fabs(dy) > threshold || std::fabs(dz) > threshold) {
            // 如果导数过大，更新lastX, lastY, lastZ为当前值，并返回0
            lastX = x;
            lastY = y;
            lastZ = z;
            return false; // 导数过大，认为是离群值
        } else {
            // 如果导数未超过阈值，只更新lastX, lastY, lastZ为当前值，并返回1
            lastX = x;
            lastY = y;
            lastZ = z;
            return true; // 导数未超过阈值，不是离群值
        }
    }

// 设置新的阈值的实现
    void AbruptChangeDetector::setThreshold(float newThreshold) {
        threshold = newThreshold;
    }

// 获取当前阈值的实现
    float AbruptChangeDetector::getThreshold() const {
        return threshold;
    }

}