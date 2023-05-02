import socket
import subprocess
import sys

subprocess.run('clear', shell=True)

remote_host = input("get host: ")
remote_ip   = socket.gethostbyname(remote_host)
port_start, port_end = map(int, input("port range: ").split('-'))

for port in range(port_start, port_end+1):
    try:
        sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        result = sockfd.connect_ex((remote_ip, port))
        if result == 0:
            print(f"port {port} open")
            sockfd.close()
    except KeyboardInterrupt:
        print("keyboard interrupt")
        sys.exit(1)
