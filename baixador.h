#ifndef baixador_h
#define baixador_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define _config "config.txt"
#define _dados "dados.txt"
#define _temp "temp.dat"
#define _ip "192.168.254.164"
#define _ftp "ftp -n -s:"
#define _txt ".txt"
#define _cbl ".cbl"
#define _log "log.txt"

using namespace std;

bool processa(string ip, string sigla, string senha, string remoto, 
			  string local);
string tipo_arquivo(string remoto);
string toup(string s);

#endif