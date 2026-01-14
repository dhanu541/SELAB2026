#include <stdio.h>
#include <ctype.h>

#define MAX_STUDENTS 50
#define SUBJECTS 7

struct Student {
    char id[20];
    char name[50];
    int marks[SUBJECTS];
    int total;
    float percentage;
    char grade[3];
    float cgpa;
};
int myStrCmp(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return a[i] - b[i];
        i++;
    }
    return a[i] - b[i];
}

void myStrCpy(char dest[], char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int validateID(char id[], struct Student s[], int count) {
    int i;
    for (i = 0; id[i] != '\0'; i++) {
        if (!isalnum(id[i]))
            return 0;
    }
    for (i = 0; i < count; i++) {
        if (myStrCmp(s[i].id, id) == 0)
            return 0;
    }
    return 1;
}

int validateName(char name[]) {
    int i;
    for (i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ')
            return 0;
    }
    return 1;
}

void assignGrade(float p, char grade[]) {
    if (p >= 90) myStrCpy(grade, "O");
    else if (p >= 85) myStrCpy(grade, "A+");
    else if (p >= 75) myStrCpy(grade, "A");
    else if (p >= 65) myStrCpy(grade, "B+");
    else if (p >= 60) myStrCpy(grade, "B");
    else if (p >= 55) myStrCpy(grade, "C");
    else if (p >= 50) myStrCpy(grade, "D");
    else myStrCpy(grade, "F");
}

float gradeToCGPA(char grade[]) {
    if (myStrCmp(grade, "O") == 0) return 10;
    if (myStrCmp(grade, "A+") == 0) return 9;
    if (myStrCmp(grade, "A") == 0) return 8;
    if (myStrCmp(grade, "B+") == 0) return 7;
    if (myStrCmp(grade, "B") == 0) return 6;
    if (myStrCmp(grade, "C") == 0) return 5;
    if (myStrCmp(grade, "D") == 0) return 4;
    return 0;
}

int main() {
    struct Student s[MAX_STUDENTS];
    int n, i, j;

    float classTotal = 0, highest = 0, lowest = 100;
    int gradeCount[8] = {0};

    FILE *fp = fopen("in.txt", "r");
    FILE *out = fopen("out.txt", "w");

    if (fp == NULL || out == NULL) {
        printf("File error\n");
        return 1;
    }

    fscanf(fp, "%d", &n);

    for (i = 0; i < n; i++) {

        fscanf(fp, "%s", s[i].id);
        if (!validateID(s[i].id, s, i)) {
            printf("Invalid Student ID\n");
            return 1;
        }

        fscanf(fp, " %[^\n]", s[i].name);
        if (!validateName(s[i].name)) {
            printf("Invalid Name\n");
            return 1;
        }

        s[i].total = 0;
        for (j = 0; j < SUBJECTS; j++) {
            fscanf(fp, "%d", &s[i].marks[j]);
            if (s[i].marks[j] < 0 || s[i].marks[j] > 100) {
                printf("Invalid Marks\n");
                return 1;
            }
            s[i].total += s[i].marks[j];
        }

        s[i].percentage = s[i].total / (float)SUBJECTS;
        assignGrade(s[i].percentage, s[i].grade);
        s[i].cgpa = gradeToCGPA(s[i].grade);

        classTotal += s[i].percentage;
        if (s[i].percentage > highest) highest = s[i].percentage;
        if (s[i].percentage < lowest) lowest = s[i].percentage;

        if (myStrCmp(s[i].grade, "O") == 0) gradeCount[0]++;
        else if (myStrCmp(s[i].grade, "A+") == 0) gradeCount[1]++;
        else if (myStrCmp(s[i].grade, "A") == 0) gradeCount[2]++;
        else if (myStrCmp(s[i].grade, "B+") == 0) gradeCount[3]++;
        else if (myStrCmp(s[i].grade, "B") == 0) gradeCount[4]++;
        else if (myStrCmp(s[i].grade, "C") == 0) gradeCount[5]++;
        else if (myStrCmp(s[i].grade, "D") == 0) gradeCount[6]++;
        else gradeCount[7]++;
    }

    fprintf(out, "ID\tName\t\tTotal\t%%\tGrade\tCGPA\n");
    for (i = 0; i < n; i++) {
        fprintf(out, "%s\t%s\t%d\t%.2f\t%s\t%.1f\n",
                s[i].id, s[i].name, s[i].total,
                s[i].percentage, s[i].grade, s[i].cgpa);
    }

    fprintf(out, "\nClass Average: %.2f\n", classTotal / n);
    fprintf(out, "Highest Percentage: %.2f\n", highest);
    fprintf(out, "Lowest Percentage: %.2f\n", lowest);

    fclose(fp);
    fclose(out);

    printf("Output written to out.txt\n");
    return 0;
}

