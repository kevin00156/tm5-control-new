#!/usr/bin/env python
import rospy
from tm_msgs.srv import SetIO, SetIORequest
import time
import argparse

def set_do0(state):
    # 初始化 ROS 節點
    rospy.init_node('set_tm5_do', anonymous=True)

    # 等待 Service 可用
    rospy.wait_for_service('/tm_driver/set_io')

    try:
        # 創建 Service Proxy
        set_io_service = rospy.ServiceProxy('/tm_driver/set_io', SetIO)

        # 構建請求
        req = SetIORequest()
        req.module = 1  # 1 表示末端模組
        req.type = 1    # 1 表示 DO（Digital Output）
        req.pin = 0     # 0 表示 DO0
        req.state = state  # 設置為 true

        # 呼叫 Service 並發送請求
        resp = set_io_service(req)

        # 檢查服務響應
        if resp.ok:
            rospy.loginfo(f"Successfully set DO0 to {state}")
        else:
            rospy.logwarn("Failed to set DO0")

    except rospy.ServiceException as e:
        rospy.logerr(f"Service call failed: {e}")

if __name__ == '__main__':
    # 設置命令行參數解析
    parser = argparse.ArgumentParser(description='Set DO0 on TM5-900 robot')
    parser.add_argument('state', choices=['on', 'off'], help='Set DO0 to on or off')
    args = parser.parse_args()

    # 根據輸入的參數決定 DO0 的狀態
    state = True if args.state == 'on' else False

    try:
        set_do0(state)
    except rospy.ROSInterruptException:
        pass