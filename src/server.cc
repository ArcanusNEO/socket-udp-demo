#include <bits/stdc++.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;
#define BUF_SIZE 128

signed main() {
  //创建套接字
  auto serv_sock = socket(AF_INET, SOCK_DGRAM, 0);
  //将套接字和IP、端口绑定
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
  serv_addr.sin_family = AF_INET;  //使用IPv4地址
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //任意IP地址
  serv_addr.sin_port = htons(8848);  //端口
  bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
  //接收客户端请求
  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_size = sizeof(clnt_addr);
  char buffer[BUF_SIZE];  //缓冲区

  while (true) {
    auto str_len = recvfrom(serv_sock, buffer, BUF_SIZE, 0, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
    sendto(serv_sock, buffer, str_len, 0, (struct sockaddr*) &clnt_addr, clnt_addr_size);
  }
  //关闭套接字
  close(serv_sock);
  return 0;
}
