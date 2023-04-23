/*
 * Program1.c
 *
 *  Created on: Feb 19, 2023
 *      Author: kwmeade
 */
#include <stdio.h>
#include <stdlib.h>
float *inputs(char *file){
	float *data = (float*)malloc(sizeof(float) * 12);
	FILE *inputFile = fopen(file, "r");
	if(inputFile == NULL){
	        printf("File not read in");
	}
	for (int i = 0; i < 12; i++){
		fscanf(inputFile, "%f", &data[i]);
	}
	return data;
}

const char *monthList[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
void monthlySales(float *sales){
	for(int i = 0; i < 12; i++){
		printf("%s $%.2f\n", monthList[i], sales[i]);
	}
}

void salesSummary(float *sales) {
	int minM = 0;
	int maxM = 0;
	float total;
	float min = sales[0];
	float max = sales[0];
	for (int i = 0; i < 12; i++){
		if (sales[i] < min) {
			minM = i;
			min = sales[i];
		}
		if (sales[i] > max) {
			maxM = i;
			max = sales[i];
		}
		total += sales[i];
	}
	float average = total / 12;
	printf("Min: $%.2f %s\n", min, monthList[minM]);
	printf("Max: $%.2f %s\n", max, monthList[maxM]);
	printf("Average: $%.2f\n", average);
}

void movingAverage(float *sales) {
	float movingAvg[7];
	for (int i = 0; i <= 6; i++) {
		float sum = 0;
		for (int j = i; j < i+6; j++) {
			sum += sales[j];
		}
		movingAvg[i] = sum / 6;
	}
	for (int i = 0; i <= 6; i++){
		printf("%s - %s : $%.2f\n", monthList[i], monthList[i + 5], movingAvg[i]);
	}
}

void sortedReport(float *sales){
	int index[12] = {0,1,2,3,4,5,6,7,8,9,10,11,};
	for (int i = 0; i < 12; i++){
		for (int j = i + 1; j < 12; j++){
			if (sales[index[i]] < sales[index[j]]){
				float temp = index[j];
				index[j] = index[i];
				index[i] = temp;
			}
		}
	}
	for (int i = 0; i < 12; i++){
		printf("%s $%.2f\n", monthList[index[i]], sales[index[i]]);
	}
}

int main(){
	float *salesList = inputs("inputs.txt");
	printf("Monthly sales report for 2022: \n");
	monthlySales(salesList);
	printf("\nSales summary: \n");
	salesSummary(salesList);
	printf("\nSix-Month moving average report:\n");
	movingAverage(salesList);
	printf("\nSales Report (Highest to Lowest)\n");
	sortedReport(salesList);
}
