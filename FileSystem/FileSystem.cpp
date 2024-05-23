
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <mutex>
#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_FILES 1000
#define MAX_FILE_NAME 32
#define MAX_DATA_SIZE 1024

typedef struct File {
	string name;
	string data;
	int size;
} File;

File files[MAX_FILES] = {};
std::mutex mt;
int place = 0;
void createFile(string name) {
	int flag = 0;
	File currFile;
	if (name.size() < MAX_FILE_NAME)
	{

		for (int i = 0; i < MAX_FILES; i++)
		{
			if (name == files->name)
			{
				cout << "There is already a file with this name" << endl;
				flag = 1;
				break;
			}
		}
		if (flag==0)
		{
			currFile.name = name;
			currFile.data.clear();
			currFile.size = 0;
			files[place] = currFile;

			cout << "The file was created succesfully" << endl;
			place++;
		}
	}
	else
		cout << "The file name exceeds the allowed length" << endl;


}

int readFile(string name) {//std::cout
	mt.lock();
	int flag = 0;
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (files[i].name == name)
		{
			if (files[i].data.empty())
			{
				cout << "The file is empty" << endl;
			}
			else
			{
				cout << "Data extracted: " << files[i].data << endl;
			}
			flag = 1;
			break;
		}
	}
	if (!flag)
	{
		cout << "The file was not found" << endl;
	}
	mt.unlock();
	return 0;
}

int writeFile(string name, string text) {
	mt.lock();
	int flag = 0;
	if (text.size() >= MAX_DATA_SIZE)
	{
		cout << "The data size exceeds the file size" << endl;
	}
	else
	{
		for (int i = 0; i < MAX_FILES; i++)
		{
			if (files[i].name == name)
			{
				flag = 1;
				files[i].data = text;
				files[i].size = text.size();
				cout << "The data is recorded" << endl;
				break;
			}
			
		}
		if (!flag)
		{
			cout << "The file was not found" << endl;
		}
	}
	mt.unlock();
	return 0;
}

int deleteFile(string name) {
	mt.lock();
	int indexToDelete = 0;
	int flag = 0;
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (files[i].name == name)
		{
			indexToDelete = i;
			flag = 1;
			break;
		}
	}
	for (int i = indexToDelete; i < MAX_FILES; i++)
	{
		files[i] = files[i + 1];
	}
	if (place > 0)
	{
		place--;
	}
	else
		place = 0;
	if (flag)
	{
		cout << "The file deleted" << endl;
	}
	else
		cout << "The file was not found" << endl;
	
	mt.unlock();
	return 0;
}

void fsInfo() {
	int count = 0;
	for (count; count < MAX_FILES; count++) {
		if (files[count].name.empty())
		{
			break;
		}
	}
	cout << "Number of files in the system: "<< count<<endl;//print all the data about fs
}

int searchFile(string text)
{
	mt.lock();
	int flag = 0;
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (files[i].name == text)
		{
			cout << "The file exists" << endl;
			flag = 1;
			break;
		}
		else if(files[i].data == text)
		{
			cout << "The file with this text exists" << endl;
			flag = 1;
			break;
		}

		
	}
	if (!flag)
	{
		cout << "The file was not found" << endl;
	}
	
	mt.unlock();
	return 0;
}

void printCommands()
{
	cout << "List of commands\n"
		<< "cf: creating a file\n"
		<< "rf: reading the contents of the file\n"
		<< "wf: changing a file\n"
		<< "df: deleting a file\n"
		<< "fI: information about the file system\n"
		<< "sf: search for file\n" 
		<< "exit: exiting the file system\n"<< endl;
	string command;
	while (true)
	{
		cin >> command;
		string nameFile;
		string textFile;
		if (command == "cf")
		{
			cout << "Enter the file name: ";
			cin >> nameFile;
			
			createFile(nameFile);
			
		}
		else if (command == "rf")
		{
			cout << "Enter the file name: ";
			cin >> nameFile;
			
			readFile(nameFile);
		}
		else if (command == "wf")
		{
		
			cout << "Enter the file name: ";
			cin >> nameFile;
			_flushall();
			
			cout << "Enter the data: ";
			cin.ignore();
			getline(cin, textFile); 
			
			
			writeFile(nameFile, textFile);
		}
		else if (command == "df")
		{
			cout << "Enter the file name: ";
			cin >> nameFile;
			
			deleteFile(nameFile);
		}
		else if (command == "fI")
		{
			fsInfo();
		}
		else if (command == "sf")
		{
			cout << "Enter the name or contents of the file: ";
			cin >> textFile;
			
			searchFile(textFile);
		}
		else if (command == "exit")
		{
			cout << "Goodbye!" << endl;
			break;
		}
		else
		{
			cout << "Error! The command was entered incorrectly" << endl;
		}
	}
}
int main() {
	printCommands();
	
}
