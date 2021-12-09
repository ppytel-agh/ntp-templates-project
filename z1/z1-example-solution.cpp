#include <iostream>
#include <cmath>

template <typename T> class vec{
  private:
    T deltaX;
    T deltaY;
  public:
    vec(T x, T y):deltaX(x), deltaY(y){}

    T getX(){
      return deltaX;
    }

    T getY(){
      return deltaY;
    }
    
    double vecLength(){
      return sqrt(deltaX*deltaX + deltaY*deltaY);
    }
};

template <typename T>
void insertSort(T *tab, int n)
{
	int j;
	T temp;

	for (int i = 1; i < n; ++i)
	{
		temp = tab[i];
		j = i - 1;

		while (j >= 0 && tab[j] > temp)
		{
			tab[j + 1] = tab[j];
			j = j - 1;
		}
		tab[j + 1] = temp;
	}
}

template <typename T>
void insertSort(vec<T> *tab, int n)
{
	int j;
	vec<T> temp = vec<T>(0,0);

	for (int i = 1; i < n; ++i)
	{
		temp = tab[i];
		j = i - 1;

		while (j >= 0 && tab[j].vecLength() > temp.vecLength())
		{
			tab[j + 1] = tab[j];
			j = j - 1;
		}
		tab[j + 1] = temp;
	}
}

template <typename T>
void printTab(T *tab, int n)
{

	for (int i = 0; i < n; ++i)
	{
		std::cout << tab[i] << ' ';
	}
	std::cout << "\n\n";
}


template <typename T>
void printTab(vec<T> *tab, int n)
{
	for (int i = 0; i < n; ++i)
	{
		std::cout <<"Length:"<< tab[i].vecLength()<<"\n";
	}
	std::cout << "\n";
}

int main() {
  int intTab[] = {45,67,420,2137,15,69,86,1152,54, 8,0,0,8,5};

  std::string stringTab[] = {"random", "words", "to","test" ,"function", "like","cat", "or", "pizza","these", "literally", "make","no", "sense","just","for","testing"};
  
  double doubleTab[] = {56.2,4.5, 2153.223, 15.6, 214.6, 0.6, 5.7,6.4};
  
  vec<double> doubleVecTab[] = {{4.5,.5}, {1,1.7}, {0,0}, {3.3,3.3},
  {15.5,1.2}, {65.1,.7}, {21.37,4.20}, {4.5,0}};

  vec<int> intVecTab[] = {{1,2},{0,0},{54,1},{67,2},{90, 5}, {5,7},{6,9},{21,37}};		

  std::cout<<"===intTab===\n";
  insertSort(intTab, sizeof(intTab) / sizeof(int));
  std::cout<<"After sort: ";
  printTab(intTab, sizeof(intTab) / sizeof(int));

  std::cout<<"===doubleTab===\n";
  insertSort(intTab, sizeof(doubleTab) / sizeof(double));
  std::cout<<"After sort: ";
  printTab(intTab, sizeof(doubleTab) / sizeof(double));

  std::cout<<"===stringTab===\n";
  insertSort(stringTab, sizeof(stringTab) / sizeof(stringTab[0]));
  std::cout<<"After sort: ";
  printTab(stringTab, sizeof(stringTab) / sizeof(stringTab[0]));

  std::cout<<"===intVecTab===\n";
  insertSort(intVecTab, sizeof(intVecTab) / sizeof(intVecTab[0]));
  std::cout<<"After sort: \n";
  printTab(intVecTab, sizeof(intVecTab) / sizeof(intVecTab[0]));

  std::cout<<"===doubleVecTab===\n";
  insertSort(doubleVecTab, sizeof(doubleVecTab) / sizeof(doubleVecTab[0]));
  std::cout<<"After sort: \n";
  printTab(doubleVecTab, sizeof(doubleVecTab) / sizeof(doubleVecTab[0]));


  return 0;
}
/* output:

===intTab===
After sort: 0 0 5 8 8 15 45 54 67 69 86 420 1152 2137 

===doubleTab===
After sort: 0 0 5 8 8 15 45 54 

===stringTab===
After sort: cat for function just like literally make no or pizza random sense test testing these to words 

===intVecTab===
After sort: 
Length:0
Length:2.23607
Length:8.60233
Length:10.8167
Length:42.5441
Length:54.0093
Length:67.0298
Length:90.1388

===doubleVecTab===
After sort: 
Length:0
Length:1.97231
Length:4.5
Length:4.52769
Length:4.6669
Length:15.5464
Length:21.7788
Length:65.1038

*/
