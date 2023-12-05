#include <iostream>
using namespace std;

class tollBooth {
private:
    unsigned int totalCars;
    double totalCash;

public:
    tollBooth()
    {
        totalCars = 0;
        totalCash = 0;
    }
    void payingCar() {
        totalCars++;
        totalCash += 0.50;
    }

    void nopayCar() {
        totalCars++;
    }

    void display() const {
        cout << "Total cars: " << totalCars << endl;
        cout << "Total cash collected: $" << totalCash << endl;
    }
};

int main() {
    tollBooth booth;
    char choice;

    cout << "Press 'a' to count a paying car, 'b' to count a nonpaying car, or 'q' to quit." << endl;

    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 'a':
                booth.payingCar();
                break;
            case 'b':
                booth.nopayCar();
                break;
            case 'q':
                booth.display();
                return 0;
            default:
                cout << "wrong choice enter 'a', 'b','q'" << endl;
                break;
        }
    }
}
