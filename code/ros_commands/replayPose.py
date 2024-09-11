#!/usr/bin/env python
import rospy
import moveit_commander
import yaml
import sys
import argparse
import os
from geometry_msgs.msg import Pose
from math import isclose

class ArmPoseReplayer:
    def __init__(self, yaml_file):
        # 初始化 ROS 節點
        rospy.init_node('arm_pose_replayer', anonymous=True)

        # 初始化 MoveIt Commander
        moveit_commander.roscpp_initialize(sys.argv)

        # 初始化 RobotCommander 和 PlanningSceneInterface
        self.robot = moveit_commander.RobotCommander()
        self.scene = moveit_commander.PlanningSceneInterface()

        # 初始化 MoveGroupCommander，這裡假設你的手臂 group 名稱是 "tmr_arm"
        self.group = moveit_commander.MoveGroupCommander("tmr_arm")

        # 設置位置和姿態的容忍度
        self.group.set_goal_position_tolerance(0.01)  # 位置容忍度
        self.group.set_goal_orientation_tolerance(0.01)  # 姿態容忍度

        # 載入 YAML 檔案
        self.yaml_file = yaml_file
        self.poses = self.load_poses()

    def load_poses(self):
        # 載入 YAML 檔案中的所有點位
        if not os.path.exists(self.yaml_file):
            rospy.logerr(f"YAML 文件 {self.yaml_file} 不存在")
            return None
        
        with open(self.yaml_file, 'r') as file:
            yaml_data = yaml.safe_load(file)
        
        if not yaml_data:
            rospy.logerr(f"YAML 文件 {self.yaml_file} 是空的或格式錯誤")
            return None
        
        return yaml_data

    def get_current_pose(self):
        # 獲取當前機械手臂的姿態
        return self.group.get_current_pose().pose

    def is_pose_reached(self, target_pose):
        current_pose = self.get_current_pose()

        return (
            isclose(current_pose.position.x, target_pose.position.x, abs_tol=0.01) and
            isclose(current_pose.position.y, target_pose.position.y, abs_tol=0.01) and
            isclose(current_pose.position.z, target_pose.position.z, abs_tol=0.01) and
            isclose(current_pose.orientation.x, target_pose.orientation.x, abs_tol=0.01) and
            isclose(current_pose.orientation.y, target_pose.orientation.y, abs_tol=0.01) and
            isclose(current_pose.orientation.z, target_pose.orientation.z, abs_tol=0.01) and
            isclose(current_pose.orientation.w, target_pose.orientation.w, abs_tol=0.01)
        )

    def move_to_pose(self, pose_data):
        pose = Pose()
        pose.position.x = pose_data['position']['x']
        pose.position.y = pose_data['position']['y']
        pose.position.z = pose_data['position']['z']
        pose.orientation.x = pose_data['orientation']['x']
        pose.orientation.y = pose_data['orientation']['y']
        pose.orientation.z = pose_data['orientation']['z']
        pose.orientation.w = pose_data['orientation']['w']

        self.group.set_pose_target(pose)
        self.group.set_planning_time(10.0)  # 設置規劃時間
        success = self.group.go(wait=True)
        self.group.stop()
        self.group.clear_pose_targets()

        if success:
            rospy.loginfo("成功移動到指定姿態")
        else:
            rospy.logerr("移動到指定姿態失敗")

        # 等待機械手臂到達目標位置
        while not rospy.is_shutdown() and not self.is_pose_reached(pose):
            rospy.sleep(0.1)

    def replay_poses(self):
        if not self.poses:
            return
        
        for pose_name, pose_data in self.poses.items():
            rospy.loginfo(f"正在移動到 {pose_name}")
            self.move_to_pose(pose_data)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Replay arm poses from a YAML file.')
    parser.add_argument('yaml_file', type=str, help='Path to the YAML file with the poses.')
    args = parser.parse_args()

    replayer = ArmPoseReplayer(args.yaml_file)

    # 確保只調用一次 replay_poses
    if replayer.poses:
        replayer.replay_poses()
