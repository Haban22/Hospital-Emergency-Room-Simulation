#include <iostream>
#include <string>

using namespace std;

class Patient {
public:
    string name;
    int age;
    string condition;
    int priority;

    Patient()
    {
        name = "";
        age = 0;
        condition = "";
        priority = 0;
    }

    Patient(string n, int a, string c)
    {
        name = n;
        age = a;
        condition = c;
        if (condition == "critical") {
            priority = 3;
        } else if (condition == "urgent") {
            priority = 2;
        } else {
            priority = 1;
        }
    }
};

class Node {

public:
    Patient pData;
    int priority;
    Node* next;

    Node(Patient p)
    {
        pData = p;
        priority = p.priority;
        next = NULL;
    }
};


class PriorityQueue
{
    Node* head;

public:
    PriorityQueue()
    {
        head = new Node(Patient());
    }

    void add_patient(Patient p)
    {
        Node* newnode = new Node(p);
        Node* temp = head;
        if(isEmpty())
        {
            head->next = newnode;
        }
        else
        {
            while(temp->next && temp->next->priority >= p.priority)
            {
                temp = temp->next;
            }
            newnode->next = temp->next;
            temp->next = newnode;
        }

        cout << "Patient " << p.name << " added to the queue." << endl;
    }

    void process_patient()
    {
        if(head->next == NULL)
            return;

        cout << "Processing Patient... \n" << "Processing patient: " << head->next->pData.name << " (Priority: " << head->next->pData.priority << ")" << endl;

        Node* temp = head->next;

        head->next = head->next->next;

        delete temp;
    }

    void update_patient(Patient p, string newCondition)
    {
        Node* temp = head->next;

        p.condition = newCondition;

        if (newCondition == "critical")
        {
            p.priority = 3;
        }
        else if (newCondition == "urgent")
        {
            p.priority = 2;
        }
        else
        {
            p.priority = 1;
        }

        add_patient(p);

        cout << "Priority of patient " << p.name << " updated to " << newCondition << endl;
    }

    void display()
    {
        Node* temp = head->next;

        cout << "Current Patients in the queue: \n";

        while(temp != NULL)
        {
            cout << "Name: " << temp->pData.name << ", Age: " << temp->pData.age << ", Condition: " << temp->pData.condition  << ", Priority: " << temp->priority << endl;
            temp = temp->next;
        }
    }

    int size()
    {
        int count = 0;
        Node* temp = head->next;
        while(temp != NULL)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void frontName()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
        }
        cout << "Front Patient Name: " << head->next->pData.name << endl;
    }

    bool isEmpty()
    {
        if(!head->next)
            return true;
        else
            return false;
    }

};

int main()
{
    PriorityQueue queue;

    Patient p1("Ahmed", 35, "critical");
    Patient p2("Mazen", 45, "urgent");
    Patient p3("Omar", 25, "normal");

    queue.add_patient(p1);
    queue.add_patient(p2);
    queue.add_patient(p3);

    queue.frontName();

    queue.display();

    queue.process_patient();

    queue.display();

    queue.update_patient(p1, "urgent");

    queue.display();

    return 0;
}