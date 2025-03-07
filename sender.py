import serial
import time
def send_message(ser, message):
    current_time = time.strftime("[SENT %Y-%m-%d %H:%M:%S]")
    full_message = f"{current_time} {message}"
    ser.write(full_message.encode())
    print(full_message)
def main():
    try:
        ser = serial.Serial('COM1', 9600, timeout=1)
        print(f"成功打开串口 {ser.name}")
        while True:
            message = input("请输入要发送的消息（输入 'exit' 退出）: ")
            if message.lower() == 'exit':
                break
            send_message(ser, message)
        ser.close()
        print("串口已关闭")
    except serial.SerialException as e:
        print(f"串口打开失败: {e}")
if __name__ == "__main__":
    main()