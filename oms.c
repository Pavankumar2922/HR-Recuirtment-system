#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 500
#define MALLOC(p,s)\
        if(!(p=malloc(s)))\
        {\
           printf("Malloc Unsuccessfull\n");\
           exit(0);\
        }
struct employees
{
   struct employees *llink;
   char empname[40];
   char empid[20];
   char gender[10];
   char designation[20];
   char emailid[40];
   char salary[10];
   int leaves;
   char bg[5];
   long int phno;
   struct employees *rlink;
};
typedef struct employees *ep;

ep insertfromfile(ep root,ep t)
{
   ep cur=root,prev=0;
   if(!cur)
      return t;
   while(cur)
   {
      if(!strcmp(t->empid,cur->empid))
      {
         printf("REDUNDANCY\n");
         free(t);
         return root;
      }
      prev=cur;
      if(strcmp(t->empid,cur->empid)<1)
         cur=cur->llink;
      else
         cur=cur->rlink;
   }
   if(strcmp(t->empid,prev->empid)<1)
      prev->llink=t;
   else
      prev->rlink=t;
   return root;
}

ep insertfromuser(ep root)
{
    ep last,t;
    MALLOC(t,sizeof(struct employees));
    printf("ENTER THE EMPLOYEE DETAILS: \n\n");
    printf("Employee Name: ");
    scanf("%s",(t->empname));
    printf("Employee ID: ");
    scanf("%s",(t->empid));
    printf("Employee Gender: ");
    scanf("%s",(t->gender));
    printf("Employee Designation: ");
    scanf("%s",(t->designation));
    printf("Employee Email-ID: ");
    scanf("%s",(t->emailid));
    printf("Employee Salary: ");
    scanf("%s",(t->salary));
    t->leaves = 0;
    printf("Employee Blood Group: ");
    scanf("%s",(t->bg));
    printf("Employee Contact Number: ");
    scanf("%ld",&(t->phno));
    
    t->llink=t->rlink=0;
    ep cur=root,prev=0;
    if(!cur)
      return t;
    while(cur)
    {
      if(!strcmp(t->empname,cur->empname))
      {
         printf("REDUNDANCY\n");
         free(t);
         return root;
      }
      prev=cur;
      if(strcmp(t->empname,cur->empname)<1)
         cur=cur->llink;
      else
         cur=cur->rlink;
    }
    if(strcmp(t->empname,prev->empname)<1)
      prev->llink=t;
    else
      prev->rlink=t;
    return root;
}

void writeinfile(ep r,FILE *fp1) 
{
   if(r)
   {
      writeinfile(r->llink,fp1);
      fprintf(fp1,"%s %s %s %s %s %s %d %s %ld\n",(r->empname),(r->empid),(r->gender),(r->designation),(r->emailid),(r->salary),(r->leaves),(r->bg),(r->phno));
      writeinfile(r->rlink,fp1);
   }
}

void inorder(ep r) 
{
   if(r)
   {
      inorder(r->llink);
      printf("\n");
      printf(" %s\t\t%s\t%s\t %s\t\t%s\t\t%s\t\t%d\t\t%s\t\t%ld\n",(r->empname),(r->empid),(r->gender),(r->designation),(r->emailid),(r->salary),(r->leaves),(r->bg),(r->phno));
      inorder(r->rlink);
   }
}

ep case1(ep root)
{
   FILE *fp;
   fp = fopen("data.txt","r");
   if(fp==0)
   {
      printf("File Open Unsuccessfull\n");
      exit(0);
   }
   int i,n;
   fscanf(fp,"%d",&n);
   for(i=0;i<n;i++)
   {
      ep t;
      MALLOC(t,sizeof(struct employees));
      fscanf(fp,"%s%s%s%s%s%s%d%s%ld",(t->empname),(t->empid),(t->gender),(t->designation),(t->emailid),(t->salary),&(t->leaves),(t->bg),&(t->phno));
      t->llink=t->rlink=0;
      root = insertfromfile(root,t);
   }
   fclose(fp);
   return root;
}

int count(ep root)
{
    if(root == NULL)
        return 0;
    else
        return 1 + count(root->llink) + count(root->rlink);
}

