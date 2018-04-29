#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "atm.h"
void stringCleaner(char string[]) {
  int i;
  for(i = 0; i < strlen(string); i++) {
    string[i] = '\0';
  }
}
void newAccount(void) {
  FILE *file;
  char fileName[50];
  int lastAccountNumber, status, creditCardNo;
  struct user newUser;
  file = fopen("dataBase/lastAccountNumber.atm", "r");
  if( file == NULL ) {
    printf("Veritabanına ulaşılamıyor...");
    exit(1);
  }
  else ;
  fscanf(file, "%d", &lastAccountNumber);
  fclose(file);
  while(1) {  //Paralo kontrolü
    printf("Lutfen 4 haneli bir parola giriniz: ");
    scanf("%d", &newUser.password);
    printf("Lutfen tekrar giriniz: ");
    scanf("%d", &newUser.rePassword);
    if( newUser.password < 1000 || newUser.password > 9999 ) {
      printf("Sifreniz 4 haneli degil lutfen tekrar deneyin\n");
      if( !( newUser.password == newUser.rePassword ) ) {
        printf("Sifreleriniz Uyusmuyor...Tekrar deneyin veya iptal icin CTRL+C\n");
      }
    }
    else if( !( newUser.password == newUser.rePassword ) ) {
      printf("Sifreleriniz Uyusmuyor...Tekrar deneyin veya iptal icin CTRL+C\n");
    }
    else break;
  }
  while(1) {  //TC Kn kontrolü
    printf("TC Numaranizi giriniz:");
    scanf("%s", &newUser.tcKN);
    if( (newUser.tcKN[10] == '\0') || newUser.tcKN[11] != '\0' || newUser.tcKN[9]  == '\0' ) {
      printf("TC numaraniz hatali lutfen tekrar deneyin ve iptal icin CTRL+C\n");
    }
    else break;
  }
  //Diğer bilgiler isteniyor---------------------------------------------------
    printf("Adinizi giriniz:      ");
    scanf("%s", &newUser.name);
    printf("Soyadinizi giriniz:   ");
    scanf("%s", &newUser.surname);
  //Kayıt Bloğu----------------------------------------------------------------

  //Son hesap numarası bir artırılıyor-------------------------------------------
    file = fopen("dataBase/lastAccountNumber.atm", "w");
    newUser.accountNumber = lastAccountNumber + 1;
    fprintf(file, "%d", newUser.accountNumber);
    fclose(file);
  //-----------------------------------------------------------------------------

  //Kullanıcı bilgileri kaydediliyor(Ad, Soyad, TC)------------------------------
    stringCleaner(fileName);
    sprintf(fileName, "dataBase/%d.info", newUser.accountNumber);
    file = fopen(fileName,  "w");
    fprintf(file, "%s\n%s\n%s", newUser.tcKN, newUser.name, newUser.surname);
    fclose(file);
    stringCleaner(fileName);
  //-----------------------------------------------------------------------------

  //Şifre dosyası oluşturuluyor--------------------------------------------------
    sprintf(fileName, "dataBase/%d.psw", newUser.accountNumber);
    file = fopen(fileName, "w");
    fprintf(file, "%d", newUser.password);
    fclose(file);
    stringCleaner(fileName);
  //-----------------------------------------------------------------------------

  //Hesap numarası adı ile hesap dosyası oluşturuluyor---------------------------
    sprintf(fileName, "dataBase/%d.account", newUser.accountNumber);
    file = fopen(fileName, "w");
    fprintf(file, "0");
    fclose(file);
    stringCleaner(fileName);
  //-----------------------------------------------------------------------------

  //TC Numarası tüm TC'ler dosyasına ekleniyor-----------------------------------
    sprintf(fileName, "dataBase/allTC.atm");
    file = fopen(fileName, "a+");
    fprintf(file, "\n%s", newUser.tcKN);
    fclose(file);
  //-----------------------------------------------------------------------------

    printf("Yeni Hesabiniz olusturuldu.. ");

  //İsteğe bağlı kredi kartı ekleme----------------------------------------------
    printf("\nHesabiniza kredi karti eklemek istedmisiniz(1/0)");
    scanf("%d", &status);
    if( status == 1 ) {
      creditCardNo = newCreditCard(newUser.accountNumber);
      file = fopen("dataBase/creditEqAcc.atm", "a+");
      fprintf(file, "%d %d\n", newUser.accountNumber, creditCardNo);
      fclose(file);
    }
    else ;
  //-----------------------------------------------------------------------------

  //Tüm hesap numaraları listesine yeni hesap numarası ekleniyor-----------------
    file = fopen("dataBase/allAccounts.atm", "a+");
    fprintf(file, "\n%d", newUser.accountNumber);
    fclose(file);

  //-----------------------------------------------------------------------------

  //newAccount sonu
}
int newCreditCard(int accountNumber) {
  FILE *file;
  int limit, balance, lastCreditCardNo, newCreditCardNo;
  int readedAccNum;
  char fileName[50];
  //Kullanıcı hesap bakiyesi çekiliyor-------------------------------------------
    stringCleaner(fileName);
    sprintf(fileName, "dataBase/%d.account", accountNumber);
    file = fopen(fileName, "r");
    fscanf(file, "%d", &balance);
    fclose(file);
  //-----------------------------------------------------------------------------

    while(1) {  //Limit belirleme ve kontrolü
      printf("\nKredi kartiniz icin bir limit belirleyiniz: ");
      scanf("%d", &limit);
      if( (limit > balance + 1000) || limit < 0 ) {
        printf("Giridiginiz limit hesap bakiyenize izin verilmiyor..\nLutfen hesap numaranizin max. 1000Tl fazlasini giriniz:");
      }
      else break;
    }
    printf("Hesabiniz olusturuluyor..");

  //Son kredi kartı numarasi çekiliyor-------------------------------------------
    file = fopen("dataBase/lastCreditCardNo.atm", "r");
    fscanf(file, "%d", &lastCreditCardNo);
    fclose(file);
  //-----------------------------------------------------------------------------

  //Son kredi kartı numarası bir artırılıyor-------------------------------------
    file = fopen("dataBase/lastCreditCardNo.atm", "w");
    newCreditCardNo = lastCreditCardNo + 1;
    fprintf(file, "%d", newCreditCardNo);
    fclose(file);
  //-----------------------------------------------------------------------------

  //Kredi kartı numarası ile yeni hesap dosyası oluşturuluyor--------------------
    stringCleaner(fileName);
    sprintf(fileName, "dataBase/%d.credit", newCreditCardNo);
    file = fopen(fileName, "w");
    fprintf(file, "0\n%d", limit);
    fclose(file);
  //-----------------------------------------------------------------------------

    printf("\n\nYeni kredi kartiniz olusturuldu");

  //Tüm kredi kartları listesine yeni kredi kartı numarası ekleniyor-------------
    file = fopen("dataBase/allCredits.atm", "rb+");
    fprintf(file, "\n%d", newCreditCardNo);
    fclose(file);
    return newCreditCardNo;
  //-----------------------------------------------------------------------------

  //newCreditCard sonu
}
void accountLogin(void) {
  FILE *file;
  Login login;
  int readedAccNum, readedCreditNum;
  char fileName[50];
  login.creditCardNumber = 0;
  printf("Hesabiniza giris yapmak icin\n");
  while(1) {
    printf("Hesap Numaranizi Giriniz: ");
    scanf("%d", &login.accountNumber);
    printf("Sifrenizi giriniz: ");
    scanf("%d", &login.reg_password);
    stringCleaner(fileName);
    sprintf(fileName, "database/%d.psw", login.accountNumber);
    file = fopen(fileName, "r");
    if( file == NULL ) {
      printf("Ilgili Veritabanına erisilemiyor. Hesap numaranizi kontrol ediniz\n\a");
      stringCleaner(fileName);
    }
    else {
      fscanf(file, "%d", &login.password);
      if( login.reg_password == login.password ) {
        puts("Giris basarili..");
        fclose(file);
        break;
      }
      else ;
    }
  }
  puts("-----------------------------------------------------------------");
  stringCleaner(fileName);
  sprintf(fileName, "dataBase/%d.info", login.accountNumber);
  file = fopen(fileName, "r");
  if( file == NULL ) {
    puts("Veritabanına erisilemiyor");
    exit(1);
  }
  fscanf(file, "%s", login.tc);
  fscanf(file, "%s", login.name);
  fscanf(file, "%s", login.surname);
  fclose(file);
  stringCleaner(fileName);
  printf("Merhaba %s %s\n\n", login.name, login.surname);
  sprintf(fileName, "dataBase/%d.account", login.accountNumber);
  if( (file = fopen(fileName, "r")) == NULL ) {
    puts("Connection error!");
    exit(1);
  }
  fscanf(file, "%d", login.accountBalance);
  fclose(file);
  stringCleaner(fileName);
  if( (file = fopen("dataBase/creditEqAcc.atm", "r")) == NULL ) {
    puts("Connection error");
    exit(1);
  }
  while( !feof(file) ) {
    fscanf(file, "%d %d", &readedAccNum, &readedCreditNum);
    if( readedAccNum == login.accountNumber ) {
      login.creditCardNumber = readedCreditNum;
      break;
    }
  }
  fclose(file);
  if( login.creditCardNumber == 0 ) ;
  else {
    stringCleaner(fileName);
    sprintf(fileName, "dataBase/%d.credit", login.creditCardNumber);
    if( (file = fopen(fileName, "r")) == NULL ) {
      puts("Connection error");
      exit(1);
    }
    fscanf(file, "%d", &login.creditBalance);
    fscanf(file, "%d", &login.creditLimit);
  }
  loginPage(login);
}

void loginPage(Login userLogin) {
  
}
