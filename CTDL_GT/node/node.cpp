#include <bits/stdc++.h>
#define null NULL
#define HEAD 1
#define LAST 2
#define SHOW 3
#define FIND 4
#define SORT 5
#define DELETE 6
#define EXIT 7
typedef struct
{
    int id;
    char name[50];
    float avg;
} Student;
typedef struct LinkedList
{
    Student student;
    LinkedList *next;
} *node;

// Khoi tao du lieu ban dau (chac chan la null roi)
node InitHead();

// tao ra 1 node moi (node duoc tao moi luon luon la null)
node CreateNode(Student student);

// them vao cuoi node
node AddTail(node head, Student student);

// them vao dau node
node AddHead(node head, Student student);

// xoa node dau tien - (bo sung neu can)
node DelHead(node head);

// xoa cuoi node - (bo sung neu can)
node DelTail(node head);

// xoa node tai 1 vi tri nao do
node DelAt(node head, int position);

/* CLONE */
node copyLinkedList(node head); // Cach 1
node Clone(node head);          // Cach 2 (recursion)

// tim kiem node theo ID (ma sinh vien)
int SearchByID(node head, int ID);

// xoa node theo id nao do
node deleteByID(node head, int ID);

// nhap du lieu cho sinh vien
Student Input();

// in tat ca cac sinh vien
void print_all_student(node head);

// in ra 1 sinh vien
void print_1_student(Student student);

// thuc hien chuc nang tim diem trung binh cua sinh vien
void findAvg(node head);

// sort theo selectionSort
// return node da sap xep (khong thay doi list g?c)
node selectionSort(node head);

// tim kiem node theo diem trung binh (AVG)
int searchByAVG(node head, float AVG);

int main()
{
    // cho head ban dau khong co du lieu gi het
    // co the gan la null
    node head = InitHead();

    // cho gia tri ban dau la -1, nghia la: chua chon gi het
    // -1 khong thuoc tu 1 -> 7
    int choice = -1; // null
    bool running = true;
    // cho menu chay vong lap vo han
    while (running)
    {
        printf("%d. Nhap thong tin sinh vien (first)\n", HEAD);
        printf("%d. Nhap thong tin sinh vien (last)\n", LAST);
        printf("%d. Xuat danh sach sinh vien\n", SHOW);
        printf("%d. Tim sinh vien co DTB la X (x: input)\n", FIND);
        printf("%d. Selection sort (khong thay doi root)\n", SORT);
        printf("%d. Xoa sinh vien theo ID\n", DELETE);
        printf("%d. Thoat\n", EXIT);
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        // xu ly cac truong hop khi chon cac so tu 1->7
        switch (choice)
        {
        // 1. nhap data vao node o dau
        case HEAD:
        {
            Student student = Input();
            if (student.id == 0)
                break;
            head = AddHead(head, student);
            system("cls"); // xoa man hinh
            break;
        }
        // 2. nhap data vao node cuoi cung
        case LAST:
        {
            Student student = Input();
            // neu nhap maSinhVien = 0 thi thoat
            if (student.id == 0)
                break;
            head = AddTail(head, student);
            system("cls"); // xoa man hinh
            break;
        }
        // 3. hien thi toan bo sinh vien
        case SHOW:
        {
            print_all_student(head);
            break;
        }
        // 4. tim kiem sinh vien theo diem trung binh
        case FIND:
        {
            findAvg(head);
            break;
        }
        // 5. sap xep tang dan theo SelectionSort
        case SORT:
        {
            // tao ra 1 node moi chua toan bo list da sap xep
            // toi khong muon list da sap xep ghi de(overwrite) len list cu(head)
            // do do ma tao 1 node moi
            node sortedNode = selectionSort(head);
            // neu bien nay khong co du lieu thi keu list rong
            if (!sortedNode)
            {
                printf("list is empty!");
                break;
            }
            // nguoc lai in tat cac sinh vien
            print_all_student(sortedNode);
            break;
        }
            // 6. Xoa sinh vien theo Ma Sinh Vien (ID)
        case DELETE:
        {
            if (!head)
            {
                printf("list is empty!\n");
                break;
            }
            int id;
            printf("\nNhap id muon xoa: ");
            scanf("%d", &id);
            head = deleteByID(head, id);
            printf("delete done!");
            //                  print_all_student(head);
            break;
        }
            // 7. Ket thuc chuong trinh
        case EXIT:
        {
            // neu ket thuc thi chi can cho "running = false;"
            // nghia la "dung vong lap vo han"
            printf("Ket thuc chuong trinh.\n");
            running = false;
            break;
        }
            // neu co nhap sai cac lua chon tu 1 -> 7 thi keu no nhap lai
        default:
        {
            printf("Lua chon khong hop ly. Vui long chon lai.\n");
            break;
        }
        }
    }

    // Giai phong bo nho khi ket thuc chuong trinh
    while (!head)
    {
        node oldNode = head;
        head = head->next;
        free(oldNode);
    }

    return 0;
}

