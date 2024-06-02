#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    int id;
    char name[50];
    int age;
    char gender[10];
    float grade1;
    float grade2;
    float grade3;
    struct Student *next;
} Student;

void read_File(Student *stu);
void init();

Student *s;

int studnet_count;

void init()
{
    s = (Student *)malloc(sizeof(Student));

    s->next = NULL;

    studnet_count = 0;

    read_File(s);
}

void wait()
{

    printf("输入0返回！\n");
    while (1)
    {
        if (getchar() == '0')
            break;
    }
}

void show(Student *p)
{
    printf("==%d==\n", p->id);
    printf("==%s==\n", p->name);
    printf("==%d==\n", p->age);
    printf("==%s==\n", p->gender);
    printf("==%f==\n", p->grade1);
    printf("==%f==\n", p->grade2);
    printf("==%f==\n", p->grade3);
}

void encryptAndSaveToFile(const char *filename, Student *students, char what[])
{
    FILE *file = fopen(filename, what);
    if (file == NULL)
    {
        fprintf(stderr, "未发现data文件！\n");
        return;
    }
    fprintf(file, "%d|", students->id);
    fprintf(file, "%s|", students->name);
    fprintf(file, "%d|", students->age);
    fprintf(file, "%s|", students->gender);
    fprintf(file, "%f|", students->grade1);
    fprintf(file, "%f|", students->grade2);
    fprintf(file, "%f|\n", students->grade3);

    fclose(file);
}

void add_Student()
{

    Student student = {}, *p = s;

    printf("请输入学号：");
    scanf("%d", &(student.id));

    printf("请输入姓名：");
    scanf("%s", student.name);

    printf("请输入年纪：");
    scanf("%d", &(student.age));

    printf("请输入性别：");
    scanf("%s", student.gender);

    printf("请输入语文成绩：");
    scanf("%f", &(student.grade1));

    printf("请输入数学成绩：");
    scanf("%f", &(student.grade2));

    printf("请输入英语成绩：");
    scanf("%f", &(student.grade3));

    while (p != NULL)
    {
        if (student.id == p->id)
        {
            printf("学号%d已存在，无法增加！\n", student.id);
            return;
        }
        p = p->next;
    }

    encryptAndSaveToFile("data.dat", &student, "ab");

    init();
}

void del_Student()
{
    if (studnet_count == 0)
    {
        printf("当前没有学生信息！\n");
        return;
    }

    int del_id;
    Student *p = s;
    printf("请输入要删除的学生的学号：");
    scanf("%d", &del_id);
    while (p->id != del_id && p->next != NULL)
    {
        p = p->next;
    }
    if (p->id != del_id)
    {
        printf("未找到该学号！\n");
    }
    else
    {
        if (studnet_count == 1)
        {
            FILE *file = fopen("data.dat", "w");
            fclose(file);
            printf("删除成功！");
            init();
            return;
        }
        FILE *file = fopen("data.dat", "w");
        fclose(file);
        p = s->next;
        while (p != NULL)
        {
            if (p->id != del_id)
                encryptAndSaveToFile("data.dat", p, "ab");
            p = p->next;
        }
        printf("删除成功！");
        init();
        return;
    }
}

void chance_Student()
{
    if (studnet_count == 0)
    {
        printf("当前没有学生信息！\n");
        return;
    }
    int chance_id = 0, input;
    Student *p = s->next, *q = s->next;
    printf("请输入要修改的学生学号：");
    scanf("%d", &chance_id);
    while (p != NULL)
    {
        if (p->id == chance_id)
            break;
        p = p->next;
    }
    if (p == NULL)
    {
        printf("未找到要修改的学生学号！\n");
        return;
    }
    printf("请输入学号：");
    scanf("%d", &input);

    while (q != NULL)
    {
        if (q->id == input)
        {
            printf("你输入的学号已存在！无法重复！");
            return;
        }
        q = q->next;
    }
    p->id = input;

    printf("请输入姓名：");
    scanf("%s", p->name);

    printf("请输入年纪：");
    scanf("%d", &(p->age));

    printf("请输入性别：");
    scanf("%s", p->gender);

    printf("请输入语文成绩：");
    scanf("%f", &(p->grade1));

    printf("请输入数学成绩：");
    scanf("%f", &(p->grade2));

    printf("请输入英语成绩：");
    scanf("%f", &(p->grade3));

    FILE *file = fopen("data.dat", "w");
    fclose(file);
    p = s->next;
    while (p != NULL)
    {
        encryptAndSaveToFile("data.dat", p, "ab");
        p = p->next;
    }
    printf("修改成功！");
}

