# 用户信息

- 真实用户ID(UID):启动程序的用户ID
- 有效用户ID(EUID):运行程序的用户拥有该程序的有效用户的权限(设置set-user-id标志后为可执行文件所有者ID)
- 真实组ID(GID):启动程序的用户组ID
- 有效组ID(EGID):给运行目标程序的组用户提供有效组的权限(设置set-user-id标志后为可执行文件所属组ID)

```
#include <sys/types.h>
#include <unistd.h>
uid_t getuid();
uid_t geteuid();
gid_t getgid();
gid_t getegid();
int setuid(uid_t uid);
int seteuid(uid_t uid);
int setgid(gid_t gid);
int setegid(gid_t gid);
```

测试进程的UID和EUID：

```
#include <unistd.h>
#include <stdio.h>

int main()
{
    uid_t uid = getuid();
    uid_t euid = geteuid();
    printf("userid is %d, effective userid is %d\n", uid, euid);
    return 0;
}
```

编译文件，将得到的可执行文件test_uid的所有者设置为root，并设置该文件的set-user-id标志，然后运行程序：

```
$ sudo chown root:root test_uid
$ sudo chmod +s test_uid
$ ./test_uid
userid is 1000, effective userid is 0
```

从测试来看，进程的UID是启动程序的用户ID，而EUID则是文件所有者(root)的ID

许多服务器程序要求以root用户启动，但是却以普通用户身份后台运行，所以需要进行切换用户的动作，例：

```
static bool switch_to_user(uid_t user_id, gid_t gp_id)
{
    //先确保目标用户不是root
    if ( (user_id == 0)&&(gp_id == 0) )
        return false;
    gid_t gid = getgid();
    uid_t uid = getuid();
    if ( (gid != 0 || uid != 0) && (gid != gp_id || uid != user_id) )
        return false;
    if (uid != 0)
        return true;
    if ( (setgid(gp_id) < 0) || (setuid(user_id) < 0) ) 
        return false;
    return true;
}
```
