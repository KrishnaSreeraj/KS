#include<fstream.h>
#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>

class doctor
     {          int DID;
		char dname[20];
		char dadd[30];
		long int dphone;
		float fee;
	public:
		void enterdrdetails();
		void drdetails1()
		{    cout<<"\n"<<DID<<"\t"<<dname<<"\t\t"<<dadd<<"\t\t"
		     <<dphone <<"\t"<<fee;
		}

		void drdetails2()
		    {
		     cout<<"\nDoctor ID         : "<<DID;
		     cout<<"\nDoctor name       : "<<dname;
		     cout<<"\nDoctor Address    : "<<dadd;
		     cout<<"\nDoctor phone      : "<<dphone;
		     cout<<"\nDoctor fee(Rs.)   : "<<fee;
		    }
		int getDID()
		   {return DID;
		   }
		float getfee()
		   {return fee;
		   }
		void modify1();


     };
     int createdid()
   {  int value1;
	  doctor d6;
		fstream file1;
		file1.open("Doctor1.dat",ios::in|ios::binary);
		if(file1)
		 {
		   file1.seekg(0,ios::beg);
		   while(file1.read((char*)&d6,sizeof(d6)));
		   value1= d6.getDID();
		   ++value1;
		 }
		 else
		  value1=1;


		file1.close();

	 return value1;
  }
void doctor::enterdrdetails()
    {
      DID=createdid();
      cout<<"\nDoctor ID                        : ";
      cout<<DID;

      cout<<"\n\nEnter the doctor's name          : ";
      gets(dname);
      cout<<"\nEnter the doctor's address       : ";
      gets(dadd);
      cout<<"\nEnter the doctor's phone number  : ";
      cin>>dphone;
      cout<<"\nEnter the fees(Rs.)              : ";
      cin>>fee;

   }

void doctor::modify1()

    {
      cout<<"\nDoctor ID       : "<<DID;
      cout<<"\nDoctor name     : "<<dname;
      cout<<"\nDoctor Address  : "<<dadd;
      cout<<"\nDoctor phone    : "<<dphone;
      cout<<"\nDoctor fee(Rs.) : "<<fee;
      char n1[20],ad1[30];
      long int dph;
      float fee1;
      cout<<"\n\nEnter the new name";
      cout<<"( enter '.'to retain the old name)     : ";
      gets(n1);
      cout<<"\nEnter the new address";
      cout<<"( enter '*'to retain the old address)  : ";
      gets(ad1);
      cout<<"\nEnter the new phone no.";
      cout<<"( enter '1'to retain the old number)   : ";
      cin>>dph;
      cout<<"\nEnter the new fee(Rs.)";
      cout<<"( enter '2'to retain the old fee)      : ";
      cin>>fee1;
      if(strcmp(n1,".")!=0)
	strcpy(dname,n1);
      if(strcmp(ad1,"*")!=0)
	strcpy(dadd,ad1);
      if(dph!=1)
	dphone=dph;
      if(fee1!=2)
	fee=fee1;
    }

void addDoctor()
    { doctor d1;
      d1.enterdrdetails();
      ofstream ofile;
      ofile.open("Doctor1.dat",ios::app|ios::binary);
	  ofile.write((char*)&d1,sizeof(d1));
	  clrscr();

	ofile.close();
    }

void deletedoctor()
    { doctor d2;
      int flag1=0;
      char confirm1='n';
      ifstream ifile;
      ifile.open("Doctor1.dat",ios::binary);
      ofstream ofile;
      ofile.open("Temp1.dat",ios::binary);
      int did1;
      cout<<"\nEnter the ID of the doctor whose record is to be deleted : ";
      cin>>did1;
      while(ifile)
	   {ifile.read((char*)&d2,sizeof(d2));
	    if(ifile.eof())break;
	    if(d2.getDID()==did1)
	      {d2.drdetails2();
	       flag1=1;
	       cout<<"\n\nAre you sure you want to delete ";
	       cout<<"this record(y/n) ? : ";
	       cin>>confirm1;
	       if(confirm1=='n')
		 ofile.write((char*)&d2,sizeof(d2));
	      }
	    else
	       ofile.write((char*)&d2,sizeof(d2));

	   }
	   if(flag1==0)
	      cout<<"\n\nSorry!!Such a Doctor ID does not exist.";
	   ifile.close();
	   ofile.close();
	   remove("Doctor1.dat");
	   rename("Temp1.dat","Doctor1.dat");
    }
