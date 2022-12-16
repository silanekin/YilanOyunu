#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>


// PROJE FAZ2 TESLIMINDE, FAZ1 DE YUKLEDIGIMIZ KODU CLEAN CODE HALINE GETIRIP HATALARIMIZI DUZELTMEYE CALISTIK//


int yilan_alani[80][23]={0};
//struct icindeki elemanlara daha anlamli isimlendirmeler verilmistir
struct icerik {int  satir_yem,sutun_yem;
int yilan_kuyruk_sutun[300];
int yilan_kuyruk_satir[300];};

int j;
int oyun_devam=1;
//burada ilk basta struct isimlendirmesini t olarak yapmisiz kotu olan isimlendirmeyi yilan_kuyruk olarak degistirdik
struct icerik yilan_kuyruk;

// internetten gecirdigimiz kisim
void gotoxy(short x ,short y){
HANDLE hConsoleOutput; 
COORD Cursor_Pos={x-1,y-1};

hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}




// yilanin dolasacagi alanin sinirlari
//burada onceden x1=sag_sinir, x2=sol_sinir y1=yukari_sinir, y2=asagi=sinir olarak belirtilmistir;
void oyun_sinirlari(int sag_sinir, int yukari_sinir, int sol_sinir, int asagi_sinir, int tur){
    int i;
    //sutun sinirlari
    for(i=sag_sinir;i<=sol_sinir;i++){
        yilan_alani[i][yukari_sinir]=tur;
        yilan_alani[i][asagi_sinir]=tur;
    }
    //satir sinirlari
    for(i=yukari_sinir;i<=asagi_sinir;i++){
        yilan_alani[sag_sinir][i]=tur;
        yilan_alani[sol_sinir][i]=tur;
    }
}


//yilanin ekranda dolasacagi kisimlar
// x ,x eksenini belirtmekte y ise y eksenini belirtmektedir konrdinat duzlemindeki noktalar anlatilmistir
void ekran_dolas(){
  int x,y;
    for(x=0;x<80;x++){
        for(y=0;y<23;y++){
            gotoxy(x+1,y+1);
            if(yilan_alani[x][y]==2){
                printf("%c",176);
            }
        }
    }
}
//yemin rastgele atanmasi
int random_yem(){

     srand(time(NULL));
     yilan_kuyruk.satir_yem=4+rand()%65;
     yilan_kuyruk.sutun_yem=4+rand()%15;
}

void main(){
random_yem();
oyun_sinirlari(0,0,79,22,2);
ekran_dolas();
unsigned char tus;
// onceden ax,ay,by,bx olarak anlimsiz bir sekilde belirtilen isimler degistirildi ve daha anlamli hale getirildi
int yilan_kuyruk_arti_x_bolumu=40;
int yilan_kuyruk_arti_y_bolumu=12;
  int yilan_kuyruk_eksi_y_bolumu=0;
  int yilan_kuyruk_eksi_x_bolumu=0;
  int k=0;//kuyruk uzunlugunu artmasi



do{
// sag sol tuslari ANSII dan bakildi
//(yeni)burada sag sol yukari asagi tuslarina basildiginda yilanin kuyrugunun nasýl hareket edecegi belirlenmistir
	if(kbhit()){
        tus=getch();
        if(tus==224){
            tus=getch();
            switch(tus)
            {
                case 72: yilan_kuyruk_eksi_y_bolumu=-1; yilan_kuyruk_eksi_x_bolumu=0;
                break;
                case 80: yilan_kuyruk_eksi_y_bolumu=1; yilan_kuyruk_eksi_x_bolumu=0;
                break;
                case 77: yilan_kuyruk_eksi_x_bolumu=1; yilan_kuyruk_eksi_y_bolumu=0;
                break;
                case 75: yilan_kuyruk_eksi_x_bolumu =-1; yilan_kuyruk_eksi_y_bolumu=0;
            }
        }
	}
//yilanin oyun alanindan cikamamasi icin yapilmistir
	yilan_kuyruk_arti_x_bolumu=yilan_kuyruk_arti_x_bolumu+yilan_kuyruk_eksi_x_bolumu;
	yilan_kuyruk_arti_y_bolumu=yilan_kuyruk_arti_y_bolumu+yilan_kuyruk_eksi_y_bolumu;
    if(yilan_kuyruk_arti_x_bolumu>78){
      printf("YANDINIZ\n");
      oyun_devam=0;}
    if(yilan_kuyruk_arti_x_bolumu<2){
      printf("YANDINIZ\n");
      getch();
      oyun_devam=0;}
    if(yilan_kuyruk_arti_y_bolumu>22){
        printf("YANDINIZ\n");
        getch();
        oyun_devam=0;}
    if(yilan_kuyruk_arti_y_bolumu<2){
        printf("YANDINIZ\n");
        getch();
          oyun_devam=0;}

yilan_kuyruk.yilan_kuyruk_sutun[0]=yilan_kuyruk_arti_x_bolumu;
yilan_kuyruk.yilan_kuyruk_satir[0]=yilan_kuyruk_arti_y_bolumu;

for(j=1;j<=k;j++){
    if(yilan_kuyruk_arti_x_bolumu==yilan_kuyruk.yilan_kuyruk_sutun[j]&& yilan_kuyruk_arti_y_bolumu==yilan_kuyruk.yilan_kuyruk_satir[j]){
        gotoxy(yilan_kuyruk_arti_x_bolumu,yilan_kuyruk_arti_y_bolumu);printf("YANDINIZ");
        getch();
        oyun_devam=0;
    }
}


gotoxy(yilan_kuyruk_arti_x_bolumu,yilan_kuyruk_arti_y_bolumu);printf("*");

for(j=0;j<=k;j++){
    gotoxy(yilan_kuyruk.yilan_kuyruk_sutun[j],yilan_kuyruk.yilan_kuyruk_satir[j]);printf("*");
}
//yemle karsilastiginda almasi ve puan yazilmasi
  if(yilan_kuyruk_arti_x_bolumu==yilan_kuyruk.satir_yem && yilan_kuyruk_arti_y_bolumu==yilan_kuyruk.sutun_yem){
    random_yem();
    k++;
    gotoxy(2,2);printf("Puan=%d",k);
  }

gotoxy(yilan_kuyruk.satir_yem,yilan_kuyruk.sutun_yem); printf("+");

//aninda yem alinmamasi ara verilmesi icin bu fonksiyon ogrenildi
Sleep(60);
gotoxy(yilan_kuyruk_arti_x_bolumu,yilan_kuyruk_arti_y_bolumu); printf(" ");

for(j=0;j<=k;j++){
    gotoxy(yilan_kuyruk.yilan_kuyruk_sutun[j],yilan_kuyruk.yilan_kuyruk_satir[j]);printf(" ");
}


for(j=k;j>0;j--){
    yilan_kuyruk.yilan_kuyruk_sutun[j]=yilan_kuyruk.yilan_kuyruk_sutun[j-1];
    yilan_kuyruk.yilan_kuyruk_satir[j]=yilan_kuyruk.yilan_kuyruk_satir[j-1];
}

} while(oyun_devam==1);



}



