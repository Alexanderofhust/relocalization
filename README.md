# 重定位demo

* 面对的问题:LIO
  机器人在连续运动中，在某一处出现碰撞、下台阶等剧烈运动场景，陀螺仪出现较大积分误差，而雷达帧未及时更新，导致LIO更新出错，最邻近匹配出现比较大的误差且无法修正的情景

* 市面上已有的解决办法：
  * 全局重定位global relocalization:模板按层次进行聚类，并用于构建由位置敏感哈希 （LSH） 和 k 维树 （KD 树） 组成的最近邻搜索引擎。在在线匹配阶段，充分利用描述符的属性、模板之间的层次结构以及最近邻搜索引擎，例如
    [基于 3D LiDAR 的导航系统的实时全局重新定位框架](https://www.mdpi.com/1424-8220/24/19/6288)
    优点：鲁棒性强，且 由粗到精的重定位对NUC算力友好
    不足：实现较为困难（指缝合到现有代码里），且未经测试，不知道在现有场景下是否适用
* 本demo的实现方法
  * 第一阶段，进行离群值检验与运动范围校准
* tips：
  1. 只对雷达帧进行检验，降低算力负荷
  2. 匹配的实现可以依赖已有的最近邻搜索算法，也可以针对当前情景进行特别的搜索（例如由粗到精）

* TODO：
  1. 部署到已有的算法中，并使用Eigen库替代当前的点坐标，测试参数
  2. 实现更鲁棒的全局重定位
  3. 考虑如何将fast-livo 的视觉信息纳入本demo