ep case2(ep root)
{
   int n=0;
   root = insertfromuser(root);
   FILE *fp1;
   fp1 = fopen("data.txt","w");
   if(fp1==0)
   {
      printf("File Open Unsuccessfull\n");
      exit(0);
   }
   n = count(root);
   fprintf(fp1,"%d\n",n);
   writeinfile(root,fp1);
   fclose(fp1);
   printf("EMPLOYEE SUCCESSFULLY INSERTED!\n");
   return root;
}

void searchbyname(ep r)
{
   if(!r)
   {
      printf("FILE IS EMPTY\n");
      return;
   }
   char name[20];
   printf("\n\t\t\t\t\t\tENTER THE EMPLOYEE NAME = ");
   scanf("%s",name);
   while(r)
   {
      if(!strcmp(name,r->empname))
      {
         printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
         printf("\n EMPLOYEE NAME \tEMPLOYEE ID\tGENDER\tDESIGNATION\tEMAIL-ID\t\t\tSALARY\t\tLEAVES\t\tBLOOD GROUP\tCONTACT NUMBER\n");
         printf("\n %s\t\t%s\t%s\t %s\t\t%s\t\t%s\t\t%d\t\t%s\t\t%ld\n",(r->empname),(r->empid),(r->gender),(r->designation),(r->emailid),(r->salary),(r->leaves),(r->bg),(r->phno));
         return;
      }
      if(strcmp(name,r->empname)<1)
          r=r->llink;
      else
          r=r->rlink;
   }
   printf("\n\t\t\t\t\t\tEMPLOYEE NOT FOUND\n\t\t\t\t\t\tTRY SEARCHING AGAIN!\n");
}

void searchbyid(ep r)
{
   if(!r)
   {
      printf("BST empty\n");
      return;
   }
   char id[20];
   printf("\n\t\t\t\t\t\tENTER THE EMPLOYEE ID = ");
   scanf("%s",id);
   while(r)
   {
      if(!strcmp(id,r->empid))
      {
         printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
         printf("\n EMPLOYEE NAME \tEMPLOYEE ID\tGENDER\tDESIGNATION\tEMAIL-ID\t\t\tSALARY\t\tLEAVES\t\tBLOOD GROUP\tCONTACT NUMBER\n");
         printf("\n %s\t\t%s\t%s\t %s\t\t%s\t\t%s\t\t%d\t\t%s\t\t%ld\n",(r->empname),(r->empid),(r->gender),(r->designation),(r->emailid),(r->salary),(r->leaves),(r->bg),(r->phno));
         return;
      }
      if(strcmp(id,r->empid)<1)
          r=r->llink;
      else
          r=r->rlink;
   }
   printf("\n\t\t\t\t\t\tEMPLOYEE NOT FOUND\n\t\t\t\t\t\tTRY SEARCHING AGAIN!\n");
}

void SBD(ep r,char designation[])
{
   if(!r)
     printf("Unsuccessful search\n");
   if(!strcmp(designation,r->designation))
   {
       printf("\n %s\t\t%s\t%s\t %s\t\t%s\t\t%s\t\t%d\t\t%s\t\t%ld\n",(r->empname),(r->empid),(r->gender),(r->designation),(r->emailid),(r->salary),(r->leaves),(r->bg),(r->phno));
       return;
   }
}

void sbd(ep r,char designation[])
{
   if(r)
   {
      SBD(r,designation);
      sbd(r->llink,designation);
      sbd(r->rlink,designation);
   }
}

void searchbydesignation(ep r)
{
   char designation[20];
   printf("\n\t\t\t\t\t\tENTER THE EMPLOYEE DESIGNATION = ");
   scanf("%s",designation);
   printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
   printf("\n EMPLOYEE NAME \tEMPLOYEE ID\tGENDER\tDESIGNATION\tEMAIL-ID\t\t\tSALARY\t\tLEAVES\t\tBLOOD GROUP\tCONTACT NUMBER\n");
   sbd(r,designation);
}

