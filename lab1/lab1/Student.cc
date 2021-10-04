#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"

std::string Student::toString() const
{
    // TODO: uncomment the following code after implementing class Student.

    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();
}

// TODO: implement functions which are declared in Student.h.
void Student::addclass(Class *c){
    classes.push_back(c);
}

double Undergraduate::getGrade(){
    double grade = 0.0;
    int total_point = 0;

    for (auto & class_item : classes)
    {
        grade += class_item->outputScore(id) / 20 * class_item->point;
        total_point += class_item->point;
    }

    if (!total_point) return 0;
    else return grade/total_point;
}

double Graduate::getGrade(){
    double grade = 0.0;
    int total_point = 0;

    for (auto & class_item : classes)
    {
        double score = class_item->outputScore(id);
        double new_grade;

        switch ((int)score/10)
        {
        case 10:
        case 9: new_grade =4.0;break;
        case 8: new_grade =3.5;break;
        case 7: new_grade =3.0;break;
        case 6: new_grade =2.5;break;
        default: new_grade =2.0;
        }

        grade += new_grade * class_item->point;
        total_point += class_item->point;
    }

    if (!total_point) return 0;
    else return grade/total_point;

}
