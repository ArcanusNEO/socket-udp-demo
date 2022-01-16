#include <bits/stdc++.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;
#define BUF_SIZE 128

signed main() {
  //创建套接字
  auto sock = socket(AF_INET, SOCK_DGRAM, 0);
  //向服务器（特定的IP和端口）发起请求
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
  serv_addr.sin_family = AF_INET;  //使用IPv4地址
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
  serv_addr.sin_port = htons(8848);  //端口

  struct sockaddr_in from_addr;
  socklen_t clnt_addr_size = sizeof(from_addr);
  while (true) {
    char buffer[BUF_SIZE] = {0};
    cout << "Input a string: ";
    cin >> buffer;
    sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    auto str_len = recvfrom(sock, buffer, BUF_SIZE, 0, (struct sockaddr*) &from_addr, &clnt_addr_size);
    buffer[str_len] = 0;
    cout << "Message form server: " << buffer << endl;
  }
  //关闭套接字
  close(sock);
  return 0;
}