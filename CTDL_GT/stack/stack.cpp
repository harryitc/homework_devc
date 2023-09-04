#include <bits/stdc++.h>

// info: Bieu thuc chi tinh duoc con so >= 10
// vi du: 3+2/2-1*2

// neu ma so > 10 thi se khong tinh duoc
// vi day la bieu thuc khong phai NANG CAO
// vidu: "3+12/2-10*2"  -> so 12 >= 10, so 10 >= 10

/* ================== muon test gi thi thay doi cho nay thoi ================ */
#define input "3+2/2-1*2" // <------ here

#define INVALID "Invalid Expression" // <---- notifi error

// DECLARE PREDENCE
#define C_PLUS '+'
#define C_MINUS '-'
#define C_MULTI '*'
#define C_DEVIDE '/'
#define C_EXCLUSIVE '^'
#define C_OPEN_BRACKET '('
#define C_CLOSE_BRACKET ')'
#define LOWEST_PRECEDENCE 0
#define PLUS 1
#define MINUS 1
#define MULTI 2
#define DEVIDE 2
#define EXCLUSIVE 3

typedef struct
{
    int top;
    unsigned capacity;
    int *array;
} Stack;

// Hàm tao 1 stack moi
Stack *createStack(unsigned capacity);

// in ra cac du lieu co trong stack
void printStack(Stack *stack);

// Hàm kiem tra xem stack co bi leak/overflow memory (tran bo nho) hay khong
bool isFull(Stack *stack);

// Hàm kiem tra xem stack co rong hay khong?
bool isEmpty(Stack *stack);

// Hàm day 1 phan tu vao cuoi stack
void push(Stack *stack, int item);

// Hàm lay phan tu cuoi cung ra khoi stack
int pop(Stack *stack);

// Hàm lay phan tu dau cua ngan xep, nhung khong xoa no
int peek(Stack *stack);

// kiem tra cap phat bo nho
bool checkAllocated(Stack *stack);

// lay do uu tien
int getPrecedence(char _operator);

// chuyen doi tu infix to postfix
char *infixToPostfix(char *infix);

// tinh toan bieu thuc postfix
int calculator(char *number);

int main()
{

    char infix[100] = input;

    // tinh bieu thuc infix -> postfix
    char *postfix = infixToPostfix(infix);
    printf("postfix = %s\n", postfix);

    // tinh ket qua dua tren postfix
    int result = calculator(postfix);
    printf("calculator = %d\n", result);

    free(postfix);
    printf("DONE!");
    return 0;
}

Stack *createStack(unsigned capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));

    stack->capacity = capacity;
    // FAQ: tai sao lai la -1.
    /* CHET ME - NHAM NGON NGU KHAC
    - Quay ve mang 1 chieu.
    - khi truy xuat phan tu dang: stack[index]: thi chung ta se lay phan tu stack tai vi tri thu index
    - Vay, khi index = -1, thi chung ta se lay vi tri cuoi cung trong mang
    vi du: [1,2,3,4,5] => voi index = -1 => stack[index] = 5;
    cung co the lam nhu sau: stack[*kich thuoc stack - 1*] = 5;
    ->>> Vay, nhin qua thi truy xuat phan tu -1 thi no tien loi hon.

    Vay, khi lam viec voi stack.
    Khi ban muon lay ra 1 gia tri.
    Thi chac chan la ban muon lay ra so 5 dung khong(lam sao ma so 1 duoc. Neu khong hieu thi doc lai ly thuyet).
    Ly thuyet la nhu the.
    Do do, chung ta se duoc bien top fixed luon la -1.
    OK chua nao!
    */
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

bool isFull(Stack *stack) { return stack->top == stack->capacity - 1; }

bool isEmpty(Stack *stack) { return stack->top == -1; }

void push(Stack *stack, int item)
{
    if (isFull(stack))
    {
        printf("stack is fulled! cannot push %d in stack\n", item);
        return;
    }
    // khi push 1 stack vao, thi chung ta cung phai tang kich thuoc tren stack len 1
    stack->array[++stack->top] = item;
}
int pop(Stack *stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}
int peek(Stack *stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}

void printStack(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack contents: ");
    for (int i = 0; i <= stack->top; i++)
    {
        printf("%c ", stack->array[i]);
    }
    printf("\n");
}

bool checkAllocated(Stack *stack)
{
    if (!stack)
    {
        printf("leak memory!");
        exit(0);
    }
    return false;
}

