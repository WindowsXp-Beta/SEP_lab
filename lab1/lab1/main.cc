#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Class.h"
#include "Error.h"
#include "Student.h"

#define Debugx

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();
    Class* getClass(const string &class_name);
    Student* getStudent(const string &student_id);

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;
    int point;
    Class *cl = nullptr;

    // Open a file as a input stream.
#ifdef Debug
    ifstream studentfile("../Students.txt");
#endif
#ifdef Debugx
    ifstream studentfile("./Students.txt");
#endif
    while (getline(studentfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.

        if (bufv[3] == "U")
            st = new Undergraduate(bufv[1], bufv[2], bufv[0]);
        else
            st = new Graduate(bufv[1], bufv[2], bufv[0]);

        studentVec.push_back(st);
    }
    studentfile.close();

    // TODO: load data from ./Classes.txt and push objects to the vector.
    // Hint: how is student information read?
#ifdef Debug
    ifstream classFile("../Classes.txt");
#endif
#ifdef Debugx
    ifstream classFile("./Classes.txt");
#endif
    bufv.clear();

    while (getline(classFile,line)) {
        if(line.empty()) {
            bufv.clear();
            continue;
        }
        if (line[0] == '#')
            continue;

        pos1 = 0;
        if (line[0] == 'C') {
            pos2 = line.find(':' , pos1+1);
            bufv.push_back(line.substr(pos2 + 1, string::npos));
            continue;
        }

        else if (line[0] == 'P') {
            pos2 = line.find(':', pos1 + 1);
            bufv.push_back(line.substr(pos2 + 1, string::npos));
            cl = new Class(bufv[0], bufv[1][0] - '0');
            classVec.push_back(cl);
            continue;
        }

        else {
           Student* stu;
           for (auto & it : studentVec) {
               if (it->id == line) stu = it;
           }
           cl->addStudent(*stu);
           stu->addclass(cl);
           continue;
        }
    }
    classFile.close();
    bufv.clear();
}

void AppX::inputScore()
{
    // TODO: implement inputScore.
    // Hint: Take a look at printAvgScore().
    string class_name;
    Class  *cl;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> class_name;
        if (class_name == "q")
            break;

        try {
            cl = getClass(class_name);
        } catch (XAppError& e){
            cout << e.getErrorMsg();
            continue;
        }

        string student_id;

        while (true) {
            cout << "Please input the student's id (or input q to quit): ";
            cin >> student_id;
            if (student_id == "q")
                break;

            try {
                StudentWrapper &stu = cl->getStudentWrapper(student_id);
                cout << stu.toString();

                double score;
                string input;

                cout << "Please input the student's score:(or input q to quit)"<<endl;
                cin >> input;
                if (input == "q") continue;
                else istringstream(input) >> score;

                stu.setScore(score);
            }  catch (XAppError &e) {
                cout << e.getErrorMsg();
                continue;
            }
        }
    }
}

void AppX::printAvgScore()
{
    string class_name;
    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> class_name;
        if (class_name == "q")
            break;
        try {
            Class *cl = getClass(class_name);
            printf( "The average score is: %.2f\n", cl -> getAvgScore());
        } catch (XAppError &e) {
            cout << e.getErrorMsg();
            continue;
        }
    }
}

void AppX::printGpa()
{
    // TODO: implement printGpa.
    // Hint: Take a look at printAvgScore().
    while (true) {
        string student_id;

        cout << "Please input the student's id (or input q to quit):" << endl;
        cin >> student_id;
        if (student_id == "q")
            break;

        try {
            Student *stu = getStudent(student_id);
            cout << stu->toString();
            printf ("GPA = %.2f\n", stu->getGrade());
        } catch (XAppError &e){
            cout << e.getErrorMsg();
            continue;
        }
    }
}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute average score of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n";
        }
    }
    return 0;
}

Class *AppX::getClass(const string &class_name) {
    for(auto &class_item : classVec){
        if(class_item -> name == class_name)
            return class_item;
    }
    throw XAppError("No match class!\n");
}

Student *AppX::getStudent(const string &student_id) {
    for(auto &student_item : studentVec){
        if(student_item -> id == student_id)
            return student_item;
    }
    throw XAppError("No match student!\n");
}

int main()
{
    AppX app;
    return app.run();
}
