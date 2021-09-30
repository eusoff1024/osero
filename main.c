//
//  main.c
//  osero
//
//  Created by Syed Mohd Eusoff on 2018/08/27.
//  Copyright © 2018年 Syed Mohd Eusoff. All rights reserved.
//

#include <stdio.h>

//マス目の数　square×square
#define square 4

//空きの時
#define MAX 100

//白
#define WHITE 50

//黒
#define BLACK 60

//盤
int board[square+1][square+1];


//画面に出力
void print_board(void){
    int i,j;
    
    for(i=0;i<square+1;i++){
        
        for(j=0;j<square+1;j++){
            if(board[i][j]==MAX){
                printf("   ");
            }else if(board[i][j]==WHITE){
                printf("⚪️ ");
            }else if(board[i][j]==BLACK){
                printf("⚫️ ");
            }else{
                printf(" %d ",board[i][j]);
            }
            
            printf("|");
        }
        
        printf("\n");
        
        for(j=0;j<square*1.5;j++){
            printf("ーー");
        }
        printf("\n");
        
    }
}

//盤を初期化
void init_board(void){
    int i,j;
    int count=0;
    
    //0行目
    for(i=0;i<square+1;i++){
        board[0][i]=count++;
    }
    
    count=1;
    
    //0列目
    for(i=1;i<square+1;i++){
        board[i][0]=count++;
    }
    
    //残り
    for(i=1;i<square+1;i++){
        for(j=1;j<square+1;j++){
            board[i][j]=MAX;
        }
    }
    
    //中央に白黒２つずつ置く
    board[square/2][square/2]=WHITE;
    board[square/2][square/2+1]=BLACK;
    board[square/2+1][square/2]=BLACK;
    board[square/2+1][square/2+1]=WHITE;
    
    //出力
    print_board();
    
}


//右側と挟んでいる箇所ひっくり返す
void reverse_right(int row,int column,int count,int color){
    int i;

    for(i=column;i<column+count;i++){
        board[row][i]=color;
    }
}


//左側と挟んでいる箇所ひっくり返す
void reverse_left(int row,int column,int count,int color){
    int i;

    for(i=column-count;i<=column;i++){
        board[row][i]=color;
    }
}


//下側で挟んでいる箇所ひっくり返す
void reverse_down(int row,int column,int count,int color){
    int i;

    for(i=row;i<row+count;i++){
        board[i][column]=color;
    }
}


//上側と挟んでいる箇所ひっくり返す
void reverse_up(int row,int column,int count,int color){
    int i;

    for(i=row;i>row-count;i--){
        board[i][column]=color;
    }
}


//右下と挟んでいる箇所ひっくり返す
void reverse_bottom_right_diagonal(int row,int column,int count,int color){
    
    for(;count>=0;count--){
        board[row+count][column+count]=color;
    }
}


//左上と挟んでいる箇所ひっくり返す
void reverse_top_left_diagonal(int row,int column,int count,int color){
    
    for(;count>=0;count--){
        board[row-count][column-count]=color;
    }
}

//右上と挟んでいる箇所ひっくり返す
void reverse_top_right_diagonal(int row,int column,int count,int color){
    
    for(;count>=0;count--){
        board[row-count][column+count]=color;
    }
}


//左下と挟んでいる箇所ひっくり返す
void reverse_bottom_left_diagonal(int row,int column,int count,int color){
    
    for(;count>=0;count--){
        board[row+count][column-count]=color;
    }
}

