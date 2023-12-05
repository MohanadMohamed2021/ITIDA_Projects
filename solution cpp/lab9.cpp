#include <iostream>
#include <cmath>

class Polar
{
private:
    double radius;
    double angle;

public:
    Polar(double cp_raduis,double cp_angle) : radius(cp_raduis), angle(cp_angle) {}
    Polar operator+(Polar &obj)
    {
        double x1 = radius * cos(angle);
        double y1 = radius * sin(angle);
        double x2 = obj.radius * cos(obj.angle);
        double y2 = obj.radius * sin(obj.angle);

        double x_sum = x1 + x2;
        double y_sum = y1 + y2;

        double new_radius = sqrt(x_sum * x_sum + y_sum * y_sum);
        double new_angle = atan2(y_sum, x_sum);

        return Polar(new_radius,new_angle);
    }

    void display() {
        std::cout << "Radius: " << radius << ", Angle: " << angle << " radians" << std::endl;
    }
};

int main() {
    Polar p1(2.0, 1.05);
    Polar p2(1.0, 2.05);

    Polar p3 = p1 + p2;

    std::cout << "Result of addition: ";
    p3.display();

    return 0;
}
