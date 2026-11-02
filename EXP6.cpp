#include <iostream>
#include <memory>
using namespace std;

// Resource class
class Resource
{
public:
    Resource()
    {
        cout << "Resource acquired" << endl;
    }
    ~Resource()
    {
        cout << "Resource released" << endl;
    }
    void use()
    {
        cout << "Resource is being used" << endl;
    }
};

// Manual Copyable Smart Pointer using Reference Counting
class MySmartPointer
{
private:
    Resource* ptr;
    int* ref_count; // Shared tracker for copies

public:
    // Constructor
    MySmartPointer(Resource* p)
    {
        ptr = p;
        ref_count = new int(1); // Initialize count to 1
    }

    // Copy Constructor (Handles sharing the resource)
    MySmartPointer(const MySmartPointer& other)
    {
        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ref_count)
        {
            (*ref_count)++; // Increment count when copied
        }
    }

    // Copy Assignment Operator
    MySmartPointer& operator=(const MySmartPointer& other)
    {
        if (this != &other) // Protect against self-assignment
        {
            cleanup(); // Release ownership of the old resource

            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count)
            {
                (*ref_count)++; // Increment count for the new resource
            }
        }
        return *this;
    }

    // Helper function to safely decrement and delete
    void cleanup()
    {
        if (ref_count)
        {
            (*ref_count)--;
            if (*ref_count == 0)
            {
                delete ptr;
                delete ref_count;
                cout << "Resource completely freed from memory" << endl;
            }
        }
    }

    // Destructor
    ~MySmartPointer()
    {
        cleanup();
        cout << "Manual smart pointer instance destroyed" << endl;
    }

    Resource* operator->()
    {
        return ptr;
    }

    int get_count() const
    {
        return ref_count ? *ref_count : 0;
    }
};

int main()
{
    cout << "----- Manual Copyable Smart Pointer -----" << endl;
    {
        MySmartPointer smartPtr1(new Resource());
        cout << "Initial Count: " << smartPtr1.get_count() << endl;

        {
            MySmartPointer smartPtr2 = smartPtr1; // Copying allowed!
            cout << "Count after copying: " << smartPtr1.get_count() << endl;
            smartPtr2->use();
        } // smartPtr2 goes out of scope here, but resource stays alive

        cout << "Count after scope exit: " << smartPtr1.get_count() << endl;
        smartPtr1->use();
    } // smartPtr1 goes out of scope here, resource is released

    cout << "\nProgram completed successfully." << endl;
    return 0;
}
