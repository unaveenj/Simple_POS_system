#include<stdio.h>
#include<process.h>
#include<conio.h>
#include<dos.h>
#include<fstream.h>
extern float vattax=0 ;
class head
{


	char Iname[50][50];
	char cname[50];

	protected:
		int totalitems;

		float Qty[3];
		float price[3];
		int vatprice[3];
		void input(void);
		void output(void);
};
class vat:public head
{
	float vats;
	public:
		void vatcal(void);
		void outputs(void);
};
// input customer name and item details
void head::input(void)
{
	cout<<"Enter Customer Name : ";
	cin>>cname;
	cout<<"How many items " << cname << " purchased?";
	cin>>totalitems;
	for(int i=0; i<totalitems; i++)
	{
		cout<<"\n Enter Item Name  "<<i+1<<": ";
		gets(Iname[i]);
		cout<<" Cost : "<<i+1<<": Rs. ";
		cin>>price[i];
		cout<<" Quantity: ";
		cin>>Qty[i];
		price[i]=Qty[i]*price[i];
	}
}
void head::output(void)
{
	int a;
	ifstream infile("COUNT.TXT");
	infile>>a;
	ofstream outfile("COUNT.TXT");
	a+=1;
	outfile<<a;
	outfile.close();
	struct date d;
	getdate(&d);
	printf("Date: %d", d.da_day);
	printf("/%d", d.da_mon);
	printf("/%d\t\t\t", d.da_year);
	struct  time t;
	gettime(&t);
	printf("Time: %2d:%02d:%02d\nBill No: %d\n",t.ti_hour, t.ti_min, t.ti_sec, a);
	int day, mon, year, hour, min, sec;
	day=d.da_day;mon=d.da_mon;year=d.da_year;
	hour=t.ti_hour;min=t.ti_min;sec=t.ti_sec;
	char *mer[4];
	if(hour>12)
	{
		hour=hour-12;
		*mer="P.M.";
	}
	else
	{
		*mer="A.M.";
	}
	{ofstream outfile("HIS.TXT", ios::app);
	outfile<<endl<<"Bill No.: "<<a<<"\tOn day: "<<day<<"/"<<mon<<"/"<<year<<"\t& time: "<<hour<<":"<<min<<":"<<sec<<" "<<*mer<<endl;
	outfile<<"------------------------------------------------------------------------"<<endl;
	cout<<"Name of item\tQuantity \tPrice\n";
	for(int i=0;i<totalitems;i++)
	{
		outfile<<"Name: "<<Iname[i]<<" Qty: "<<Qty[i]<<" Price: "<<price[i]<<endl;
		cout<<Iname[i]<<"\t\t"<<Qty[i]<<"\t\t"<<price[i]<<'\n';
	}
	outfile<<"------------------------------------------------------------------------"<<endl;
	outfile.close();
	}
}
void vat::vatcal(void)
{

	input();

	for(int i=0;i<totalitems;i++)
	{

		vatprice[i]=price[i]+(0.1*price[i]);
		vattax = vattax + (0.1*price[i]);
	}
}
void vat::outputs(void)
{
	output();
	float cash=0,sum=0,qty=0;

	for(int i=0;i<totalitems;i++)
	{
		sum+=vatprice[i];
		qty+=Qty[i];
	       //	vattax += vatprice[i];
	}
	cout<<"Total:------------------------------------------------------------------------";
	cout<<"\n\t\t Tax :                  Rupees :" <<vattax;
	cout<<"\n\t\t Quantity= "<<qty<<"\t\t Rupees= "<<sum;
	cout<<"\n******************************************************************************";
	pay:
	cout<<"\nTransaction Details\n";
	cout<<" \n Total cash given: Rupees : ";
	cin>>cash;
	if(cash>=sum)
		cout<<"Total cash repaid: Rupees : "<<cash-sum<<'\n';
	else
	{	cout<<"Cash given is less than total amount!!!";
		getch();
		goto pay;
	}
}
void main()
{
	vat obj;
	char opt, ch;
	start:
	clrscr();
	cout<<"**************************** \n ******** Sales Inventory ************* \n  ********************************************\n Please Enter Number 1 to enter new sales Record or enter 2 to view sales records...";
	cout<<"\n1.Add New sales Record\t  \n2.\tTo view previous entries\n3.\tExit\n";
	cout<<"Enter your option: ";
	cin>>opt;
	switch(opt)
	{
		// purchase item
		case'1':clrscr();
			obj.vatcal();
			cout<<"Items Entered Successfully... \n Press any key to continue........";
			getch();
			clrscr();
			obj.outputs();
			getch();
			goto start;
			//view item details
		case'2':clrscr();
			ifstream fin;
			fin.open("HIS.TXT", ios::in);
			while(fin.get(ch))
			{
				cout<<ch;
			}
		 fin.close();
			getch();
			goto start;
			// close application
		case'3':cout<<"\n Thanks for using Sales Inventory\n ";
			delay(1000);
			exit(0);
	}
	getch();
}