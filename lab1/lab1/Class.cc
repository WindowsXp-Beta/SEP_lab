#include "Class.h"
#include "Error.h"
#include <string>
#include "Student.h"

void Class::addStudent(const Student &st)
{
    StudentWrapper sw(st, st.id);
    students.push_back(sw);
}

StudentWrapper &Class::getStudentWrapper(const std::string &studentId)
{
    for (auto & student : students) {
        if (student.id == studentId)
            return student;
    }
    throw XAppError("No match student!\n");
}

double Class::getAvgScore()
{
    // TODO: implement getAvgScore.
    double total_score = 0.0;
    int count = 0;
    for (auto & student : students)   {
        ++count;
        total_score += student.getScore();
    }

    if (!count) return 0;
    return total_score / count;
}
double Class::outputScore(string id){
    for(auto & student : students)
        if (id == student.id) return student.getScore();
    throw XAppError("Invalid student id!\n");
}
