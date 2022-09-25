//Водоем
// функции:
// определение объема
// определение площади
// метод определения, относятся ли водоемы к одному типу? (comparison Type)
// метод(функция) сравнения площади водной поверхности водоемов одного типа (comparison S)
// метод для копирования объектов
//

#include <iostream>
#include <fstream>
#include <io.h>
#include <stdio.h>

using namespace std;

class Reservoir
{
private:
	char name[20];
	double length;//длина
	double width;//ширина
	double height;//высота
	char type[6];
	double V = 0;//объем
	double S = 0;//площадь
public:
	int CountRes = 0;
	static int SizeSave;//статическая переменная, для записи количества объектов класса, для того, чтобы знать, какое кол-во объектов мы считываем 
	//конструктор с параметрами//конструктор с записанными параметрами
	Reservoir(const char* name, int length, int width, int height,const char* type)
	{
		strcpy_s(this->name, 20, name);
		this->length = length;
		this->width = width;
		this->height = height;
		strcpy_s(this->type, 6, type);
		this->V = length * width * height;
		this->S = length * width;
	} 
	Reservoir() : Reservoir(" ", 0, 0, 0, " ") {}//дефолтный конструктор
	Reservoir(const Reservoir& r)//конструктор копирования
	{
		strcpy_s(this->name, 20, r.name);
		this->length = r.length;
		this->width = r.width;
		this->height = r.height;
		strcpy_s(this->type, 6, r.type);
		this->V = r.V;
		this->S = r.S;
	}
	void input();//correct job
	void print() const ;//correct job
	friend void DeleteReservoir(Reservoir*& arr, int& size);
	friend void ComparisonsS(Reservoir* arr, int& size);
	friend void CopyReservoir(Reservoir*& arr, int& size);
	bool ComparisonsType(const Reservoir& r); 
};
int Reservoir::SizeSave;

void showAllRes(Reservoir* arr, int& size);//correct job
void AddReservoir(Reservoir*& arr, int& size); //correct job
void DeleteReservoir(Reservoir*& arr, int& size); //correct job
void CopyReservoir(Reservoir*& arr, int& size);//correct job
												//как реализовывать копирование? т.к. в Задании нет уточнения,(может это просто конструктор копирования),
												//то я просто добавлю копию найденную по имени в конец массива
void ComparisonsS(Reservoir* arr, int& size);//сравнение по площади поверхности воды //correct job
void savedata_bin(Reservoir* arr, int& size);
void loaddata_bin(Reservoir* arr, int& size);

void Savedata(Reservoir* arr, int& size);
void Loaddata(Reservoir*& arr, int& size);

int main()
{
	int size = 0;
	Reservoir* arrRes = new Reservoir[size];
	int k;

	//loaddata_bin(arrRes, size);

	//arrRes[0].input();
	do
	{
		system("cls");
		cout << "1 - Show all reservoirs;" << endl;
		cout << "2 - Add reservoir;" << endl;
		cout << "3 - Delete reservoir;" << endl;
		cout << "4 - Copy reservoir on end array;" << endl;
		cout << "5 - Comparison reservoirs;" << endl;
		cout << "6 - Save Data;" << endl;
		cout << "7 - Load Data;" << endl;
		cout << "0 - EXIT;" << endl;
		cin >> k;
		switch (k)
		{
		case 1:
			showAllRes(arrRes, size);
			break;
		case 2:
			AddReservoir(arrRes, size);
			break;
		case 3:
			DeleteReservoir(arrRes, size);
			break;
		case 4:
			CopyReservoir(arrRes, size);
			break;
		case 5:
			ComparisonsS(arrRes, size);
			break;
		case 6:
			Savedata(arrRes, size);
			break;
		case 7:
			Loaddata(arrRes, size);
			break;
		}
	} while (k != 0);

	//savedata_bin(arrRes, size);
	
	delete[] arrRes;

	return 0;
}

void Reservoir::input()
{
	cout << "Enter Name Reservoir: ";
	cin >> name;
	cout << "Enter length: ";
	cin >> length;
	cout << "Enter width: ";
	cin >> width;
	cout << "Enter height: ";
	cin >> height;
	cout << "Enter type reservoir(fresh or salty): ";
	cin >> type;
	
	V = length * width * height;
	S = length * width;
}

void Reservoir::print() const
{
	cout << "Name of reservoir: " << name << endl;
	cout << "Length: " << length << endl;
	cout << "Width: " << width << endl;
	cout << "Height: " << height << endl;
	cout << "Type of reservoir: " << type << endl;
	cout << "Volume of reservoir: " << V << endl;
	cout << "Square of reservoir: " << S << endl;
	cout << "Count objects: " << SizeSave << endl;
}

bool Reservoir::ComparisonsType(const Reservoir& r) 
{
	if (strcmp(this->type, r.type) == 0)
		return true;
	else
		return false;
}

void showAllRes(Reservoir* arr, int& size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i].print();
		cout << endl;
	}cout << endl;
	system("pause");
}

void AddReservoir(Reservoir*& arr, int& size)
{
	Reservoir* newArray = new Reservoir[size + 1];
	for (int i = 0; i < size; i++)
	{
		newArray[i] = arr[i];
	}
	newArray[size].input();
	Reservoir::SizeSave++;
	size++;
	cout << "SizeSave = " << Reservoir::SizeSave << " Size = " << size << endl;
	system("pause");
	delete[] arr;
	arr = newArray;
}

