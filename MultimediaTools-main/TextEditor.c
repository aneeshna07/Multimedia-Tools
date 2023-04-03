#include<stdio.h>
#include<conio.h>
#include<process.h>
#include <stdlib.h>

int a;
char b[20],c;
FILE *f1;

void Create_Overwrite();
void Append();
void Delete();
void Display();
void Find_Pattern();
void TE()
//void main()
{
 do
 {
  printf("\n\n");
  printf("\n\tTEXT EDITOR\n");
  printf("\n\tMENU:");
  printf("\n\t1.CREATE_OR_OVERWRITE\n\t2.DISPLAY\n\t3.APPEND\n\t4.DELETE\n\t5.EXIT\n");
  printf("\n\tEnter your choice:");
  scanf("%d",&a);
  switch(a)
  {
  case 1:
    Create_Overwrite();
    break;
  case 2:
    Display();
    break;
  case 3:
    Append();
    break;
  case 4:
    Delete();
    break;
  case 5:
    exit(0);
  }
  }while(1);
}


void Create_Overwrite()
{   
  printf("\n\tEnter the filename:");
  scanf("%s",b);
  remove(b);
  f1=fopen(b,"w");
  printf("\n\tEnter the text\n");
  while((c=getchar())!=EOF)
  {
  fputc(c,f1);  
  }
  fclose(f1);    
}


void Display()
{
  printf("\n\tEnter the file name:");
  scanf("%s",b);
  f1=fopen(b,"r");
  if(f1==NULL)
  {
  printf("\n\tFile not found");
  fclose(f1);
  }
  while((c=fgetc(f1))!=EOF)
  {
  fputc(c,stdout);
  } 
  fclose(f1);
  
}


void Delete()
{
  printf("\n\tEnter the file name: ");
  scanf("%s",b);
  f1=fopen(b,"r");
  if(f1==NULL)
  {
  printf("\n\tFile not found!");
  fclose(f1);
  }
  if(remove(b)==0)
  {
  printf("\n\n\tFile has been deleted successfully!");
  } 
}


void Append()
{
  printf("\n\tEnter the file name:");
  scanf("%s",b);
  f1=fopen(b,"a");
  if(f1==NULL)
  {
  printf("\n\tFile not found");
  fclose(f1);
  }
  while((c=getchar())!=EOF)
  {
  fputc(c,f1);
  }
  fclose(f1);
}


void Find_Pattern(){
  printf("\n\tEnter the file name:");
  scanf("%s",b);
  char d[100];
  printf("\n\tEnter the string:");
  scanf("%s",d);
  f1=fopen(b,"r");
  if(f1==NULL)
  {
  printf("\n\tFile not found");
  fclose(f1);
  }
  else
  {
  int l=1;
  int i=0,w=0,back=0,count=0,mark=0;
  char c;
  while((c=fgetc(f1))!=EOF)
  {
  if(c=='\n')
  {
  l++;
  back=0;
  mark=1;
  }
  else if((c=='\t') || (c==' ') || (c==',') || (c==':') || (c==';') || (c=='/') || (c=='?')|| (c=='.'))
  {
  if (back==1)
  {
  w++;
  back=0;
  }
  mark=1;
  }
  else
  {
  back=1;
  mark=0;
  }
  if(i==strlen(d))
  {
  if(mark==1)
  {
  count++;
  printf("\n\tThe input string occurs after the word %d in the line %d",w,l);
  }
  i=0;
  }
  else{}  
  if(c==d[i])
  i++;
  else
  i=0;
  }
  fclose(f1);
  if (count==0)
  printf("\n\tThe input string not found");
  else
  printf("\n\tThe input string appeared %d times",count);
  } 
  
}
