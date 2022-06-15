#include "apelib.h"

int main(int argc, char *argv[])
{
  IMG out;
  int i, j, k;
  int r_value, g_value, b_value;
  int x_size, y_size;

  //scanf()関数を適切に設定する
  printf("画像の縦サイズ：");
  scanf("%d",&x_size);
  printf("画像の横サイズ：");
  scanf("%d",&y_size);
  printf("Rの輝度値[0~255]：");
  scanf("%d",&r_value);
  printf("Gの輝度値[0~255]：");
  scanf("%d",&g_value);
  printf("Bの輝度値[0~255]：");
  scanf("%d",&b_value);
  
  out.row = x_size; // 画像の縦サイズを指定
  out.col = y_size; // 画像の横サイズを指定
  out.bas = 3;
  out.type = 0;

  MemImage(&out);
  
  // 出力画像用の三次元配列に適切にRGB値を代入しよう。色チャンネルには必ず赤，緑，青の順番で輝度値を代入すること。
  for(k = 0; k < out.bas; k++){
    for(i = 0; i < out.row; i++){
      for(j = 0; j < out.col; j++){
        if(k==0) out.data[k][i][j] = r_value; 
        else if(k==1) out.data[k][i][j] = g_value;
        else out.data[k][i][j] = b_value;
      }
    }
  }

  WriteImage(&out,argv[1]); //引数を正しく指定しよう。
  return 0;
}
