#include <stdio.h>
#include <stdlib.h>
void Init(int osero[8][8]){
    for(int j=0;j<8;j++){
        for(int k=0;k<8;k++){
            if(j==3&&k==3||j==4&&k==4)
                osero[j][k]=1;
            else if(j==3&&k==4||j==4&&k==3)
                osero[j][k]=2;
            else
                osero[j][k]=0;
                
        }
    }
}

void display(int osero[8][8]){
    system("cls");
    for(int i=0;i<8;i++){
        printf(" %d",i);
    }
    printf("\n");
    for(int j=0;j<8;j++){
        printf("%d",j);
        for(int k=0;k<8;k++){
            
            if(osero[j][k]==0)
                printf(". ");
            else if(osero[j][k]==1)
                printf("● ");
            
            else if(osero[j][k]==2)
                printf("○ ");
        }
        printf("\n");
    }
    printf("\n");
}

int check_putable(int player,int a_1,int b_1,int osero[8][8]){
    int turn=0;
    
    if(osero[a_1][b_1]!=0)
        return turn;
    
    for(int c_1=-1;c_1<2;c_1++){
        for(int d_1=-1;d_1<2;d_1++){
            if(a_1+c_1>7||b_1+d_1>7||a_1+c_1<0||b_1+d_1<0||osero[a_1+c_1][b_1+d_1]!=3-player){
                continue;
            }
            for(int e_1=1;e_1<8;e_1++){
                if(a_1+c_1*e_1>7||b_1+d_1*e_1>7||a_1+c_1*e_1<0||b_1+d_1*e_1<0)
                   break;
                else if(osero[a_1+c_1*e_1][b_1+d_1*e_1]==0)
                    break;
                else if(osero[a_1+c_1*e_1][b_1+d_1*e_1]==player){
                    turn=1;
                    break;
                }
            }
        }
    }
    return turn;
}

void check_turn(int player,int x,int y,int osero[8][8]){
    int n=0;
    
    for(int j=-1;j<2;j++){
        for(int k=-1;k<2;k++){
            if((x+j>7||y+k>7||x+j<0||y+k<0)||osero[x+j][y+k]!=3-player){
                continue;
            }
            
            for(n=1;n<8;n++){
                if(x+j*n>7||y+k*n>7||x+j*n<0||y+k*n<0)
                    break;
                if(osero[x+j*n][y+k*n]!=3-player){
                    break;
                }
            }
            if(x+j*n>7||y+k*n>7||x+j*n<0||y+k*n<0) continue;
            if(osero[x+j*n][y+k*n]==player){
                for(int m=1;m<n;m++){
                    osero[x+j*m][y+k*m]=player;
                }
            }
        }
    }
}

void judge(int count_1,int count_2,int osero[8][8]){
    for(int r=0;r<8;r++){
        for(int s=0;s<8;s++){
            if(osero[r][s]==1)
                count_1++;
            else if(osero[r][s]==2)
                count_2++;
        }
    }
    
    if(count_1<count_2)
        printf("CPUの勝ち\n");
    else if(count_1>count_2)
        printf("プレーヤーの勝ち\n");
    else
        printf("引き分け\n");
    
    printf("CPU：%d, プレーヤー：%d\n",count_2,count_1);
    
}



int main(void){
    
    int osero[8][8];
    int i=0,posx,posy,player=0;
    int n=0,flag=0;
    int count_1=0,count_2=0;
    int again=0,turn=0,x=0,y=0;
    int j, k;
    system("chcp 65001");
    Init(osero);
    
    for(i=0;i<61;i++){
        player=i%2+1;
        flag = 0;
        turn = 0;
        x=0;
        y=0;
        
        display(osero);
        
        for(j=0;j<8;j++){
            for(k=0;k<8;k++){
                //printf("%d\n",check_putable(player,j,k,osero));
                if(check_putable(player,j,k,osero)) break;
            }
            if(k != 8) break;
        }
        if(j == 8) continue;
        
        
        /*cpu*/
        if(player==2){
            printf("CPU(黒)の番です。入力してください。\n");
            for(j=0;j<8;j++){
                for(k=0;k<8;k++){
                    if(check_putable(player,j,k,osero)) break;
                }
                if(k != 8) break;
            }
            x=j;
            y=k;
            osero[x][y]=2;
            printf("%d\n",x);
            printf("%d\n",y);
        }
        
        if(player==1){
            do{
                printf("あなた(白)の番です。入力してください。\n");
                printf("横列："); 
                scanf("%d",&x);
                printf("縦列："); 
                scanf("%d",&y);
            }while(!check_putable(player,x,y,osero));
            osero[x][y]=player;
        }
        
        check_turn(player,x,y,osero);
      
    }
    
    display(osero);
    
    judge(count_1,count_2,osero);
    
    return 0;
}
