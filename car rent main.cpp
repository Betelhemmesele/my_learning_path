using namespace std;
#include <iostream>
#include <cstdlib>
#include<conio.h>
#include<unistd.h>
#include<fstream>
#include<string>
#include<windows.h>
#include<limits>
#include<iomanip>
int vehicle_no=0,start=1,customer_no=0,registry_no=0,service_no=0,str;

//the following line is necessary for the
//  GetConsoleWindow() function to work!
//it basically says that you are running this
//  program on Windows 2000 or higher
#define _WIN32_WINNT 0x0500
COORD coord={0,0};void gotoxy(int x, int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
fstream file;

struct date
{
int year ;
int month ;
int day;
long int seconds_elapsed;
};


struct  service
{
 char *description=new char[str];
 float price;
 int id;

};
struct vehicle {
 char *name=new char[str];
 char *type=new char[str];
float price;
 char *plate_no=new char[str];
int availablity;
int id;

} ;

struct customer
{
 char *name=new char[str];
 int id;
long int phone_no;

};

struct registration
{
    int customer_id;
    int car_id;
   date local_date   ;
    int duration ;
    bool return_check;
    int receipt_id;
    float total_price ;

};

void customer_registration( );
registration registry(int customer_id,int vehicle_id,vehicle *vehicle_info);
void vehicle_registration();
int rent(customer *customer_info, vehicle *vehicle_info,registration *registry_info);
void customer_table_printer (customer customer_info);
void title_printer (string title);
void body_printer(string body);
void vehicle_table_printer (vehicle vehicle_info);
void registry_table_printer (registration registry_info);
void cin_fix();
void notifications (registration *registry_info,vehicle *vehicle_info);
main()
{
    if(start==1)
    {
        file.open("numbers.txt",ios::in);
        if (file.is_open())
        {
 file>>vehicle_no>>customer_no>>registry_no>> service_no;
 file.close();
        }
    }
    service *service_package;
    customer *customer_info;
    registration *registry_info;
    vehicle *vehicle_info;


service_package= new service [service_no+1];
customer_info=new customer [customer_no+1];
registry_info=new registration[registry_no+1];
vehicle_info=new vehicle [vehicle_no+1];


file.open("customer_info.txt",ios::in);
if (file.is_open())
{
   for (int i=1;i<=customer_no;i++ )
   {
       string id;
       string phone_no;
    file>>customer_info[i].name>>id>> phone_no;
    customer_info[i].id=stoi(id);
    customer_info[i].phone_no=stol(phone_no);

   }
   file.close();
}
file.open("vehicle_info.txt",ios::in);
if (file.is_open())
{

   for (int i=1;i<=vehicle_no;i++ )
   {
       string price,availablity,id;

    file>>vehicle_info[i].name>>vehicle_info[i].type>>price>>vehicle_info[i].plate_no>>availablity>>id;
   vehicle_info[i].price=stof(price);
    vehicle_info[i].availablity=stoi(availablity);
    vehicle_info[i].id=stoi(id);
   }
   file.close();
}
file.open("registry_info.txt");
if(file.is_open())
    {
for (int i=1;i<=registry_no;i++)
{
    string customer_id,car_id,duration,date_year,date_month,date_day,date_sec,return_check,receipt_id,total_price;
file>>customer_id>>car_id>>date_year>>date_month>>date_day>>date_sec>>duration>> return_check>>receipt_id>>total_price;
registry_info[i].customer_id=stoi(customer_id);
registry_info[i].car_id=stoi(car_id);
registry_info[i].local_date.year=stoi(date_year);
registry_info[i].local_date.month=stoi(date_month);
registry_info[i].local_date.day=stoi(date_day);
registry_info[i].local_date.seconds_elapsed=stol(date_sec);
registry_info[i].duration=stoi(duration);
registry_info[i].return_check=stoi(return_check);
registry_info[i].receipt_id=stoi(receipt_id);
registry_info[i].total_price=stof(total_price);
}
 file.close();
    }

    // Get the console handle
    HWND console = GetConsoleWindow();

    //MoveWindow(window_handle, x, y, width, height, redraw_window);
    MoveWindow(console, 300, 0, 1000, 800, TRUE);
    label:
    system ("cls");

    cout <<"\n\n\t\t\t#----------------------------------------------------------------------------- \n";
    cout <<"\t\t\t#                   car  rental service portal                               #\n"
         <<"\t\t\t#                                                                            #\n"
         <<"\t\t\t#----------------------------------------------------------------------------# \n";
    cout <<"\t\t\t#       press the corresponding number from  the following options:          #\n"
         <<"\t\t\t#----------------------------------------------------------------------------# \n";
    cout <<"\t\t\t#  1. view daily notifications                                               # \n"
         <<"\t\t\t#  2. register a new vehicle                                                 # \n"
         <<"\t\t\t#  3. register a new customer                                                #\n"
         <<"\t\t\t#  4. process a vehicle rent                                                 #\n"
         <<"\t\t\t#  5. add a service package                                                  #\n"
         <<"\t\t\t#  6.open receipt archive                                                    #\n"
         <<"\t\t\t#  7.open customer list archive                                              #\n"
         <<"\t\t\t#  8.open vehicle list archive                                               #\n"
         <<"\t\t\t#  9.to delete whole data                                                    #\n"
         <<"\t\t\t#  0.to exit                                                                 #\n"
         <<"\t\t\t#                                                                            #\n"
         <<"\t\t\t#///////////////////////////////////////////////////////////////////////////// \n" ;
 char user_choice;
 user_choice=getch();
 start=0;
 switch(user_choice)
 {
case '1':
notifications (registry_info,vehicle_info);
break;
case '2':
    vehicle_registration();
   main();
case '3':
    {
   customer_registration();


   main();
   break;}
case '4':
int status; //checks if the vehicle is reserved or rented
status=rent(customer_info,vehicle_info,registry_info);
switch (status)
{
    case 1 :
    vehicle_info[vehicle_no].availablity=0;
    case 2:
    vehicle_info[vehicle_no].availablity=2;
}
    main();
case '5':
    system("cls");
    label5:
    body_printer("enter the service description");
    cin>>service_package[service_no].description;
    if (cin.fail())
{
    cin_fix();
    goto label5;
}
label6:
    body_printer("enter the service percent reduction");
     cin>>service_package[service_no].price;
     if (cin.fail())
{
    cin_fix();
    goto label6;
}
    char flag;
    body_printer("press any key to return to the home screen");
    flag=getch();
     goto label;
    break;
case '6':

  {
      system("cls");
    title_printer("registry list");
    body_printer("choose a way to sort the list");
    body_printer("press 1,for newest  first");
    body_printer("press 2,for oldest first");
    char op;
    op=getch();
    switch(op)
    {
    case '1' :
{
system("cls");
 int count1=registry_no-1;
int count2=0;
    for(int i=1;i<=registry_no;i++)
    {
        for(int j=1;j<=registry_no;j++)
        {
            if ( registry_info[i].local_date.seconds_elapsed > registry_info[j].local_date.seconds_elapsed)
                count2++;
        }
        if (count2 >= count1)
        {

        registry_table_printer(registry_info[i]);
        count1--;
        }
    }

break; }


case '2':
    system("cls");
 int count1=registry_no-1;
int count2=0;
    for(int i=1;i<=registry_no;i++)
    {
        for(int j=1;j<=registry_no;j++)
        {
             if ( registry_info[i].local_date.seconds_elapsed < registry_info[j].local_date.seconds_elapsed)
                count2++;
        }
        if (count2 >= count1)
        {

        registry_table_printer(registry_info[i]);
        count1--;
        }
    }



    break; }
body_printer("press 1,to search");
  body_printer("press 2,to select registry");
  body_printer("press any key,to return to the starting screen");
char op1;
  op1=getch();
  switch (op1)
  {
  case '1':
  {
      system("cls");
body_printer("search with ");
body_printer(" 1, customer id ");
body_printer(" 2, vehicle id ");
char op2;
op2=getch();
system("cls");
label7:
body_printer("enter key word ");

switch(op2)
{
case '1':
    {
        int customer_id ;
        cin>>customer_id;
        if (cin.fail())
{
    cin_fix();
    goto label7;
}
        for (int i=1;i<=registry_no;i++)
        {
            if (registry_info[i].customer_id==customer_id)
                registry_table_printer(registry_info[i]);
        }
    break;}

case '2':
    {
        int vehicle_id ;
        cin>>vehicle_id;
        if (cin.fail())
{
    cin_fix();
    goto label7;
}
        for (int i=1;i<=registry_no;i++)
        {
            if (registry_info[i].car_id==vehicle_id)
                registry_table_printer(registry_info[i]);
        }
  break;  }
}

  }
case '2':
   {
       label8:
    body_printer("enter the corresponding id of the registry you want to select");
    body_printer(" or enter 0 to return to the starting screen");
    int id ;
    cin>>id;if (cin.fail())
{
    cin_fix();
    goto label8;
}
    if (id==0)
        main();
    system("cls");
body_printer("press 1,to delete this registry ");
body_printer("press any other key to return to the starting page");
   char op3;
   op3=getch();
   switch(op3)
   {

   case '1':
       {
    body_printer("deleted");
    usleep(500000);
    registry_no--;
    for (int i=id;i<=registry_no;i++)
    {
        registry_info[i]=registry_info[i+1];
    }
    file.open("registry_info.txt",ios::out);
for (int i=1;i<=registry_no;i++ )
         {

 file<<registry_info[i].customer_id<<" "<<registry_info[i].car_id<<" "<<registry_info[i].local_date.year<<" "<<registry_info[i].local_date.month<<" "<<registry_info[i].local_date.day<<" "<<registry_info[i].local_date.seconds_elapsed<<" "<<registry_info[i].duration<<" "<<registry_info[i].return_check<<" "<<registry_info[i].receipt_id<<" "<<registry_info[i].total_price;

         }
        file.close();
        main();
   }

default:
    main();
  }

break ;
 }

   default:
    main();
  }
  break;
  }


case '7' :
    {

    system("cls");
    title_printer("customers list");
    body_printer("choose a way to sort the list");
    body_printer("press 1,for ascending order");
    body_printer("press 2,for descending order");
    char op;
    op=getch();
    switch(op)
    {

case '1' :
{
system("cls");
 int count1=customer_no-1;
int count2=0;
    for(int i=1;i<=customer_no;i++)
    {
        for(int j=1;j<=customer_no;j++)
        {
            if (strcmpi(customer_info[i].name,customer_info[j].name) <0)
                count2++;
        }
        if (count2 >= count1)
        {

        customer_table_printer(customer_info[i]);
        count1--;
        }
    }

break; }


case '2':
    system("cls");
 int count1=customer_no-1;
int count2=0;
    for(int i=1;i<=customer_no;i++)
    {
        for(int j=1;j<=customer_no;j++)
        {
            if (strcmpi(customer_info[i].name,customer_info[j].name) >0)
                count2++;
        }
        if (count2 >= count1)
        {

        customer_table_printer(customer_info[i]);
        count1--;
        }
    }



    break; }

    body_printer("press 1,to search");
  body_printer("press 2,to select customers");
  body_printer("press any key,to return to the starting screen");
char op1;
  op1=getch();
  switch (op1)
  {
  case '1':
  {
      system("cls");
body_printer("search with ");
body_printer(" 1, customer name ");
body_printer(" 2, customer id ");
char op2;
op2=getch();
system("cls");
label9:
body_printer("enter key word ");

switch(op2)
{
case '1':
    {
        string name ;
        cin>>name;
        if (cin.fail())
{
    cin_fix();
    goto label9;
}
        for (int i=1;i<=customer_no;i++)
        {
            if (customer_info[i].name==name)
                customer_table_printer(customer_info[i]);
        }
    break;}

case '2':
    {
        int id ;
        cin>>id;
        if (cin.fail())
{
    cin_fix();
    goto label9;
}
        for (int i=1;i<=customer_no;i++)
        {
            if (customer_info[i].id==id)
                customer_table_printer(customer_info[i]);
        }
  break;  }
}

  }
case '2':
   {
       label10:
    body_printer("enter the corresponding id of the customer you want to select");
    body_printer(" or enter 0 to return to the starting screen");
    int id ;
    cin>>id;
    if (cin.fail())
{
    cin_fix();
    goto label10;
}
    if (id==0)
        main();
    system("cls");
    body_printer("press 1,to modify this customer");
body_printer("press 2,to delete this customer ");
body_printer("press any other key to return to the starting page");
   char op3;
   op3=getch();
   switch(op3)
   {
   case '1':
    {
        system("cls");
    label11:
        body_printer("enter the name of the customer");
        cin>>customer_info[id].name;
if (cin.fail())
{
    cin_fix();
    goto label11;
}
label12:
        body_printer("enter the phone number of the customer");
        cin>>customer_info[id].phone_no;
if (cin.fail())
{
    cin_fix();
    goto label12;
}
        file.open("customer_info.txt",ios::out);
         for (int i=1;i<=customer_no;i++ )
         {

  file<<customer_info[i].name <<" "<<customer_info[i].id<<" "<<customer_info[i].phone_no<<" "<<endl;

         }
        file.close();
  main();  }

   case '2':
       {
    body_printer("deleted");
    usleep(500000);
    customer_no--;
    for (int i=id;i<=customer_no;i++)
    {
        customer_info[i]=customer_info[i+1];
    }
for (int i=1;i<=customer_no;i++ )
         {

 file<<customer_info[i].name <<" "<<customer_info[i].id<<" "<<customer_info[i].phone_no<<" "<<endl;

         }
        file.close();
        main();
   }

default:
    main();
  }

break ;
 }

   default:
    main();
  }
  }

case '8':
  {
      system("cls");
    title_printer("vehicle list");
    body_printer("choose a way to sort the list");
    body_printer("press 1,for ascending order");
    body_printer("press 2,for descending order");
    char op1;
    op1=getch();
    switch(op1)
    {

case '1' :
{
system("cls");
 int count1=vehicle_no-1;
int count2=0;
    for(int i=1;i<=vehicle_no;i++)
    {
        for(int j=1;j<=vehicle_no;j++)
        {
            if (strcmpi(vehicle_info[i].name,vehicle_info[j].name) <0)
                count2++;
        }
        if (count2 >= count1)
        {

        vehicle_table_printer(vehicle_info[i]);
        count1--;
        }
    }

}
break ;

case '2':
    system("cls");
 int count1=vehicle_no-1;
int count2=0;
    for(int i=1;i<=vehicle_no;i++)
    {
        for(int j=1;j<=vehicle_no;j++)
        {
            if (strcmpi(vehicle_info[i].name,vehicle_info[j].name) >0)
                count2++;
        }
        if (count2 >= count1)
        {

        vehicle_table_printer(vehicle_info[i]);
        count1--;
        }
    }

break;

    }
  body_printer("press 1,to search");
  body_printer("press 2,to select vehicles");
  body_printer("press any key,to return to the starting screen");
  op1=getch();
  switch (op1)
  {
  case '1':
  {
      system("cls");
body_printer("search with ");
body_printer(" 1, vehicle name ");
body_printer(" 2, vehicle type ");
body_printer(" 3, vehicle id ");
char op2;
op2=getch();
system("cls");
label13:
body_printer("enter key word ");

switch(op2)
{
case '1':
    {
        string name ;
        cin>>name;if (cin.fail())
{
    cin_fix();
    goto label13;
}
        for (int i=1;i<=vehicle_no;i++)
        {
            if (vehicle_info[i].name==name)
                vehicle_table_printer(vehicle_info[i]);
        }
    break;}
 case '2':
    {
        string type ;
        cin>>type;
        if (cin.fail())
{
    cin_fix();
    goto label13;
}
        for (int i=1;i<=vehicle_no;i++)
        {
            if (vehicle_info[i].type==type)
                vehicle_table_printer(vehicle_info[i]);
        }
    break;}
case '3':
    {
        int id ;
        cin>>id;
        if (cin.fail())
{
    cin_fix();
    goto label13;
}
        for (int i=1;i<=vehicle_no;i++)
        {
            if (vehicle_info[i].id==id)
                vehicle_table_printer(vehicle_info[i]);
        }
  break;  }
}

  }
case '2':
   {
       label14:
    body_printer("enter the corresponding id of the vehicle you want to select");
    body_printer(" or enter 0 to return to the starting screen");
    int id ;
    cin>>id;
    if (cin.fail())
{
    cin_fix();
    goto label14;
}
    if (id==0)
        main();
    system("cls");
    body_printer("press 1,to modify this vehicle");
body_printer("press 2,to delete this vehicle ");
body_printer("press any other key to return to the starting page");
   char op3;
   op3=getch();
   switch(op3)
   {
   case '1':
    {label15:
        system("cls");
        body_printer("enter the name of the vehicle");
        cin>>vehicle_info[id].name;
        if (cin.fail())
{
    cin_fix();
    goto label15;
}
label16:
        body_printer("enter the type of the vehicle");
        cin>>vehicle_info[id].type;
        if (cin.fail())
{
    cin_fix();
    goto label16;
}
label17:
        body_printer("enter the price per day of the vehicle");
        cin>>vehicle_info[id].price;
        if (cin.fail())
{
    cin_fix();
    goto label17;
}
label18:
        body_printer("enter the plate no of the vehicle");
        cin>>vehicle_info[id].plate_no;
        if (cin.fail())
{
    cin_fix();
    goto label18;
}
label19:
        body_printer("is the vehicle available for rent(1,for available 2,for unavailable)");
        cin>>vehicle_info[id].availablity;
        if (cin.fail())
{
    cin_fix();
    goto label19;
}
        file.open("vehicle_info.txt",ios::out);
         for (int i=1;i<=vehicle_no;i++ )
         {

 file<<vehicle_info[i].name <<" "<<vehicle_info[i].type<<" "<<vehicle_info[i].price<<" "<< vehicle_info[i].plate_no<<" "<< vehicle_info[i].availablity<<" "<<vehicle_info[i].id<<" "<<endl;

         }
        file.close();
  main();  }

   case '2':
       {
    body_printer("deleted");
    usleep(500000);
    vehicle_no--;
    for (int i=id;i<=vehicle_no;i++)
    {
        vehicle_info[i]=vehicle_info[i+1];
    }
for (int i=1;i<=vehicle_no;i++ )
         {

 file<<vehicle_info[i].name <<" "<<vehicle_info[i].type<<" "<<vehicle_info[i].price<<" "<< vehicle_info[i].plate_no<<" "<< vehicle_info[i].availablity<<" "<<vehicle_info[i].id<<" "<<endl;

         }
        file.close();
        main();
   }

default:
    main();
  }

break ;
 }

   default:
    main();
  }
  }
   case '0':
    break;
   case '9':
    {
        system("cls");
        body_printer("select the type of archive you want to erase");\
        body_printer("1, customer archive");
        body_printer("2, vehicle archive");
        body_printer("3, registry archive");
        char choice;
        choice=getch();
        switch(choice)
        {
        case '1':
            customer_no=0;
            file.open("customer_info.txt",ios::out);
            break;
        case '2':
            vehicle_no=0;
            file.open("vehicle_info.txt",ios::out);
            break;

        case '3':
            registry_no=0;
            file.open("registry_info.txt",ios::out);
            break;
        }
        body_printer("deleted");
        usleep(500000);

    }
   default:
    main();
 }
 file.open("numbers.txt",ios::out);
 file<<vehicle_no<<" "<<customer_no<<" "<<registry_no<<" "<<service_no;
 file.close();




}
void customer_registration( )
{

char flag ='0';
    while (flag == '0')
    {
customer_no++;
        system("cls");
label23:
        body_printer("enter the customer's name");
        string customer_name;
        cin>>customer_name;
        if (cin.fail())
{
    cin_fix();
    goto label23;
}


        label21:
        body_printer("enter the customer's phone number");
        long int phone_number;
        cin>>phone_number;
        if (cin.fail())
        {
cin_fix();
goto label21;
      }
        int customer_id=customer_no;


        file.open("customer_info.txt",ios::app);


            file<<customer_name <<" "<<customer_id<<" "<<phone_number<<" "<<endl;

        file.close();

         body_printer(" press 0 to continue registration ,or press any other key to return to the home screen ");
   flag=getch();
    }



}
registration registry(int customer_id,int vehicle_id,vehicle *vehicle_info)
{
     // current date/time based on current system
   time_t now = time(0);

   tm *ltm = localtime(&now);
system("cls");
label22:
cout<<"enter the duration of the contract in days \n";
int duration;
    cin>>duration;
    if (cin.fail())
{
    cin_fix();
    goto label22;
}
float total_price=(duration*vehicle_info[vehicle_id-1].price);
file.open("registry_info.txt",ios::out);

registry_no++;

file<<customer_id<<" "<<vehicle_id<<" "<<(1900 + ltm->tm_year)<<" "<<(1 + ltm->tm_mon)<<" "<<(ltm->tm_mday)<<" "<<now<<" "<<duration<<" "<< "0"<<" "<<registry_no<<" "<<total_price<<endl;
registration registry_info;
registry_info.customer_id=customer_id;
registry_info.car_id=vehicle_id;
registry_info.local_date.year=(1900 + ltm->tm_year);
registry_info.local_date.month=(1 + ltm->tm_mon);
registry_info.local_date.day=(ltm->tm_mday);
registry_info.local_date.seconds_elapsed=now;
registry_info.duration=duration;
registry_info.return_check=0;
registry_info.receipt_id=registry_no;
registry_info.total_price=total_price;

 file.close();

return  registry_info;

    }
void vehicle_registration()
{


    char flag ='0';
    while (flag == '0')
    {
        vehicle_no++;
        system("cls");
        label24:
    body_printer("enter the vehicle's name ");

    string name;

  cin>>name;
  if (cin.fail())
{
    cin_fix();
    goto label24;
}

label25:
body_printer("enter the vehicle's type (automobile,truck,motorbike,bus)");
string type;
 cin>>type;
 if (cin.fail())
{
    cin_fix();
    goto label25;
}
label26:
body_printer("enter the vehicle's price per day ");

    float price;
    cin>>price;
    if (cin.fail())
{
    cin_fix();
    goto label26;
}
label27:
    body_printer("enter the vehicle's plate no ");
string plate_no;

   cin>>plate_no;
   if (cin.fail())
{
    cin_fix();
    goto label27;
}
label28:
 body_printer("is the vehicle available for rent (enter 1 for yes,0 for no) ");
  int availablity;
  cin>>availablity;
  if (cin.fail())
{
    cin_fix();
    goto label28;
}
  int id=vehicle_no;
vehicle_no++;
 file.open("vehicle_info.txt",ios::app);


            file<<name <<" "<<type<<" "<<price<<" "<< plate_no<<" "<< availablity<<" "<<id<<" "<<endl;

        file.close();
    body_printer("press 0 to continue registration ,or press any other key to return to the home screen ");

   flag=getch();
    }

main();

return;
}
int rent(customer *customer_info, vehicle *vehicle_info,registration *registry_info)
{

        system("cls");
  cout <<  "press 1 ,to reserve a vehicle \n"
  <<"press 2, to rent out a vehicle \n"
  <<"press 0, to return to the home  screen";
  char user_choice;
  user_choice=getch();
  switch (user_choice)
  {
  case '1':
     label29:
          system("cls");
if (customer_no==0)
    body_printer("there are no customers registered");
    else
{
title_printer("choose the customer from the following list and enter the corresponding id  ");
for (int i=1;i<=customer_no;i++)
    {

    customer_table_printer(customer_info[i]);
    }
}

body_printer("if the customer is new please go back and register him/her at the home screen");
body_printer("enter 0 to return to the home screen");
int customer_id ;

cin>>customer_id;
if (cin.fail() || customer_id>customer_no || customer_id<0 )
{
    cin_fix();
    goto label29;
}

if (customer_id==0)
{
    main();

}
label30:
    system("cls");
title_printer("choose the vehicle from the following list and enter the corresponding id ");
for (int i=1;i<vehicle_no;i++)
    if (vehicle_info[i].availablity==1)
{
    vehicle_table_printer(vehicle_info[i]);
}
body_printer("or enter 0 to cancel this process and return to the home screen");
int vehicle_id ;

cin>>vehicle_id;
if (cin.fail() || vehicle_id>vehicle_no || vehicle_id<0 )
{
    cin_fix();
    goto label30;
}
if (vehicle_id==0)
{
    main();

}
registration registry_info;
registry_info=registry(customer_id,vehicle_id,vehicle_info);

body_printer("here is the receipt");
registry_table_printer(registry_info);
body_printer("press any key to return to the starting screen");
getch();
return 2;
      break;
  case '2':

  label31:
          system("cls");
if (customer_no==0)
    body_printer("there are no customers registered");
    else
{
title_printer("choose the customer from the following list and enter the corresponding id  ");
for (int i=1;i<=customer_no;i++)
    {

    customer_table_printer(customer_info[i]);
    }
}
body_printer("if the customer is new please go back and register him/her at the home screen");
body_printer("enter 0 to return to the home screen");


cin>>customer_id;
if (cin.fail() || customer_id>customer_no || customer_id<0 )
{
    cin_fix();
    goto label31;
}

if (customer_id==0)
{
    main();

}
label32:
    system("cls");
title_printer("choose the vehicle from the following list and enter the corresponding id ");
for (int i=1;i<vehicle_no;i++)
    if (vehicle_info[i].availablity==1)
{
    vehicle_table_printer(vehicle_info[i]);
}
body_printer("or enter 0 to cancel this process and return to the home screen");


cin>>vehicle_id;
if (cin.fail() || vehicle_id>vehicle_no || vehicle_id<0 )
{
    cin_fix();
    goto label32;
}
if (vehicle_id==0)
{
    main();

}

registry_info=registry(customer_id,vehicle_id,vehicle_info);

body_printer("here is the receipt");
registry_table_printer(registry_info);
body_printer("press any key to return to the starting screen");
getch();
return 1;
      break;
}

}
void customer_table_printer (customer customer_info)
{
    for (int y=12;y<24;y++)
{
gotoxy(31,y);
cout<<"|";
gotoxy(102,y);
cout<<"|";
}
for (int y=11;y<26;y+=4)
{
gotoxy(32,y);
  cout << setfill ('-') << setw (70)<<"-";

}
gotoxy(32,13);
cout <<"customer's id : "<<customer_info.id;
gotoxy(32,17);
cout <<"customer's name : "<<customer_info.name;
gotoxy(32,21);
cout<<"customer's phone number: "<<customer_info.phone_no;
gotoxy (32,25);
}

void title_printer (string title)
{


  int width =(133-title.length())/2;
 gotoxy(width-39+title.length()/2,5);
cout <<"------------------------------------------------------------------------------ \n";
  gotoxy(width,6 );
  cout <<title;
   gotoxy(width-39+title.length()/2,7);
  cout <<"------------------------------------------------------------------------------ \n";
}
void body_printer(string body)
{
     cout <<"\n \t \t \t ------------------------------------------------------------------------------ \n";
    cout<<"\t \t \t ###  "<<body;
    cout <<"\n \t \t \t ------------------------------------------------------------------------------ \n";
}
void vehicle_table_printer (vehicle vehicle_info)
{
    for (int y=12;y<36;y++)
{
gotoxy(31,y);
cout<<"|";
gotoxy(102,y);
cout<<"|";
}
for (int y=11;y<36;y+=4)
{
gotoxy(32,y);
  cout << setfill ('-') << setw (70)<<"-";

}
gotoxy(32,13);
cout <<"vehicles's id : "<<vehicle_info.id;
gotoxy(32,17);
cout <<"vehicle's name : "<<vehicle_info.name;
gotoxy (32,21);
cout<<"vehicle's type: "<<vehicle_info.type;
gotoxy(32,25);
cout<<"vehicle's plate number: "<<vehicle_info.plate_no;
gotoxy (32,29);
cout<<"vehicle's price per day: "<<vehicle_info.price;
gotoxy (32,33);
switch (vehicle_info.availablity)
{
case 0:
cout<<"vehicle's availability: not available ";
break;
case 1:
cout<<"vehicle's availability: available ";
break;
case 2:
cout<<"vehicle's availability: reserved ";
break;

}
gotoxy(32,41);
}
void registry_table_printer (registration registry_info)
{
    for (int y=12;y<40;y++)
{
gotoxy(31,y);
cout<<"|";
gotoxy(102,y);
cout<<"|";
}
for (int y=11;y<40;y+=4)
{
gotoxy(32,y);
  cout << setfill ('-') << setw (70)<<"-";

}
gotoxy(32,13);
cout <<"customers's id : "<<registry_info.customer_id;
gotoxy(32,17);
cout <<"vehicle's id : "<<registry_info.car_id;
gotoxy (32,21);
cout<<"date rented (dd/mm/yy): "<<registry_info.local_date.day<<"/"<<registry_info.local_date.month<<"/"<<registry_info.local_date.year;
gotoxy(32,25);
cout<<"duration : "<<registry_info.duration<<" days";
gotoxy (32,29);
switch (registry_info.return_check)
{
case 0:
cout<<"is returned: NO ";
break;
case 1:
cout<<"is returned: YES ";
break;

}
gotoxy(32,33);
cout<<"receipt id :" <<registry_info.receipt_id;
gotoxy(32,37);
cout<<" total price :" <<registry_info.total_price;
gotoxy(32,43);
}
void cin_fix()
{
               cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');

cout<<"invalid input ";
usleep(500000);
system("cls");
}
void notifications (registration *registryinfo,vehicle *vehicle_info)
{
    label35:
        system("cls");
    title_printer("today's over dues are :");

    // current date/time based on current system
   time_t now = time(0);

   tm *ltm = localtime(&now);
   if (registry_no==0)
   {
    body_printer("no data");
    usleep(4000000);
    main();
    return;
   }

  for (int i=0;i<registry_no;i++)
  {
    if ((registryinfo[i].local_date.seconds_elapsed+(registryinfo[i].duration*86400))<now && registryinfo[i].return_check==0)
    {
      registry_table_printer(registryinfo[i]);

    }
  }
  label34:
  cout<<"please enter the id of the receipt you wish to process or enter 0 if to return to the home screen :";
  int receipt_id;
  cin>>receipt_id;
  if (cin.fail())
{
    cin_fix();
    goto label34;
}
  if (receipt_id==0)
    {
        main();
        return ;
    }

       if (receipt_id<registry_no)
      {
          if ((registryinfo[receipt_id-1].local_date.seconds_elapsed+(registryinfo[receipt_id-1].duration*86400))<now && registryinfo[receipt_id-1].return_check==0)
      {
          int overdue=((vehicle_info[(registryinfo[receipt_id-1].car_id-1)].price)*(now-(registryinfo[receipt_id-1].local_date.seconds_elapsed+(registryinfo[receipt_id-1].duration*86400))))/86400;
     cout <<"\n \t \t \t ------------------------------------------------------------------------------ \n";
    cout<<"\t \t \t ### overdue = "<<overdue;
    cout <<"\n \t \t \t ------------------------------------------------------------------------------ \n";
body_printer("press 1 to process this receipt, or press any other key to return to the  notifications window");
char user_choice;
user_choice=getch();
if (user_choice==1)
{
registryinfo[receipt_id-1].return_check=1;
title_printer("transaction completed");
body_printer ("press 1,to go to the notifications window or press any other key to return to the home screen");
char user_choice2;
user_choice2=getch();
switch(user_choice2)
{
case '1':
    goto label35;
    break;
default :
    main();
    return;
}

}
else
    main();
    return;
      }
      else
{
body_printer("no overdue");
body_printer ("press 1,to go to the notifications window or press any other key to return to the home screen");
char user_choice3;
user_choice3=getch();
switch(user_choice3)
{
case '1':
    goto label35;
    break;
default :
    main();
    return ;
}

}
      }
      else
      {
          body_printer("invalid input please try again");
          goto label34;
      }
      }

