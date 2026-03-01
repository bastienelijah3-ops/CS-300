#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// --- Data Structures ---

// Structure to hold course information 
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;

    Course() {}
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize with a course
    Node(Course aCourse) : Node() {
        this->course = aCourse;
    }
};

// --- Binary Search Tree Class ---

class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string courseNumber);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void DeleteTree(Node* node);
    void InOrder();
    void Insert(Course course);
    Course Search(string courseNumber);
};

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    DeleteTree(root);
}

void BinarySearchTree::DeleteTree(Node* node) {
    if (node != nullptr) {
        DeleteTree(node->left);
        DeleteTree(node->right);
        delete node;
    }
}

/**
 * Traverse the tree in order to print alphanumerically
 */
void BinarySearchTree::InOrder() {
    this->inOrder(root);
}

/**
 * Insert a course into the BST
 */
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->addNode(root, course);
    }
}

/**
 * Search for a specific course
 */
Course BinarySearchTree::Search(string courseNumber) {
    Node* current = root;

    while (current != nullptr) {
        if (current->course.courseNumber == courseNumber) {
            return current->course;
        }
        if (courseNumber < current->course.courseNumber) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    Course emptyCourse;
    return emptyCourse;
}

void BinarySearchTree::addNode(Node* node, Course course) {
    if (node->course.courseNumber > course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            this->addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            this->addNode(node->right, course);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {
    if (node == nullptr) {
        return;
    }
    inOrder(node->left);
    cout << node->course.courseNumber << ", " << node->course.courseName << endl;
    inOrder(node->right);
}

// --- Helper Functions ---

/**
 * Load data from CSV file into the BST 
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    ifstream file(csvPath);
    if (!file.is_open()) {
        cout << "Error: Could not open file. Check the file name and try again." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split line by commas 
        while (getline(ss, token, ',')) {
            // Clean up carriage returns/whitespace
            token.erase(remove(token.begin(), token.end(), '\r'), token.end());
            token.erase(remove(token.begin(), token.end(), '\n'), token.end());
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }

        // Basic validation: must have at least Number and Name 
        if (tokens.size() < 2) {
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.courseName = tokens[1];

        // Add prerequisites if any 
        for (size_t i = 2; i < tokens.size(); i++) {
            course.prerequisites.push_back(tokens[i]);
        }

        bst->Insert(course);
    }
    file.close();
}

/**
 * Convert string to uppercase for case-insensitive searching 
 */
string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// --- Main Program Loop ---

int main() {
    BinarySearchTree* bst = new BinarySearchTree();
    string csvPath, courseKey;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter the file name containing the course data: ";
            cin >> csvPath;
            loadCourses(csvPath, bst);
            break;

        case 2:
            cout << "Here is a sample schedule:" << endl;
            bst->InOrder();
            break;

        case 3:
            cout << "What course do you want to know about? ";
            cin >> courseKey;
            courseKey = toUpperCase(courseKey); // Match sample output "csci400" 

            {
                Course course = bst->Search(courseKey);
                if (!course.courseNumber.empty()) {
                    cout << course.courseNumber << ", " << course.courseName << endl;
                    cout << "Prerequisites: ";
                    if (course.prerequisites.empty()) {
                        cout << "None";
                    }
                    else {
                        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                            cout << course.prerequisites[i];
                            if (i < course.prerequisites.size() - 1) cout << ", ";
                        }
                    }
                    cout << endl;
                }
                else {
                    cout << "Course not found." << endl;
                }
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl; // 
            break;
        }
    }

    delete bst;
    return 0;
}
// I changed the name of the csv file to "data" a simplier name to prevent mistakes in the console that previously prevented the file from being found 