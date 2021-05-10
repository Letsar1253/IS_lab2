#include <iostream>
#include <ctime>

using namespace std;

double equation(double x)
{
	return x * x + 4;
}


class Point
{
public:
	double x=0;
	double y=0;

	Point() {};
	~Point() {};
    bool operator<(Point& obj)
    {
        return (this->y < obj.y);
    };
    bool operator>(Point& obj)
    {
        return (this->y > obj.y);
    };
    Point& operator=(Point& obj)
    {
        this->x = obj.x;
        this->y = obj.y;
        return *this;
    };

private:
	

};

void crossing(Point& FirstParent, Point& SecondParent, Point& FirstChild, Point& SecondChild)
{
    double randomValeu = ((double)rand() / (double)RAND_MAX);
    FirstChild.x = randomValeu * FirstParent.x + (1 - randomValeu) * SecondParent.x;
    SecondChild.x = randomValeu * SecondParent.x + (1 - randomValeu) * FirstParent.x;
}

double rnd()
{
    return -0.5 + ((double)rand() / (double)RAND_MAX);
}

template <typename T>

static void quick_sort(T* arr, int right, int left)
{
    T x;
    int i, j, c = right, d = left;
    while (c < d) {
        int f = rand() % (d + 1 - c) + c;
        x = arr[f]; i = c; j = d;
        while (i < j) {
            while (arr[i] < x) i++;
            while (arr[j] > x) j--;
            if (i <= j)
            {
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++; j--;
            }
        }
        if (j - c < d - i)
        {
            if (c < j) quick_sort(arr, c, j); c = i;
        }
        else { if (i < d) quick_sort(arr, i, d); d = j; }
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
	srand((int)time(0));
	cout << "Ввод кол-во особей: ";
	int individualCount = 0;
	cin >> individualCount;
    cout << "\nВвод шанса кроссенговера: ";
    double chanceCrossover, chanceMutation;
    cin >> chanceCrossover;
    cout << "\nВвод шанса мутации: ";
    cin >> chanceMutation;
    Point** pointMatrix = new Point*[2];
    int indexParent = 0, indexChildren = 1;
    for (int i = 0; i < 2; i++)
    {
        pointMatrix[i] = new Point[individualCount];
    }
    //создание особей
	for (int i = 0; i < individualCount; i++)
	{
        pointMatrix[indexParent][i].x = rand();
		pointMatrix[indexParent][i].y = equation(pointMatrix[indexParent][i].x);
	}
    //сортировка их по возрастанию
    quick_sort<Point>(pointMatrix[indexParent], 0, individualCount - 1);


    int countGlobal = 0, countOfCorrectValues=0;
    //////////////////////////////////////////////////
    while (countOfCorrectValues!=1000)
    {

        //шанс и кол-во особей для скрещивание
        double chanceCrosses = 0.3 + (rand() % 5) * 0.1;
        int numberCrosses = (int) chanceCrosses * individualCount;
        int firstParent = 0, secondParent = 0;
        for (int i = 0; i < individualCount;)
        {
            firstParent = (int)((double)rand() / (double)RAND_MAX) * numberCrosses;
            secondParent = (int)((double)rand() / (double)RAND_MAX) * numberCrosses;
            if (chanceCrossover >= ((double)rand() / (double)RAND_MAX))
            {
                //кроссинговер
                crossing(
                    pointMatrix[indexParent][firstParent],
                    pointMatrix[indexParent][secondParent],
                    pointMatrix[indexChildren][i],
                    pointMatrix[indexChildren][i + 1]);
            }
            else
            {
                //наследование без кроссинговера
                pointMatrix[indexChildren][i].x = pointMatrix[indexParent][firstParent].x;
                pointMatrix[indexChildren][i + 1].x = pointMatrix[indexParent][secondParent].x;
            }
            i += 2;
        }
        //мутация от -0.5 до 0.5
        for (int i = 0; i < individualCount; i++)
        {
            if (chanceMutation >= ((double)rand() / (double)RAND_MAX))
            {
                pointMatrix[indexChildren][i].x += rnd();
            }
            pointMatrix[indexChildren][i].y = equation(pointMatrix[indexChildren][i].x);
        }
        //сортировка детей по возрастанию
        quick_sort<Point>(pointMatrix[indexChildren], 0, individualCount -1);

        countGlobal++;
        int temp = indexChildren;
        indexChildren = indexParent;
        indexParent = temp;
        if (abs(pointMatrix[indexParent][0].y - pointMatrix[indexChildren][0].y) < 0.001)
        {
            countOfCorrectValues++;
        }
        else
        {
            countOfCorrectValues = 0;
        }
    }
    cout << endl << "кол-во итераций : "<<countGlobal-1000 << endl << "Min : "<<pointMatrix[indexParent][0].y;
}
