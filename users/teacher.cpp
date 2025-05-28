// Felipe Urra Rivadeneira 0MI8000066

#include "teacher.h"

Teacher::Teacher(CustomString& name, CustomString& lastName, CustomString& password) :
    User(name, lastName, password, UserType::Teacher) {}

Teacher::~Teacher() {
    for (uint8_t i = 0; i < this->courses.getSize(); i++) {
        delete this->courses[i];
    }
}

// getters and setters
CustomVector<Course*>& Teacher::getCourses() {return courses;}
void Teacher::setCourses(CustomVector<Course*>& courses) {this->courses = courses;}

void Teacher::createCourse(CustomString& name, CustomString& password) {
    Course* course = new Course(name, password);
    this->courses.push_back(course);
}

void Teacher::createAssignment(Course* course, CustomString& name) {
    Assignment* assignment = new Assignment(name);
    course->getAssignments().push_back(assignment);
}

void Teacher::enrollStudent(Course* course, Student* student) {
    course->getStudentsMembers().push_back(student);
    student->getCoursesEnrolled().push_back(course);
}

Course* Teacher::getCourseByName(CustomString& courseName){ // change this functions
    for (uint8_t i = 0; i < this->courses.getSize(); i++) {
        if (this->courses[i]->getName() == courseName) {
            return this->courses[i];
        }
    }

    return nullptr;
}

// Serialize/deserialize
    void Teacher::serialize(std::ofstream& out) const {
        User::serialize(out);

        int courseCount = this->courses.getSize();
        out.write(reinterpret_cast<const char*>(&courseCount), sizeof(courseCount));
        for (int i = 0; i < courseCount; i++) {
            courses[i]->serialize(out);
        }
    }
    void Teacher::deserialize(std::ifstream& in, const CustomVector<Student*>& students) {
        User::deserialize(in);

        int courseCount;
        in.read(reinterpret_cast<char*>(&courseCount), sizeof(courseCount));
        this->courses.clear();
        for (int i = 0; i < courseCount; i++) {
            Course* c = new Course();
            c->deserialize(in, students);
            courses.push_back(c);
        }
    }