void modifydoctor()
    { int did2;
      char found1='f';
      long pos1;
      doctor d3;
      fstream file1;
      file1.open("Doctor1.dat",ios::in|ios::out|ios::binary);
      cout<<"\nEnter the doctor ID to be modified : ";
      cin>>did2;
      while(file1)
	   { pos1=file1.tellg();
	     file1.read((char*)&d3,sizeof(d3));
	     if (file1.eof()) break;
	     if(d3.getDID()==did2)
	       { d3.modify1();
		 file1.seekg(pos1);
		 file1.write((char*)&d3,sizeof(d3));
		 found1='t';
		 break;
	       }
	   }
	  if(found1=='f')
	    cout<<"\n\nSorry!!Record not found.";
	  file1.close();
    }

void alldoctor()
    {
      doctor d4;
      ifstream ifile;
      ifile.open("Doctor1.dat",ios::binary);
      cout<<"\nReport of all the doctors";
      cout<<"\n\nID"<<"\t"<<"Name"<<"\t\t"<<"Address"<<"\t\t"<<"Phone"
	  <<"\t"<<"Fee";
      while(ifile)
	   {ifile.read((char*)&d4,sizeof(d4));
	     if(ifile.eof())
		  {break;
		  }
	     d4.drdetails1();
	     if(ifile.eof())
		  {break;
		  }

	   }
	   getch();
	 ifile.close();
    }
void indidoctor()
    { doctor d5;
      int did3,flag2=0;
      long pos2;
      ifstream ifile;
      ifile.open("Doctor1.dat",ios::binary);
      clrscr();
      cout<<"\nEnter the ID of the Doctor whose";
      cout<<"record is to be displayed : ";
      cin>>did3;
      clrscr();
      while(ifile)
	   {pos2=ifile.tellg();
	    ifile.read((char*)&d5,sizeof(d5));
	     if(d5.getDID()==did3)
		{ifile.seekg(pos2);
		 d5.drdetails2();
		 flag2=1;
		 getch();
		 break;
		}

	   }
       if(flag2==0)
       {
	 cout<<"\nSorry!!Such a Doctor Report does not exist.";
	 getch();
	}
       ifile.close();
    }
void doctor_report()
    { int ch2;

      do
	{clrscr();
	 cout<<"\n\t\t\tDoctor Report";
	 cout<<"\n\n1.Report of all the doctors";
	 cout<<"\n2.Individual Doctor Report";
	 cout<<"\n3.Go back to main menu";
	 cout<<"\n\nEnter the choice : ";
	 cin>>ch2;
	 switch(ch2)
	  {case 1: clrscr();
		   alldoctor();
		   break;
	   case 2 :clrscr();
		   indidoctor();
		   break;
	   case 3 :break;
	   default:cout<<"\nSorry!!You have entered the wrong choice.";
	  }
	}while(ch2<3);
     }

void doctor_menu()
{
	clrscr();
	int chD;
	do
	  {clrscr();
	   cout<<"\n\t\t\tDoctor Menu";
	   cout<<"\n\n1.Add doctor";
	   cout<<"\n2.Delete doctor";
	   cout<<"\n3.Modify doctor";
	   cout<<"\n4.Go back to main menu";
	   cout<<"\n\nEnter the choice : ";
	   cin>>chD;

	   switch(chD)
	    {case 1 :clrscr();
		     addDoctor();
		     break;
	     case 2 :clrscr();
		     deletedoctor();
		     break;
	     case 3 :clrscr();
		     modifydoctor();
		     break;
	     case 4 :break;
	     default:cout<<"\n\nSorry!! You have entered the wrong choice.";
	    }
	 }while(chD<4);

}
class patient
     {          int PID,DID;
		char pname[20],dis[30];
		char padd[30];
		long int Pphone;
		float lfee,mfee,fee,tot;
		char sex;
	public:
		void enterpatdetails();
		void patdetails1()
		{ cout<<"\n"<<PID<<"\t"<<pname<<"\t"<<sex<<"\t"
		  <<padd<<"\t"<<Pphone<<"\t"<<dis
		  <<"\t"<<DID<<"\t"<<lfee<<"\t"<<mfee<<"\t"<<fee<<"\t"<<tot;
		}
		void patdetails2()
		   {cout<<"\nPatient ID        : "<<PID;
		    cout<<"\nPatient name      : "<<pname;
		    cout<<"\nPatient's sex     : "<<sex;
		    cout<<"\nPatient Address   : "<<padd;
		    cout<<"\nPatient phone no. : "<<Pphone;
		    cout<<"\nDisease           : "<<dis;
		    cout<<"\nDoctor ID.        : "<<DID;
		    cout<<"\nLab fee(Rs.)      : "<<lfee;
		    cout<<"\nMedical fee(Rs.)  : "<<mfee;
		    cout<<"\nDoctor fee(Rs.)   : "<<fee;
		    cout<<"\n Total fee	       : "<<tot;
		   }
		int getPID()
		 {  return PID;
		 }
		void modify2();
		void calctot()
		  { tot=lfee+mfee+fee;

		  }
		 int retDID()
		    {return DID;
		    }
		 void assignfee( float f)
		 { fee=f;}
		 void updatefee(float l,float m)
		 { lfee=l;
		   mfee=m;
		 }

     };
     int createpid()
     {  int value2;
	  patient p7;
		fstream file1;
		file1.open("Patient.dat",ios::in|ios::binary);
		if(file1)
		 {
		   file1.seekg(0,ios::beg);
		   while(file1.read((char*)&p7,sizeof(p7)));
		   value2= p7.getPID();
		   ++value2;
		 }
		 else
		  value2=1;


		file1.close();

	 return value2;
  }
