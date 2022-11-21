//=========================================================
// Name        : phoneBook.cpp
// Author      : John Paul Jones
// ID          : 1001639122
// Version     : 1.2 Working, with config functionality, logs, missing prepare statement functionality
// Copyright   : 2021
// Description : phoneBook.cpp written in C++ with SQlite
//=========================================================

//=========================================================
//Compile      : ./compile.sh
//=========================================================

#include <iostream>
#include <string>
#include <string.h>
#include <sqlite3.h>
#include <algorithm>
#include <regex>
#include <unistd.h>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;

string readIntoString(string filename)
{
   fstream inf(filename, fstream::in );
   string s;
   if(inf)
    getline(inf, s);
    //getline( inf, s, '\0');

   //cout << "filename is : "+ s << endl; //DEBUG
   inf.close();
   return s;
}

void writeFile(string filename, string name, string cmd)
{
  ofstream outf;
  outf.open(filename, ofstream::app);
  //Get time
  auto timeAtNow =
     chrono::system_clock::to_time_t(chrono::system_clock::now());

  //Check for errors
  if (!outf)
  {
    cout << "File write unsuccessfull! Exiting..." << endl;
    exit(1);
  }
  //Command and log information write out
  if(cmd == "LIST")
    outf <<"User ID: " << getuid() << ", Username: " << getenv("USER") << " executed command " + cmd + " At time: " + ctime(&timeAtNow);//<< endl;
  else
    outf <<"User ID: " << getuid() << ", Username: " << getenv("USER") << " executed command " + cmd + " At value: " + name + " At time: " + ctime(&timeAtNow); //<< endl;

  outf.close();
  cout << "\nFinished writing to log file" << endl;
}

// Required callback function for SQLite
static int callback(void *NotUsed, int argc, char **argv, char **szColName)
{
  for(int i = 0; i < argc; i++)
  {
    std::cout << szColName[i] << " = " << argv[i] << std::endl;
  }

  std::cout << "\n";

  return 0;
}

bool nameMatch(string str)
{
  smatch m;

  //cout << "string is: " + str << endl; //DEBUG
  //---- White List ----//
  regex reg("^[a-zA-Z]+ [a-zA-Z]+$");
  regex reg2("^[a-zA-Z]+, [a-zA-Z]+$");
  regex reg3("^[a-zA-Z]+, [a-zA-Z]+ [a-zA-Z]+$");
  regex reg4("^[a-zA-Z][\\'][a-zA-z].*[\\,] [a-zA-Z].*[\\.]$");
  //regex reg4("^[O][\\'][a-zA-z]+$"); //For Testing O'MalleyJohn
  regex reg5("^[a-zA-Z].* [a-zA-z]{1}[\\'][a-zA-z].*[\\-][a-zA-z].*$");
  regex reg6("^[a-zA-Z]+$");

  //regex_search(str, m, reg);
  if( regex_search(str, m, reg) )
    return true;
  //printSmatch(m);
  else if( regex_search(str, m, reg2) )
    return true;
  //printSmatch(m);
  else if( regex_search(str, m, reg3) )
    return true;
  //printSmatch(m);
  else if( regex_search(str, m, reg4) )
    return true;
  //printSmatch(m);
  else if( regex_search(str, m, reg5) )
    return true;
  //printSmatch(m);
  else if( regex_search(str, m, reg6) )
    return true;
  //printSmatch(m);
  else
  {
    //cout << "Not a valid Name!" << endl;
    return false;
  }
}

