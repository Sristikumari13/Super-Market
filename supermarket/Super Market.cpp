//*******************************************************
//           HEADER FILE USED IN PROJECT
//*******************************************************
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
using namespace std;
//********************************************************
//           CLASS USED IN PROJECT
//*********************************************************
class product
{
	int pno;
	char name[50];
	float price,qty,tax,dis;
	public:
		void create_product()
		{
			cout<<"\nPlease Enter The Product No. of The Product: ";
			cin>>pno;
			cout<<"\n\nPlease Enter The Name of The Product: ";
			fflush(stdin);
			gets(name);
			cout<<"\nPlease Enter The Price Of The Product: ";
			cin>>price;
			cout<<"\nPlease Enter The Discout(%): ";
			cin>>dis;
		}
		void show_product()
		{
			cout<<"\nThe Product No. of The Product: "<<pno;
			cout<<"\nThe Name Of The Product: ";
			puts(name);
			cout<<"\nThe Price of The Product: "<<price;
			cout<<"\nDiscount: "<<dis;
		}
		int retpno()
		{
			return pno;
		}
		float retprice()
		{
			return price;
		}
		char* retname()
		{
			return name;
		}
		int retdis()
		{
			return dis;
		}
};
//***************************************************************
//       GLOBAL DECLARATION FOR STREAM OBJECT,OBJECT
//***************************************************************

fstream fp;
product pr;

//***************************************************************
//        FUNCTION TO WRITE IN FILE
//***************************************************************

void write_product()
{
	fp.open("Shop.dat",ios::out|ios::app);
	pr.create_product();
	fp.write((char*)&pr,sizeof(product));
	fp.close();
	cout<<"\n\nThe Product Has Been Created ";
	getch();
}

//****************************************************************
//             FUNCTION TO READ ALL RECORDS FROM FILE
//****************************************************************


void display_all()
{
	cout<<"\n\n\n\tDISPLAY ALL RECORD !!!\n\n";
	fp.open("Shop.dat",ios::in);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		pr.show_product();
		cout<<"\n\n=========================================";
		getch();
	}
	fp.close();
}

//*****************************************************************
//    FUNCTION TO READ SPECIFIC RECORD FROM FILE
//*****************************************************************

