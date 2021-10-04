#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
#include "Error.h"
using namespace std;

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
private:
    const string name;
    const string year;
    const Degree degree;
protected:
    vector<Class*> classes;
public:
    const string id;

    Student(string name, string year, Degree degree, string id): name(name),year(year),degree(degree),id(id){}
    virtual ~Student(){};

    virtual double getGrade() = 0;
    void addclass(Class* c);
    std::string toString() const;
};

class Graduate : public Student {

public:
    Graduate(string name, string year, string id): Student(name, year, graduate, id){}
    ~Graduate() override = default;

    double getGrade() override;
};

class Undergraduate : public Student {

public:
    Undergraduate(string name, string year, string id): Student(name, year, undergraduate, id){}
    ~Undergraduate() override = default;

    double getGrade() override;
};


class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const string id;
    StudentWrapper(const Student &student, const string &id): student(student), id(id){}

    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw XAppError("Wrong score!\n");
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_
