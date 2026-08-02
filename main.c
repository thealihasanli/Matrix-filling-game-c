#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_PLAYERS 100
#define MAX_RANDOM 100
#define MAX_DOSYA 15   

typedef struct {
    char name[50];
    int score;
} Player;

void automatically(); // Rastgele Matris Otomatik Doldur
void automatically2(); // Dosya Matris Otomatik Doldur
void drawBoard(int matris[][MAX_DOSYA], int N); // Dosya Matris Icin fonksiyon
void readFromFile(int matris[][MAX_DOSYA], char *fileName); // Dosya Matris Icin fonksiyon
void fill(int matris[][MAX_DOSYA], int previous_matris[][MAX_DOSYA], int *score); // Dosya Matris Icin fonksiyon
void fillOut(int matris[][MAX_DOSYA], int N); // // Dosya Matris Icin Otomatik Doldurma için fonksiyon
void undo(int matris[][MAX_DOSYA], int previous_matris[][MAX_DOSYA], int *score); // Dosya Matris Icin fonksiyon
int gameOver(const int matris[][MAX_DOSYA], int N); // Dosya Matris Icin fonksiyon
void addPlayer(Player players[], int *playerCount, char *name, int score); // Dosya Matris Icin fonksiyon

int getPreviousScore(Player players[], int playerCount, char *name); // Oyunda onceki skor gormek icin olan fonksiyon
void displayPlayerScores(Player players[], int playerCount); // Oyuncularin Skor tablosunu icin olan fonksiyon

void create_random_matrix(int matrix[MAX_RANDOM][MAX_RANDOM], int n); // Rastgele Matris Icin fonksiyon
void print_matrix(const int matrix[MAX_RANDOM][MAX_RANDOM], int n); // Rastgele Matris Icin fonksiyon
void copy_matrix(const int src[MAX_RANDOM][MAX_RANDOM], int dest[MAX_RANDOM][MAX_RANDOM], int n); // Rastgele Matris Icin fonksiyon
int is_matrix_filled(const int matrix[MAX_RANDOM][MAX_RANDOM], int n); // Rastgele Matris Icin fonksiyon

void fill_empty_cells(int n, int matrix[MAX_RANDOM][MAX_RANDOM]); // Rastgele Matris Icin fonksiyon
void copy_matrix2(int n, int src[MAX_RANDOM][MAX_RANDOM], int dest[MAX_RANDOM][MAX_RANDOM]); // Rastgele Matris Icin fonksiyon
void create_random_matrix2(int n, int matrix[MAX_RANDOM][MAX_RANDOM]); // Rastgele Matris Icin fonksiyon
void print_matrix2(int n, int matrix[MAX_RANDOM][MAX_RANDOM]); // Rastgele Matris Icin fonksiyon 

