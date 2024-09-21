#include <iostream>
#include <string>
#include <functional>
/* 加法哈希 */
int addHash(std::string key)
{
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key)
    {
        hash = (hash + (int)c) % MODULUS;
    }
    return (int)hash;
}

/* 乘法哈希 */
int mulHash(std::string key)
{
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key)
    {
        hash = (31 * hash + (int)c) % MODULUS;
    }
    return (int)hash;
}

/* 异或哈希 */
int xorHash(std::string key)
{
    int hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key)
    {
        hash ^= (int)c;
    }
    return hash & MODULUS;
}

/* 旋转哈希 */
int rotHash(std::string key)
{
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key)
    {
        hash = ((hash << 4) ^ (hash >> 28) ^ (int)c) % MODULUS;
    }
    return (int)hash;
}

int main()
{
    int num = 3;
    size_t hashNum = std::hash<int>()(num);
    std::cout << hashNum << std::endl;
    bool bol = true;
    size_t hashBol = std::hash<bool>()(bol);
    std::cout << hashBol << std::endl;
    double d = 3.14;
    size_t hashd = std::hash<bool>()(d);
    std::cout << hashd << std::endl;
    std::string str = "hola";
    size_t hashStr = std::hash<std::string>()(str);
    std::cout << hashStr << std::endl;
    return 0;
}