bool phoneMatch(string str)
{
  smatch m;
  //---- White List ----//
  regex reg("^[0-9]{5}$");
  regex reg2("^\\([0-9]{3}\\)[0-9]{3}[\\-][0-9]{4}$");
  regex reg3("^[0-9]{3}[\\-][0-9]{4}$");
  regex reg4("^\\+[0-9]{1}\\([0-9]{3}\\)[0-9]{3}[\\-][0-9]{4}$");
  regex reg5("^\\+[0-9]{2} \\([0-9]{2}\\) [0-9]{3}[\\-][0-9]{4}$");
  regex reg6("^[0-9]{1}\\([0-9]{3}\\)[0-9]{3}[\\-][0-9]{4}$");
  regex reg7("^[0-9]{3} [0-9]{3} [0-9]{3} [0-9]{4}$");
  regex reg8("^[0-9]{5}[\\.][0-9]{5}$");
  regex reg9("^[0-9]{3} [0-9]{1} [0-9]{3} [0-9]{3} [0-9]{4}$");
  regex reg10("^[0-9]{3}[\\-][0-9]{3}[\\-][0-9]{4}$");
  regex reg11("^[1][\\-][0-9]{3}[\\-][0-9]{3}[\\-][0-9]{4}$");
  regex reg12("^[0-9]{3} [0-9]{3} [0-9]{4}$");
  regex reg13("^[0-9]{3}[\\.][0-9]{3}[\\.][0-9]{4}$");
  regex reg14("^[1] [0-9]{3} [0-9]{3} [0-9]{4}$");
  regex reg15("^[1][\\.][0-9]{3}[\\.][0-9]{3}[\\.][0-9]{4}$");
  regex reg16("^[0-9]{2} [0-9]{2} [0-9]{2} [0-9]{2}$");
  regex reg17("^[0-9]{4} [0-9]{4}$");
  regex reg18("^[4][5] [0-9]{4} [0-9]{4}$");
  regex reg19("^[4][5] [0-9]{2} [0-9]{2} [0-9]{2} [0-9]{2}$");
  regex reg20("^[4][5][\\.][0-9]{4}[\\.][0-9]{4}$");
  regex reg21("^[4][5][\\.][0-9]{2}[\\.][0-9]{2}[\\.][0-9]{2}[\\.][0-9]{2}$");
  regex reg22("^[0-9]{2}[\\.][0-9]{2}[\\.][0-9]{2}[\\.][0-9]{2}$");
  regex reg23("^[0-9]{4}[\\.][0-9]{4}$");
  regex reg24("^[0-9]{3}[\\.][0-9]{4}$");

  //regex_search(str, m, reg);
  if( regex_search(str, m, reg) )
    return true;
  else if( regex_search(str, m, reg2) )
    return true;
  else if( regex_search(str, m, reg3) )
    return true;
  else if( regex_search(str, m, reg4) )
    return true;
  else if( regex_search(str, m, reg5) )
    return true;
  else if( regex_search(str, m, reg6) )
    return true;
  else if( regex_search(str, m, reg7) )
    return true;
  else if( regex_search(str, m, reg8) )
    return true;
  else if( regex_search(str, m, reg9) )
    return true;
  else if( regex_search(str, m, reg10) )
    return true;
  else if( regex_search(str, m, reg11) )
    return true;
  else if( regex_search(str, m, reg12) )
    return true;
  else if( regex_search(str, m, reg13) )
    return true;
  else if( regex_search(str, m, reg14) )
    return true;
  else if( regex_search(str, m, reg15) )
    return true;
  else if( regex_search(str, m, reg16) )
    return true;
  else if( regex_search(str, m, reg17) )
    return true;
  else if( regex_search(str, m, reg18) )
    return true;
  else if( regex_search(str, m, reg19) )
    return true;
  else if( regex_search(str, m, reg20) )
    return true;
  else if( regex_search(str, m, reg21) )
    return true;
  else if( regex_search(str, m, reg22) )
    return true;
  else if( regex_search(str, m, reg23) )
    return true;
  else if( regex_search(str, m, reg24) )
    return true;
  else
  {
    //cout << "Not a valid Phone number!" << endl;
    return false;
  }
}

void rcMsg(int rc, string msg)
{
  if(rc)
    std::cout << "Error Opening Database!\n";
  else
    std::cout << "Successfully Opened Database " + msg << endl;
}

string replaceSingleQuote( std::string const& original )
{
    std::string results;
    for ( std::string::const_iterator current = original.begin();
            current != original.end();
            ++ current ) {
        if ( *current == '\'' ) {
            results.push_back( '\'');
        }
        results.push_back( *current );
    }
    return results;
}


