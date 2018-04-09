#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#define _dados "dados.txt"
#define _temp "temp.dat"
#define _ip "192.168.254.164"
#define _ftp "ftp -n -s:temp.dat 192.168.254.164"

using namespace std;

int main(int argc , char *argv[]){
	ifstream dados(_dados);
	
	string remoto, local, sigla, senha;
	if(!(dados >> sigla) || !(dados >> senha)) {
		cout << "Erro de leitura" << endl;
	} else {
		while(true){
			if(!(dados >> remoto) || !(dados >> local)) break;
			ofstream temp(_temp);
			temp << "user "		<< sigla << endl;
			temp << senha		<< endl;
			temp << "get"		<< endl;
			temp << remoto		<< endl;
			temp << local		<< endl;
			temp << "disconnet"	<< endl;
			temp << "quit"		<< endl;
			cout << "Tentando arquivo: " << remoto << endl;
			system(_ftp);
			temp.close();
			remove(_temp);
		}
	}
	dados.close();
	cout << endl << "Pressione Enter" << endl;
    getchar();
	return 0;
}