node CreateNode(Student student)
{
    node temp; // declare a node
    /* tai sao lai cap phat?
    -- khi tao 1 node moi. dong nghia voi viec phai cap phat 1 bo nho
    -- de chung co the luu tru data cua rieng chung
     */
    temp = (node)malloc(sizeof(struct LinkedList)); // C?p phát vùng nh? dùng malloc()
    temp->next = NULL;                              // Cho next tr? t?i NULL
    temp->student = student;                        // Gán giá tr? cho Node
    return temp;                                    // Tr? v? node m?i dã có giá tr?
}

void print_all_student(node head)
{
    if (!head)
    {
        printf("list is empty!\n");
        return;
    }
    printf("\nDanh sach sinh vien:\n");
    for (node p = head; p != NULL; p = p->next)
    {
        printf("\n--------------------------\n");
        printf("\nMa sinh vien: %d", p->student.id);
        printf("\nHo ten: %s", p->student.name);
        printf("\nDiem trung binh: %.2f", p->student.avg);
        printf("\n--------------------------\n");
    }
}

node AddTail(node head, Student student)
{

    if (!head)
        return CreateNode(student);

    node lastNode;

    // lay node cuoi
    for (node currentNode = head; currentNode != NULL; currentNode = currentNode->next)
    {
        // tro toi currentNode
        lastNode = currentNode;
    }

    // tao node moi
    node newNode = CreateNode(student);

    // cho node cuoi cung tro den node moi vua duoc tao
    lastNode->next = newNode;

    /*
       sau khi da lien ket node cuoi roi thi return ve thang dau
    */
    return head;
}

node AddHead(node head, Student student)
{
    //    node temp = CreateNode(student); // Kh?i t?o node temp v?i data = value
    //    if(head == NULL){
    //        head = temp; // //N?u linked list dang tr?ng thì Node temp là head luôn
    //    }else{
    //        temp->next = head; // Tr? next c?a temp = head hi?n t?i
    //        head = temp; // Ð?i head hi?n t?i = temp(Vì temp bây gi? là head m?i mà)
    //    }
    //    return head;

    if (!head)
        return CreateNode(student);
    // tao ra 1 mode moi
    node newNode = CreateNode(student);
    // sau khi tao node moi, thi hien tai dang tro ve null
    // cho node moi tro den node dau tien (ten la head)
    newNode->next = head;
    // dat lai vi tri dau la node vua duoc tao
    // nghia la: dia chi(cu) cua head = dia chi moi(new node)
    head = newNode;
    return head;
}

node DelHead(node head)
{
    if (head == NULL)
    {
        printf("\nCha co gi de xoa het!");
    }
    else
    {
        head = head->next;
    }
    return head;
}

node DelTail(node head)
{
    if (head == NULL || head->next == NULL)
    {
        return DelHead(head);
    }
    node p = head;
    while (p->next->next != NULL)
    {
        p = p->next;
    }
    p->next = p->next->next; // Cho next b?ng NULL
    // Ho?c vi?t p->next = NULL cung du?c
    return head;
}