int main() {
    int secim;
    char username[50];
    Player players[MAX_PLAYERS];
    int playerCount = 0;
    int secim2;
    int matris[MAX_DOSYA][MAX_DOSYA]={{0}};
    int previous_matris[MAX_DOSYA][MAX_DOSYA] = {{0}};
    int N, score = 0;
    char fileName[20], playerName[50];

    while(1) {
        printf("Ana Menu:\n");
        printf("1.Rastgele Matris Olustur:\n");
        printf("2.Dosyadan Matris Olustur:\n");
        printf("3.Kullanicilarin Skor Tablosu:\n");
        printf("4.Cikis:\n");

        printf("Seciminizi girin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                printf("\nOyun Menu: \n");
                int sub_secim;
                do {
                    printf("1.Manuel Mod'da Oyna:\n");
                    printf("2.Otomatik Mod'da Oyna:\n");
                    printf("3.Ana Menu'ye geri git:\n");

                    printf("Seciminizi girin: ");
                    scanf("%d", &sub_secim);

                    switch (sub_secim) {
                        case 1:
                          
                          printf("Manuel Mod'da Oynuyorsunuz...\n");
                          printf("Kullanici Adinizi Girin: ");
                          scanf("%s", playerName);
                          
                          int matrix[MAX_RANDOM][MAX_RANDOM]; // Mevcut Matris
                          int last_matrix[MAX_RANDOM][MAX_RANDOM]; // En son matrisin durumunu tutar
                          int n; // Matrisin boyutu
                          int score = 0; // Skor
                          
                          printf("Matrisin boyutunu girin: ");
                          scanf("%d", &n);

                          create_random_matrix(matrix, n);
                          copy_matrix(matrix, last_matrix, n); // Ilk matrisi last_matrix olarak kopyala 
                          print_matrix(matrix, n);


                          int choice;
                          int run = 1;
                        
                        while (run) {
                          printf("\n1. Sayiyi hareket ettir\n2. Geri al\n3. Cikis\n4. Yeni Matris Olustur\nLutfen secim yapiniz: ");
                          scanf("%d", &choice);

                        if (choice == 1) {
                          copy_matrix(matrix, last_matrix, n); // mevcut durumu last_matrix'e kopyala
                          int filled_cells = move_number(matrix, n);
                          
                          // Skor hesaplama
                          score += fillScore(filled_cells);
                          print_matrix(matrix, n);
                          
                        if (is_matrix_filled(matrix, n)) {
                          addPlayer(players, &playerCount, playerName, score);
                          printf("\nOyun Bitti! Kullanici adi: %s, Toplam skorunuz: %d\n", playerName, score);
                          run = 0;
                          }
                          
                          }
                          
                        else if (choice == 2) {
                          
                          copy_matrix(last_matrix, matrix, n); // last_matrix durumuna geri dön
                          score -= 10; // Skordan 10 puan çikart
                          print_matrix(matrix, n);
                          
                        }
                          
                        else if (choice == 3) {
                          
                          run = 0;
                          
                        }
                          
                        else if (choice == 4) {
                          
                         create_random_matrix(matrix, n); // Yeni matris olustur
                         copy_matrix(matrix, last_matrix, n); // Yeni matrisi last_matrix olarak kopyala
                         print_matrix(matrix, n);
                          
                        }
                          
                        else {
                          
                         printf("\nGeçersiz Secim Yaptiniz, Lutfen tekrar secim yapiniz.");
                          
                        }
                        } 
                        break;

                       case 2:
                         
                        automatically();
                         
                       break;
                      
                       case 3:
                         
                       break;
                      
                       default:
                         
                         printf("Gecersiz secim yaptiniz, Tekrar deneyin.\n");
                      
                       }
                      }while (sub_secim != 3);
              
                       break;
          
                       case 2:
              
                         printf("\n Oyun Menu: \n");
                         int sub_secim2;
              
                do {
                  printf("1.Manuel Mod'da Oyna:\n");
                  printf("2.Otomatik Mod'da Oyna:\n");
                  printf("3.Ana Menu'ye Geri Git:\n");

                  printf("Seciminizi girin: ");
                  scanf("%d", &sub_secim2);

                  switch (sub_secim2){
                        case 1:
                          
                          printf("Oyuncu ismini giriniz: ");
                          scanf("%s",playerName);
                          printf("Dosya Adini Giriniz: ");
                          scanf("%s",fileName);
                          printf("Dosyanin boyutunu giriniz: ");
                          scanf("%d",&N);
                          
                          readFromFile(matris, fileName);
                          drawBoard(matris, N);

                          printf("Oyuncunun onceki skoru: %d\n", getPreviousScore(players, playerCount, playerName));

                          int choice;
                          
                        do {
                          
                          printf("\nMenu:\n1. Sayiyi hareket ettir\n2. Geri al\n3. Cikis\nLutfen secim yapiniz: ");
                          scanf("%d", &choice);
                           
                          switch(choice) {
                        case 1:
                          
                          fill(matris, previous_matris, &score);
                          
                          if(gameOver(matris, N)){
                          printf("Oyun Bitti!\n");
                          addPlayer(players, &playerCount, playerName, score);
                          printf("Oyuncu %s, toplam skorunuz: %d\n", playerName, score);
                          }
                        break;
                            
                        case 2:
                          undo(matris, previous_matris, &score);
                        break;
            
                        case 3:
                          printf("Programdan Cikiliyor...\n");
                        break;
                            
                        default:
                          printf("Hatali secim yaptiniz, Tekrar Deneyin.\n");
                        break;
                        }
                          
                        drawBoard(matris, N);
                          
                        } while (choice != 3);
                        break;
                    
                        case 2:
                         
                            automatically2();
                            break;
                        case 3:
                            break;
                        default:
                            printf("Gecersiz secim yaptiniz, Tekrar deneyin.\n");
                         }    
                        } while(sub_secim2 != 3);
                            break;
          
            case 3:
                displayPlayerScores(players, playerCount);
                break;
          
            case 4:
                printf("Cikis yapildi\n");
                return 0;
          
            default:
                printf("Gecersiz secim yaptiniz, Tekrar deneyin.\n");
           }
          }
      return 0;
    }

