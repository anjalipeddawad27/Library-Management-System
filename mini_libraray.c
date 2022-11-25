#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>                  //contains strcmp(),strcpy(),strlen(),etc
#include<ctype.h>                   //contains toupper(), tolower(),etc
#include<dos.h>                     //contains _dos_getdate
#include<time.h>
//#include<bios.h>

//#define RETURNTIME 15

char catagories[][15]={"Computer","Electronics","Electrical","Civil","Mechnnical","Architecture"};
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
//list of glob
FILE *fp,*ft,*fs;//global file can access program
//list of global variable
int s;
char findbook;
struct meroDate
{
int mm,dd,yy;
};
struct books
{
int id;
char stname[20];
char name[20];
char Author[20];
int quantity;
float Price;
int count;
int rackno;
char *cat;
struct meroDate issued;
struct meroDate duedate;
};
struct books a;
void main()
{
//loaderanim();
system("cls");
//    textbackground(13);
int i,t;
printf("\n 1. Add Books   ");
printf("\n 2. Delete books");
printf("\n 3. Search Books");
printf("\n 4. Issue Books");
printf("\n 5. View Book list");
printf("\n 6. Edit Book's Record");
printf("\n 7. Close Application");
//t();
printf("\n Enter your choice:");
switch(getch())
{
case '1':
addbooks();
break;
case '2':
deletebooks();
break;
case '3':
searchbooks();
break;
case '4':
issuebooks();
break;
case '5':
viewbooks();
break;
case '6':
editbooks();
break;
case '7':
{
system("cls");
printf("\tLibrary Management System");
printf("\tMini Project in C");
printf("\tis brought to you by");
}
default:
{
printf("\n Wrong Entry!!Please re-entered correct option");
if(getch())
main();
}

}
}
void addbooks(void)    //funtion that add books
{
system("cls");
int i;
printf("\n************SELECT CATEGOIES**************");
printf("\n 1. Computer");
printf("\n 2. Electronics");
printf("\n 3. Electrical");
printf("\n 4. Civil");
printf("\n 5. Mechanical");
printf("\n 6. Architecture");
printf("\n 7. Back to main menu");
printf("\n Enter your choice:");
scanf("%d",&s);
if(s==7)

main() ;
system("cls");
fp=fopen("Bibek.dat","ab+");
if(getdata()==1)
{
a.cat=catagories[s-1];
fseek(fp,0,SEEK_END);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
printf("\n The record is sucessfully saved");
printf("\n Save any more?(Y / N):");
if(getch()=='n')
main();
else
system("cls");
addbooks();
}
}void deletebooks()    //function that delete items from file fp
{
system("cls");
int d;
char another='y';
while(another=='y')  //infinite loop
{
system("cls");
printf("\n Enter the Book ID to  delete:");
scanf("%d",&d);
fp=fopen("Bibek.dat","rb+");
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id==d)
{

printf("\n The book record is available");
printf("\n Book name is %s",a.name);
//printf("Rack No. is %d",a.rackno);
findbook='t';
}
}
if(findbook!='t')
{
printf("\n No record is found modify the search");
if(getch())
main();
}
if(findbook=='t' )
{
if(getch()=='y')
{
ft=fopen("test.dat","wb+");  //temporary file for delete
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id!=d)
{
fseek(ft,0,SEEK_CUR);
fwrite(&a,sizeof(a),1,ft); //write all in tempory file except that
}                              //we want to delete
}
fclose(ft);
fclose(fp);
remove("Bibek.dat");
rename("test.dat","Bibek.dat"); //copy all item from temporary file to fp except that
fp=fopen("Bibek.dat","rb+");    //we want to delete
if(findbook=='t')
{
printf("\n The record is sucessfully deleted");
printf("\n Delete another record?(Y/N)");
}
}
else
main();
fflush(stdin);
another=getch();
}
}
main();
}
void searchbooks()
{
system("cls");
int d;
printf("*****************************Search Books*********************************");
printf("\n 1. Search By ID");
printf("\n 2. Search By Name");
printf("\n Enter Your Choice");
fp=fopen("Bibek.dat","rb+"); //open file for reading propose
rewind(fp);   //move pointer at the begining of file
switch(getch())
{
case '1':
{
system("cls");
printf("****Search Books By Id****");
printf("\n  the book id:");
scanf("%d",&d);
printf("\n Searching........");
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id==d)
{
printf("\n The Book is available");
printf("\n ID:%d",a.id);
printf("\n Name:%s",a.name);
printf("\n Author:%s ",a.Author);
//printf("\n Qantity:%d ",a.quantity);
printf("\n Price:Rs.%.2f",a.Price);
//printf("\n Rack No:%d ",a.rackno);
findbook='t';
}

}
if(findbook!='t')  //checks whether conditiion enters inside loop or not
{
printf("\n No Record Found");
}
printf("\n Try another search?(Y/N)");
if(getch()=='y')
searchbooks();
else
main();
break;
}
case '2':
{
char s[15];
system("cls");
printf("****Search Books By Name****");
printf("\n Enter Book Name:");
scanf("%s",s);
int d=0;
while(fread(&a,sizeof(a),1,fp)==1)
{
if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
{
printf("\n The Book is available");
printf("\n ID:%d",a.id);
printf("\n Name:%s",a.name);
printf("\n Author:%s",a.Author);
printf("\n Qantity:%d",a.quantity);
printf("\n Price:Rs.%.2f",a.Price);
//printf("\n Rack No:%d ",a.rackno);
d++;
}

}
if(d==0)
{
printf("\aNo Record Found");
}
printf("\n Try another search?(Y/N)");
if(getch()=='y')
searchbooks();
else
main();
break;
}
default :
getch();
searchbooks();
}
fclose(fp);
}
void issuebooks(void)  //function that issue books from library
{
int RETURNTIME,t;

system("cls");
printf("*******ISSUE SECTION*******");
printf("\n 1. Issue a Book");
printf("\n 2. View Issued Book");
printf("\n 3. Search Issued Book");
printf("\n 4. Remove Issued Book");
printf("Enter a Choice:");
switch(getch())
{
case '1':  //issue book
{
system("cls");
int c=0;
char another='y';
while(another=='y')
{
system("cls");
printf("***Issue Book section***");
printf("\n Enter the Book Id:");
scanf("%d",&t);
fp=fopen("Bibek.dat","rb");
fs=fopen("Issue.dat","ab+");
if(checkid(t)==0) //issues those which are present in library
{
printf("The book record is available");
printf("The name of book is %s",a.name);
printf("Enter student name:");
scanf("%s",a.stname);
//struct dosdate_t d; //for current date
//_dos_getdate(&d);
//a.issued.dd=d.day;
//a.issued.mm=d.month;
//a.issued.yy=d.year;
printf("Issued date=%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
printf("The BOOK of ID %d is issued",a.id);
a.duedate.dd=a.issued.dd+RETURNTIME;   //for return date
a.duedate.mm=a.issued.mm;
a.duedate.yy=a.issued.yy;
if(a.duedate.dd>30)
{
a.duedate.mm+=a.duedate.dd/30;
a.duedate.dd-=30;

}
if(a.duedate.mm>12)
{
a.duedate.yy+=a.duedate.mm/12;
a.duedate.mm-=12;

}
printf("To be return:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
fseek(fs,sizeof(a),SEEK_END);
fwrite(&a,sizeof(a),1,fs);
fclose(fs);
c=1;
}
if(c==0)
{
printf("No record found");
}
printf("Issue any more(Y/N):");
fflush(stdin);
another=getche();
fclose(fp);
}

break;
}
case '2':  //show issued book list
{
system("cls");
int j=4;
printf("*******************************Issued book list*******************************\n");
printf("\n STUDENT NAME   \n  CATEGORY   \n ID   \n BOOK NAME   \n ISSUED DATE  \n  RETURN DATE");
fs=fopen("Issue.dat","rb");
while(fread(&a,sizeof(a),1,fs)==1)
{

printf("%s",a.stname);
printf("%s",a.cat);
printf("%d",a.id);
printf("%s",a.name);
printf("%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy );
printf("%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
//struct dosdate_t d;
//_dos_getdate(&d);
//            printf("Current date=%d-%d-%d",d.day,d.month,d.year);
j++;

}
fclose(fs);
returnfunc();
}
break;
case '3':   //search issued books by id
{
system("cls");
printf("Enter Book ID:");
int p,c=0;
char another='y';
while(another=='y')
{

scanf("%d",&p);
fs=fopen("Issue.dat","rb");
while(fread(&a,sizeof(a),1,fs)==1)
{
if(a.id==p)
{
issuerecord();
printf("Press any key.......");
getch();
issuerecord();
c=1;
}

}
fflush(stdin);
fclose(fs);
if(c==0)
{
printf("No Record Found");
}
printf("Try Another Search?(Y/N)");
another=getch();
}
}
break;
case '4':  //remove issued books from list
{
system("cls");
int b;
FILE *fg;  //declaration of temporary file for delete
char another='y';
while(another=='y')
{
printf("\n Enter book id to remove:");
scanf("%d",&b);
fs=fopen("Issue.dat","rb+");
while(fread(&a,sizeof(a),1,fs)==1)
{
if(a.id==b)
{
issuerecord();
findbook='t';
}
if(findbook=='t')
{
printf("Do You Want to Remove it?(Y/N)");
if(getch()=='y')
{
fg=fopen("record.dat","wb+");
rewind(fs);
while(fread(&a,sizeof(a),1,fs)==1)
{
if(a.id!=b)
{
fseek(fs,0,SEEK_CUR);
fwrite(&a,sizeof(a),1,fg);
}
}
fclose(fs);
fclose(fg);
remove("Issue.dat");
rename("\n record.dat","Issue.dat");
printf("\n The issued book is removed from list");

}

}
if(findbook!='t')
{
printf("\n No Record Found");
}
}
printf("\n Delete any more?(Y/N)");
another=getch();
}
}
default:
printf("\n Wrong Entry!!");
getch();
issuebooks();
break;
}
returnfunc();
}
void viewbooks(void)  //show the list of book persists in library
{
int i=0,j;
system("cls");
printf("********Book List******");
printf(" \n CATEGORY    \n ID   \n BOOK NAME    \n AUTHOR     \n  PRICE  ");
j=4;
fp=fopen("Bibek.dat","rb");
while(fread(&a,sizeof(a),1,fp)==1)
{
printf("\n Category- %s",a.cat);
printf("\n Book_ID- %d",a.id);
printf("\n Book_Name- %s",a.name);
printf("\n Author_Name- %s",a.Author);
printf("\n Book_Price- %.2f",a.Price);
printf("\n \n \n\n \n");
j++;
i=i+a.quantity;
}
printf("\n Total Books =%d",i);
fclose(fp);
returnfunc();
}
void editbooks(void)  //edit information about book
{
system("cls");
int c=0;
int d,e;
printf("****Edit Books Section****");
char another='y';
while(another=='y')
{
system("cls");
printf("\n Enter Book Id to be edited:");
scanf("%d",&d);
fp=fopen("Bibek.dat","rb+");
while(fread(&a,sizeof(a),1,fp)==1)
{
if(checkid(d)==0)
{
printf("\n The book is availble");
printf("\n The Book ID:%d",a.id);
printf("\n Enter new name:");
scanf("%s",a.name);
printf("\n Enter new Author:");
scanf("%s",a.Author);
printf("\n Enter new quantity:");
scanf("%d",&a.quantity);
printf("\n Enter new price:");
scanf("%f",&a.Price);
//printf("\n Enter new rackno:");
//scanf("%d",&a.rackno);
printf("\n The record is modified");
fseek(fp,ftell(fp)-sizeof(a),0);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
c=1;
}
if(c==0)
{
printf("\n No record found");
}
}
printf("\n Modify another Record?(Y/N)");
fflush(stdin);
another=getch() ;
}
returnfunc();
}
void returnfunc(void)
{
{
printf(" \n Press ENTER to return to main menu");
}
a:
if(getch()==13) //allow only use of enter
main();
else
goto a;
}

int getdata()
{
int t;
printf("\n Enter the Information Below");
printf("\n Category:");
printf("%s",catagories[s-1]);
printf("\n Book ID:\t");
scanf("%d",&t);
if(checkid(t) == 0)
{
printf("\n The book id already exists\a");
getch();
main();
return 0;
}
a.id=t;
printf("\n Book Name:");
scanf("%s",a.name);
printf("\n Author:");
scanf("%s",a.Author);
//printf("\n Quantity:");
//scanf("%d",&a.quantity);
printf("\n Price:");
scanf("%f",&a.Price);
//printf("\n Rack No:");
//scanf("%d",&a.rackno);
return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
if(a.id==t)
return 0;  //returns 0 if book exits
return 1; //return 1 if it not
}
int t(void) //for time
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}
void issuerecord()  //display issued book's information
{
system("cls");
printf("\n The Book has taken by Mr. %s",a.stname);
printf("\n Issued Date:%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
printf("\n Returning Date:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
}
