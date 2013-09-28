#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct monster
{
	string name;
	string type;
	int level;
	string tc;
};

int FindNext(string src, int prevIndex)
{
	int i;
	i = 1 + prevIndex;
	char c;
	while(true)
	{
		c = src[i];
		if (c == char(13)) break;
		i++;
	}
	return i;
}

string FindMonster(string line, int num)
{
	int y = 0;
	for (int i = 0; i < num+1; i++)  // num+1 to ignore the sample "Class Type LevelTreasreClass" at the beginning
	{
		y = FindNext(line, y);
	}
	
	return line.substr(y, FindNext(line, y)-y);  // get the substring that belongs to the monster
}

monster getMonster(string src)
{
	monster found;
	// get name
	found.name = src.substr(0, src.find('\t'));

	// get type
	src.erase(0, src.find('\t')+1);
	found.type = src.substr(0, src.find('\t'));

	// get level as int
	src.erase(0, src.find('\t')+1);
	stringstream ss(src.substr(0, src.find('\t')));
	ss >> found.level;

	src.erase(0, src.find('\t')+1);
	found.tc = src;

	return found;
}


int main ()
{
	string line;
	ifstream infile("large_data/monstats.txt");
	
	if (infile) getline(infile, line);
	infile.close();

	monster monsterToFight;
	monsterToFight = getMonster(FindMonster(line, 48));
	
	cout << monsterToFight.name << endl << 
			monsterToFight.type << endl << 
			monsterToFight.level << endl <<
			monsterToFight.tc << endl;

	// randomly pick monster to fight and beat
	// look up treasure class of that monster and generate BASE ITEM that is dropped
	// generate base stats for base item
	// generate affixes and stat modifiers
	cin.get();
	return 0;
}


/*
*
* This works fine unless you try to get the last monster from the file:
* Monster #49, the OverSeer.
*
* I was going to fix it, but the lab I'm in is closing, so I'll leave it.
* Feel free to fix it if you want.
* I think eventually the ifstream should go right into the FindMonster function
* so it owns the string, rather than passing it all over the place.
*
*
*/