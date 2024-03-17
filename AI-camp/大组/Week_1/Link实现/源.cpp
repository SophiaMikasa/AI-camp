#include<stdio.h>
#include<stdlib.h>

//单向链表所需结构体
typedef struct NodeOne {
    int num;
    struct NodeOne* next;
} NodeOne, * NodeOneList;

//双向链表所需结构体
typedef struct NodeTwo {
    struct NodeTwo* pre;
    int num;
    struct NodeTwo* next;
} NodeTwo, * NodeTwoList;

void menu(NodeOneList* singleList, NodeTwoList* doubleList);
//创造链表
void CreateSingleList(NodeOneList* singleList);
void CreateDoubleList(NodeTwoList* doubleList);
//插入链表（用头插法）
void InsertSingleList(NodeOneList* singleList);
void InsertDoubleList(NodeTwoList* doubleList);
//打印链表
void PrintSingleList(NodeOneList* singleList);
void PrintDoubleList(NodeTwoList* doubleList);
//链表对应选作题的菜单
void SingleListMenu(NodeOneList* singleList);
void DoubleListMenu(NodeTwoList* doubleList);
//单向链表的奇偶调换
void ParitySwap(NodeOneList* singleList);
//单向链表的寻找中心
void FindCenterPoint(NodeOneList* singleList);
//判断循环
void SingleIsLoop(NodeOneList* singleList);
//链表反转
void ConvertSingleList(NodeOneList* singleList);
void DoubleIsLoop(NodeTwoList* doubleList);
void ConvertDoubleList(NodeTwoList* doubleList);

int main() {
    NodeOneList singleList = NULL;
    NodeTwoList doubleList = NULL;

    menu(&singleList, &doubleList);

    return 0;
}
void menu(NodeOneList* singleList, NodeTwoList* doubleList) {
    char choice;

    while (1) {
        system("cls");
        printf("======================\n");
        printf("实现单链表还是双链表？\n");
        printf("======================\n");
        printf("1.单链表\n");
        printf("2.双链表\n");
        printf("3.退出\n");
        printf("======================\n");
        scanf_s("%c", &choice, (unsigned int)sizeof(choice));
        while (getchar() != '\n');
        switch (choice) {
        case '1':
            CreateSingleList(singleList);
            InsertSingleList(singleList);
            SingleListMenu(singleList);
            break;
        case '2':
            CreateDoubleList(doubleList);
            InsertDoubleList(doubleList);
            DoubleListMenu(doubleList);
            break;
        case '3':
            printf("退出成功\n");
            exit(0);
            break;
        default:
            printf("输入错误,请重新输入\n");
            system("pause");
            break;
        }
    }
}

