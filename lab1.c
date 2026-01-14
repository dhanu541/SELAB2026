#include <stdio.h>
#include <ctype.h>

#define MAX 100
#define SUBJECTS 7

struct Student{
char id[20];
char name[50];
int internal[SUBJECTS];
int external[SUBJECTS];
int total;
float percentage;
float cgpa;
char grade[3];
};

int myStrCmp(char a[],char b[]){
int i=0;
while(a[i]&&b[i]){
if(a[i]!=b[i]) return a[i]-b[i];
i++;
}
return a[i]-b[i];
}

void myStrCpy(char d[],char s[]){
int i=0;
while(s[i]){
d[i]=s[i];
i++;
}
d[i]='\0';
}

void assignGrade(float p,char g[]){
if(p>=90) myStrCpy(g,"O");
else if(p>=85) myStrCpy(g,"A+");
else if(p>=75) myStrCpy(g,"A");
else if(p>=65) myStrCpy(g,"B+");
else if(p>=60) myStrCpy(g,"B");
else if(p>=55) myStrCpy(g,"C");
else if(p>=50) myStrCpy(g,"D");
else myStrCpy(g,"F");
}

int main(){
struct Student s[MAX];
int n,i,j;
float classTotal=0,highest=0,lowest=100;
int gradeCount[8]={0};
FILE *in=fopen("in.txt","r");
FILE *out=fopen("out.txt","w");
if(in==NULL||out==NULL){
printf("File error\n");
return 1;
}
fscanf(in,"%d",&n);
for(i=0;i<n;i++){
fscanf(in,"%s",s[i].id);
fscanf(in," %[^\n]",s[i].name);
s[i].total=0;
for(j=0;j<SUBJECTS;j++){
fscanf(in,"%d %d",&s[i].internal[j],&s[i].external[j]);
if(s[i].internal[j]<0||s[i].internal[j]>40||s[i].external[j]<0||s[i].external[j]>60){
printf("Invalid marks\n");
return 1;
}
s[i].total+=s[i].internal[j]+s[i].external[j];
}
s[i].percentage=s[i].total/(float)SUBJECTS;
s[i].cgpa=s[i].percentage/10.0;
assignGrade(s[i].percentage,s[i].grade);
classTotal+=s[i].percentage;
if(s[i].percentage>highest) highest=s[i].percentage;
if(s[i].percentage<lowest) lowest=s[i].percentage;
if(myStrCmp(s[i].grade,"O")==0) gradeCount[0]++;
else if(myStrCmp(s[i].grade,"A+")==0) gradeCount[1]++;
else if(myStrCmp(s[i].grade,"A")==0) gradeCount[2]++;
else if(myStrCmp(s[i].grade,"B+")==0) gradeCount[3]++;
else if(myStrCmp(s[i].grade,"B")==0) gradeCount[4]++;
else if(myStrCmp(s[i].grade,"C")==0) gradeCount[5]++;
else if(myStrCmp(s[i].grade,"D")==0) gradeCount[6]++;
else gradeCount[7]++;
}
fprintf(out,"ID\tName\t\tTotal\t%%\tGrade\tCGPA\n");
for(i=0;i<n;i++){
fprintf(out,"%s\t%s\t%d\t%.2f\t%s\t%.2f\n",s[i].id,s[i].name,s[i].total,s[i].percentage,s[i].grade,s[i].cgpa);
}
fprintf(out,"\nClass Average Percentage: %.2f\n",classTotal/n);
fprintf(out,"Highest Percentage: %.2f\n",highest);
fprintf(out,"Lowest Percentage: %.2f\n",lowest);
fprintf(out,"\nNumber of Students in Each Grade:\n");
fprintf(out,"O  : %d\n",gradeCount[0]);
fprintf(out,"A+ : %d\n",gradeCount[1]);
fprintf(out,"A  : %d\n",gradeCount[2]);
fprintf(out,"B+ : %d\n",gradeCount[3]);
fprintf(out,"B  : %d\n",gradeCount[4]);
fprintf(out,"C  : %d\n",gradeCount[5]);
fprintf(out,"D  : %d\n",gradeCount[6]);
fprintf(out,"F  : %d\n",gradeCount[7]);
fclose(in);
fclose(out);
printf("Output written to out.txt\n");
return 0;
}
