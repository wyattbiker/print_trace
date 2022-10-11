
#include "print_trace.cpp"
#include <vector>

using namespace std;

class MyClass {        // The class
  public:              // Access specifier
    void myMethod1(int *q);   // Method/function declaration
    int myMethod2(const char * some_value);
};

// Method/function definition outside the class
void MyClass::myMethod1(int *q) {
  int res=myMethod2("Some value");
}

int MyClass::myMethod2(const char * some_value) {
    print_trace();
    return 10;
}

/* tests */
void _some_func_A();
void _some_func_B1(int);
void _some_func_C23();

void _some_func_A() {
    _some_func_B1(1);
}

void _some_func_B1(int num) {
    _some_func_C23();
}

void _some_func_C23() {
    print_trace(2);
}


int main(int argc, char **argv) {
    _some_func_A();
    MyClass myObj;     // Create an object of MyClass
    int p=20;
    int *q=&p;
    myObj.myMethod1(q);  // Call the method
    return 0;
}
/****/
