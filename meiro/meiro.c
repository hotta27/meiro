#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<GL/glut.h>

struct player
{
	int dna[20], object[2], xobject[2];//{y,x}
	int unroad;
}p[8];
int algo();

int meiro[10][10] = { {1,1,1,1,1,1,1,1,1,1},{1,0,0,0,1,0,0,0,0,1} ,{1,0,1,1,1,0,0,0,0,1},{1,0,0,0,1,0,0,0,0,1},{1,1,1,1,1,0,0,0,0,1} };
int goal[2] = { 7,3 }, start[2] = {7,5};//{y,x}
int N = 8, gene = 20, nn = 0;
int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));
	FILE* f,*d;
	char b;
	f = fopen("01.txt", "r");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fscanf(f, "%d%c", &meiro[i][j], &b);
		}
	}
	
	fclose(f);


	if (meiro[goal[0]][goal[1]] == 1 || meiro[start[0]][start[1]] == 1) { printf("error"); return 1; }
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < gene; j+=2) {
			p[i].dna[j] = rand() % 4;
			p[i].dna[j+1] = rand() % 10;
			
			//printf("%d,%d:%d \n", i, j, p[i].dna[j]);
		}//p[i].dna[0] = 2; p[i].dna[1] = 2; 
	}
	printf("%d %d", p[0].object[0], p[0].object[1]);
	int c = 2,n=0;
	while (c > 0) {
		//移動
		//リセット
		for (int i = 0; i < N; i++) {
			p[i].object[0] = start[0];
			p[i].object[1] = start[1];
			p[i].unroad = 0;
		}

		//for (int i = 0; i < N; i++) {
		//	for (int j = 0; j < 10; j+=2) {
		//		if (p[i].dna[j] == 0)      p[i].xobject[1] -= p[i].dna[j+1];
		//		else if (p[i].dna[j] == 1) p[i].xobject[1] += p[i].dna[j+1];
		//		else if (p[i].dna[j] == 2) p[i].xobject[0] += p[i].dna[j+1];
		//		else if (p[i].dna[j] == 3) p[i].xobject[0] -= p[i].dna[j+1];

		//		if ((0 < p[i].xobject[0] && p[i].xobject[0] < 10) && (0 < p[i].xobject[1] && p[i].xobject[1] < 10)) {
		//			if (meiro[p[i].xobject[0]][p[i].xobject[1]] == 0) {
		//				p[i].object[0] = p[i].xobject[0]; p[i].object[1] = p[i].xobject[1];
		//			}
		//			//else printf("er\n");
		//		}
		//		//else printf("er\n");
		//	}
		//	printf("dna:%d %d\nobject:%d %d\n", p[i].dna[0], p[i].dna[1], p[i].object[0], p[i].object[1]);
		//}
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < gene; j+=2) {
				switch (p[i].dna[j])
				{
				case 0:
					for (int n = 0; n < p[i].dna[j+1]; n++) {
						p[i].object[0]--;
						if (meiro[p[i].object[0]][p[i].object[1]] == 1){
							p[i].object[0]++;
							p[i].unroad++;
						}
					}
					break;
				case 1:
					for (int n = 0; n < p[i].dna[j + 1]; n++) {
						p[i].object[0]++;
						if (meiro[p[i].object[0]][p[i].object[1]] == 1) {
							p[i].object[0]--; 
							p[i].unroad++;
						}
					}
					break;
				case 2:
					for (int n = 0; n < p[i].dna[j + 1]; n++) {
						p[i].object[1]++;
						if (meiro[p[i].object[0]][p[i].object[1]] == 1) {
							p[i].object[1]--;
							p[i].unroad++;
						}
					}
					break;
				case 3:
					for (int n = 0; n < p[i].dna[j + 1]; n++) {
						p[i].object[1]--;
						if (meiro[p[i].object[0]][p[i].object[1]] == 1) {
							p[i].object[1]++;
							p[i].unroad++;
						}
					}
					break;
				}
			}p[i].unroad /= 10;
			//printf("un:%d\n", p[i].unroad);
		}

		c=algo();
		printf("c:%d\n", c);		
		n++;printf("n:%d\n\n", n);
		//if (n > 10000)break;
	}
	
	return 0;
}
int algo() {
	//評価
	//       N       N  gene
	int gosa[8], box[8][20];
	for (int i = 0; i < N; i++) {
		gosa[i] = abs(p[i].object[0] - goal[0]) + abs(p[i].object[1] - goal[1]);//+p[i].unroad;
		printf("gosa:%d\n", gosa[i]);
	}
	//評価の高い4つ
	//int min = gosa[0],max=gosa[0], n[4] = { 0,0 ,0,0 };
	//for (int i = 1; i < N; i++) {
	//		if (min > gosa[i]) { min = gosa[i]; n[0] = i; }
	//		if (max < gosa[i]) { max = gosa[i]; }
	//	}
	//for (int j = 1; j < N-(N-4); j++) {
	//	//printf("r=%d\n", r);
	//	for (int i = 1; i < N; i++) {//
	//		if (max>gosa[i]&&min<gosa[i]) { min = gosa[i]; n[j] = i; }
	//		printf("min%d max%d\n\n",min, max);
	//		/*if (j == 0) { if (x > gosa[i]) { x = gosa[i]; n[j] = i; } }
	//		else{ if (gosa[n[j - 1]] < gosa[i] && x>=gosa[i]) { x = gosa[i]; n[j] = i; } }*/
	//		//printf("%d:r= %d\n",i, r);
	//	}
	//	max = min; 
	//	min = gosa[0];
	//}printf("n= %d %d %d %d",n[0],n[1],n[2],n[3]);
	
	//トーナメント方式
	int n[4] = { NULL,NULL,NULL,NULL };
	for (int i = 0; i < N; i += 2) {
		if (gosa[i] < gosa[i + 1])n[i / 2] = i;
		else n[i / 2] = i + 1;
	}
	//printf("n= %d %d %d %d", n[0], n[1], n[2], n[3]);
	int h;
	for (h = 0; h < N; h++) {
		int a = rand() % 100;
		if (a < 60) {//交叉
			printf("kousa\n");
			int r2 = 0;
			for (int j = 0; j < gene; j += 2) {
				int r1 = rand() % 4; if (r2 < 4)r2++; else r2 = 0;
				box[h][j] = p[n[r1]].dna[j];
				box[h][j + 1] = p[n[r2]].dna[j + 1];
				//printf("%d %d ", r1, r2);
			}
			//printf("\n");
		}
		else if (a < 90) {//copy
			printf("copy\n");
			for (int j = 0; j < gene; j += 2) {
				int r = rand() % 4;
				box[h][j] = p[n[r]].dna[j];
				box[h][j + 1] = p[n[r]].dna[j + 1];
			}
		}
		else {//突然変異
			printf("totuzenn\n");
			for (int j = 0; j < gene; j += 2) {
				box[h][j] = rand() % 4;
				box[h][j + 1] = rand() % 10;
			}
		}
	}

	int min = gosa[0];
	for (int i = 0; i < N; i++) {
		if (min > gosa[i]) { min = gosa[i]; nn = i; }		
	}

	FILE* fp = NULL,*save = NULL;
	fopen_s(&fp, "dna.txt", "w");
	printf("%d\n", nn);
	fprintf(fp,"(y,x)\nstart:%d,%d goal:%d,%d\n", start[0],start[1],goal[0],goal[1]);
	for (int i = 0; i < gene; i++) {
		printf("%d,", p[nn].dna[i]);
		fprintf(fp, "%d,", p[nn].dna[i]);
		
		if (i % 2 == 1)printf("\n");
	}
	printf("\n%d %d\n", p[nn].object[0], p[nn].object[1]);
	fclose(fp);
	

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < gene; j += 2) {
			p[i].dna[j] = box[i][j];
			p[i].dna[j + 1] = box[i][j + 1];
			//printf("%d %d \n", p[i].dna[j], p[i].dna[j+1]);
		}

	}
	
	
	return min;
}



