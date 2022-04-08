#include<stdio.h>
#include<stdlib.h>
void noOfGoals(float* s, int t1, int t2, int a[6][2]) {
	int i;
	int goal[4] = { 0,0,0,0 };
	for (i = 0; i < 6; i++) {
		if (i < 3) {
			goal[0] += a[i][0];
			goal[i + 1] += a[i][1];
		}
		else if (i < 5) {
			goal[1] += a[i][0];
			goal[i - 1] += a[i][1];
		}
		else {
			goal[2] += a[i][0];
			goal[3] += a[i][1];
		}

	}
	if (goal[t1] < goal[t2]) {
		s[t2] += 0.1;
	}
	else {
		s[t1] += 0.1;
	}
}
void goalDiff(float* s, int t1, int t2, int a[6][2]) {
	int i;
	int goaldif[4] = { 0,0,0,0 };
	for (i = 0; i < 6; i++) {
		if (i < 3) {
			goaldif[0] += a[i][0] - a[i][1];
			goaldif[i + 1] += a[i][1] - a[i][0];
		}
		else if (i < 5) {
			goaldif[1] += a[i][0] - a[i][1];
			goaldif[i - 1] += a[i][1] - a[i][0];
		}
		else {
			goaldif[2] += a[i][0] - a[i][1];
			goaldif[3] += a[i][1] - a[i][0];
		}
		
	}
	if (goaldif[t1] > goaldif[t2]) {
		s[t1] += 0.1;
	}
	else if (goaldif[t1] < goaldif[t2]) {
		s[t2] += 0.1;
	}
	else {
		noOfGoals( s, t1, t2, a);
	}
}

int tieBreaker(float* s, int a[6][2]) {
	int i,j;
	for (i = 0; i < 3; i++) {
		for (j = i + 1; j < 4; j++) {
			if (s[i] == s[j]) {
				goalDiff(s, i, j, a);
				return i;
			}
		}
	}
	return -1;
}

int* getSortedTeams(int a[6][2]) {
	int i;
	float scores[4] = { 0,0,0,0 };
	for (i = 0; i < 6; i++) {
		if (a[i][0] > a[i][1]) {
			if (i < 3) {
				scores[0] += 3;
			}
			else if (i < 5) {
				scores[1] += 3;
			}
			else {
				scores[2] += 3;
			}
		}
		else if (a[i][0] == a[i][1]) {
			if (i < 3) {
				scores[0] += 1;
				scores[i + 1] += 1;
			}
			else if (i < 5) {
				scores[1] += 1;
				scores[i - 1] += 1;
			}
			else {
				scores[2] += 1;
				scores[3] += 1;
			}
		}
		else {
			if (i < 3) {
				scores[i+1] += 3;
			}
			else if (i < 5) {
				scores[i-1] += 3;
			}
			else {
				scores[3] += 3;
			}
		}
	}
	while(tieBreaker(scores,a)!=-1){}
	int sortedarr[4];
	int j;
	for (i = 0; i < 4; i++) {
		sortedarr[i] = i;
		for (j = 0; j < 4; j++) {
			if (scores[sortedarr[i]] < scores[j]) {
				sortedarr[i] = j;
			}
		}
		scores[sortedarr[i]] = -1;
	}
	/*for (i = 0; i < 4; i++) {
		printf("%f\n", scores[i]);
	}*/
	return sortedarr;
}
void main() {
	/*int scores[6][2] = { {1, 0} ,{2, 0},{3, 2},{2, 2},{3, 0},{0, 0} };*/
	/*int scores[6][2] = { {1, 1} ,{1, 1},{1, 1},{1, 1},{1, 1},{1, 1} };*/
	/*int scores[6][2] = { {1, 0} ,{2, 2},{0, 2},{2, 0},{1, 2},{1, 0} };*/
	int scores[6][2];
	int k;
	char inp[20];
	for (k = 0; k < 6; k++) {
		int temp1;
		gets(inp);

		temp1 = atoi(inp);
		scores[k][0] = temp1 / 10;
		scores[k][1] = temp1 % 10;
	}
	char teams[4] = { 'A','B','C','D' };
	int* arr;
	arr = getSortedTeams(scores);
	int j;
	for (j = 0; j < 4; j++) {
		printf("%c", teams[arr[j]]);
	}
}