void patient::enterpatdetails()
    { cout<<"\nPatient ID                       : ";
      PID=createpid();
      cout<<PID;
      cout<<"\n\nEnter the patient's name         : ";
      gets(pname);
      cout<<"\nEnter the patient's sex(M/F)     : ";
      cin>>sex;
      cout<<"\nEnter the patient's address      : ";
      gets(padd);
      cout<<"\nEnter the patient's phone number : ";
      cin>>Pphone;
      cout<<"\nEnter the patient's disease      : ";
      cin>>dis;
      cout<<"\nEnter the doctor ID              : ";
      cin>>DID;
      lfee=0;
      mfee=0;
      tot=0;
    }
   void patient::modify2()
    {
      cout<<"\nPatient ID        : "<<PID;
      cout<<"\nPatient name      : "<<pname;
      cout<<"\nPatient sex       : "<<sex;
      cout<<"\nPatient Address   : "<<padd;
      cout<<"\nPatient phone no. : "<<Pphone;
      cout<<"\nDisease           : "<<dis;
      cout<<"\nDoctor no.        : "<<DID;
      cout<<"\nLab fee(Rs.)      : "<<lfee;
      cout<<"\nMedical fee(Rs.)  : "<<mfee;
      cout<<"\nDoctor fee(Rs.)   : "<<fee;
      char Pn1[20],Pad1[30],dis1[30];
      char sex1;
      long int Pph;
      float fee1,lfee1,mfee1;
      int did2;
      cout<<"\n\nEnter the new name";
      cout<<"( enter '#'to retain the old name)      : ";
      gets(Pn1);
      cout<<"\nEnter the sex";
      cout<<"( enter '0'to retain the sex)           : ";
      cin>>sex1;
      cout<<"\nEnter the new address";
      cout<<"( enter '&'to retain the old address)   : ";
      gets(Pad1);
      cout<<"\nEnter the new phone no.";
      cout<<"( enter '-1'to retain the old number)    : ";
      cin>>Pph;
      cout<<"\nEnter the new disease";
      cout<<"( enter '!'to retain the old disease)   : ";
      gets(dis1);
      cout<<"\nEnter the new lab fee(Rs.)";
      cout<<"( enter '-1'to retain the old lab fee)   : ";
      cin>>lfee1;
      cout<<"\nEnter the new medical fee(Rs.)";
      cout<<"(enter '-1'to retain the old med fee)    : ";
      cin>>mfee1;
      if(strcmp(Pn1,"#")!=0)
	strcpy(pname,Pn1);
      if(sex1!=0)
	 sex=sex1;
      if(strcmp(Pad1,"&")!=0)
	strcpy(padd,Pad1);
      if(Pph!= -1)
	 Pphone=Pph;
      if(strcmp(dis1,"!")!=0)
	strcpy(dis,dis1);
      if(lfee1!= -1)
	 lfee=lfee1;
      if(mfee1!= -1)
	mfee=mfee1;
	tot=lfee+mfee+fee;
    }
void addPatient()
    { patient p1;
      doctor d6;
      int d,flag=0;
      float fe;
      p1.enterpatdetails();
      d=p1.retDID();
      ifstream ifile;
      ifile.open("Doctor1.dat",ios::binary);
      while(!ifile.eof())
	   {ifile.read((char*)&d6,sizeof (d6));
	    if(d6.getDID()==d)
	      {  flag=1;
		 fe=d6.getfee();
		 cout<<"\nDoctor's fee                     : "<<fe;
		 getch();
		 break;
	      }
	   }

      if(flag==1)
     { p1.assignfee(fe);
       p1.calctot();
       ofstream ofile;
       ofile.open("Patient.dat",ios::app|ios::binary);
	  ofile.write((char*)&p1,sizeof(p1));
	  //clrscr();
	ofile.close();
     }
     else
	{ cout<<"\nSuch a Doctor does not exist!!";
	  getch();
	  }
    }
