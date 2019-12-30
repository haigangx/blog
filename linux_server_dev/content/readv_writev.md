# readv和writev

readv：将数据从文件描述符读到分散的内存块中，即分散读

writev：将数据从多块分散的内存数据一并写入文件描述符中，即集中写

```
#include <sys/uio.h>
ssize_t readv(int fd, const struct iovec* vector, int count);
ssize_t writev(int fd, const struct iovec* vector, int count);

struct iovec
{
    void *iov_base;    //内存起始地址
    size_t iov_len;     //这块内存的长度
};
```

vector：iovec描述一块内存区，count表示vector数组中内存区iovec的数量

readv和writev在成功时返回读入/写入fd的字节数，失败返回-1并设置errno


## 使用：

在Web服务器上集中写：

```
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

static const char* status_line[2] = {"200 OK", "500 Internal server error"};

int main(int argc, char* argv[]) {
    if (argc <= 3) {
        printf("usage: %s ip_address port_number filename\n", basename(argv[0]));
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);
    const char* file_name = argv[3];

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    int ret = bind(sockfd, (struct sockaddr*)&address, sizeof(address));
    assert(sockfd != -1);

    ret = listen(sockfd, 5);
    assert(ret != -1);
    
    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    
    int connfd = accept(sockfd, (struct sockaddr*)&client, &client_addrlength);
    if (connfd < 0) {
        printf("errno is : %d\n", errno);
    } else {
        char header_buf[BUFFER_SIZE];
        memset(header_buf, '\0', BUFFER_SIZE);
        char* file_buf;
        struct stat file_stat;
        bool valid = true;
        int len = 0;
        if (stat(file_name, &file_stat) < 0) {
            valid = false;
        } else {
            if (S_ISDIR(file_stat.st_mode)) {
                valid = false;
            } 
            else if (file_stat.st_mode & S_IROTH) {
                int fd = open(file_name, O_RDONLY);
                file_buf = new char[file_stat.st_size+1];
                memset(file_buf, '\0', file_stat.st_size+1);
                if (read(fd, file_buf, file_stat.st_size) < 0) {
                    valid = false;
                }
            }
            else {
                valid = false;
            }
        }

        if (valid) {
            ret = snprintf(header_buf, BUFFER_SIZE-1, "%s %s\r\n", "HTTP/1.1", status_line[0]);
            len += ret;
            ret = snprintf(header_buf+len, BUFFER_SIZE-1-len, "Content-Length: %d\r\n", file_stat.st.size);
            len += ret;
            struct iovec iv[2];
            iv[0].iov_base = header_buf;
            iv[0].iov_len = strlen(header_buf);
            iv[0].iov_base = file_buf;
            iv[0].iov_len = file_stat.st_size;
            ret = writev(connfd, iv, 2);
        }
        else {
            ret = snprintf(header_buf, BUFFER_SIZE-1, "%s %s\r\n", "HTTP/1.1", status_line[1]);
            len += ret;
            ret = snprintf(header_buf+len, BUFFER_SIZE-1-len, "%s", "\r\n");
            send(connfd, header_buf, strlen(header_buf), 0);
        }
        close(connfd);
        delete [] file_buf;
    }
    close(sock);
    return 0;
}
```
