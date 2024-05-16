#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Task {
    int taskID;
    int enterTime;
    int execTime;
    int completionTime = 0;
    int turnaroundTime = 0;
    int waitTime = 0;
    int initialExecTime;
};

void loadTasks(const string& filePath, vector<Task>& taskList) {
    ifstream inputFile(filePath);
    if (!inputFile) {
        cout << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    int taskCount, arrival, burst;
    inputFile >> taskCount;
    for (int i = 0; i < taskCount; i++) {
        inputFile >> arrival >> burst;
        taskList.push_back({ i + 1, arrival, burst, 0, 0, 0, burst });
    }
    inputFile.close();
}

void simulateFCFS(vector<Task>& taskList, int switchCost) {
    int currentTime = 0;
    for (auto& task : taskList) {
        if (currentTime < task.enterTime) {
            currentTime = task.enterTime;
        }
        task.waitTime = currentTime - task.enterTime;
        currentTime += task.execTime + switchCost;
        task.completionTime = currentTime - switchCost;
        task.turnaroundTime = task.completionTime - task.enterTime;
    }
}

void simulateSRT(vector<Task>& taskList, int switchCost) {
    auto comparator = [](Task* left, Task* right) { return left->execTime > right->execTime; };
    priority_queue<Task*, vector<Task*>, decltype(comparator)> pq(comparator);

    int currentMoment = 0, index = 0;
    while (!pq.empty() || index < taskList.size()) {
        while (index < taskList.size() && taskList[index].enterTime <= currentMoment) {
            pq.push(&taskList[index++]);
        }

        if (!pq.empty()) {
            Task* currentTask = pq.top();
            pq.pop();
            currentMoment++;
            currentTask->execTime--;

            if (currentTask->execTime > 0) {
                pq.push(currentTask);
            }
            else {
                currentTask->completionTime = currentMoment;
                currentTask->turnaroundTime = currentTask->completionTime - currentTask->enterTime;
                currentTask->waitTime = currentTask->turnaroundTime - currentTask->initialExecTime;
            }

            currentMoment += switchCost;
        }
        else if (index < taskList.size()) {
            currentMoment = taskList[index].enterTime;
        }
    }
}

void simulateRR(vector<Task>& taskList, int quantum, int switchCost) {
    queue<Task*> queue;
    int currentMoment = 0, index = 0;
    while (!queue.empty() || index < taskList.size()) {
        while (index < taskList.size() && taskList[index].enterTime <= currentMoment) {
            queue.push(&taskList[index++]);
        }

        if (!queue.empty()) {
            Task* currentTask = queue.front();
            queue.pop();
            int timeSlice = min(quantum, currentTask->execTime);
            currentTask->execTime -= timeSlice;
            currentMoment += timeSlice;

            if (currentTask->execTime > 0) {
                queue.push(currentTask);
            }
            else {
                currentTask->completionTime = currentMoment;
                currentTask->turnaroundTime = currentTask->completionTime - currentTask->enterTime;
                currentTask->waitTime = currentTask->turnaroundTime - currentTask->initialExecTime;
            }

            currentMoment += switchCost;
        }
        else if (index < taskList.size()) {
            currentMoment = taskList[index].enterTime;
        }
    }
}

void displayResults(const vector<Task>& taskList) {
    double totalTurnaround = 0, totalWait = 0;
    cout << "Task\tArrival\tBurst\tEnd\tWaiting\tTurnaround\n";
    for (const auto& task : taskList) {
        cout << task.taskID << "\t" << task.enterTime << "\t" << task.initialExecTime << "\t"
            << task.completionTime << "\t" << task.waitTime << "\t" << task.turnaroundTime << endl;
        totalTurnaround += task.turnaroundTime;
        totalWait += task.waitTime;
    }

    cout << "Average Waiting Time: " << totalWait / taskList.size() << endl;
    cout << "Average Turnaround Time: " << totalTurnaround / taskList.size() << endl;
}

int main() {
    string dataFile = R"(D:\Asp.Net-Backend\C#\New-2024\Final Project OS\Final.txt)";
    vector<Task> tasks;
    loadTasks(dataFile, tasks);

    int contextSwitchDelay = 2;
    int timeSlice = 4;
    int schedulerOption;
    cout << "Choose Scheduler:\n1.FCFS\n2.SRT\n3.RR\n4.Exit" << endl;
    cin >> schedulerOption;

    switch (schedulerOption) {
    case 1:
        cout << "FCFS Scheduler:" << endl;
        simulateFCFS(tasks, contextSwitchDelay);
        displayResults(tasks);
        break;
    case 2:
        cout << "SRT Scheduler:" << endl;
        simulateSRT(tasks, contextSwitchDelay);
        displayResults(tasks);
        break;
    case 3:
        cout << "RR Scheduler:" << endl;
        simulateRR(tasks, timeSlice, contextSwitchDelay);
        displayResults(tasks);
        break;
    case 4:
        cout << "Exit..." << endl;
        break;
    default:
        cout << "Invalid option selected." << endl;
    }

    return 0;
}
