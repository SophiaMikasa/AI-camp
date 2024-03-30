#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "Stack.h"
#include "sort.h"
#include "task.h"

typedef void (*SortFunc)(int arr[], int low, int high);

int main() {
	char aglchoice,appchoice;
	while (1) {
		//int nums[10] = { 0,1,2,2,1,0,0,1,1,2 };
		SortFunc Sort = NULL;
		//int nums[MAXSIZE] = { 129,315,232,416,758,428,649,904,142,407 };
		appchoice = AppMenu();
		if (appchoice == '3'||appchoice == '5'|| appchoice == '6') {
			if (appchoice == '3')
				Generate_File(DATA_SIZE);
			else if (appchoice == '5')
				sortColors();
			else
				create_and_fine_small();
			while (getchar() != '\n');
			continue;
		}
		aglchoice = AglMenu();

		switch (aglchoice) {
		case '1':
			Sort = InsertSort;
			break;
		case '2':
			Sort = MergeSort;
			break;
		case '3':
			Sort = QuickSort_recursion;
			break;
		case '4':
			Sort = QuickSort_None;
			break;
		case '5':
			Sort = CountSort;
			break;
		case '6':
			Sort = RadixCountSort;
			break;
		case '7':
			Sort = Bubble_Sort;
			break;
		default:
			Sort = NULL;
			break;
		}
		switch (appchoice) {
		case '1':
			Test_one(Sort);
			break;
		case '2':
			Test_two(Sort);
			break;
		case '4':
			Reed_File(Sort, DATA_SIZE);
			break;
		}
		while (getchar() != '\n');
		system("pause");
	}

	return 0;
}