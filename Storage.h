#ifndef STORAGE_H
#define STORAGE_H
#include "Student.h"
class Storage{
    private:
//        Student Students[MAX_STUDENTS_NUM];
        vector<Student> Students;
        int TotalStudentNumber;
    public:
        int& getTotalStudentNumberRefer();
        Storage();
        const Student& getStudent(int n);
        const Student& operator [](int n);
        Student* getStudentHandle(int n);
		Student * newStudentHandle(int n);
        int Add();
        int Find(int StudentId);
        int print();
};
#endif