ep increment(ep r,char emp[])
{
   if(!r)
   {
      printf("\n\t\t\t\t\t\tEMPLOYEE NOT FOUND\n\t\t\t\t\t\tTRY SEARCHING AGAIN!\n");
      return 0;
   }
   if(!strcmp(r->empid,emp))
   {
       char position[20],sal[20];
       printf("\n\t\t\t\t\t\tEMPLOYEE DETAILS = \n");
       printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
       printf("\n EMPLOYEE NAME \tEMPLOYEE ID\tGENDER\tDESIGNATION\tEMAIL-ID\t\t\tSALARY\t\tLEAVES\t\tBLOOD GROUP\tCONTACT NUMBER\n");
       printf("\n %s\t\t%s\t%s\t %s\t\t%s\t\t%s\t\t%d\t\t%s\t\t%ld\n",(r->empname),(r->empid),(r->gender),(r->designation),(r->emailid),(r->salary),(r->leaves),(r->bg),(r->phno));
       printf("\n\t\t\t\t\t\tENTER THE POSITION TO INCREMENT = ");
       scanf("%s",position);
       strcpy(r->designation,position);
       printf("\n\t\t\t\t\t\tENTER THE NEW SALARY OF THE EMPLOYEE = ");
       scanf("%s",sal);
       strcpy(r->salary,sal);
       printf("\n\t\t\t\t\t\tEMPLOYEE HAS BEEN SUCCESSFULLY INCREMENTED\n");
       return r;
   }
   if(!r)
   {
      printf("\n\t\t\t\t\t\tEMPLOYEE NOT FOUND\n\t\t\t\t\t\tTRY SEARCHING AGAIN!\n");
   }
   return r;
}

void inc(ep r,char emp[])
{
   if(r)
   {
      increment(r,emp);
      inc(r->llink,emp);
      inc(r->rlink,emp);
   }
}

void case4(ep r)
{
   int n=0;
   char emp[20];
   printf("\n\t\t\t\t\t\tENTER THE EMPLOYEE EMPLOYEE ID = ");
   scanf("%s",emp);
   inc(r,emp);
   FILE *fp1;
   fp1 = fopen("data.txt","w");
   if(fp1==0)
   {
      printf("File Open Unsuccessfull\n");
      exit(0);
   }
   n = count(r);
   fprintf(fp1,"%d\n",n);
   writeinfile(r,fp1);
   fclose(fp1);
}

ep fireemployee(ep root,char id[],int *ch)
{
   ep cur,parent,q,suc;
   parent=0;
   cur=root;
   while(cur)
   {
      if(!strcmp(id,cur->empid))
      { 
         printf("\n\t\t\t\t\t\tEMPLOYEE HAS BEEN SUCCESSFULLY FIRED!\n");
         break;
      }
      parent=cur;
      if(strcmp(id,cur->empid)<1)
      {
         (*ch)++;
         cur=cur->llink;
      }
      else
      {
         (*ch)++;
         cur=cur->rlink;
      }
   }
   if(!cur)
   { 
      printf("\n\t\t\t\t\t\tEMPLOYEE NOT FOUND\n\t\t\t\t\t\tTRY SEARCHING AGAIN!\n");
      return root;
   }
   if(!cur->llink)
      q=cur->rlink;
   else if(!cur->rlink)
      q=cur->llink;
   else
   {
     suc = cur->rlink;
     while(suc->llink)
        suc=suc->llink;
     suc->llink=cur->llink;
     q=cur->rlink;
   }
   if(!parent) 
      return q;

   if(cur == parent->llink)
      parent->llink = q;
   else
      parent->rlink = q;
   free(cur);
   return root;
}

ep case5(ep root)
{
   int n=0,ch=1;;
   char id[20];
   printf("\n\t\t\t\t\t\tENTER THE EMPLOYEE ID TO FIRE = ");
   scanf("%s",id);
   root = fireemployee(root,id,&ch);
   int cnt=0;
   cnt = count(root);
   
   FILE *fp1;
   fp1 = fopen("data.txt","w");
   if(fp1==0)
   {
      printf("File Open Unsuccessfull\n");
      exit(0);
   }
   n = count(root);
   fprintf(fp1,"%d\n",n);
   writeinfile(root,fp1);
   fclose(fp1);
   return root;
}

