/*
Nandan Krishnakumar
Student List - Galbraith C++/Data Structures
10/16/26 6:34 PM
Citations: https://cplusplus.com/reference/cstring/, Used ClaudeAI to debug on 10/16/26
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

struct Student //Student struct with a char array for first name, last name, sutdent ID, and student GPA
{
  char firstName[11];
  char lastName[21];
  int id;
  float GPA;
};

void addStudent(vector<Student*> &vect); //Function Prototypes
void printStudentList(vector<Student*> &vect);
void deleteStudent(vector<Student*> &vect);
char* getValidName(int order);
int getValidID();
float getValidGPA();

int main()
{
  vector<Student*> studentList; //initializing the vector of Student pointers
  char action[7] = "ADD"; //variable to keep track of what the user would like to do
  cout << "Welcome to student list! Here you can keep track of all the students in your school, "
	  "add students, delete students, and see which students are in your school. Let's add a student to get started!" << endl;
  do //do...while loop to run the program. Starts with adding a student first by default.
  {
    if (strcmp(action, "ADD") == 0)
    {
      addStudent(studentList);
    }
    else if (strcmp(action, "PRINT") == 0)
    {
      printStudentList(studentList);
    }
    else if (strcmp(action, "DELETE") == 0)
    {
      deleteStudent(studentList);
    }
    else
    {
      cout << "INVALID COMMAND\nVALID COMMANDS: ADD, PRINT, DELETE, AND QUIT" << endl;
    }

    cout << "WHAT WOULD YOU LIKE TO DO?" << endl;
    cin.get(action, 7);
    if (cin.fail())
    {
      cin.clear();
      action[0] = '\0';
    }
	else if (cin.peek() != '\n') //This block was given by ClaudeAI to handle extra characters in the buffer if the user entered something longer than 6 chars in cin.
	{
		action[0] = '\0';
	}
	cin.ignore(1000, '\n');
  } while (strcmp(action, "QUIT") !=0);
  for (vector<Student*>::iterator it = studentList.begin(); it != studentList.end(); it++) //deleting all the heap addresses at the end to clean up memory
  {
	  delete (*it);
  }
  return 0;
}

void addStudent(vector<Student*> &vect) //takes the inputs for name (first and last), student id, and student gpa from the user, adds them to a new student created in the heap with a pointer, which is then appended to the vector. This one was tough. ClaudeAI helped me debug and figure out that strcpy can't coppy the address one pointer is pointer is pointing to into another, even if they are the same data type pointer. Sorry Mr. Galbraith, I found out the hard way :(. Looks like we were wrong about that. I should have caught it because you said it  internally dereferences.
{
  Student* newStudent = new Student;
  char* first = getValidName(1);
  char* last = getValidName(2);
  int studentID = getValidID();
  float gpa = getValidGPA();

  strcpy(newStudent->firstName, first);
  strcpy(newStudent->lastName, last);
  newStudent->id = studentID;
  newStudent->GPA = gpa;

  vect.push_back(newStudent);
  cout << "New Student Added!" << endl;
  delete[] first; //Preventing memory leaks
  delete[] last;
}

void printStudentList(vector<Student*> &vect) //goes through all the student pointers in the vector, dereferences them, and prints their attributes
{
  int studentNum = 1;
  for (vector<Student*>::iterator it = vect.begin(); it != vect.end(); it++)
  {
    cout << "Student " << studentNum << ":" << endl;
    cout << "First Name: " << (*it)->firstName << endl;
    cout << "Last Name: " << (*it)->lastName << endl;
    cout << "ID: " << (*it)->id << endl;
    cout << "GPA: " << fixed << setprecision(2) << (*it)->GPA << endl;
    cout << endl;
    studentNum++;
  }
}

void deleteStudent(vector<Student*> &vect) //Deletes the student with the given ID. Tells the user that the ID was not in the system if a student doesn't have that ID number
{
  int deleteID = getValidID();
  for (vector<Student*>::iterator it = vect.begin(); it != vect.end(); it++)
  {
    if ((*it)->id == deleteID)
    {
      delete(*it);
      vect.erase(it);
      cout << "Student deleted!" << endl;
      return;
    }
  }
  cout << "ID number not in system." << endl;
}

char* getValidName(int order) //Function to create a char array that holds either the first or last name of the student (depending on the order) and returns a pointer to the char array. Clears input stream of any extra characters for future inputs and handles all memory leaks if a failbit is triggered or the input is taken successfully
{
  while (true)
  {
    char* name;
    int size;
    if (order == 1)
    {
      cout << "What is the student's first name?: " << endl;
      size = 11;
    }
    else if (order == 2)
    {
      cout << "What is the student's last name?: " << endl;
      size = 21;
    }
    name = new char[size];
    cin.get(name, size);
    if (cin.fail())
    {
        cout << "Enter a valid name" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
		delete[] name; //Avoids memory leak... THANK GOD I CAUGHT THAT
        continue;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return name;
  }
}

int getValidID() //Gets ID numbers (as ints) from the user and handles all cin failbits, as well as clearing the input stream for future inputs
{
  while (true)
  {
    int ID;
    cout << "What is the student's ID number?: " << endl;
    cin >> ID;
    if (cin.fail())
    {
        cout << "Enter an ID number" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        continue;
    }
	cin.ignore(1000,'\n');
    return ID;
  }
}

float getValidGPA() //Gets GPA numbers (as floats) from the user and handles all cin failbits, as well as clearing the input stream for future inputs
{
  while (true)
  {
    float grades;
    cout << "What is the student's GPA?: " << endl;
    cin >> grades;
    if (cin.fail())
    {
	cout << "Enter a valid GPA Value" << endl;
	cin.clear();
	cin.ignore(1000, '\n');
	continue;
    }
	cin.ignore(1000,'\n');
    return grades;
  }      
}