void create_random_matrix(int matrix[MAX_RANDOM][MAX_RANDOM], int n) {
    srand(time(0)); // Rastgele sayi üreteciyi baslat

    int num_count[MAX_RANDOM+1]; // Her sayinin kaç kez kullanildigi tutmak için bir dizi

    // Diziyi sifirla
    int i,j;
    for ( i = 0; i <= n; i++) {
        num_count[i] = 0;
    }

    // Matrisi olustur
    for (i = 0; i < n; i++) {
        for ( j = 0; j < n; j++) {
            // Her bir numaranyn sadece iki kez kullanylmasyny garantiye al
            int k = (rand() % n) + 1;
            if (num_count[k] < 2) {
                num_count[k]++;
                matrix[i][j] = k;
            } else {
                matrix[i][j] = 0;
            }
        }
    }
}

void create_random_matrix2(int n, int matrix[MAX_RANDOM][MAX_RANDOM]) {
    srand(time(0)); 

    int i, j, k;
    int num_count[MAX_RANDOM+1]; 

    for (i = 0; i <= n; i++) {
        num_count[i] = 0;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            k = (rand() % n) + 1;
            if (num_count[k] < 2) {
                num_count[k]++;
                matrix[i][j] = k;
            } else {
                matrix[i][j] = 0;
            }
        }
    }
}

void print_matrix(const int matrix[MAX_RANDOM][MAX_RANDOM], int n) {
    // Matrisi ekrana yazdyr
    int i,j;
    for ( i = 0; i < n; i++) {
        for ( j = 0; j < n; j++) {
            if (matrix[i][j] == 0) {
                printf("|      ");
            } else {
                printf("|  %d   ", matrix[i][j]);
            }
        }
        printf("|\n");
        for (j = 0; j < n; j++) {
            printf("------");
        }
        printf("-\n");
    }
}

void print_matrix2(int n, int matrix[MAX_RANDOM][MAX_RANDOM]) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (matrix[i][j] == 0) {
                printf("|      ");
            } else {
                printf("|  %d   ", matrix[i][j]);
            }
        }
        printf("|\n");
        for (j = 0; j < n; j++) {
            printf("------");
        }
        printf("-\n");
    }
}

void move_number(int matrix[MAX_RANDOM][MAX_RANDOM], int n) {
    int old_row, old_col, new_row, new_col;
    int i,j;

    printf("\nHangi sayinin satir koordinatini tasimak istersiniz: ");
    scanf("%d", &old_row);
    printf("Hangi sayinin sutun koordinatini tasimak istersiniz: ");
    scanf("%d", &old_col);
    printf("Hedef satir koordinatini girin: ");
    scanf("%d", &new_row);
    printf("Hedef sutun koordinatini girin: ");
    scanf("%d", &new_col);
    printf("\n");
  
    if (matrix[new_row][new_col] != 0) {
        printf("Hedef konum dolu. Lutfen bos bir konum secin.\n");
        return;
    }

    int moving_number = matrix[old_row][old_col];

    // Yatay hareket
    if (old_row == new_row) {
        int min_col = old_col < new_col ? old_col : new_col;
        int max_col = old_col > new_col ? old_col : new_col;
        for ( i = min_col; i <= max_col; i++)
            matrix[old_row][i] = moving_number;
    }
    // Dikey hareket
    else if (old_col == new_col) {
        int min_row = old_row < new_row ? old_row : new_row;
        int max_row = old_row > new_row ? old_row : new_row;
        for (i = min_row; i <= max_row; i++)
            matrix[i][old_col] = moving_number;
    }
}

