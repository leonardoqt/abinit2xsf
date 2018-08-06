#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

int main()
{
	string flag_end="iterations are completed or convergence reached";
	string flag_coord="Cartesian coordinates";
	string flag_cell="Real space primitive translations";

	string flag_nat="mqgrid", check_nat="natom";
	string flag_nel="ntime", check_nel="ntypat";
	string flag_atom="tolmxf", check_atom="typat";
	string flag_el="opening atomic psp file";
	const double b2a = 0.529177249;

	string tmp;
	int nat, nel;
	int *at_l;
	string *el_l;
	double *x,*y,*z;
	double X[3],Y[3],Z[3];

	//find number of atoms
	getline(cin,tmp);
	while(tmp.find(flag_nat) == string::npos)
		getline(cin,tmp);
	cin>>tmp;
	if (tmp != check_nat)
	{
		cout<<"Error, could not find natom"<<endl;
		exit(0);
	}
	else
	{
		cin>>tmp>>nat;
	}
	//find number of elements
	while(tmp.find(flag_nel) == string::npos)
		getline(cin,tmp);
	cin>>tmp;
	if (tmp != check_nel)
	{
		cout<<"Error, could not find ntypat"<<endl;
		exit(0);
	}
	else
	{
		cin>>nel;
	}
	//define array of atoms and elements;
	at_l = new int[nat];
	el_l = new string[nel];
	x = new double[nat];
	y = new double[nat];
	z = new double[nat];
	//find atom type
	while(tmp.find(flag_atom) == string::npos)
		getline(cin,tmp);
	cin>>tmp;
	if (tmp != check_atom)
	{
		cout<<"Error, could not find typat"<<endl;
		exit(0);
	}
	else
	{
		for (int t1=0; t1<nat; t1++)
		{
			cin>>at_l[t1];
			at_l[t1]--;
		}
	}
	// find element symbol
	for (int t1=0; t1<nel; t1++)
	{
		while(tmp.find(flag_el) == string::npos)
			getline(cin,tmp);
		cin>>tmp>>el_l[t1];
		getline(cin,tmp);
	}
	// find atom position and cell paramter
	while(!cin.eof())
	{
		while(tmp.find(flag_coord) == string::npos)
			getline(cin, tmp);
		for (int t1=0; t1<nat; t1++)
		{
			cin>>x[t1]>>y[t1]>>z[t1];
			x[t1] *= b2a;
			y[t1] *= b2a;
			z[t1] *= b2a;
		}
		while(tmp.find(flag_cell) == string::npos)
			getline(cin, tmp);
		for (int t1=0; t1<3; t1++)
		{
			cin>>X[t1]>>Y[t1]>>Z[t1];
			X[t1] *= b2a;
			Y[t1] *= b2a;
			Z[t1] *= b2a;
		}
		while(tmp.find(flag_coord) == string::npos && tmp.find(flag_end) == string::npos)
			getline(cin,tmp);
		if (tmp.find(flag_end) != string::npos)
			break;
	}
	if (tmp.find(flag_end) == string::npos)
		cout<<"# Warning, calculation may not fully relaxed"<<endl;
	cout<<"PRIMCELL"<<endl;
	for(int t1=0; t1<3; t1++)
		cout<<setw(14)<<setprecision(9)<<fixed<<X[t1]<<setw(14)<<setprecision(9)<<fixed<<Y[t1]<<setw(14)<<setprecision(9)<<fixed<<Z[t1]<<endl;
	cout<<"PRIMVEC"<<endl;
	cout<<nat<<" 1"<<endl;
	for(int t1=0; t1<nat; t1++)
		cout<<setw(2)<<el_l[at_l[t1]]<<setw(14)<<setprecision(9)<<fixed<<x[t1]<<setw(14)<<setprecision(9)<<fixed<<y[t1]<<setw(14)<<setprecision(9)<<fixed<<z[t1]<<endl;

	return 0;
}