int choose()
{
    int ch;
    printf("\n\t\t\t\t\t\tPLEASE ENTER YOUR CHOICE (1-7) = ");
    scanf("%d",&ch);
    if(ch==1 || ch ==2 || ch==3|| ch==4|| ch==5|| ch==6|| ch==7)
        return ch;
    else
      choose();
}

int main()
{
   ep root=0;
   root = case1(root);  //GET DETAILS OF ALL EMPLOYEES FROM FILE

   char pc[10];
   int granted;
   printf("************************************************************************************************************************************************************\n");
   printf("\t\t\t\t\t\t\t\tOFFICE MANAGEMENT SYSTEM\n");
   int j=6;
   for(int i=0;i<6;i++)
   {
      if(j<=3)
        printf("  \t\t\t\t\t\t\t%d chances Left!\n",j);
      
      printf("\n\t\t\t\t\t\tENTER PASSCODE = ");
      scanf("%s",pc);
      granted=0;
      j--;
      
      if(!strcmp(pc,"2021") || !strcmp(pc,"2022") || !strcmp(pc,"2023"))
      {
         granted=1;
         break;
      }
      printf("  \t\t\t\t\t\t\tIncorrect Passcode! Try Again\n");
   }
   
   if(granted==0)
      exit(0);
   
   if(!strcmp(pc,"2021"))
      printf("\n\t\t\t\t\t\tAccess Granted!\n\n\t\t\t\t\t\t\t\tWELCOME Mr. VICE PRESIDENT\n");
   if(!strcmp(pc,"2022"))
      printf("\n\t\t\t\t\t\tAccess Granted!\n\n\t\t\t\t\t\t\t\tWELCOME Mr. ADMINISTRATOR\n");
   if(!strcmp(pc,"2023"))
      printf("\n\t\t\t\t\t\tAccess Granted!\n\n\t\t\t\t\t\t\t\tWELCOME Mr. MANAGER\n");
   
   while(granted)
   {
      printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
      printf("\n\t\t\t\t1.GET THE DETAILS OF ALL THE EMPLOYEES\t\t2.INSERT A NEW EMPLOYEE DETAILS\n");
      printf("\n\t\t3.SEARCH AN EMPLOYEE       4.INCREMENT AN EMPLOYEE       5.FIRE AN EMPLOYEE       6.CHECK-IN CHECK-OUT OF EACH EMPLOYEE       7.EXIT");
      
      int ch,choice;
      printf("\n");
      ch = choose();
      
      switch(ch)
      {
          case 1 : printf("\n");
                   printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                   printf(" EMPLOYEE NAME \tEMPLOYEE ID\tGENDER\tDESIGNATION\tEMAIL-ID\t\t\tSALARY\t\tLEAVES\t\tBLOOD GROUP\tCONTACT NUMBER\n");
                   printf("\n");
                   inorder(root);  //PRINT THE DETAILS OF ALL THE EMPLOYEES
                   break;
          case 2 : root = case2(root);  //INSERT NEW EMPLOYEE DETAILS FROM USER
                   break;
          case 3 : for(;;)  //SEARCH FOR EMPLOYEE DETAILS
                   {
                      printf("\n");
                      printf("\t\t\t1.SEARCH BY HIS/HER NAME \t 2.SEARCH BY HIS/HER ID \t 3.SEARCH BY DESIGNATION \t4.GO BACK\n");
                      printf("\n\t\t\t\t\t\tPLEASE ENTER YOUR CHOICE = ");
                      scanf("%d",&choice);
                      switch(choice)
                      {
                         case 1 : searchbyname(root);
                                  break;
                         case 2 : searchbyid(root);
                                  break;
                         case 3 : searchbydesignation(root);
                                  break;
                         default: break;
                      }
                      break;
                   }
                   break;
          case 4 : case4(root);  //INCREMENT AN EMPLOYEE TO A PARTICULAR POSITION
                   break;
          case 5 : root = case5(root); //FIRE AN EMPLOYEE
                   break;
          case 7 : exit(0);

      }
      
   }
   	
   return 0;
}