void copy_matrix(const int src[MAX_RANDOM][MAX_RANDOM], int dest[MAX_RANDOM][MAX_RANDOM], int n) {
	int i,j;
    for ( i = 0; i < n; i++) {
        for ( j = 0; j < n; j++) {
            dest[i][j] = src[i][j];
        }
    }
}
void copy_matrix2(int n, int src[MAX_RANDOM][MAX_RANDOM], int dest[MAX_RANDOM][MAX_RANDOM]) {
    int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            dest[i][j] = src[i][j];
        }
    }
}


int is_matrix_filled(const int matrix[MAX_RANDOM][MAX_RANDOM], int n) {
	int i,j;
    for ( i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (matrix[i][j] == 0) {
                return 0; // Matris hala bo? hücreler içeriyorsa, 0 döndür
            }
        }
    }
    return 1; // Tüm hücreler doluysa, 1 döndür
}

void displayPlayerScores(Player players[], int playerCount) { // Oyuncularin Skor Tablosu
    int i;
    time_t currentTime;
    struct tm *localTime;
    char buffer[80];

    time(&currentTime);
    localTime = localtime(&currentTime);

    // Format the date string
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
    printf("\n***********************\n");
    printf("*     Skor Tablosu    *\n");
    printf("***********************\n\n");
    for(i = 0; i < playerCount; i++) {
        printf("%s: %d\n", players[i].name, players[i].score);
    }
    printf("\Tarih: %s\n\n", buffer);
    printf("***********************\n\n");
}

void readFromFile(int matris[][MAX_DOSYA], char *fileName){
    int i,j, temp;
    FILE *data = fopen(fileName,"r");
    if(!data){
        printf("Dosya Acilamadi!\n");
        return;
    }
    while(!feof(data)){
        fscanf(data,"%d %d %d\n",&i,&j,&temp);  
        matris[i][j]=temp; 
    }  
    fclose(data);
}

void drawBoard(int matris[][MAX_DOSYA], int N){
    int i,j,k;
    for(i=0;i<N;i++){
        printf("\n");
        for (k=0;k<N;k++)
            printf("-------");
        printf("\n");
        for(j=0;j<N;j++)
            if (matris[i][j]!=0)
                printf("  %d   |",matris[i][j]);
            else
                 printf("      |");
    }
    printf("\n");
}

void copyMatrix(int src[][MAX_DOSYA], int dest[][MAX_DOSYA]) {
	int i,j;
    for ( i = 0; i < MAX_DOSYA; i++)
        for ( j = 0; j < MAX_DOSYA; j++)
            dest[i][j] = src[i][j];
}

int fillScore(int count) { // Skor Rakamlarini belirtdiyim fonksiyon
    switch (count) {
        case 1: return 5;
        case 2: return 15;
        case 3: return 20;
        case 4: return 25;
        case 5: return 30;
        case 6: return 35;
        case 7: return 40;
        case 8: return 45;
        case 9: return 50;
        case 10: return 55;
        case 11: return 60;
        case 12: return 65;
        case 13: return 70;
        case 14: return 75;
        case 15: return 80;
        default: return 0;
    }
}

void fill(int matris[][MAX_DOSYA], int previous_matris[][MAX_DOSYA], int *score) {
    int i,j,row, col, row_dir, col_dir, number, filledCount = 0;
   printf("Hangi sayinin satir koordinatini tasimak istersiniz: ");
    scanf("%d", &row);
    printf("Hangi sayinin sutun koordinatini tasimak istersiniz: ");
    scanf("%d",&col);
    printf("Hedef satir koordinatini girin:  ");
    scanf("%d",&row_dir);
    printf("Hedef sutun koordinatini girin:  ");
    scanf("%d",&col_dir);
    printf("\n");
    if (matris[row_dir][col_dir] != 0) {
        printf("Hedef konum dolu. Lutfen bos bir konum secin.\n");
        return;
    }
    number = matris[row][col];
    copyMatrix(matris, previous_matris); // doldurmadan önceki durumu kaydet
    for ( i = row; i <= row_dir; i++){
        for ( j = col; j <= col_dir; j++){
            if(matris[i][j] == 0) {
                filledCount++;
            }
            matris[i][j] = number;
        }
    }
    *score += fillScore(filledCount);
}

