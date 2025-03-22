import pyshark
import csv
from datetime import datetime
def extract_ftp_info(pcap_file):
    tshark_path = '"D:\\Software\\Wireshark\\tshark.exe"' 
    cap = pyshark.FileCapture(pcap_file, display_filter='ftp', tshark_path=tshark_path)
    ftp_sessions = {}
    for packet in cap:
        try:
            time = datetime.fromtimestamp(float(packet.sniff_timestamp)).strftime('%Y-%m-%d %H:%M:%S')
            src_mac = packet.eth.src
            src_ip = packet.ip.src
            dst_mac = packet.eth.dst
            dst_ip = packet.ip.dst
            if 'ftp.request.command' in packet.ftp.field_names:
                command = packet.ftp.request.command
                if command == 'USER':
                    username = packet.ftp.request.arg
                    if (src_ip, dst_ip) not in ftp_sessions:
                        ftp_sessions[(src_ip, dst_ip)] = {
                            'time': time,
                            'src_mac': src_mac,
                            'src_ip': src_ip,
                            'dst_mac': dst_mac,
                            'dst_ip': dst_ip,
                            'username': username,
                            'password': None,
                            'result': None
                        }
                elif command == 'PASS':
                    password = packet.ftp.request.arg
                    if (src_ip, dst_ip) in ftp_sessions:
                        ftp_sessions[(src_ip, dst_ip)]['password'] = password
            elif 'ftp.response.code' in packet.ftp.field_names:
                response_code = packet.ftp.response.code
                if response_code.startswith('230'):
                    result = 'SUCCEED'
                elif response_code.startswith('530'):
                    result = 'FAILED'
                if (src_ip, dst_ip) in ftp_sessions:
                    ftp_sessions[(src_ip, dst_ip)]['result'] = result
                    # 输出到 CSV
                    with open('ftp_log.csv', 'a', newline='') as csvfile:
                        fieldnames = ['时间', '源MAC', '源IP', '目标MAC', '目标IP', '登录名', '口令', '成功与否']
                        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
                        if csvfile.tell() == 0:
                            writer.writeheader()
                        writer.writerow({
                            '时间': ftp_sessions[(src_ip, dst_ip)]['time'],
                            '源MAC': ftp_sessions[(src_ip, dst_ip)]['src_mac'],
                            '源IP': ftp_sessions[(src_ip, dst_ip)]['src_ip'],
                            '目标MAC': ftp_sessions[(src_ip, dst_ip)]['dst_mac'],
                            '目标IP': ftp_sessions[(src_ip, dst_ip)]['dst_ip'],
                            '登录名': ftp_sessions[(src_ip, dst_ip)]['username'],
                            '口令': ftp_sessions[(src_ip, dst_ip)]['password'],
                            '成功与否': ftp_sessions[(src_ip, dst_ip)]['result']
                        })
                    del ftp_sessions[(src_ip, dst_ip)]
        except AttributeError:
            continue
    cap.close()
if __name__ == "__main__":
    pcap_file = '3rd.pcap' 
    extract_ftp_info(pcap_file)