void DeleteReservoir(Reservoir*& arr, int& size)
{
	int p = -1;
	char name[20];
	cout << "Enter the name of reservoir for DELETE: ";
	cin >> name;
	for (int i = 0; i < size; i++)
	{
		if (strcmp(name, arr[i].name) == 0)
			p = i;
	}
	if (p > 0)
	{
		
		Reservoir* newArray = new Reservoir[size - 1];
		for (int i = 0; i < p; i++)
		{
			newArray[i] = arr[i];
		}
		for (int i = p+1; i < size; i++)
		{
			newArray[i-1] = arr[i];
		}
		size--;
		delete[]arr;
		arr = newArray;
	}
	else if (p == 0)
	{
		size--;
		Reservoir* newArray = new Reservoir[size];
		for (int i = 0; i < size; i++)
		{
			newArray[i] = arr[i + 1];
		}
		delete[] arr;
		arr = newArray;
	}
	else
		cout << "Reservoir not found!!!" << endl;
}

void CopyReservoir(Reservoir*& arr, int& size)
{
	char tempName[20];
	cout << "Enter name reservoir for copy to end array: ";
	cin >> tempName;
	
	for (int i = 0; i < size; i++)
	{
		if (strcmp(arr[i].name, tempName) == 0)
		{
			Reservoir* newArray = new Reservoir[size + 1];
			for (int i = 0; i < size; i++)
			{
				newArray[i] = arr[i];
			}
			newArray[size] = arr[i];
			size++;
			delete[] arr;
			arr = newArray;
			break;
		}
	}

}

void ComparisonsS(Reservoir* arr, int& size)
{
	char tempName1[6];
	char tempName2[6];
	int t1 = -1, t2 = -1;
	cout << "Enter name of first reservoir: ";
	cin >> tempName1;
	cout << "Enter name of second reservoir: ";
	cin >> tempName2;

	for (int i = 0; i < size; i++)
	{
		if (strcmp(arr[i].name, tempName1) == 0)
			t1 = i;
	}
	for (int i = 0; i < size; i++)
	{
		if (strcmp(arr[i].name, tempName2) == 0)
			t2 = i;
	}

	if (t1 < 0 || t2 < 0)
		cout << "Not correct name reservoirs!" << endl;
	else
	{
		if (arr[t1].ComparisonsType(arr[t2]))
		{
			cout << "Squar first reservoir: " << arr[t1].S << endl;
			cout << "Squar first reservoir: " << arr[t2].S << endl;
			if (arr[t1].S == arr[t2].S)
				cout << "Reservoirs is equal!" << endl;
			else if (arr[t1].S > arr[t2].S)
				cout << "Reservoir " << arr[t1].name << " biggest Reservoir " << arr[t2].name << endl;
			else
				cout << "Reservoir " << arr[t2].name << " biggest Reservoir " << arr[t1].name << endl;
		}
		else
			cout << "Reservoirs not same type!!!" << endl;
	}

	cout << endl;
}

void savedata_bin(Reservoir* arr, int& size)
{
	FILE* file;
	const char* filename = "File_one.txt";
	fopen_s(&file, filename, "wb");
	fwrite(&arr[0], sizeof(Reservoir), size, file);
	fclose(file);
}

void loaddata_bin(Reservoir* arr, int& size)
{
	FILE* file;
	const char* filename = "File_one.txt";
	struct _finddata_t myfileinfo;
	intptr_t done = _findfirst(filename, &myfileinfo);
	if (done == -1)
	{
		fopen_s(&file, filename, "wb");
		fclose(file);
	}
	fopen_s(&file, filename, "rb");
	while (!feof(file))
	{
		fread(&arr[size], sizeof(Reservoir), 1, file);
		size++;
	}
	fclose(file);
	size--;
}

void Savedata(Reservoir* arr, int& size)
{
	char filename[15] = "SecondFile.txt";
	ofstream fout;
	fout.open(filename);
	if (!fout.is_open())
	{
		cout << "Error... file is not open!" << endl;
	}
	else
	{
		cout << "File is open!" << endl;
		arr[0].CountRes += Reservoir::SizeSave;
		cout << "arr[0].CountRes = " << arr[0].CountRes << endl;
		system("pause");

		for (int i = 0; i < size; i++)
		{
			fout.write((char*)&arr[i], sizeof(Reservoir));
		}
	}
	//size = Reservoir::SizeSave;
	fout.close();
}

void Loaddata(Reservoir*& arr, int& size)
{
	char filename[15] = "SecondFile.txt";
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "Error... file is not open!" << endl;
		system("pause");
	}
	else
	{
		cout << "File is open!" << endl;
		Reservoir temp;
		fin.read((char*)&temp, sizeof(Reservoir));
		cout << "temp.CountRes = " << temp.CountRes << endl;
		size = temp.CountRes;
		//cout << "SizeSave = " << temp.SizeSave << " Size = " << size << endl;
		Reservoir* newArr = new Reservoir[size];
		for (int i = 0; i < size; i++)
		{
			fin.read((char*)&newArr[i], sizeof(Reservoir));
		}
		arr = newArr;
	}
	fin.close();
}
