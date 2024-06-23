#include <iostream>
#include <math.h>

using namespace std;

class ellipse
{
    double x1,y1,x2,y2;
    double distance;
public:
    ellipse()
    {
        cout << "Enter x1,y1,x2,y2: ";
        cin >> x1 >> y1 >> x2 >> y2;
        cout << "Enter distance (2A): ";
        cin >> distance;
    }
    void Area();
    bool PointInside(double x, double y);
    bool Overlap(ellipse b);
};

void ellipse::Area()
{
    double s;
    s = 3.14 * distance/2 * sqrt(pow(distance/2, 2) - pow(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2))/2, 2));
    cout << "Area of Ellipse: " << s << "\n\n";
}

bool ellipse::PointInside(double x, double y)
{
    double z;
    z = sqrt(pow(x - x1, 2) + pow(y - y1, 2)) + sqrt(pow(x - x2, 2) + pow(y - y2, 2));
    if(z <= distance) return true;
    return false;
}

/*
bool ellipse::Overlap(ellipse b)
{
    if(x1 < b.x1 < x2 && y1 < b.y1 < y2) return true;
    if(x1 < b.x2 < x2 && y1 < b.y1 < y2) return true;
    if(x1 < b.x1 < x2 && y1 < b.y2 < y2) return true;
    if(x1 < b.x2 < x2 && y1 < b.y2 < y2) return true;
    return false;
}
*/ //

int main()
{
    cout << "Ellipse 1:\n";
    ellipse a;
    a.Area();
    
    cout << "Ellipse 2:\n";
    ellipse b;
    b.Area();
    
    if(a.Overlap(b))
        cout << "2 Ellipses overlap each others" << "\n\n";
    else
        cout << "2 Ellipses do not overlap each others" << "\n\n";
    
    double x,y;
    cout << "Nhap diem A: ";
    cin >> x >> y;
    if(a.PointInside(x,y))
        cout << "Point A is inside Ellipse 1" << "\n";
    else
        cout << "Point A is not inside Ellipse 1" << "\n";
    if(b.PointInside(x,y))
        cout << "Point A is inside Ellipse 2" << "\n";
    else
        cout << "Point A is not inside Ellipse 2" << "\n";
        
    return 0;
}
