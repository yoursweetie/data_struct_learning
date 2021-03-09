#include <stdio.h>
#include <stdlib.h>

/* DEBUG模式的切换 */
#define DEBUG 0

#define equal   1
#define unequal 0

/* 每个list中元素的最大个数设置为100 */
#define LENGTH_MAX 100


typedef struct
{
    int length;
    int arr[LENGTH_MAX];
} List;

/* 给list赋长度 */
void ListCreat(List* list, int length)
{
    list->length = length;
}

/* 为list中的元素赋值 */
void ListInit(List *list)
{
    for (int i = 0; i < list->length; i++)
    {
        /* 如果在DEBUG模式下,直接给元素赋简单的值 */
#if DEBUG
        list->arr[i] = i * 2;
#else
        /*
         * 如果不是在DEBUG模式下,
         * 产生小于50的随机数,初始化list中的arr数组
         */
        list->arr[i] = rand() % 50;
#endif
    }

}

/* PPT中要求的初始化函数,给list赋长度为0 */
void InitList(List *list)
{
    list->length = 0;
}

/* 返回list中元素的个数 */
int ListLength(List list)
{
    return list.length;
}

/* 将list中的arr[index]元素赋值给result */
void GetElem(List list, int index, int *result)
{
    *result = list.arr[index];
}

/*
 * 在list中查找是否有与tar这个目标元素相同的元素,
 * 如果有,返回equal,否则返回unequal
 * equal是定义为1的宏,unqual是定义为0的宏
 * 当传入的relation不是equal时,直接返回unequal
 * 可以改进
 */
int LocateElem(List* list, int tar, int relation)
{
    if (relation == equal)
    {
        for (int i = 0; i < list->length; i++)
        {
            if (list->arr[i] == tar)
                return equal;
        }
        return unequal;
    }
    /* TO DO: (relation != equal)*/
    return unequal;
}

/* 在list->arr[]数组的末尾插入append_member */
void ListInsert(List *list, int length_later, int append_member)
{
    list->length += 1;
    list->arr[list->length- 1] = append_member;
}

/* union函数(union是C语言中的关键字,所以命名不能冲突,改成ListUnion) */
void ListUnion(List *La, List Lb)
{
    int La_len, Lb_len, i;
    /* ElemType e; */
    int e;
    /* La_len = ListLength(La); */
    La_len = ListLength(*La);
    Lb_len = ListLength(Lb);

    /* for (i = 1; i <= Lb_len; i++) */
    for (i = 0; i < Lb_len; i++)
    {
        GetElem(Lb, i, &e);
        if (!LocateElem(La, e, equal))
        {
            ListInsert(La, ++La_len, e);
        }
    }
}

/* 打印出list中的所有元素 */
void Print_List(List *list, char* listname)
{
    printf("%s: \n", listname);
    for (int i = 0; i < list->length; i++)
    {
        printf("%s[%d]: %d\n", listname, i, list->arr[i]);
    }
}

void MergeList(List La, List Lb, List *Lc)
{
    int La_len, Lb_len, i, j, k;
    /* ElemType ai, bj; */
    int ai, bj;
    InitList(Lc);
    i = j = 0;
    k = 0;
    La_len=ListLength(La);
    Lb_len=ListLength(Lb);
    while ((i < La_len) && (j < Lb_len))
    {
        GetElem(La, i, &ai);
        GetElem(Lb, j, &bj);
        if (ai <= bj)
        {
            ListInsert(Lc, ++k, ai);
            ++i;
        }
        else
        {
            ListInsert(Lc, ++k, bj);
            ++j;
        }
    }

    while (i < La_len)
    {
        GetElem(La, i++, &ai);
        ListInsert(Lc, ++k, ai);
    }
    while (j < Lb_len)
    {
        GetElem(Lb, j++, &bj);
        ListInsert(Lc, ++k, bj);
    }
        /*
         * printf("after one list be run out:\n");
         * Print_List(Lc, "L5");
         */
}

int main()
{
    List L1, L2;
    /* 在内存中开辟空间 */
    ListCreat(&L1, 10);
    ListCreat(&L2, 12);

    /* 初始化list中的arr数组 */
    ListInit(&L1);
    ListInit(&L2);

    printf("****** Function union ******\n");

    /* 打印初始化后L1, L2中的所有元素 */
    Print_List(&L1, "L1");
    Print_List(&L2, "L2");

    /* union L1 和 L2中的元素并打印 */
    ListUnion(&L1, L2);
    printf("****** After union ******\n");
    Print_List(&L1, "L1");

    /* MergeList的实现 */
    printf("****** Function merge ******\n");

    /* L3和L4为待merge的list, L5为merge后的list */
    List L3, L4;
    List L5;

    /*
     * 初始化L3和L4中的元素以及长度
     * L3和L4中元素为升序排列
     */
    L3.arr[0] = 1;
    L3.arr[1] = 3;
    L3.arr[2] = 7;
    L3.arr[3] = 10;
    L3.length = 4;

    L4.arr[0] = 0;
    L4.arr[1] = 2;
    L4.arr[2] = 5;
    L4.arr[3] = 8;
    L4.length = 4;

    Print_List(&L3, "L3");
    Print_List(&L4, "L4");

    MergeList(L3, L4, &L5);
    printf("****** After merge ******\n");
    Print_List(&L5, "L5");
    return 0;
}
