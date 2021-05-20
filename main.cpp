#include "data_structure.hpp"
#include <iostream>
#include<cmath>
#include<stack>
#include<vector>
#include<fstream>
#include <string>
#include <chrono>


using namespace std;

struct Point
{
    double x;
    double y;
};
// находит индекс самой нижней левой точки
int Lowest_point(vector<Point> value, const int n)
{
    Point p0 = value[0];
    int k = 0;
    for (int i = 0; i < n; i++) {
        if ((value[i].y < p0.y) || (value[i].y == p0.y && value[i].x < p0.x)) {
            p0 = value[i];
            k = i;
        }
    }
    return k;
}

// даются 2 вектора p1p2 и p1p3, смотрим их ориентацию
double orientation(Point p, Point q, Point r)
{
    return (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
}

int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
vector<Point> jarvis(vector<Point> ps) {
    int size = ps.size();
    if (size < 3) return ps;
    vector<Point> hull;
    int j = Lowest_point(ps, size);
    int p = j;
    bool flag = true;
    int len = 0;
    // p - текущая точка, q - следующая точка, мы сравниваем угол между pq и pi (если i правее, то записываем её в оболочку
    while (flag) {
        int nextPoint = (p + 1) % size;
        for (int i = 0; i < size; i++) {
            if (orientation(ps[nextPoint], ps[p], ps[i]) > 0 || (orientation(ps[nextPoint], ps[p], ps[i]) == 0 && distSq(ps[p], ps[i]) >= distSq(ps[p], ps[nextPoint]))) {
                nextPoint = i;
            }
        }
        p = nextPoint;
        hull.push_back(ps[p]);
        len++;
        if (p == j) {
            flag = false;
        }
    }
    return hull;
}

int main()
{
    vector<Point> points;
    ifstream fin;
    
    fin.open("C:\\Users\\Daniil\\semester-work-jarvis-march-11-003\\dataset\\data\\Data10000.csv");

    Point point;

    string s;
    while (!fin.eof())
    {
        getline(fin, s);
        auto pos = s.find(",");
        if (pos != string::npos)
        {
            string s1 = s.substr(0, pos);
            string s2 = s.substr(pos + 1);
            point = { atof(s1.c_str()),atof(s2.c_str()) };
        }
        points.push_back(point);
    }
    fin.close();
    auto begin = std::chrono::steady_clock::now();
    vector<Point> hull = jarvis(points);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "Jarvis time in ms is " << elapsed_ms.count() << endl;

    for (int i = 0; i < hull.size(); i++)
    {
        cout << hull[i].x << " " << hull[i].y << endl;
    }
}