void read_File(Student *stu)
{

    char str[99];

    Student *p = stu;

    FILE *file = fopen("data.dat", "r");

    if (file == NULL)
    {

        printf("第一次使用正在初始化软件！\n");

        file = fopen("data.dat", "w");
        if (file != NULL)
        {
            printf("初始化成功！\n");
        }
        else
        {
            printf("初始化失败！\n");
            exit(1);
        }
    }

    while (fgets(str, sizeof(str), file))
    {

        Student *s = (Student *)malloc(sizeof(Student));

        s->next = NULL;

        char ch[99];

        int i = 0, j = 0, flag = 0;

        while (str[j] != '\0')
        {
            if ((str[j] != '|'))
            {
                ch[i] = str[j];

                i++;

                j++;
            }
            else
            {

                ch[i] = '\0';

                i = 0;

                switch (flag)
                {
                case 0:
                    s->id = atoi(ch);
                    flag++;
                    break;
                case 1:
                    strcpy(s->name, ch);
                    flag++;
                    break;
                case 2:
                    s->age = atoi(ch);
                    flag++;
                    break;
                case 3:
                    strcpy(s->gender, ch);
                    flag++;
                    break;
                case 4:
                    s->grade1 = atof(ch);
                    flag++;
                    break;
                case 5:
                    s->grade2 = atof(ch);
                    flag++;
                    break;
                case 6:
                    s->grade3 = atof(ch);
                    flag++;
                    break;
                }

                j += 1;
            }
        }
        p->next = s;
        p = p->next;
        studnet_count++;
    }
    fclose(file);
}

void search_Student()
{
    if (studnet_count == 0)
    {
        printf("当前没有学生信息！\n");
        return;
    }
    int num;

    printf("请输入要查询的学生的学号：");

    scanf("%d", &num);

    Student *p = s;

    while (p->id != num && p->next != NULL)
    {
        p = p->next;
    }
    if (p->id == num)
    {
        printf("查询成功！\n");
        show(p);
    }
    else
    {
        printf("未找到该学生！\n");
    }
}

void show_All_Student()
{
    Student *p = s->next;
    if (studnet_count == 0)
    {
        printf("当前没有学生信息！\n");
        return;
    }
    while (p != NULL)
    {
        show(p);
        p = p->next;
    }
}

void menu()
{
    printf("***********欢迎使用学生信息管理系统（当前共有%d名学生）***********\n", studnet_count);
    printf("1. 添加学生信息\n");
    printf("2. 删除学生信息\n");
    printf("3. 修改学生信息\n");
    printf("4. 查询学生信息\n");
    printf("5. 显示所有学生信息以及统计信息\n");
    printf("0. 退出系统\n");
    printf("****************************************************************");
    printf("\n");
}

void handleInput(char choice)
{

    switch (choice)
    {
    case '0':
        printf("退出成功！");
        exit(0);
        break;
    case '1':
        add_Student();
        wait();
        menu();
        break;
    case '2':
        del_Student();
        wait();
        menu();
        break;
    case '3':
        chance_Student();
        wait();
        menu();
        break;
    case '4':
        search_Student();
        wait();
        menu();
        break;
    case '5':
        show_All_Student();
        wait();
        menu();
        break;
    }
}

int main()
{
    init();
    menu();
    while (1)
    {
        char choice = getchar();
        handleInput(choice);
    }
    return 0;
}