node DelAt(node head, int position)
{
    if (position == 0 || head == NULL || head->next == NULL)
    {
        head = DelHead(head); // N?u v? trí chèn là 0, t?c là thêm vào d?u
    }
    else
    {
        // B?t d?u tìm v? trí c?n chèn. Ta s? dùng k d? d?m cho v? trí
        int k = 1;
        node p = head;
        while (p->next->next != NULL && k != position)
        {
            p = p->next;
            ++k;
        }

        if (k != position)
        {
            // N?u duy?t h?t danh sách lk r?i mà v?n chua d?n v? trí c?n chèn, ta s? m?c d?nh xóa cu?i
            // N?u b?n không mu?n xóa, hãy thông báo v? trí xóa không h?p l?
            head = DelTail(head);
            // printf("Vi tri xoa vuot qua vi tri cuoi cung!\n");
        }
        else
        {
            p->next = p->next->next;
        }
    }
    return head;
}

node InitHead()
{
    //    node head;
    //    head = NULL;
    //    return head;
    return null;
}

Student Input()
{
    Student student;
    printf("\nNhap ID: ");
    scanf("%d", &student.id);
    if (student.id == 0)
    {
        printf("\nBan da nhap so 0 => out");
        return student;
    }
    printf("\nNhap ten: ");
    scanf(" %30[^\n]", student.name);
    printf("\nNhap diem trung binh: ");
    scanf("%f", &student.avg);
    printf("Them sinh vien thanh cong!\n");
    return student;
}

void print_1_student(Student student)
{
    printf("\n---------------------");
    printf("\nMa sinh vien: %d", student.id);
    printf("\nHo ten: %s", student.name);
    printf("\nDiem trung binh: %.2f", student.avg);
    printf("\n---------------------");
}

void findAvg(node head)
{
    if (!head)
        return;
    float value;
    printf("\nNhap DTB(avg) muon tim: ");
    scanf("%f", &value);

    if (searchByAVG(head, value) == -1)
    {
        printf("\n----Khong co sinh vien nao co dtb la: %.2f", value);
        return;
    }

    for (node currentNode = head; currentNode != NULL; currentNode = currentNode->next)
    {
        if (currentNode->student.avg == value)
        {
            print_1_student(currentNode->student);
        }
    }
}

node Clone(node head)
{
    if (!head)
        return null;

    node result = (node)malloc(sizeof(struct LinkedList));
    result->student = head->student;
    result->next = Clone(head->next);
    return result;
}

node copyLinkedList(node head)
{

    node newHead = NULL;
    node tail = NULL;

    node current = head;
    while (current != NULL)
    {

        node newNode = (node)malloc(sizeof(struct LinkedList));
        newNode->student = current->student;
        newNode->next = NULL;

        if (newHead == NULL)
        {
            newHead = newNode;
            tail = newNode;
        }
        else
        {

            tail->next = newNode;
            tail = newNode;
        }

        current = current->next;
    }

    return newHead;

    /*
//    if(!head) return null;
//    node newNode = null; // return
//    node current = head;
//    while (current != NULL) {
//      newNode = AddTail(newNode, student);
//        current = current->next;
//    }
//    return newNode;
    */
}

node selectionSort(node head)
{
    if (!head)
        return null;

    node result = Clone(head);

    for (node currentNode = result; currentNode; currentNode = currentNode->next)
    {
        node indexMinNode = currentNode;
        for (
            node currentNextNode = currentNode->next;
            currentNextNode && currentNextNode->student.avg < indexMinNode->student.avg; // condition
            currentNextNode = currentNextNode->next)
        {
            indexMinNode = currentNextNode;
        }

        std::swap(currentNode->student, indexMinNode->student);
    }
    return result;
}

int SearchByID(node head, int ID)
{
    int position = 0;
    for (node p = head; p != NULL; p = p->next)
    {
        if (p->student.id == ID)
        {
            return position;
        }
        ++position;
    }
    return -1;
}

int searchByAVG(node head, float AVG)
{
    int position = 0;
    for (node p = head; p != NULL; p = p->next)
    {
        if (p->student.avg == AVG)
        {
            return position;
        }
        ++position;
    }
    return -1;
}

node deleteByID(node head, int ID)
{
    if (!head)
        return null;
    int position = SearchByID(head, ID);
    while (position != -1)
    {
        DelAt(head, position);
        position = SearchByID(head, ID);
    }
    return head;
}