void CreateSingleList(NodeOneList* singleList) {
    NodeOne* p = (NodeOne*)malloc(sizeof(NodeOne));
    if (p == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    p->num = 0;
    p->next = NULL;
    *singleList = p;
}

void CreateDoubleList(NodeTwoList* doubleList) {
    *doubleList = (NodeTwo*)malloc(sizeof(NodeTwo));
    if (*doubleList == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    (*doubleList)->pre = NULL;
    (*doubleList)->next = NULL;
    (*doubleList)->num = 0;
}

void InsertSingleList(NodeOneList* singleList) {
    system("cls");
    printf("单链表：\n");
    int num;

    for (int i = 1;;i++) {
        NodeOne* p = (NodeOne*)malloc(sizeof(NodeOne));
        if (p == NULL) {
            printf("内存分配失败\n");
            exit(1);
        }
        printf("请输入第%d个元素的值(输入非数字结束): ",i);
        if (scanf_s("%d", &num) == 1) {
            //有头节点,并且用头插法
            p->num = num;
            p->next = (*singleList)->next;
            (*singleList)->next = p;
        }
        else {
            printf("输入结束\n");
            system("pause");
            system("cls");
            free(p);
            break;
        }
    }
}

void InsertDoubleList(NodeTwoList* doubleList) {
    system("cls");
    printf("双链表：\n");
    int num;

    for (int i = 1;; i++) {
        NodeTwo* p = (NodeTwo*)malloc(sizeof(NodeTwo));
        if (p == NULL) {
            printf("内存分配失败\n");
            exit(1);
        }
        printf("请输入第%d个元素的值(输入非数字结束): ", i);
        if (scanf_s("%d", &num) == 1) {
            //有头节点,并且用头插法
            p->pre = *doubleList;
            p->num = num;
            p->next = (*doubleList)->next;
            (*doubleList)->next = p;
        }
        else {
            printf("输入结束\n");
            system("pause");
            system("cls");
            free(p);
            break;
        }
    }
}

void PrintSingleList(NodeOneList* singleList) {
    NodeOneList p = (*singleList)->next;
    while (p) {
        printf("%d ", p->num);
        p = p->next;
    }
    system("pause");
}

void PrintDoubleList(NodeTwoList* doubleList) {
    NodeTwoList p = (*doubleList)->next;
    while (p) {
        printf("%d ", p->num);
        p = p->next;
    }
    system("pause");
}

void SingleListMenu(NodeOneList* singleList) {
    char choice;
    while (1) {
        system("cls");
        printf("==================\n");
        printf("现在可以......\n");
        printf("==================\n");
        printf("1.单链表奇偶调换\n");
        printf("2.找到单链表的中点\n");
        printf("3.判断链表是否成环\n");
        printf("4.反转链表\n");
        printf("5.退出\n");
        printf("==================\n");
        while (getchar() != '\n');
        scanf_s("%c", &choice, (unsigned int)sizeof(choice));
        switch (choice) {
            case '1':
                ParitySwap(singleList);
                break;
            case '2':
                FindCenterPoint(singleList);
                break;
            case '3':
                SingleIsLoop(singleList);
                break;
            case '4':
                ConvertSingleList(singleList);
                break;
            case '5':
                printf("退出成功\n");
                system("pause");
                while (getchar() != '\n');
                return;
        }
    }
}

void DoubleListMenu(NodeTwoList* doubleList) {
    char choice;
    while (1) {
        system("cls");
        printf("==================\n");
        printf("现在可以......\n");
        printf("==================\n");
        printf("1.判断链表是否成环\n");
        printf("2.反转链表\n");
        printf("3.退出\n");
        printf("==================\n");
        while (getchar() != '\n');
        scanf_s("%c", &choice, (unsigned int)sizeof(choice));
        while (getchar() != '\n');
        switch(choice) {
            case '1':
                DoubleIsLoop(doubleList);
                break;
            case '2':
                ConvertDoubleList(doubleList);
                break;
            case '3':
                printf("退出成功\n");
                system("pause");
                while (getchar() != '\n');
                return;
        }
    }
}

void ParitySwap(NodeOneList* singleList) {
    printf("调换成功\n");
    printf("原来的链表为：\n");
    PrintSingleList(singleList);
    NodeOne* odd = (*singleList)->next, * even = odd->next;

    while (even != NULL && even->next != NULL) {

        int temp = odd->num;
        odd->num = even->num;
        even->num = temp;

        // 更新奇数位置节点
        odd = odd->next->next;
        // 更新偶数位置节点
        even = even->next->next;
    }
    if (even) {
        int temp = odd->num;
        odd->num = even->num;
        even->num = temp;
    }
    printf("调换之后的链表为:\n");
    // 打印链表以验证调换结果
    PrintSingleList(singleList);
}

void FindCenterPoint(NodeOneList* singleList) {
    NodeOne* p1 = (*singleList)->next, * p2 = p1;
    printf("当前链表为：\n");
    PrintSingleList(singleList);
    if (p1 == NULL || p2 == NULL)
        return;

    while (p2->next) {
        p2 = p2->next;
        if (p2->next != NULL) {
            p1 = p1->next;
            p2 = p2->next;
        }
        else {
            printf("该链表有两个中点：\n");
            printf("%d %d\n",p1->num,p1->next->num);
            system("pause");
            return;
        }
    }
    printf("该链表的中点值为:%d\n",p1->num);
    system("pause");
}

void SingleIsLoop(NodeOneList* singleList) {
    NodeOne* p1 = (*singleList)->next, * p2 = p1->next;

    if ((*singleList)->next == NULL) {
        printf("该链表不是循环链表\n");
        system("pause");
        return;
    }
    while (p2 != NULL && p2->next != NULL) {
        if (p1 == p2) {
            //如果快慢指针相遇则说明为循环链表
            printf("该链表为循环链表\n");
            system("pause");
            return;
        }
        p1 = p1->next;
        p2 = p2->next->next;
    }
    printf("该链表不是循环链表\n");
    system("pause");
}

void ConvertSingleList(NodeOneList* singleList) {
    NodeOne* pre = NULL, * current = NULL, * next = NULL;
    current = (*singleList)->next;
    while (current) {
        next = current->next;
        current->next = pre;
        pre = current;
        current = next;
    }

    (*singleList)->next = pre;
    PrintSingleList(singleList);
    system("pause");
}

void DoubleIsLoop(NodeTwoList* doubleList) {
    //方法跟单链表一样的啦
    NodeTwo* p1 = (*doubleList)->next, * p2 = p1->next;

    if ((*doubleList)->next == NULL) {
        printf("该链表不是循环链表\n");
        system("pause");
        return;
    }
    while (p2 != NULL && p2->next != NULL) {
        if (p1 == p2) {
            printf("该链表为循环链表\n");
            system("pause");
            return;
        }
        p1 = p1->next;
        p2 = p2->next->next;
    }
    printf("该链表不是循环链表\n");
    system("pause");
}

void ConvertDoubleList(NodeTwoList* doubleList) {
    printf("反转之前:");
    PrintDoubleList(doubleList);
    NodeTwo* pre = NULL, * current = NULL, * next = NULL;
    current = (*doubleList)->next;
    while (current) {
        next = current->next;
        current->next = pre;
        pre = current;
        current = next;
    }
    (*doubleList)->next = pre;
    printf("\n反转之后：");
    PrintDoubleList(doubleList);
    system("pause");
}