static int initTable()
{
	sqlite3 *db;
	char* messageError;

  //Read in sql information
  string sqlConfig = readIntoString("config.cfg");

	string cmd = "CREATE TABLE IF NOT EXISTS DIRECTORY("
	"Name	     TEXT,"
	"Phone	   TEXT );";

	try
	{
		int exit = 0;
		exit = sqlite3_open(sqlConfig.c_str(), &db);
    //exit = sqlite3_open("phonebook.db", &DB); //Hardcoded
    rcMsg(exit, "For Initialization");
    exit = sqlite3_exec(db, cmd.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK)
    {
			cerr << "Error in initTable function!" << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Successfully Initialized Table!\n" << endl;
		sqlite3_close(db);
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}

	return 0;
}

void helpPrint()
{
  cout << "\nTo Run: Enter command as first argument followed by next arguments enclosed in quotes\n" << endl <<
  "Ex: ./directory ADD \"Jones, John Paul\" \"817.555.4545\"" << endl <<
  "======================================================================================" << endl;
  cout << "ADD \"Full Name\" \"Phone number\" \t-> Add a user to database" << endl;
  cout << "DEL \"Full Name\" \t\t-> Delete a user from database from name provided" << endl;
  cout << "DEL \"Phone Number\" \t\t-> Delete user from database from phone number provided" << endl;
  cout << "LIST \t\t\t\t-> Display all current fields in the database" << endl;
}

void listDatabase(sqlite3 **db)
{
  string sqlConfig = readIntoString("config.cfg");
	string list = "SELECT * FROM DIRECTORY";
	//LIST records
	cout << "\nNow listing from database..." << endl;
	//int rc = sqlite3_open("phonebook.db", &db);
	int rc = sqlite3_open(sqlConfig.c_str(), *&db); //Using Pointers (This creates a new file!)
  //int rc = sqlite3_open("phonebook.db", *&db); //Using Pointers (Hardcoded)
  char *szErrMsg = 0;
	rcMsg(rc, "For Listing");
  rc = sqlite3_exec(*&*db, list.c_str(), callback, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		std::cout << "SQL Error: " << szErrMsg << std::endl;
		sqlite3_free(szErrMsg);
		//break;
	}
}

void addUser(sqlite3 **db, string name, string phone)
{
  string sqlConfig = readIntoString("config.cfg");
	//Insert Command
	//string cmd = "INSERT INTO NUMBERS(Firstname, Age) VALUES ('"+ firstname +"', '"+ lastname +"', "+ age +")";
  bool checkName = nameMatch(name);
  bool checkPhone = phoneMatch(phone);

  //Debug
  //cout << "Name result:  "<< std::boolalpha << checkName << endl;
  //cout << "Phone result:  "<< std::boolalpha << checkPhone << endl;
  if (checkName && checkPhone)
  {
    //Replace Results
    //cout << "Initial String :" << name << endl; //DEBUG
    string results = replaceSingleQuote(name);
    //cout << "Final String :" << results << endl;

    string cmd = "INSERT INTO DIRECTORY(Name, Phone) VALUES ('"+ results +"', '"+ phone +"')"; //non prepared Version
  	cout << "Now adding " + name + " to database..." << endl;



  	int rc = sqlite3_open(sqlConfig.c_str(), *&db); //Using Pointers
    //int rc = sqlite3_open("phonebook.db", *&db); //Using Pointers (Hardcoded)
  	char *szErrMsg = 0;
    rcMsg(rc, "to Add Entry");
  	rc = sqlite3_exec(*&*db, cmd.c_str(), callback, 0, &szErrMsg);
  	if(rc != SQLITE_OK)
  	{
  	  std::cout << "SQL Error: " << szErrMsg << std::endl;
  	  sqlite3_free(szErrMsg);
  	  //break;
  	}
  }
  else
  {
    cout << "You entered invalid inputs.\nExiting..." << endl;
    exit(1);
  }
}


void deleteFromName(sqlite3 **db, string s)
{
  string sqlConfig = readIntoString("config.cfg");
  bool checkName = nameMatch(s);
  bool checkPhone = phoneMatch(s);

  if(checkName || checkPhone)
  {
    int rc = sqlite3_open(sqlConfig.c_str(), *&db); //Using Pointers
    //int rc = sqlite3_open("phonebook.db", *&db); //Using Pointers (Hardcoded)
    char *szErrMsg = 0;
    rcMsg(rc, "For Deletion");
    // Build the SQLite command
    string cmd = "DELETE FROM DIRECTORY WHERE Name = '"+ s +"'";
    string cmd2 = "DELETE FROM DIRECTORY WHERE Phone = '"+ s +"'";
    if(checkName)
      rc = sqlite3_exec(*&*db, cmd.c_str(), callback, 0, &szErrMsg);
    else if(checkPhone)
      rc = sqlite3_exec(*&*db, cmd2.c_str(), callback, 0, &szErrMsg);

    if(rc != SQLITE_OK)
    {
      std::cout << "SQL Error: " << szErrMsg << std::endl;
      sqlite3_free(szErrMsg);
      //break;
    }
    if(checkName)
  	 cout << "Now deleting " + s + " from database..." << endl;
    else if(checkPhone)
      cout << "Now deleting " + s + " from database..." << endl;
  }
  else
  {
    cout << "You entered invalid inputs.\nExiting..." << endl;
    exit(1);
  }

}

// ---- Main program with command line arguments ----//
int main(int argc, char *argv[])
{
  sqlite3 *db;
  char *szErrMsg = 0;

  if(argv[1] == NULL)
  {
    cout << "No arguments were entered for this session\nHelp menu printing to screen..." << endl;
    helpPrint();
  }

  else if(argv[1] != NULL || argv[2] != NULL) // Make sure first two args are present
  {
    // If first command argument is present, convert to string!
    string cmd(argv[1]);
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper); //convert to uppercase

    initTable(); //Create a table if there is none already created

    //Main Menu
    if( argv[3] != NULL && argv[2] != NULL && cmd  == "ADD" ) // Make sure 3rd arg is present
    {
      string phone(argv[3]);
      string name(argv[2]);
      addUser(&db, name, phone); //Add a user to db
      //addUserPrepared(&db, name, phone);
      cout << "ADD command executed..." << endl;
      writeFile("audit.LOG", name, cmd);
    }
    else if( argv[2] != NULL && cmd == "DEL" )
    {
      string value(argv[2]); //This will hold either the name or the phone number string
      deleteFromName(&db, value);
      cout << "DEL command executed..." << endl;
      writeFile("audit.LOG", value, cmd);
    }
    else if( cmd  == "LIST" )
    {
      cout << "LIST command executed... " << endl;
      listDatabase(&db); // Function to Print out db
      string name = "";
      writeFile("audit.LOG", name, cmd);
    }
    else
    {
      //System.err.println("Invalid argument: " + args[0]);
      cout << "Arguments are not correct!" << endl;
      exit(1);
    }

  }

  // Close the database
  if(db)
    sqlite3_close(db);

  return 0;
}