//同じ色で挟めているのかの判定(挟めている→1,挟めていない→0 を返す)
int check(int row,int column,int color){
    int x=0;          //リバースした場合1にする
    //右側と挟んでいるか
    int count=1;        //何個挟んでいるか
    while(column+count<=square){                         //square以下で同じ色にぶつかるまでループ
        if(board[row][column+count]==MAX||board[row][column+count]==color){             ////空白又は同じ色だった場合ループ脱出
            break;
        }
        count++;
    }
    
    if(board[row][column+count]!=MAX&&count>1&&column+count<=square){                  //挟めている場合
        reverse_right(row,column,count,color);            //ひっくり返す
        x=1;
    }
    
    //左側と挟んでいるか
    count=1;            //リセット
    
    while(column-count>0){              //1以上で同じ色にぶつかるまでループ
        if(board[row][column-count]==MAX||board[row][column-count]==color){             //空白又は同じ色だった場合ループ脱出
            break;
        }
        count++;
    }
    
    if(board[row][column-count]!=MAX&&count>1&&column-count>0){
        reverse_left(row,column,count,color);
        x=1;
    }
    
    //下側と挟んでいるか
    count=1;        //リセット
    
    while(row+count<=square){
        if(board[row+count][column]==MAX||board[row+count][column]==color){
            break;
        }
        count++;
    }
    
    if(board[row+count][column]!=MAX&&count>1&&row+count<=square){
        reverse_down(row,column,count,color);
        x=1;
    }
    
    //上側と挟んでいるか
    count=1;        //リセット
    
    while(row-count>0){
        if(board[row-count][column]==MAX||board[row-count][column]==color){
            break;
        }
        count++;
    }
    
    if(board[row-count][column]!=MAX&&count>1&&row-count>0){
        reverse_up(row,column,count,color);
        x=1;
    }
    
    //斜め
    //右下と挟んでいるか
    count=1;            //リセット
    while(column+count<=square&&row+count<=square){
        if(board[row+count][column+count]==MAX||board[row+count][column+count]==color){
            break;
        }
        count++;
    }
    
    if(board[row+count][column+count]!=MAX&&board[row+count][column+count]==color&&count>1&&column+count<=square&&row+count<=square){
        reverse_bottom_right_diagonal(row,column,count,color);
        x=1;
    }
    
    //左上と挟んでいるか
    count=1;        //リセット
    while(column-count>0&&row-count>0){
        if(board[row-count][column-count]==MAX||board[row-count][column-count]==color){
            break;
        }
        count++;
    }
    
    if(board[row-count][column-count]!=MAX&&board[row-count][column-count]==color&&count>1&&column-count>0&&row-count>0){
        reverse_top_left_diagonal(row,column,count,color);
        x=1;
    }
    
    //右上と挟んでいるか
    count=1;        //リセット
    while(column+count<=square&&row-count>0){
        if(board[row-count][column+count]==MAX||board[row-count][column+count]==color){
            break;
        }
        count++;
    }
    
    if(board[row-count][column+count]!=MAX&&board[row-count][column+count]==color&&count>1&&column+count<=square&&row-count>0){
        reverse_top_right_diagonal(row,column,count,color);
        x=1;
    }
    
    //左下と挟んでいるか
    count=1;        //リセット
    while(row+count<=square&&column-count>0){
        if(board[row+count][column-count]==MAX||board[row+count][column-count]==color){
            break;
        }
        count++;
    }
    
    if(board[row+count][column-count]!=MAX&&board[row+count][column-count]==color&&count>1&&row+count<=square&&column-count>0){
        reverse_bottom_left_diagonal(row,column,count,color);
        x=1;
    }
    
    
    
    return x;
}

