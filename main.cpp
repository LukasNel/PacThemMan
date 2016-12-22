#include <iostream>
#include "ConsoleFunctions.h"
#define KD(vk)(GetAsyncKeyState(vk) & 0x8000)
#define SG(cx,tx) ((tx > cx) ? cx+1 : (tx < cx) ? cx-1 : cx)
using namespace std;
int keyboardcommand(){
    if(KD(VK_UP))return 1;
    if(KD(VK_DOWN))return 2;
    if(KD(VK_RIGHT))return 3;
    if(KD(VK_LEFT))return 4;
    if(KD(VK_ESCAPE))return 5;
    if(KD(VK_LSHIFT))return 6;
    return 0;
}
int main()
{
    int px=1,py=1,gx=10,gy=10,opx=px,opy=py,ogx=gx,ogy=gy,score=0,key=0,lives = 4,btime = 0,bx=px,by=py,sx = px, sy = py,totalpips = 0,steps = 0,totalbaits = 0;
    char old_char = ' ';
       startgame:
    char world[27][27] =
    {
        {"xxxxxxxxxxxxxxxxxxxxxxxxxx"},
        {"x........................x"},
        {"x........................x"},
        {"xxxxxxx..................x"},
        {"x.....x..................x"},
        {"x.....x..................x"},
        {"x.....x..................x"},
        {"x.....xx.................x"},
        {"x........................x"},
        {"xxxxxxx..................x"},
        {"x.....x..................x"},
        {"x.....x..................x"},
        {"x.....x..................x"},
        {"x........................x"},
        {"xxxxxxx..................x"},
        {"x.....x..................x"},
        {"x.....x..................x"},
        {"x.....x..................x"},
        {"x.....xx.................x"},
        {"x........................x"},
        {"x........................x"},
        {"x........................x"},
        {"x........................x"},
        {"x........................x"},
        {"x........................x"},
        {"xxxxxxxxxxxxxxxxxxxxxxxxxx"}
    };
    string outStr;

        px=1,py=1,gx=10,gy=10,opx=px,opy=py,ogx=gx,ogy=gy,score=0,key=0,lives = 4,btime = 0,bx=px,by=py,sx = px, sy = py,totalpips = 0,steps = 0,totalbaits = 0;

        for(int i = 0;i<27;i++){
            for(int j = 0;j<27;j++){
                if(world[i][j] == '.')totalpips++;
            }
        }
    while(true){

        if(key==5)break;

        px +=(key==3)? 1 : (key==4) ? -1 : 0;
        py +=(key==2)? 1 : (key==1) ? -1 : 0;
        steps++;
        if(world[py][px] == 'x'){
            px=opx;
            py=opy;
            steps--;
        }else if(world[py][px] == '.'){
            world[py][px] = ' ';
            score++;
            totalpips--;
        }

        if(key == 6 && score-10 > 0 && !btime){
            score -= 10;
            btime = 10;
            bx = px;
            by = py;
            old_char = world[by][bx];
            totalbaits++;
        }
        if(btime){
            sx = bx;
            sy = by;
            if(btime == 1)
                world[by][bx] = old_char;
            else world[by][bx] = 'b';
            btime--;
        }else{
            sx = px;
            sy = py;
        }

        gx=SG(gx,sx);
        if(world[gy][gx] == 'x'){
            gx=ogx;
        }
        gy=SG(gy,sy);
        if(world[gy][gx] == 'x'){
           gy=ogy;
        }
        if(gx == px && gy == py){
            lives--;

            do{
                gx = rand()%24;
                gy = rand()%24;
            }while((gx == px && gy == py) || world[gx][gy] == 'x');
        }

        ClearScreen();
        for(int i = 0;i<26;i++){
            outStr = world[i];
            if(gy == i)outStr[gx] = 'G';
            if(py == i)outStr[px] = 'P';
            cout << outStr << endl;
        }
        opx=px;
        opy=py;
        ogx=gx;
        ogy=gy;
        cout << "Score: " << score << endl;
        cout << "Lives: " << lives << endl;
        cout << "Total Pips Left: " << totalpips << endl;
        if(btime)cout << "Life Of Bait: " << btime << endl;
        Sleep(100);
        if(totalpips == 0){
                cout << "YOU WON!" << endl;
                cout << "Score: " << score << endl;
                cout << "Lives Left: " << lives << endl;
                cout << "Steps Taken: " << steps << endl;
                cout << "Total Baits Used: " << totalbaits << endl;
                Sleep(1000);
                break;
            }
        if(lives == 0){
                cout << "Score: " << score << endl;
                cout << "Lives Left: " << lives << endl;
                cout << "Steps Taken: " << steps << endl;
                cout << "Total Baits Used: " << totalbaits << endl;
                cout << "You Lose!" << endl;
                Sleep(1000);
                break;
        }
        cout << "nextturn" << endl;
        while(!(key=keyboardcommand()));
    }
    while(!(key=keyboardcommand()));
    if(key != 5)goto startgame;

}
