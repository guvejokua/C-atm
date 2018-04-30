#ifndef atm
#define atm
struct user {
  int accountNumber, password, rePassword;
  char name[30], surname[20];
  char tcKN[11];
};
struct loginUser {
  char name[30], surname[20], tc[12];
  int accountNumber, password, creditCardNumber, creditBalance, accountBalance, creditLimit;
  int reg_password;       //reg is registered
};
typedef struct loginUser Login;
void newAccount(void);
int newCreditCard(int accountNumber);
void stringCleaner(char string[]);
void accountLogin(void);
void loginPage(Login userLogin);
void operation(Login userInfo);
void wdMoney(int accountNumber, int accountBalance);
void dpstMoney(int accountNumber, int accountBalance);
void transfer(int accountNumber, int accountBalance);
void changePsw(int accountNumber);
void payment(int accountNumber, int creditCardNumber, int creditBalance, int accountBalance);
void limit(int accountBalance, int creditCardNumber, int creditBalance);
#endif
