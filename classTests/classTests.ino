/*
  TITLE
  By V205
*/


#include <functional>
#include <map>

class testClass {
private:
  //honestly? i'm not completly sure what this does
    std::map<int, std::function<void()>> functionMap;
public:
    // at least I understand this part

    testClass() {}

    // registering functions....
    void registerFunction(int key, void (*function)()) {
        functionMap[key] = std::function<void()>(function);
    }
    //I don't really know how to use the std thing

    // ooh linked functions to ints
    void triggerFunction(int key) {
        auto it = functionMap.find(key);
        if (it != functionMap.end()) {
            it->second();
        } else {
            Serial.println("No function registered for this key.");
        }
    }
};

// testing with boring functions
void functionA() {
    Serial.println("a did something");
}

void functionB() {
    Serial.println("b did something");
}

void functionC() {
    Serial.println("c did something ");
}

testClass test;

void setup() {
    // serial as normal
    Serial.begin(9600);



    //connnect functions to ints
    test.registerFunction(1, functionA);
    test.registerFunction(2, functionB);
    test.registerFunction(3, functionC);
    test.triggerFunction(1);
}

void loop() {
    //user inputs, maybe works? nope edit I broke it.

    test.triggerFunction(1);
    
    /*
    if (Serial.available() > 0) {
        //int key = Serial.read();
        test.triggerFunction(key);

    }*/

}