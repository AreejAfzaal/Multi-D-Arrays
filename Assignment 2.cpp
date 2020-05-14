#include<iostream>
using namespace std;
template <class T>
class mdArray;


template <class T>
class mdArray
{
	int row; //the first dimension
	int col; //the second dimension
	int zaxis; //the third dimension
	int dim; //the number of dimensions
	int arrSize; //the array size of linear array
	T * arr; //linear array to store the multi dim arrays
	int *dimArr; //the array to store dimensions
public:
	
	mdArray()  //DEFAULT CONSTRUCTOR
	{
		row = 0;
		col = 0;
		zaxis = 0;
		dim = 0;
		arrSize = 0;
		arr = NULL;
		dimArr = NULL;
	}

	mdArray(int d) //PARAMETRIZED CONSTRUCTOR
	{
		row = 0;
		col = 0;
		zaxis = 0;
		dim = 0;
		dimArr = NULL;
		dimension(d);
		arrSize = 0;
		arr = NULL;
	}

	mdArray(const mdArray& a) //COPY CONSTRUCTOR
	{
		row = a.row;
		col = a.col;
		zaxis = a.zaxis;
		dim = a.dim;
		arrSize = a.arrSize;
		dimArr = new int[dim];
		for (int i = 0; i < dim; i++) 
		{
			dimArr[i] = a.dimArr[i];
		}
		arr = new int[arrSize];
		for (int i = 0; i <arrSize; i++) 
		{
			arr[i] = a.arr[i];
		}
	}

	~mdArray() //DESTRUCTOR
	{
		if (dimArr != NULL)
		{
			delete[]dimArr;
			dimArr = NULL;
		}
		if (arr != NULL)
		{
			delete[]arr;
			arr = NULL;
		}
	}

	void dimension(int d) //FUNCTION TO INPUT THE NUMBER OF DIMENSIONS AND THE DIMENSIONS
	{
		cout << "Enter the number of dimension(s): ";
		cin >> d;
		dim = d;

		dimArr = new int[dim];

		cout << "Enter the dimension(s):\n";
		for (int i = 0; i < dim; i++)
		{
			cin >> dimArr[i];
			if (i == 0)
			{
				row = dimArr[i];
			}
			else if (i == 1) 
			{
				col = dimArr[i];
			}
			else if (i == 2)
			{
				zaxis = dimArr[i];
			}
		}
	}

	friend ostream & operator<<(ostream & out, mdArray a);  //OVERLOADING THE STREAM INSERTION OPERATOR

	void input() //INPUTTING THE ELEMENTS
	{
		arrSize = dimArr[0];
		for (int i = 1; i < dim; i++)  //calculating size of the array
		{
			arrSize *= dimArr[i]; 
		}

		cout << "\n\narray size: " << arrSize << endl << endl;

		arr = new T[arrSize]; //creating the linear array to store the elements

		cout << "Enter the elements of the " << dim << "-D array:\n";
		for (int i = 0; i < arrSize; i++)
		{
			cin >> arr[i]; //taking input from the user
		}
	}

	T * Insert() //ADD AN ELEMENT AT A GIVEN INDEX	
	{
		int insert = 0, insertIndex = 0;
		cout << "\nEnter the element to be inserted: "; //take the index and element from the user
		cin >> insert;
		cout << "Enter the index: ";
		cin >> insertIndex;
		cout << endl;

		for (int i = arrSize; i > insertIndex; i--) //create space at that index by shifting the elements 
		{
			arr[i] = arr[i - 1];
		}
		arr[insertIndex] = insert; //insert at the index

		arrSize++; //increase the size of the array

		cout << "\nThe new array is:\n";

		return arr;
	}

