《剑指offer》题目总结

<details><summary>1. 赋值运算符函数</summary>

# 面试题1：赋值运算符函数

题目：如下为类型CMyString的声明，请为该类型添加赋值运算符函数
```
class CMyString {
public:
    CMyString(char* pData = nullptr);
    CMyString(const CMyString& str);
    ~CMyString(void);

private:
    char* m_pData;
};
```

### 需要注意的点：

- 赋值运算符函数返回值类型为引用，并且在函数结束前返回实例自身的引用(*this)，以实现连续赋值
- 考虑到效率，传入参数应设为常量引用类型
- 是否释放实例自身已有的内存，在分配新内存之前要释放自身已有的空间
- 判断传入参数和当前实例(*this)是否为同一实例


### 解法一：经典解法
```
CMyString& CMyString::operator=(const CMyString &str) {
    if (this == &str)
        return *this;

    delete []m_pData;
    m_pData = nullptr;

    //未考虑到异常安全情况，一旦这里出现问题，将发生重大错误
    m_pData = new char[strlen(str.m_pData)+1];  
    strcpy(m_pData, str.m_pData);

    return *this;
}
```

### 解法二：考虑到异常安全的解法
```
CMyString& CMyString::operator=(const CMyString &str) {
    if (this != str) {
        CMyString strTemp(str);

        char* pTemp = strTemp.m_pData;
        strTemp.m_pData = m_pData;
        m_pData = pTemp;
    }
    return *this;
}
```

</details>