void undo(int matris[][MAX_DOSYA], int previous_matris[][MAX_DOSYA], int *score) {
    copyMatrix(previous_matris, matris); // önceki durumu geri yükle
    *score -= 10; // Geri al Puan Kýrýlmasý
    if (*score < 0) *score = 0; 
}

int gameOver(const int matris[][MAX_DOSYA], int N){
	
	int i,j;
    for ( i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (matris[i][j] == 0) {
                return 0; // Matris hala bos kordinatlar içeriyorsa, 0 döndür
            }
        }
    }
    return 1; // Tüm hücreler doluysa, 1 döndür
}

void fill_empty_cells(int n, int matrix[MAX_RANDOM][MAX_RANDOM]) {
    srand(time(0)); 

    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][j] = (rand() % n) + 1;
            }
        }
    }
}


void fillOut(int matris[][MAX_DOSYA], int N) {
    int i, j, k, found;
    int unique[MAX_DOSYA*MAX_DOSYA] = {0};
    int unique_count = 0;
    int fill_val = 0;

    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            if (matris[i][j] != 0) {
                found = 0;
                for (k=0; k<unique_count; k++) {
                    if (unique[k] == matris[i][j]) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    unique[unique_count++] = matris[i][j];
                }
            }
        }
    }

    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            if (matris[i][j] == 0) {
                matris[i][j] = unique[fill_val];
                fill_val = (fill_val + 1) % unique_count;
            }
        }
    }
}

void automatically(){
  
	  int matrix[MAX_RANDOM][MAX_RANDOM]; 
    int last_matrix[MAX_RANDOM][MAX_RANDOM];
    int n;
  
   	printf("Matris boyutunu giriniz: ");
    scanf("%d", &n);

    create_random_matrix2(n, matrix);
    copy_matrix2(n, matrix, last_matrix); 
    print_matrix2(n, matrix);

    int choice;
    do {
        printf("\n1  Yeni Matris Olustur\n2 Cikis\n3 Otomatik Doldur\n:Lutfen secim yapiniz: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            create_random_matrix2(n, matrix);
            copy_matrix2(n, matrix, last_matrix);
            print_matrix2(n, matrix);
            break;
        case 2:
            break;
        case 3:
            fill_empty_cells(n, matrix);
            print_matrix2(n, matrix);
            break;
        }
    } while (choice != 2);

}


void automatically2(){
	int matris[MAX_DOSYA][MAX_DOSYA]={{0}};
    int previous_matris[MAX_DOSYA][MAX_DOSYA] = {{0}};
    int N;
    char fileName[20];

    printf("Dosya Adini Giriniz: ");
    scanf("%s",fileName);
    printf("Dosyanin boyutunu giriniz: ");
    scanf("%d",&N);
    readFromFile(matris, fileName);
    drawBoard(matris, N);

    int choice;
    do {
        printf("\nMenu:\n1. Otomatik Doldur\n2. Cikis\nLutfen secim yapiniz: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                fillOut(matris, N);
                break;
            
            case 2:
                printf("Programdan cikiliyor...\n");
                
                break;
            default:
                printf("Hatali secim. Tekrar deneyin.\n");
                break;
        }
        drawBoard(matris, N);
    } while (choice != 2);
}

void addPlayer(Player players[], int *playerCount, char *name, int score) {
    strcpy(players[*playerCount].name, name);
    players[*playerCount].score = score;
    (*playerCount)++;
}

int getPreviousScore(Player players[], int playerCount, char *name) {
    int i;
    for( i = 0; i < playerCount; i++) {
        if(strcmp(players[i].name, name) == 0) {
            return players[i].score;
        }
    }
    
    return 0;
    
}

