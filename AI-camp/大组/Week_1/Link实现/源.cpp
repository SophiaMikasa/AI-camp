#include<stdio.h>
#include<stdlib.h>

//������������ṹ��
typedef struct NodeOne {
    int num;
    struct NodeOne* next;
} NodeOne, * NodeOneList;

//˫����������ṹ��
typedef struct NodeTwo {
    struct NodeTwo* pre;
    int num;
    struct NodeTwo* next;
} NodeTwo, * NodeTwoList;

void menu(NodeOneList* singleList, NodeTwoList* doubleList);
//��������
void CreateSingleList(NodeOneList* singleList);
void CreateDoubleList(NodeTwoList* doubleList);
//����������ͷ�巨��
void InsertSingleList(NodeOneList* singleList);
void InsertDoubleList(NodeTwoList* doubleList);
//��ӡ����
void PrintSingleList(NodeOneList* singleList);
void PrintDoubleList(NodeTwoList* doubleList);
//�����Ӧѡ����Ĳ˵�
void SingleListMenu(NodeOneList* singleList);
void DoubleListMenu(NodeTwoList* doubleList);
//�����������ż����
void ParitySwap(NodeOneList* singleList);
//���������Ѱ������
void FindCenterPoint(NodeOneList* singleList);
//�ж�ѭ��
void SingleIsLoop(NodeOneList* singleList);
//����ת
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
        printf("ʵ�ֵ�������˫����\n");
        printf("======================\n");
        printf("1.������\n");
        printf("2.˫����\n");
        printf("3.�˳�\n");
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
            printf("�˳��ɹ�\n");
            exit(0);
            break;
        default:
            printf("�������,����������\n");
            system("pause");
            break;
        }
    }
}

void CreateSingleList(NodeOneList* singleList) {
    NodeOne* p = (NodeOne*)malloc(sizeof(NodeOne));
    if (p == NULL) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    p->num = 0;
    p->next = NULL;
    *singleList = p;
}

void CreateDoubleList(NodeTwoList* doubleList) {
    *doubleList = (NodeTwo*)malloc(sizeof(NodeTwo));
    if (*doubleList == NULL) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    (*doubleList)->pre = NULL;
    (*doubleList)->next = NULL;
    (*doubleList)->num = 0;
}

void InsertSingleList(NodeOneList* singleList) {
    system("cls");
    printf("������\n");
    int num;

    for (int i = 1;;i++) {
        NodeOne* p = (NodeOne*)malloc(sizeof(NodeOne));
        if (p == NULL) {
            printf("�ڴ����ʧ��\n");
            exit(1);
        }
        printf("�������%d��Ԫ�ص�ֵ(��������ֽ���): ",i);
        if (scanf_s("%d", &num) == 1) {
            //��ͷ�ڵ�,������ͷ�巨
            p->num = num;
            p->next = (*singleList)->next;
            (*singleList)->next = p;
        }
        else {
            printf("�������\n");
            system("pause");
            system("cls");
            free(p);
            break;
        }
    }
}

void InsertDoubleList(NodeTwoList* doubleList) {
    system("cls");
    printf("˫����\n");
    int num;

    for (int i = 1;; i++) {
        NodeTwo* p = (NodeTwo*)malloc(sizeof(NodeTwo));
        if (p == NULL) {
            printf("�ڴ����ʧ��\n");
            exit(1);
        }
        printf("�������%d��Ԫ�ص�ֵ(��������ֽ���): ", i);
        if (scanf_s("%d", &num) == 1) {
            //��ͷ�ڵ�,������ͷ�巨
            p->pre = *doubleList;
            p->num = num;
            p->next = (*doubleList)->next;
            (*doubleList)->next = p;
        }
        else {
            printf("�������\n");
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
        printf("���ڿ���......\n");
        printf("==================\n");
        printf("1.��������ż����\n");
        printf("2.�ҵ���������е�\n");
        printf("3.�ж������Ƿ�ɻ�\n");
        printf("4.��ת����\n");
        printf("5.�˳�\n");
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
                printf("�˳��ɹ�\n");
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
        printf("���ڿ���......\n");
        printf("==================\n");
        printf("1.�ж������Ƿ�ɻ�\n");
        printf("2.��ת����\n");
        printf("3.�˳�\n");
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
                printf("�˳��ɹ�\n");
                system("pause");
                while (getchar() != '\n');
                return;
        }
    }
}

void ParitySwap(NodeOneList* singleList) {
    printf("�����ɹ�\n");
    printf("ԭ��������Ϊ��\n");
    PrintSingleList(singleList);
    NodeOne* odd = (*singleList)->next, * even = odd->next;

    while (even != NULL && even->next != NULL) {

        int temp = odd->num;
        odd->num = even->num;
        even->num = temp;

        // ��������λ�ýڵ�
        odd = odd->next->next;
        // ����ż��λ�ýڵ�
        even = even->next->next;
    }
    if (even) {
        int temp = odd->num;
        odd->num = even->num;
        even->num = temp;
    }
    printf("����֮�������Ϊ:\n");
    // ��ӡ��������֤�������
    PrintSingleList(singleList);
}

void FindCenterPoint(NodeOneList* singleList) {
    NodeOne* p1 = (*singleList)->next, * p2 = p1;
    printf("��ǰ����Ϊ��\n");
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
            printf("�������������е㣺\n");
            printf("%d %d\n",p1->num,p1->next->num);
            system("pause");
            return;
        }
    }
    printf("��������е�ֵΪ:%d\n",p1->num);
    system("pause");
}

void SingleIsLoop(NodeOneList* singleList) {
    NodeOne* p1 = (*singleList)->next, * p2 = p1->next;

    if ((*singleList)->next == NULL) {
        printf("��������ѭ������\n");
        system("pause");
        return;
    }
    while (p2 != NULL && p2->next != NULL) {
        if (p1 == p2) {
            //�������ָ��������˵��Ϊѭ������
            printf("������Ϊѭ������\n");
            system("pause");
            return;
        }
        p1 = p1->next;
        p2 = p2->next->next;
    }
    printf("��������ѭ������\n");
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
    //������������һ������
    NodeTwo* p1 = (*doubleList)->next, * p2 = p1->next;

    if ((*doubleList)->next == NULL) {
        printf("��������ѭ������\n");
        system("pause");
        return;
    }
    while (p2 != NULL && p2->next != NULL) {
        if (p1 == p2) {
            printf("������Ϊѭ������\n");
            system("pause");
            return;
        }
        p1 = p1->next;
        p2 = p2->next->next;
    }
    printf("��������ѭ������\n");
    system("pause");
}

void ConvertDoubleList(NodeTwoList* doubleList) {
    printf("��ת֮ǰ:");
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
    printf("\n��ת֮��");
    PrintDoubleList(doubleList);
    system("pause");
}