	void output() //SIMPLE OUTPUT FUNCTION
	{
		cout << "\nYour array of dimension(s) ";
		for (int i = 0; i < dim; i++)
		{
			cout << dimArr[i];
			if (i != dim - 1)
			{
				cout << " x ";
			}
		}
		cout << " is:\n";
		int l = 0;
		for (int k = 0; k < zaxis; k++) 
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					cout << arr[l++] << " ";
				}
				cout << endl;
			}
			cout << "\n\n";
		}

		if (l < arrSize) 
		{
			while (l < arrSize) 
			{
				cout << arr[l++] << " ";
			}
		}
	}

	bool Retrieve() //SEarch AND RETURN ANY ELEMENT FROM THE ARRAY
	{
		int retrieve = 0;
		cout << "\nEnter the element to retrieve: "; //take input from the user
		cin >> retrieve;

		for (int i = 0; i < arrSize; i++)
		{
			if (arr[i] == retrieve)   //if element is found
			{
				return 1; //return true
			}
		}
		return 0;
	}

	//GETTERS AND SETTERS
	void setRow(int r)
	{
		row = r;
	}
	void setCol(int c)
	{
		col = c;
	}
	void setZ(int z)
	{
		zaxis = z;
	}
	int  getDim()
	{
		return dim;
	}
	int * getDimArr()
	{
		return dimArr;
	}

	void Extend() //DOUBLE THE ARRAY IN SIZE
	{
		T*tarr = new T[arrSize]; //create a temp array

		for (int i = 0; i < arrSize; i++) //copy the array elements into temp array
		{
			tarr[i] = arr[i];
		}
		//delete[]arr; //delete the array

		int tsize = arrSize; //save the old size
		arrSize *= 2; //double the size

		arr = new T[arrSize]; //point the pointer to the new array now doubled in size
		for (int i = 0; i < tsize; i++)
		{
			arr[i] = tarr[i]; //copy back the elements from temp to the new array
		}
		//delete[]tarr; //delete the temp array
		tarr = NULL;

		//cout << "\nNEW SIZE IS: " << arrSize << endl;
	}

	void Shrink() //REDUCE THE ARRAY SIZE TO HALF
	{
		arrSize /= 2; //divide the array size by half
		T*tarr = new T[arrSize]; //create a temp array of the new size
		for (int i = 0; i < arrSize; i++) 
		{
			tarr[i] = arr[i]; //copy the elements to the temp array
		}
		//delete arr; //delete the array

		arr = new T[arrSize]; //point to a new array of size halved
		for (int i = 0; i < arrSize; i++) 
		{
			arr[i] = tarr[i]; //copy back from the temp to the original array (only half elements wil exist)
		}
		//delete tarr;
		tarr = NULL;
		//cout << "\nNEW SIZE IS: " << arrSize << endl;
	}

	void Delete() //SEARCH AND REMOVE AN ELEMENT AT A GIVEN INDEX
	{
		int Index = 0;
		cout << "\nEnter the index of element to be deleted: "; //input the index from user
		cin >> Index;
		for (int i = Index; i < arrSize; i++)
		{
			arr[i] = arr[i + 1]; //shift the elements one position back
		}
		arrSize--; //reduce array size

		T *tarr = new T[arrSize]; 
		for (int i = 0; i < arrSize; i++)
		{
			tarr[i] = arr[i]; //copy to temp array
		}
		delete[] arr; 
		arr = NULL;

		cout << "\narray size\n" << arrSize;
		arr = new T[arrSize]; //point to array with size-1
		for (int i = 0; i < arrSize; i++)
		{
			arr[i] = tarr[i]; //copy back the elements
		}
		delete[] tarr; //delete the temp arary

		cout << "\nThe new array is:\n";
		//cout << arr;
	}
};

template <class T>
ostream & operator<<(ostream & out, mdArray<T> a) //STREAM OPERATOR OVERLOADED
{
	int l = 0;
	for (int k = 0; k <a.zaxis; k++) //outputting the array uptil third dimensions in table form
	{
		for (int i = 0; i < a.row; i++)
		{
			for (int j = 0; j < a.col; j++)
			{
				out << a.arr[l++] << " ";
			}
			out << endl;
		}
		out << "\n";
	}

	if (l < a.arrSize)  //outputing the rest of elements in higher dimensions in linear form 
	{
		while (l < a.arrSize)
		{
			out << a.arr[l++] << " ";
		}
	}

	return out;
}

int main()
{
	//----------------------ConstructorWithDimension----------------------//
	mdArray<int> a(0);
	//----------------------------Constructor-----------------------------//
	//int d = 0;
	//a.dimension(d);
	//-------------------------------Input--------------------------------//
	a.input();
	//-----------------------------Delete---------------------------------//
	a.Delete();
	cout << a;
	//-------------------------------Insert-------------------------------//
	a.Insert();
	//-------------------------------Print--------------------------------//
	cout << a;
	//------------------------------Retrieve------------------------------//
	if (a.Retrieve())
	{
		cout << "\nElement is present in the array.\n";
	}
	else
	{
		cout << "\nElement is NOT present in the array.\n";
	}
	cout << "\n--------------------------------------------------------------\nWithout copy constructor:\n";
	cout << a << endl;
	//-------------------------CopyConstructor----------------------------//
	mdArray<int> b(a);
	cout << "--------------------------------------------------------------\nCopy Constructor called:\n" << b;
	
	//-----------------------------Extend---------------------------------//
	cout << "\n--------------------------------------------------------------\nExtend Called:\n";
	a.Extend();
	cout << a;
	//-----------------------------Shrink---------------------------------//
	cout << "\n--------------------------------------------------------------\nShrink Called:\n";
	a.Shrink();
	cout << a;

	system("pause");
}