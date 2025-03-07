import serial
import time
def receive_message(ser):
    while True:
        try:
            data = ser.readline().decode().strip()
            if data:
                current_time = time.strftime("[RECV %Y-%m-%d %H:%M:%S]")
                full_received_message = f"{current_time} {data}"
                print(full_received_message)
        except UnicodeDecodeError:
            print("接收到的数据无法解码")

def main():
    try:
        ser = serial.Serial('COM2', 9600, timeout=1)
        print(f"成功打开串口 {ser.name}")
        receive_message(ser)
        ser.close()
        print("串口已关闭")
    except serial.SerialException as e:
        print(f"串口打开失败: {e}")
if __name__ == "__main__":
    main()