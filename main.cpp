#include "header.h"
#include <iostream>
#include <cstdlib>  // 用于rand()
#include <ctime>    // 用于time()

// 创建一个数组来存储100个点
float points[100][3];

//float stable_point[25][3];

void point_create()
{
    // 初始化随机数生成器
    std::srand(std::time(0));
    for (int i = 0; i < 100; ++i) {
        float x = static_cast<float>(std::rand()) / RAND_MAX * 15.0f - 100.0f;
        float y = static_cast<float>(std::rand()) / RAND_MAX * 10.0f - 500.0f;
        float z = static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 10.0f;
        points[i][0] = x;
        points[i][1] = y;
        points[i][2] = z;

    }
    //手动修改三个point值，模拟异常点
    points[14][0] = 2000.0f;
    points[24][1] = 2000.0f;
    points[30][2] = 19.0f;
}


int main() {


    relocalization::Relocalization relocalization;
    point_create();
    relocalization::AbruptChangeDetector detector(points[0][0], points[0][1], points[0][2], 10.0f);



    // 创建100个点并处理
    for (int i = 0;i<100;i++) {
        float x= points[i][0];
        float y= points[i][1];
        float z= points[i][2];

        bool relocalization_flag = relocalization.miss_detect(x, y, z)&&detector.detectAbruptChange(x, y, z);
        if (relocalization_flag) {
            relocalization.add_point(x, y, z);

            std::cout << "Added point: (" << x << ", " << y << ", " << z << ")" << std::endl;
        } else {
            std::cout << "Point out of range(" << x << ", " << y << ", " << z << ")"<< std::endl;
            float first_x, first_y, first_z;
            relocalization.Relocalize(first_x, first_y, first_z);
            points[i][0] = first_x;
            points[i][1] = first_y;
            points[i][2] = first_z;
            std::cout << "Assigned first point: (" << first_x << ", " << first_y << ", " << first_z << ")" << std::endl;
            std::cout << "Successfully relocalize! "<<std::endl;
        }
    }



    return 0;
}