//打てる場所があるかないかの判定
int have_a_place(int row,int column, int color){
        //右側と挟んでいるか
        int count=1;        //何個挟んでいるか
        while(column+count<=square){                         //square以下で同じ色にぶつかるまでループ
            if(board[row][column+count]==MAX||board[row][column+count]==color){             ////空白又は同じ色だった場合ループ脱出
                break;
            }
            count++;
        }
        
        if(board[row][column+count]!=MAX&&count>1&&column+count<=square){                  //挟めている場合
            return 1;
        }
        
        //左側と挟んでいるか
        count=1;            //リセット
        
        while(column-count>0){              //1以上で同じ色にぶつかるまでループ
            if(board[row][column-count]==MAX||board[row][column-count]==color){             //空白又は同じ色だった場合ループ脱出
                break;
            }
            count++;
        }
        
        if(board[row][column-count]!=MAX&&count>1&&column-count>0){
           return 1;
        }
        
        //下側と挟んでいるか
        count=1;        //リセット
        
        while(row+count<=square){
            if(board[row+count][column]==MAX||board[row+count][column]==color){
                break;
            }
            count++;
        }
        
        if(board[row+count][column]!=MAX&&count>1&&row+count<=square){
            return 1;
        }
        
        //上側と挟んでいるか
        count=1;        //リセット
        
        while(row-count>0){
            if(board[row-count][column]==MAX||board[row-count][column]==color){
                break;
            }
            count++;
        }
        
        if(board[row-count][column]!=MAX&&count>1&&row-count>0){
            return 1;
        }
        
        //斜め
        //右下と挟んでいるか
        count=1;            //リセット
        while(column+count<=square&&row+count<=square){
            if(board[row+count][column+count]==MAX||board[row+count][column+count]==color){
                break;
            }
            count++;
        }
        
        if(board[row+count][column+count]!=MAX&&board[row+count][column+count]==color&&count>1&&column+count<=square&&row+count<=square){
            return 1;
        }
        
        //左上と挟んでいるか
        count=1;        //リセット
        while(column-count>0&&row-count>0){
            if(board[row-count][column-count]==MAX||board[row-count][column-count]==color){
                break;
            }
            count++;
        }
        
        if(board[row-count][column-count]!=MAX&&board[row-count][column-count]==color&&count>1&&column-count>0&&row-count>0){
            return 1;
        }
        
        //右上と挟んでいるか
        count=1;        //リセット
        while(column+count<=square&&row-count>0){
            if(board[row-count][column+count]==MAX||board[row-count][column+count]==color){
                break;
            }
            count++;
        }
        
        if(board[row-count][column+count]!=MAX&&board[row-count][column+count]==color&&count>1&&column+count<=square&&row-count>0){
            return 1;
        }
        
        //左下と挟んでいるか
        count=1;        //リセット
        while(row+count<=square&&column-count>0){
            if(board[row+count][column-count]==MAX||board[row+count][column-count]==color){
                break;
            }
            count++;
        }
        
        if(board[row+count][column-count]!=MAX&&board[row+count][column-count]==color&&count>1&&row+count<=square&&column-count>0){
            return 1;
        }
        
        
        
        return 0;
    

}

//打てるところがあるかどうか調べる
int check_places(int color){
    int i,j;
    
    for(i=1;i<=square;i++){
        for(j=1;j<=square;j++){
            if(board[i][j]==MAX){
                if(have_a_place(i,j,color)){
                    return 1;
                }
            }
        }
    }
   
    return 0;
}


//打つ
void put(int color){
    int row,column;     //行、列
    
    //どこにも置けない場合交代
    if(!check_places(color)){
        printf("\n\n打てるところがありません。\n\n");
        return ;
    }

    if(color==WHITE){
        printf("\n\n白のターン\n\n");
    }else{
        printf("\n\n黒のターン\n\n");
    }
    
    while(1){
        do{
        
            //マスの指定
            //行
            while(1){
                printf("行：");
                scanf("%d",&row);
        
                if(row>0&&row<=8){
                    break;
                }
                printf("\n\n%d〜%dの行を指定してください。\nもう一度入力してください\n",1,square);
            }
        
            //列
            while(1){
                printf("列：");
                scanf("%d",&column);
                if(column>0&&column<=8){
                    break;
                }
            printf("\n\n%d〜%dの列を指定してください。\nもう一度入力してください\n",1,square);
        }
        
        //空きマスか
        if(board[row][column]==MAX){
            break;
        }
            
        printf("\n\n既に埋まっています。もう一度入力してください\n\n");
            
       }while(1);
        

        //入力したマスが適切な場合終了
        if(check(row,column,color)){
            break;
        }
        
        printf("そのマスは不適です。もう一度入力してください\n\n");
    }
    
}

//勝者の判定
void winner(){
    int black=0,white=0;
    int i,j;
    
    for(i=1;i<square+1;i++){
        for(j=1;j<square+1;j++){
            if(board[i][j]==BLACK){
                black++;
            }
            else{
                white++;
            }
        }
    }
    
    if(black>white){
        printf("\n\n黒の勝ち！\n\n");
    }else if(white>black){
        printf("\n\n白の勝ち！\n\n");
    }else{
        printf("\n\n引き分け...\n\n");
    }
}

int main(void){
    int remain=square*square-4;      //残りのマスの数
    int color=BLACK;                   //黒からスタート
    
    //初期化
    init_board();
 
    
    while(remain>0){
        put(color);
        
        if(color==BLACK){           //色を変える
            color=WHITE;
        }else{
            color=BLACK;
        }
        print_board();              //出力
        remain--;
    }
    
    winner();
    
    return 1;
    
}
