#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;

enum armorTypes { CLOTH, LEATHER, CHAIN, PLATE};

struct gear {
	string name;
	armorTypes type;
	int numSlots;
};

string ToString(armorTypes type) {
	string s;
	switch (type) {
	case CLOTH: return "CLOTH"; break;
	case LEATHER: return "LEATHER"; break;
	case CHAIN: return "CHAIN"; break;
	case PLATE: return "PLATE"; break;
	default: return ""; break;
	}
}

string getName(armorTypes type){
	string result = "";
	string t = ToString(type);
	vector<string> pre, core, suf;

	// core
	ifstream openfile;
	openfile.open("Text Files/names.txt");
	if(openfile) {
		while (openfile.good()) {
			string line;

			getline(openfile, line);
			if (line.find(t) != string::npos) {
				while (true) {
					getline(openfile, line);
					if (line.find("--") != string::npos) break;
					core.push_back(line);
				}
			}
		}
	}
	openfile.close();

	// prefix
	openfile.open("Text Files/prefixes.txt");
	if(openfile) {
		while (openfile.good()) {
			string line;

			getline(openfile, line);
			if (line.find(t) != string::npos) {
				while (true) {
					getline(openfile, line);
					if (line.find("--") != string::npos) break;
					pre.push_back(line);
				}
			}
		}
	}
	openfile.close();

	// suffix
	openfile.open("Text Files/suffixes.txt");
	if(openfile) {
		while (openfile.good()) {
			string line;

			getline(openfile, line);
			if (line.find(t) != string::npos) {
				while (true) {
					getline(openfile, line);
					if (line.find("--") != string::npos) break;
					suf.push_back(line);		
				}
			}
		}
	}
	openfile.close();


	// ASSEMBLE THAT NAME!
	int p, s;
	p = rand()%100;
	s = rand()%100;
	// what a mess...
	if (p >= 33) { result.append(pre[rand()%(int)pre.size()]); result.append(" ");}
	result.append(core[rand()%(int)core.size()]);
	if (s >= 50) {result.append(" "); result.append(suf[rand()%(int)suf.size()]);}

	return result;
}

int main () {
	srand(time(NULL));
	gear item;
	armorTypes type;

	type = CLOTH;
	
	// just for fun, let's make a bunch!
	for (int i = 0; i < 20; i++) {
		item.name = getName(type);
		cout << item.name << endl;
	}

	cin.get();
	return 0;
}