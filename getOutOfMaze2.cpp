/*
作者:sgjzfzzf
时间:2020.10.02
内容:迷宫自动寻路C++实现，这是栈版本
*/

#include<iostream>
#include<vector>
#include<stack>
using namespace std;

struct Point {
	int x;
	int y;
	Point(int, int);
	bool operator==(Point);
	bool operator!=(Point);
};

Point::Point(int X, int Y) :x(X), y(Y) {}

bool Point::operator==(Point point) {
	return (x == point.x) && (y == point.y);
}

bool Point::operator!=(Point point) {
	return !(*this == point);
}

class Path {
private:
	vector<Point> passedPoints;
public:
	Path();
	Path(const Path&);
	Path passPoint(Point);
	bool havePassed(Point);
	void printPath();
};

Path::Path() {
	passedPoints.push_back(Point(0, 0));
}

Path::Path(const Path& path) {
	for (int i = 0; i < path.passedPoints.size(); ++i) {
		passedPoints.push_back(path.passedPoints[i]);
	}
}

Path Path::passPoint(Point point) {
	Path newPath = *this;
	newPath.passedPoints.push_back(point);
	return newPath;
}

bool Path::havePassed(Point point) {
	for (int i = 0; i < passedPoints.size(); ++i) {
		if (passedPoints[i] == point) {
			return true;
		}
	}
	return false;
}

void Path::printPath() {
	cout << "START->";
	for (int i = 0; i < passedPoints.size(); ++i) {
		cout << '(' << passedPoints[i].x << ',' << passedPoints[i].y << ')' << "->";
	}
	cout << "END,Length is " << passedPoints.size() << endl;
}

struct searchPathInfo {
	Path path;
	int x;
	int y;
	searchPathInfo(Path, int, int);
};

searchPathInfo::searchPathInfo(Path pathInfo, int xInfo, int yInfo) :path(pathInfo), x(xInfo), y(yInfo) {}

void searchPath(int* maze[], int row, int line) {
	stack<searchPathInfo> searchPathStack;
	Path path;
	searchPathStack.push(searchPathInfo(path, 0, 0));
	while (!searchPathStack.empty()) {
		int x = searchPathStack.top().x, y = searchPathStack.top().y;
		path = searchPathStack.top().path;
		searchPathStack.pop();
		if (x == row - 1 && y == line - 1) {
			path.printPath();
		}
		Point possibleNextPoints[] = { Point(x - 1, y),Point(x + 1, y),Point(x, y - 1),Point(x, y + 1) };
		for (int i = 0; i < 4; ++i) {
			if (!path.havePassed(possibleNextPoints[i])
				&& possibleNextPoints[i].x >= 0
				&& possibleNextPoints[i].x < row
				&& possibleNextPoints[i].y >= 0
				&& possibleNextPoints[i].y < line
				&& maze[possibleNextPoints[i].x][possibleNextPoints[i].y] != 1) {
				Path newPath = path.passPoint(possibleNextPoints[i]);
				searchPathStack.push(searchPathInfo(newPath, possibleNextPoints[i].x, possibleNextPoints[i].y));
			}
		}
	}
}
