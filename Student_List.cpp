#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

struct Student
{
  char firstName[11];
  char lastName[21];
  int id;
  float GPA;
};

int main()
{
  vector<Student*> studentList;
  char action[7] = "ADD";

  do
  {
    if (strcmp(action, "ADD") == 0)
    {
      addStudent();
    }
    else if (strcmp(action, "PRINT") == 0)
    {
      printStudentList();
    }
    else if (strcmp(action, "DELETE") == 0)
    {
      deleteStudent();
    }
    else
    {
      cout << "INVALID COMMAND\nVALID COMMANDS: ADD, PRINT, DELETE, AND QUIT" << endl;
    }

    cout << "WHAT WOULD YOU LIKE TO DO?" << endl;
    cin >> action;
    if (cin.fail())
    {
      cin.clear();
      cin.ignore(1000, '\n');
      action[0] = '\0';
    }
  } while (strcmp(action, "QUIT") !=0);
  return 0;
}

void addStudent(vector<Student*> &vect)
{
  Student* newStudent = new Student;
  char* first;
  strcpy(first, getValidName(1));
  char* last;
  strcpy(last, getValidName(2));
  int studentID = getValidID();
  float gpa = getValidGPA();

  strcpy(newStudent->firstName, first);
  strcpy(newStudent->lastName, last);
  newStudent->id = studentID;
  newStudent->GPA = gpa;

  vect.push_back(newStudent);
  cout << "New Student Added!" << endl;
}

void printStudentList(vector<Student*> &vect)
{
  for (vector<Student*>::iterator it = vect.begin(); it != vect.end(); it++)
  {
    int studentNum = 1;
    cout << "Student " << studentNum << ":" << endl;
    cout << "First Name: " << (*it)->firstName << endl;
    cout << "Last Name: " << (*it)->lastName << endl;
    cout << "ID: " << (*it)->id << endl;
    cout << "GPA: " << fixed << setprecision(2) << (*it)->GPA << endl;
    cout << endl;
    studentNum++;
  }
}

void deleteStudent(vector<Student*> &vect)
{
  int deleteID = getValidID();
  for (vector<Student*>::iterator it = vect.begin(); it != vect.end(); it++)
  {
    if ((*it)->id == deleteID)
    {
      delete(*it);
      v.erase(it);
      cout << "Student deleted!" << endl;
      return;
    }
  }
}

char* getValidName(int order)
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

int getValidID()
{
  while (true)
  {
    int ID;
    cout << "What is the student's ID number?: " << endl;
    cin >> ID;
    if (cin.fail())
    {
        cout << "Enter an ID nummber" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        continue;
    }
    return ID;
  }
}

float getValidGPA()
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
    return grades;
  }      
}

//REMEMBER TO PROTOTYPE YOUR FUNCTIONS!!!!!!!
