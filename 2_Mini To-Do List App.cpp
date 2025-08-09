#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Task
{
public:
    string description;
    Task(const string& desc)
    {
        description = desc;
    }
};

class ToDoList
{
private:
    vector<Task> tasks;
    string filename = "tasks.txt";

public:
    ToDoList()
    {
        loadTasksFromFile();
    }

    void addTask(const string& desc)
    {
        Task newTask(desc);
        tasks.push_back(newTask);
        saveTaskToFile(desc);
        cout << "\n[+] Task added successfully.\n";
    }

    void viewTasks() const
    {
        if (tasks.empty())
        {
            cout << "\n[!] No tasks found.\n";
            return;
        }

        cout << "\n===== Your To-Do List =====\n";
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            cout << i + 1 << ". " << tasks[i].description << endl;
        }
        cout << "============================\n";
        cout << "Total tasks: " << tasks.size() << endl;
    }

private:
    void saveTaskToFile(const string& taskDesc) const
    {
        ofstream outFile(filename, ios::app);
        if (outFile.is_open())
        {
            outFile << taskDesc << '\n';
            outFile.close();
            cout << "[Debug] Task written to file.\n";
        }
        else
        {
            cerr << "[x] Error: Unable to open file for writing.\n";
        }
    }

    void loadTasksFromFile()
    {
        ifstream inFile(filename);
        string line;
        if (inFile.is_open())
        {
            while (getline(inFile, line))
            {
                if (!line.empty())
                {
                    tasks.emplace_back(line);
                }
            }
            inFile.close();
        }
    }
};

int main()
{
    ToDoList todo;
    int choice;
    string desc;

    do
    {
        cout << "\n===== To-Do List Menu =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Exit\n";
        cout << "===============================\n";
        cout << "Enter your choice (1-3): ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[x] Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore();

        switch (choice)
        {
            case 1:
                cout << "\nEnter task description: ";
                getline(cin, desc);
                if (desc.empty())
                {
                    cout << "[!] Task description cannot be empty.\n";
                }
                else
                {
                    todo.addTask(desc);
                }
                break;

            case 2:
                todo.viewTasks();
                break;

            case 3:
                cout << "\nExiting... Goodbye!\n";
                break;

            default:
                cout << "[x] Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