void deletepatient()
    { patient p2;
      char confirm2='n';
      int flag3=0;
      ifstream ifile;
      ifile.open("Patient.dat",ios::binary);
      ofstream ofile;
      ofile.open("Temp2.dat",ios::binary);
      int pid;
      cout<<"\nEnter the ID of the patient whose record is to be deleted : ";
      cin>>pid;
      while(ifile)
	   {ifile.read((char*)&p2,sizeof(p2));
	    if(ifile.eof())
	      {break;
	      }
	    if(p2.getPID()==pid)
	      {p2.patdetails2();
	       flag3=1;
	       cout<<"\n\nAre you sure you want to";
	       cout<<" delete this record(y/n) ? : ";
	       cin>>confirm2;
	       if(confirm2=='n')
		  ofile.write((char*)&p2,sizeof(p2));
	      }
	    else
		ofile.write((char*)&p2,sizeof(p2));
	   }
	   if(flag3==0)
	      cout<<"\n\nSorry,such a Patient ID does not exist.";
	   ifile.close();
	   ofile.close();
	   remove("Patient.dat");
	   rename("Temp2.dat","Patient.dat");
    }
void modifypatient()
    { int pid2;
      char found2='f';
      long pos3;
      patient  p3;
      fstream file1;
      file1.open("Patient.dat",ios::in|ios::out|ios::binary);
      clrscr();
      cout<<"\nEnter the patient's ID whose record is to be modified : ";
      cin>>pid2;
      while(file1)
	   { pos3=file1.tellg();
	     file1.read((char*)&p3,sizeof(p3));
	     if (file1.eof())
		break;
	     if(p3.getPID()==pid2)
	       { p3.modify2();
		 file1.seekg(pos3);
		 file1.write((char*)&p3,sizeof(p3));
		 found2='t';
		 break;
	       }
	   }
	  if(found2=='f')
	   { cout<<"\n\nSorry!!Record not found.";
	     getch();
	   }
	  file1.close();
    }
 void allpatient()
    {
      patient p4;
      ifstream ifile;
      ifile.open("Patient.dat",ios::binary);
       cout<<"\n\nPatient's Information";
	   cout<<"\nID"<<"\tName"<<"\tSex"<<"\tAddress"<<"\tPhone"
	   <<"\tDisease"<<"\tDr.ID"
	   <<"\tLab Fee"<<"\tMed fee"<<"\tDr.fee"<<"\t Total fee";
      while(ifile.read((char*)&p4,sizeof(p4)))
	  {
	     p4.patdetails1();
	   }
	 getch();
	 ifile.close();
    }
void indipatient()
    { patient p5;
      int pid3,flag4=0;
      long pos4;
      ifstream ifile;
      ifile.open("Patient.dat",ios::binary);
      clrscr();
      cout<<"\nEnter the ID of the Patient whose";
      cout<<"record is to be displayed : ";
      cin>>pid3;
     // clrscr();
      while(ifile)
	   {pos4=ifile.tellg();
	    ifile.read((char*)&p5,sizeof(p5));
	     if(p5.getPID()==pid3)
		{ifile.seekg(pos4);
		// clrscr();
		 p5.patdetails2();
		 flag4=1;
		 getch();
		 break;
		}

	   }
       if(flag4==0)
       {
	 cout<<"\nSorry!!Such a Patient Report does not exist.";
	 getch();
	 }
       ifile.close();
    }
