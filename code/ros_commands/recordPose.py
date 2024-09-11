#!/usr/bin/env python
import rospy
import moveit_commander
import yaml
import os
import sys  # 添加這一行來導入 sys 模組
import argparse
from geometry_msgs.msg import PoseStamped

class ArmPoseRecorder:
    def __init__(self, yaml_file):
        # 初始化 ROS 節點
        rospy.init_node('arm_pose_recorder', anonymous=True)

        # 初始化 MoveIt Commander
        moveit_commander.roscpp_initialize(sys.argv)

        # 初始化 RobotCommander 和 PlanningSceneInterface
        self.robot = moveit_commander.RobotCommander()
        self.scene = moveit_commander.PlanningSceneInterface()

        # 初始化 MoveGroupCommander，這裡假設你的手臂 group 名稱是 "tmr_arm"
        self.group = moveit_commander.MoveGroupCommander("tmr_arm")

        # 設置 YAML 檔案路徑
        self.yaml_file = yaml_file
        # 檢查並創建目錄路徑
        directory = os.path.dirname(self.yaml_file)
        if not os.path.exists(directory):
            os.makedirs(directory)
            rospy.loginfo(f"創建目錄: {directory}")
        
        # 載入點位
        self.point_counter = self.load_existing_points()

    def load_existing_points(self):
        if os.path.exists(self.yaml_file):
            with open(self.yaml_file, 'r') as file:
                yaml_data = yaml.safe_load(file) or {}
                # 找到現有的點位中最大的號碼
                max_point = 0
                for key in yaml_data.keys():
                    if key.startswith('P'):
                        try:
                            point_num = int(key[1:])
                            max_point = max(max_point, point_num)
                        except ValueError:
                            pass
                return max_point + 1
        return 1

    def get_end_effector_pose(self):
        # 讀取末端執行器姿態
        pose = self.group.get_current_pose().pose
        return pose

    def record_pose(self):
        pose = self.get_end_effector_pose()
        if not pose:
            rospy.logerr("未能讀取末端執行器的姿態")
            return False

        point_name = f'P{self.point_counter}'
        data = {
            point_name: {
                'position': {
                    'x': pose.position.x,
                    'y': pose.position.y,
                    'z': pose.position.z,
                },
                'orientation': {
                    'x': pose.orientation.x,
                    'y': pose.orientation.y,
                    'z': pose.orientation.z,
                    'w': pose.orientation.w,
                }
            }
        }

        # 如果文件存在，打開並附加新點位；如果不存在，創建新文件
        if os.path.exists(self.yaml_file):
            with open(self.yaml_file, 'r') as file:
                yaml_data = yaml.safe_load(file) or {}
            yaml_data.update(data)
        else:
            yaml_data = data

        try:
            with open(self.yaml_file, 'w') as file:
                yaml.dump(yaml_data, file)
        except IOError:
            rospy.logerr(f"無法寫入到 {self.yaml_file}")
            return False

        rospy.loginfo(f"已記錄 {point_name} 到 {self.yaml_file}")
        self.point_counter += 1
        return True

    def run(self):
        rospy.loginfo("Arm Pose Recorder 已啟動。按下 Enter 鍵以記錄當前點位。")
        while not rospy.is_shutdown():
            input("按下 Enter 鍵以記錄當前點位：")
            if not self.record_pose():
                return False

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Record arm poses to a YAML file.')
    parser.add_argument('yaml_file', type=str, help='Path to the YAML file to store the poses.')
    args = parser.parse_args()

    recorder = ArmPoseRecorder(args.yaml_file)

    # 紀錄點位並檢查結果
    if recorder.record_pose():
        rospy.loginfo("run success")
        sys.exit(0)  # 成功
    else:
        rospy.logerr("run fail")
        sys.exit(1)  # 失敗
