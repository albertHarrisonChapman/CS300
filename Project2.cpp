// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<sstream>

using namespace std;

struct Course {
    string courseId;
    string name;
    vector<string> prerequisites;
    Course() {
        courseId = "null";
        name = "null";
        prerequisites;
    }
    Course(string a, string b) {
        courseId = a;
        name = b;
    }
    Course(string a, string b, vector<string> c) {
        courseId = a;
        name = b;
        prerequisites = c;
    }
};

struct Node {
    Course course;
    Node *left;
    Node *right;
    Node() {
        left = nullptr;
        right = nullptr;
    }
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

class Tree {
private:
    Node* root;
    void addCourse(Node* node, Course course);
    void printAlphanumaric(Node* node);
public:
    Tree();
    Course searchCourse(string courseId);
    void printCoursePrereq(Course course);
    void printCourse(Course course);

    void PrintAlphanumaric();

    void Insert(Course course);
    
};

Tree::Tree() {
    root = nullptr;
}

void Tree::printCoursePrereq(Course course) {
    cout << course.courseId << ", " << course.name<<"\n";
    if (size(course.prerequisites) > 0) {
        cout << "Prerequisites: ";
        for (int i = 0; i < size(course.prerequisites); i++) {
            cout << course.prerequisites.at(i);
            if (size(course.prerequisites) > i)
                cout << ', ';
        }
    }
    cout << "\n";
    return;
}

void Tree::printCourse(Course course) {
    cout << course.courseId << ", " << course.name << "\n";
    return;
}
void Tree::PrintAlphanumaric() {
    printAlphanumaric(root);
}
void Tree::printAlphanumaric(Node* node) {
    if (node != nullptr) {
        printAlphanumaric(node->left);
        printCourse(node->course);
        printAlphanumaric(node->right);
    }
}
Course Tree::searchCourse(string courseId) {
    Node* node = root;
    while (node != nullptr) {
        if (node->course.courseId.compare(courseId) == 0)
            return node->course;
        if (node->course.courseId > courseId)
            node = node->left;
        else
            node = node->right;
    }
    Course course;
    return course;
}

void Tree::Insert(Course course) {
    if (root == nullptr)
        root = new Node(course);
    else
        addCourse(root, course);
}

void Tree::addCourse(Node* node, Course course){
    if (node->course.courseId.compare(course.courseId) > 0) {
        if (root->left == nullptr)
            root->left = new Node(course);
        else
            addCourse(node->left, course);
    }
    else {
        if (root->right == nullptr)
            root->right = new Node(course);
        else
            addCourse(node, course);
    }
}
void readFile(Tree &tree) {
    ifstream input;
    input.open ("CS 300 ABCU_Advising_Program_Input.csv");
    if (!input.is_open())
        return;
    string line, courseId, name, check;
    vector<string> prerequisites;
    while (!input.eof()) {
        getline(input, line);
        stringstream ss(line);
        int columnIndex = 0;
        while (ss) {
            if (columnIndex == 0)
                ss>>courseId;
            else if(columnIndex == 1)
                ss>>name;
            else if(columnIndex > 1) {
                ss>>check;
                prerequisites.push_back(check);
            }
            columnIndex++;
        }
        if (columnIndex > 1) {
            Course newCourse(courseId, name, prerequisites);
            tree.Insert(newCourse);
        }
        else {
            Course newCourse(courseId, name);
            tree.Insert(newCourse);
        }
    }
    
    input.close();
}

int main()
{
    string searchedCourse;
    Tree tree;
    cout << "Welcome to the course planner.\n\n";
    int choice = NULL;
    while(choice != 9) {
        cout << "1. Load Data Structure.\n";
        cout << "2.Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "9. Exit\n\n";
        cout << "What would you like to do? ";
        cin >> choice;
        switch (choice) {
        case 1:
            readFile(tree);
            break;
        case 2:
            cout << "Here is a sample schedule:\n\n";
            tree.PrintAlphanumaric();
            break;
        case 3:
            cout << "WHat course do you want to know about? ";
            cin >> searchedCourse;
            tree.printCoursePrereq(tree.searchCourse(searchedCourse));
            break;
        case 9:
            break;
        default:
            cout << choice << " is not a valid option.";
            break;
        }
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