void bill()
{ clrscr();
  patient p6;
  int pid4;
  char date1[11];
  cout<<"\nEnter the date :";
  gets(date1);
  cout<<"\nEnter the ID of the Patient whose record is to be displayed : ";
  cin>>pid4;
  int flag5=0;
  float lf,mf,t;
  long pos5;
  fstream file1;
  file1.open("Patient.dat",ios::in|ios::out|ios::binary);
  cout<<"\nEnter the lab fee : ";
  cin>>lf;
  cout<<"\nEnter the medicinal fee : ";
  cin>>mf;
    clrscr();
  while(!file1.eof())
       {  pos5=file1.tellg();
	  file1.read((char*)&p6,sizeof(p6));
	     if(p6.getPID()==pid4)
	      { file1.seekg(pos5);
		 p6.updatefee(lf,mf);
		 p6.calctot();
		 file1.write((char*)&p6,sizeof(p6));
		 flag5=1;
		 break;
	      }
       }

      file1.close();
      if(flag5==1)
      {
      ifstream ifile1;
      ifile1.open("Patient.dat",ios::binary);
      while(!ifile1.eof())
       {  ifile1.read((char*)&p6,sizeof(p6));
	     if(p6.getPID()==pid4)
	     { //t=p6.total();
	     //  break;

		 clrscr();
		 cout<<"\t\t\t\tASTER MEDCITY";
		 cout<<"\n\t\t\t    We'll Treat You Well ";
		 cout<<"\n\n\t\t\t  Kuttysahib Road,Near P.O,";
		 cout<<"\n\t\t\t  Cheraneloor,Kothad Bridge,";
		 cout<<"\n\t\t\t  South Chittoor,Kochi";
		       "\n\t\t\t  Kerala 682027";
		 cout<<"\n\t\t\t  Ph : 0484 6699999 ";
		 cout<<"\n===============================";
		 cout<<"=================================================";
		 cout<<"\n\n\tDate : "<<date1;
		 cout<<"\n\n";
		 p6.patdetails2();
	       //	 cout<<"\n\nTotal Amount      = Rs."<<p6.total();
		 getch();
		 flag5=1;
		 break;
		}
	 }
      }
      else
	 { cout<<"\n\nSorry!!Such a patient does not exist.";
	    getch();
	 }
}
void patient_report()
    { int ch4;
      do
	{clrscr();
	 cout<<"\n\t\t\tPatient Report";
	 cout<<"\n\n1.Report of all the patients";
	 cout<<"\n2.Report of a particular patient";
	 cout<<"\n3.Bill";
	 cout<<"\n4.Go back to main menu";
	 cout<<"\n\nEnter the choice : ";
	 cin>>ch4;
	 switch(ch4)
	  {case 1 :clrscr();
		   allpatient();
		   break;
	   case 2 :clrscr();
		   indipatient();
		   break;
	   case 3 :bill();
		   break;
	   case 4 :break;
	   default:cout<<"\nSorry!!You have entered the wrong choice.";
	  }
	}while(ch4<4);
     }


void patient_menu()
{
	clrscr();
	int chP;
	do
	  {clrscr();
	   cout<<"\n\t\t\tPatient Menu";
	   cout<<"\n\n1.Add Patient";
	   cout<<"\n2.Delete Patient";
	   cout<<"\n3.Modify Patient";
	   cout<<"\n4.Go back to main menu";
	   cout<<"\n\nEnter the choice : ";
	   cin>>chP;

	   switch(chP)
	    {case 1 :clrscr();
		     addPatient();
		     break;
	     case 2 :clrscr();
		     deletepatient();
		     break;
	     case 3 :clrscr();
		     modifypatient();
		     break;
	     case 4 :break;
	     default:cout<<"\n\nSorry!! You have entered the wrong choice.";
	    }
	 }while(chP<4);

}
void report_menu()
    {
	clrscr();
	int chR;
	do
	  {clrscr();
	   cout<<"\n\t\t\tHOSPITAL REPORT";
	   cout<<"\n1.Doctor Report";
	   cout<<"\n2.Patient Report";
	   cout<<"\n3.Go back to main menu";
	   cout<<"\n\nEnter the choice : ";
	   cin>>chR;
	   switch(chR)
	    {case 1 :doctor_report();
		     break;
	     case 2 :patient_report();
		     break;
	     case 3 :break;
	     default:cout<<"\n\nSorry!!You have entered the wrong choice.";
	    }
	  }while(chR!=3);
    }
void main()
{
	clrscr();
	int ch;
	cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\tASTER MEDCITY";
	cout<<"\n\n\t\t\t   We'll  Treat  You  Well";
	do
	  {clrscr();
	   cout<<"\n\n\t\t\tHOSPITAL MANAGEMENT SYSTEM";
	   cout<<"\n\n1.Doctor Menu";
	   cout<<"\n2.Patient Menu";
	   cout<<"\n3.Report";
	   cout<<"\n4.Exit";
	   cout<<"\n\nEnter the choice : ";
	   cin>>ch;
	   switch(ch)
	    { case 1 :doctor_menu();
		      break;
	      case 2 :patient_menu();
		      break;
	      case 3 :report_menu();
		      break;
	      case 4 :exit(0);
	      default:cout<<"\n\nSorry!! You have entered a wrong choice";
	    }
	  }while(ch!=4);
	 getch();
}

