### Elijah Bastien
### CS-300 
### Course Planner (Data Structures & BST)
This project involved developing a system for academic advisors to manage a curriculum by loading course data (ID, title, and prerequisites) from a CSV file.

### 📋 Reflection
**What was the problem you were solving?**
The goal was to provide an efficient way to view a sorted list of all courses or look up specific details, including prerequisite requirements, for a large curriculum.

**How did you approach the problem?**
I evaluated Vectors, Hash Tables, and Binary Search Trees (BST). I chose a **Binary Search Tree** because it inherently maintains data in alphanumeric order, allowing for an O(n) In Order traversal and efficient O(\log n) searching.



**How did you overcome roadblocks?**
A major challenge was ensuring that every listed prerequisite actually existed in the system. I implemented a logical validation pass that searches the BST for each prerequisite ID. I also simplified the file loading process by renaming the data source to "data.csv" to reduce user input errors in the console.

**How has this project evolved your approach to software?**
* **Scalability:** I now design with "Big O" complexity in mind to ensure programs remain fast as data grows.
* **Maintainability:** By using clear structures and modular functions, I ensure the code is readable and easy to adapt, such as swapping a CSV reader for a database without breaking the core logic.
* **Robustness:** I implemented case insensitive searching to ensure the program handles various user inputs without crashing.
