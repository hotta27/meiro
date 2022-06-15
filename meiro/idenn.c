#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "apelib.h"

struct player
{
	int dna[10], object[2], xobject[2];//{x,y}
}p[5];
int algo();

int meiro[10][10] = { {1,1,1,1,1,1,1,1,1,1},{1,0,0,0,1,0,0,0,0,1} ,{1,0,1,1,1,0,0,0,0,1},{1,0,0,0,1,0,0,0,0,1},{1,1,1,1,1,0,0,0,0,1} };
int goal[2] = { 1,5 };
int N = 5;

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));
	IMG in, out;

	int i, j, k;
	ReadImage(&in, argv[1]);
	out.row = in.row;
	out.col = in.col;
	out.bas = in.bas;
	out.type = in.type;
	MemImage(&out);
	for (k = 0; k < out.bas; k++) {
		for (i = 0; i < out.row; i++) {
			for (j = 0; j < out.col; j++) {
				//out.data[0][i][j] = 255-(meiro[i][j]*255);
				out.data[k][i][j] = in.data[k][i][j];
				//printf("%d ", meiro[i][j]);
			}
			printf("\n");
		}
	}
	
	WriteImage(&out, argv[2]); //ˆø”‚ð³‚µ‚­Žw’è‚µ‚æ‚¤B
	
	for (int i = 0; i < N; i++) {
		p[i].object[0] = p[i].xobject[0] = 5;
		p[i].object[1] = p[i].xobject[1] = 5;
		for (int j = 0; j < 10; j++) {
			p[i].dna[j] = rand() % 4;
			//printf("%d,%d:%d \n", i, j, p[i].dna[j]);
		}
	}

	int c = 2,n=0;
	while (c > 1) {
		//ˆÚ“®

		for (int i = 0; i < N; i++) {
			p[i].object[0] = p[i].xobject[0] = 5;
			p[i].object[1] = p[i].xobject[1] = 5;
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < 10; j+=2) {
				if (p[i].dna[j] == 0)      p[i].xobject[1] -= p[i].dna[j+1];
				else if (p[i].dna[j] == 1) p[i].xobject[1] += p[i].dna[j+1];
				else if (p[i].dna[j] == 2) p[i].xobject[0] += p[i].dna[j+1];
				else if (p[i].dna[j] == 3) p[i].xobject[0] -= p[i].dna[j+1];

				if ((0 < p[i].xobject[0] && p[i].xobject[0] < 10) && (0 < p[i].xobject[1] && p[i].xobject[1] < 10)) {
					if (meiro[p[i].xobject[0]][p[i].xobject[1]] == 0) {
						p[i].object[0] = p[i].xobject[0]; p[i].object[1] = p[i].xobject[1];
					}
					//else printf("er\n");
				}
				//else printf("er\n");
			}
			printf("dna:%d %d\nobject:%d %d\n", p[i].dna[0], p[i].dna[1], p[i].object[0], p[i].object[1]);
		}

		c=algo();
		printf("c:%d\n", c);
		n++;
		if (n > 2)break;
	}
	printf("%d\n\n", n);

	
	return 0;
}
int algo() {
	//•]‰¿
	int gosa[5], box[5][10];
	for (int i = 0; i < N; i++) {
		gosa[i] = abs(p[i].object[0] - goal[0]) + abs(p[i].object[1] - goal[1]);
		printf("gosa:%d\n", gosa[i]);
	}
	int h;
	for (h = 0; h < N; h++) {
		int x, n[2] = { 0,0 };
		for (int j = 0; j < 2; j++) {
			int r = rand() % N;
			x = gosa[r];
			//printf("r=%d\n", r);
			for (int i = 0; i < 3; i++) {
				int r = rand() % N;
				if (x < gosa[r]) { x = gosa[r]; n[j] = r; }
				//printf("%d:r= %d\n",i, r);
			}			
		}printf("n= %d %d",n[0],n[1]);
		int a = rand() % 100;
		if (a < 60) {//Œð³
			printf("kousa\n");
			for (int j = 0; j < 10; j+=2) {
				box[h][j] = p[n[0]].dna[j];
				box[h][j+1] = p[n[1]].dna[j+1];
			}
		}
		else if (a < 90) {//copy
			printf("copy\n");
			for (int j = 0; j < 10; j += 2) {
				box[h][j] = p[n[0]].dna[j];
				box[h][j+1] = p[n[0]].dna[j+1];
			}
		}
		else {//“Ë‘R•ÏˆÙ
			printf("totuzenn\n");
			for (int j = 0; j < 10; j += 2) {
				box[h][j] = rand() % 4;
				box[h][j + 1] = rand() % 4;
			}
		}
	}
	int x = gosa[0], n = 0;
	for (int i = 0; i < N; i++) {
		if (x < gosa[i]) { x = gosa[i]; n = i; }
		for (int j = 0; j < 10; j += 2) {
			p[i].dna[j] = box[i][j];
			p[i].dna[j+1] = box[i][j+1];
			printf("%d %d \n", p[i].dna[j], p[i].dna[j+1]);
		}
		
	}
	return gosa[n];
}

