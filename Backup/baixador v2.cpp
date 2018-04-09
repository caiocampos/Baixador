#include "baixador.h"

int main(int argc , char *argv[]){
	unsigned i, nome_ini, nome_tam;
	ifstream dados, teste, config(_config);
	stringstream ss;
	string remoto, local, localt, sigla, senha, tipo, nome,
		   ip, nome_entrada, dir;
	
	if(not (config >> sigla >> senha)) {
		cout << "Erro de leitura para o arquivo " << _config << endl;
	} else {
		config >> ip >> nome_entrada >> dir;
		
		if(ip.empty()) ip = _ip;
		if(nome_entrada.empty()) nome_entrada = _dados;
		
		dados.open(nome_entrada.c_str());
		while(true) {
			i = 1, nome_ini = nome_tam = 0;
			if(not (dados >> remoto >> localt)) break;
			
			remoto = toup(remoto);
			if(localt == ".") localt.clear();
			if(!dir.empty()) localt = dir + '/' + localt;
			if(localt.empty() or localt.at(localt.size() - 1) == '/') {
				nome_ini = remoto.find_last_of('.');
				if(nome_ini != string::npos or nome_ini == 0) {
					nome     = remoto.substr(nome_ini + 1);
					nome_tam = nome.find_last_of("\'´`");
					if(nome_tam != string::npos or nome_tam == 0) {
						nome = nome.substr(0, nome_tam);
					}
				}
				localt += nome;
				tipo    = tipo_arquivo(remoto);
			} else {
				nome_tam = localt.find_last_of('.');
				if(nome_tam == string::npos or nome_tam == 0) {
					tipo = tipo_arquivo(remoto);
				} else {
					tipo   = localt.substr(nome_tam);
					localt = localt.substr(0, nome_tam - 1);
				}
			}
			local = localt;
			while(true) {
				teste.open((local + tipo).c_str());
				if(teste) {
					ss.str("");
					ss << ++i;
					
					local = localt + '_' + ss.str();
				} else {
					break;
				}
				teste.close();
			}
			cout << "----------------------------------------";
			cout << "----------------------------------------" << endl;
			cout << "Tentando arquivo: " << remoto << endl;
			
			processa(ip, sigla, senha, remoto, local + tipo);
		}
	}
	dados.close();
	config.close();
	cout << endl <<	endl << "Pressione Enter" << endl;
    getchar();
	return 0;
}

void processa(string ip, string sigla, string senha, string remoto,
			  string local) {
	ofstream temp(_temp), log(_log, fstream::app);
	ifstream teste;
	
	temp << "user "	<< sigla << endl;
	temp << senha	<< endl;
	temp << "get"	<< endl;
	temp << remoto	<< endl;
	temp << local	<< endl;
	temp << "quit"	<< endl;
	
	system((string(_ftp) + _temp + ' ' + ip).c_str());
	teste.open(local.c_str());
	
	log << "Arquivo remoto: "	<< remoto	<< endl;
	log << "Arquivo local: "	<< local	<< endl;
	if(teste) {
		log << "Arquivo local gerado "	<< endl << endl;
	} else {
		log << "Arquivo local não gerado "	<< endl << endl;
	}
	log.close();
	temp.close();
	teste.close();
	remove(_temp);
}

string tipo_arquivo(string remoto) {
	if(remoto.rfind(".SRB") != string::npos) return _cbl;
	if(remoto.rfind(".SRC") != string::npos) return _cbl;
	if(remoto.rfind(".CPY") != string::npos) return _cbl;
	if(remoto.rfind(".CP2") != string::npos) return _cbl;
	if(remoto.rfind(".S4B") != string::npos) return _cbl;
	if(remoto.rfind(".S4C") != string::npos) return _cbl;
	if(remoto.rfind(".C4Y") != string::npos) return _cbl;
	if(remoto.rfind(".C42") != string::npos) return _cbl;
	if(remoto.rfind(".MPC") != string::npos) return _cbl;
	if(remoto.rfind(".SEO") != string::npos) return _cbl;
	if(remoto.rfind(".SRE") != string::npos) return _cbl;
	if(remoto.rfind(".SRO") != string::npos) return _cbl;
	if(remoto.rfind(".SRT") != string::npos) return _cbl;
	return _txt;
}

string toup(string s) {
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}