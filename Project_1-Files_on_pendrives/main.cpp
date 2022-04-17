#include <iostream>
#include <cstdio>
#pragma warning(disable : 4996)
using namespace std;

#define NUMBER_OF_PENDRIVES 2
#define NUMBER_OF_DATA 2
#define SIZE 1
#define ID 0

struct pendrive {
	int size = 0;
	int numberOfFiles = 0;
	int begining = 0;
	int ending = 0;
};


int partition(int * tabToSort, int* tabConnected, int begining, int ending) {
	int pivot = tabToSort[begining], l = begining-1, r = ending+1;
	bool nDone = true;
	while (nDone) {
		bool nFound1 = true, nFound2 = true;
		while (nFound1 && l < ending) {
			l++;
			if (tabToSort[l] >= pivot) {
				nFound1 = false;
			}
		}
		while (nFound2 && r > begining) {
			r--;
			if (tabToSort[r] <= pivot) {
				nFound2 = false;
			}
		}
		if (l < r) {
			int z = tabToSort[r];
			int x = tabConnected[r];
			tabToSort[r] = tabToSort[l];
			tabConnected[r] = tabConnected[l];
			tabToSort[l] = z;
			tabConnected[l] = x;
		}else {
			nDone = false;
		}
	}
	return r;
}

void sort(int* tabToSort, int* tabConnected, int begining, int ending) {
	if (begining < ending) {
		int r = partition(tabToSort, tabConnected, begining, ending);
		sort(tabToSort, tabConnected, begining, r);
		sort(tabToSort, tabConnected, r+1, ending);
	}
}


void readData(int **files, int n) {
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &(files[ID][i]), &(files[SIZE][i]));
	}
}

void printData(int* files, int begining, int ending, int number0fPendrive) {
	printf("%d:", number0fPendrive);
	if (ending > 0) {
		for (int i = ending-1; i >= begining; i--) {
			printf(" %d", files[i]);
		}
	}
	printf("\n");
}


void createArray(int** array, int n) {
	for (int i = 0; i < NUMBER_OF_DATA; i++) {
		array[i] = new int[n];
	}
}

void deleteArray(int** files) {
	for (int i = 0; i < NUMBER_OF_DATA; i++) {
		delete[] files[i];
	}
}


void copyFiles(int **files, int n, int size, pendrive *pendrives) {
	int ptrOnFile = 0;   //wskaŸnik na aktualnie kopiowany plik
	for (int i = 0; i < NUMBER_OF_PENDRIVES; i++) {
		bool nDone = true;
		pendrives[i].begining = ptrOnFile;
		while (nDone) {
			if (pendrives[i].size + files[SIZE][ptrOnFile] <= size && ptrOnFile < n) {
				pendrives[i].numberOfFiles++;
				pendrives[i].size = pendrives[i].size + files[SIZE][ptrOnFile];
				ptrOnFile++;
				pendrives[i].ending = ptrOnFile;
			}else {
				nDone = false;
			}
		}
	}
}


int main() {
	int n, p;		//n - number of files; p - pendrives' size
	int** files = new int* [NUMBER_OF_DATA];		//files[0] - id, files[1] - size
	pendrive pendrives[NUMBER_OF_PENDRIVES];

	scanf("%d %d", &n, &p);

	createArray(files, n);

	readData(files, n);

	sort(files[SIZE], files[ID], 0, n - 1);
	
	copyFiles(files, n, p, pendrives);

	printf("%d\n", pendrives[0].numberOfFiles + pendrives[1].numberOfFiles);
	for (int i = 0; i < NUMBER_OF_PENDRIVES; i++) {
		sort(files[ID], files[SIZE], pendrives[i].begining, pendrives[i].ending - 1);
		printData(files[ID], pendrives[i].begining, pendrives[i].ending, i+1);
	}
	
	deleteArray(files);
	delete[] files;
	
	return 0;
}