// lay do uu tien
int getPrecedence(char _operator)
{
    int predenece = LOWEST_PRECEDENCE;
    switch (_operator)
    {
    case C_PLUS:
        predenece = PLUS;
        break;
    case C_MINUS:
        predenece = MINUS;
        break;
    case C_MULTI:
        predenece = MULTI;
        break;
    case C_DEVIDE:
        predenece = DEVIDE;
        break;
    case C_EXCLUSIVE:
        predenece = EXCLUSIVE;
        break;
    default:
        predenece = LOWEST_PRECEDENCE;
    }
    return predenece;
}

bool isOperator(char character)
{
    return (
        character == C_PLUS ||
        character == C_MINUS ||
        character == C_MULTI ||
        character == C_DEVIDE ||
        character == C_EXCLUSIVE);
}

char *infixToPostfix(char *infix)
{
    int length = strlen(infix);

    // declare result
    // co the la luu tru cac ky tu bracket, cho nen +2 hoac +3 gi do thoi la ok
    char *postfix = (char *)malloc(sizeof(char) * (length + 2));

    // store operator
    Stack *stack = createStack(length);

    // khong cap phat thanh cong thi "dung" he dieu hanh
    checkAllocated(stack);

    int j = 0;

    for (int i = 0; i < length; i++)
    {

        // neu la khoang trong hoac khoang cach
        if (infix[i] == ' ' || infix[i] == '\t')
            continue;

        // neu la toan hang
        if (isalnum(infix[i]))
        {
            postfix[j++] = infix[i];
        }

        // neu la ky tu '('
        if (infix[i] == C_OPEN_BRACKET)
        {
            push(stack, infix[i]);
        }

        // neu la ky tu ')'
        if (infix[i] == C_CLOSE_BRACKET)
        {
            while (!isEmpty(stack) && peek(stack) != C_OPEN_BRACKET)
            {
                postfix[j++] = pop(stack);
            }
            // sau khi xong het roi
            // thi xoa cai ky tu '('. Do do, kiem tra roi moi xoa
            // neu khong co ky tu '(' thi bieu thuc sai.
            // khong hieu thi code giay di :)
            if (!isEmpty(stack) && peek(stack) == C_OPEN_BRACKET)
                pop(stack);
            else
                return INVALID;
        }

        // neu la toan tu
        if (isOperator(infix[i]))
        {
            // ktra do uu tien
            // neu do uu tien trong stack cao hon do uu tien cua infix
            // dua het cac ky tu tu stack vao posfix
            while (!isEmpty(stack) && getPrecedence(infix[i]) <= getPrecedence(peek(stack)))
            {
                postfix[j++] = pop(stack);
            }
            push(stack, infix[i]);
        }
    }

    /*
        mac du da xong het roi.
        Nhung ma van con 1 so du lieu trong stack
        Do do, push het vao chuoi -> return result
    */
    while (!isEmpty(stack))
    {
        if (peek(stack) == C_CLOSE_BRACKET)
        {
            return INVALID;
        }
        postfix[j++] = pop(stack);
    }

    // lam gi lam, giai phong bo nho
    free(stack);

    // tai vi o tren kia length + 2 hay gi do
    // do do, cho vi tri cuoi cung la rong(nghia la: xoa di cac kytu thua)
    postfix[j] = '\0';

    // tra ve
    return postfix;
}

int calculator(char *number)
{
    int length = strlen(number);
    Stack *stack = createStack(length);
    printf("\nQuy trinh tinh toan:\n");
    for (int i = 0; i < length; i++)
    {
        if (isOperator(number[i]))
        {
            int b = pop(stack);
            int a = pop(stack);
            int result = 0;
            switch (number[i])
            {
            case C_PLUS:
                result = a + b;
                break;
            case C_MINUS:
                result = a - b;
                break;
            case C_MULTI:
                result = a * b;
                break;
            case C_DEVIDE:
                result = a / b;
                break;
            case C_EXCLUSIVE:
                result = pow(a, b);
                break;
            default:
                printf("no opeator this\n");
                result = 0;
                break;
            }
            printf("%d. %d %c %d = %d", i, a, number[i], b, result);
            if (number[i] == C_DEVIDE && result % 2 && result > 2)
            {
                printf(" -> float -> %.2f\n", (float)a / b);
            }
            else
            {
                printf("\n");
            }
            push(stack, result);
        }
        else
        {
            push(stack, number[i] - '0');
        }
    }
    return pop(stack);
}