void display_sp(int n)
{
	int flag=0;
	fp.open("Shop.dat",ios::in);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		if(pr.retpno()==n)
		{
			pr.show_product();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	{
		cout<<"\n\nRECORD NOT EXIST";
	}
}

//***********************************************************
//      FUNCTION TO MODIFY RECORD OF FILE
//***********************************************************
void modify_product()
{
	int no,found=0;
	cout<<"\n\n\tTo Modify ";
	cout<<"\n\n\tPlease Enter The Product No. of The Product: ";
	cin>>no;
	fp.open("Shop.dat",ios::in|ios::out);
	while(fp.read((char*)&pr,sizeof(product) && found==0))
	{
		fp.close();
		if(found==0)
		{
			cout<<"\n\nRECORD NOT FOUND ";
		}
	}
}

//***************************************************************
//         FUNCTION TO DELETE RECORD OF FILE
//***************************************************************

void delete_product()
{
	int no;
	cout<<"\n\n\nDelete Record";
	cout<<"\n\nPlease Enter The Product no. Of The Product You Want TO Delete: ";
	cin>>no;
	fp.open("Shop.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		if(pr.retpno()!=no)
		{
			fp2.write((char*)&pr,sizeof(product));
		}
	}
	fp2.close();
	fp.close();
	remove("Shop.dat");
	rename("Temp.dat","Shop.dat");
	cout<<"\n\n\tRecord Deleted...";
}

//*********************************************************************
//     FUNCTION TO DISPLAY ALL PRODUCTS PRICE LIST
//*********************************************************************

void menu()
{
	fp.open("Shop.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN \n\n\n Go To Admin Menu To Create File";
		cout<<"\n\n\n Program is closing.....";
		exit(0);
	}
	cout<<"\n\n\t PRODUCT MENU\n\n";
	cout<<"\n=============================================\n";
	cout<<"\P.NO. \t\tName \t\tPRICE\n";
	cout<<"\n=============================================\n";
	
	while(fp.read((char*)&pr,sizeof(product)))
	{
		cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	}
	fp.close();
}
//***********************************************************************
//        FUNCTION TO PLACE ORDER AND GENERATING BILL FOR PRODUCTS
//***********************************************************************

void place_order()
{
	int order_arr[50],quan[50],c=0;
	float amt,damt,total=0;
	char ch='Y';
	menu();
	cout<<"\n======================================";
	cout<<"\n       PLACE YOUR ORDER";
	cout<<"\n======================================\n";
	do
	{
		cout<<"\n\nEnter The Product No. Of The Product: ";
		cin>>order_arr[c];
		cout<<"\nEnter Quantity In Number: ";
		cin>>quan[c];
		c++;
		cout<<"\nDo You Want To Order Another Product ?(y/n): ";
		cin>>ch;
	}while(ch=='y' || ch=='Y');
	cout<<"\n\nThank You For Placing The Order";
	cout<<"\n*INVOICE*";
	cout<<"\nPr No. \tPr Name \tQuantity \tPrice \tAmount \tAmount After Discount\n";
	for(int x=0;x<=c;x++)
	{
		fp.open("Shop.dat",ios::in);
		fp.read((char*)&pr,sizeof(product));
		while(!fp.eof())
		{
			if(pr.retpno()==order_arr[x])
			{
				amt=pr.retprice()*quan[x];
				damt=amt-(amt*pr.retdis()/100);
				cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
				total+=damt;
			}
			fp.read((char*)&pr,sizeof(product));
		}
		fp.close();
	}
	cout<<"\n\n\t\t\t\tTOTAL= "<<total;
}
//***********************************************************************
//                      INTRODUCTION FUNCTION
//***********************************************************************

void intro()
{
	cout<<"SUPER MARKET";
	cout<<" BILLING";
	cout<<" PROJECT";
	cout<<"\n\nMADE BY: SRISTI KUMARI";
	cout<<"\n\nREG. NO: 2130510";
	cout<<"\n\nCLASS: GCS";
	cout<<"\n\nCOLLEGE: SLIET";
	getch();
}
//********************************************************************
//                  ADMINSTRATION MENU FUNCTION
//********************************************************************

void admin_menu()
{
	char ch2;
	cout<<"\n\n\nADMIN MENU";
	cout<<"\n\n\t1.CREATE PRODUCT";
	cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
	cout<<"\n\n\t3.QUERY";
	cout<<"\n\n\t4.MODIFY PRODUCT";
	cout<<"\n\n\t5.DELETE PRODUCT";
	cout<<"\n\n\t6.VIEW PRODUCT MENU";
	cout<<"\n\n\t7.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-7): ";
	ch2=getche();
	switch(ch2)
	{
		case '1':
			write_product();
			break;
		case '2':
		    display_all();
			break;	
		case '3':
		    int num;
			cout<<"\n\nPlease Enter The Product No: ";
			cin>>num;
			display_sp(num);
			break;
		case '4':
		    modify_product();
			break;
		case '5':
		    delete_product();
			break;
		case '6':
		    menu();
		case '7':
		    break;
		default:
		    cout<<"\a";admin_menu();						
	}
}

//***************************************************************
//              THE MAIN FUNCTION OF PROGRAM
//***************************************************************


int main()
{
	int ch;
	intro();
	do
	{
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t1. CUSTOMER";
		cout<<"\n\n\t2. ADMINISTRATOR";
		cout<<"\n\n\t3. EXIT";
		cout<<"\n\n\t Please Select Your Option(1-3): ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				place_order();
				break;
			case 2:
			    admin_menu();
				break;
			case 3:
			    exit(0);
			default:
			    cout<<"\a";			
		}
	}while(ch!='3');	
}
//*************************************************************
//              END OF PROJECT
//**************************************************************
