#pragma once
class Random
{
};

/**
 * 随机数宏
 */
#define TO_ODD(x) (((x) % 2 == 0) ? (x)-1 : (x))
#define TO_EVEN(x) (((x) % 2) ? (x)-1 : (x))

#define RAND_RANGE(x, y) (rand() % ((y) - (x)) + (x))

#define RAND_ODD(x) (rand() % ((x) / 2) * 2 + 1)  //产生[0,x)之间的随机奇数
#define RAND_EVEN(x) (rand() % (((x) + 1) / 2) * 2)  //产生[0,x)之间的随机偶数

#define RAND_ODD_RANGE(x, y)                                                   \
    ((x) + RAND_ODD(((y) - (x))))  //产生[x,y)之间的随机奇数
#define RAND_EVEN_RANGE(x, y)                                                  \
    ((x) + RAND_EVEN(((y) - (x))))  //产生[x,y)之间的随机偶数
