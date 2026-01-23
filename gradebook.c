#include <stdio.h>
#include <string.h>

struct StudentRecord {
    int id;
    char grade;
    char name[100];
};

int main() {
    struct StudentRecord record;
    record.id = 123;
    record.grade = 'A';
    strcpy(record.name, "John");

    printf("%d\n", record.id);
    printf("%c\n", record.grade);
    printf("%s\n", record.name);
    return 0;
}