#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

const char alphanum[] = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int string_length = sizeof(alphanum) - 1;

void generatePassword(int n, string times);
void getTime(int n1);
int main()
{
  int input;

generate:
  cout << "=================================" << endl;
  cout << "Program Random Password Generator1" << endl;
  cout << "=================================" << endl
       << endl;

  cout << "Masukan panjang password: ";
  cin >> input;

  if (input > 100)
  {
    cout << "Melebihi batas maksimal panjang password (1-100)" << endl;

#ifdef _WIN32
    Sleep(2000);
    system("cls");
#else
    sleep(2);
    system("clear");
#endif

    goto generate;
  }

  getTime(input);

  cout << "\n\nPassword disimpan didalam file password.txt" << endl;
  cout << "Press enter to close...." << endl;
  cin.get();
  cin.get();

  return 0;
}

void getTime(int n1)
{
  stringstream timeTemp;
  time_t now;
  struct tm nowLocal;
  string times;

  now = time(NULL);

  nowLocal = *localtime(&now);

  timeTemp << "Created at: " << nowLocal.tm_mday << "/" << nowLocal.tm_mon + 1 << "/" << nowLocal.tm_year + 1900 << " - " << nowLocal.tm_hour << ":" << nowLocal.tm_min << ":" << nowLocal.tm_sec;

  times = timeTemp.str();

  generatePassword(n1, times);
}

void generatePassword(int n, string times)
{
  fstream generatedPassword;
  string listPass[100];
  stringstream tempPass, timeTemp;

  srand(time(0));
  generatedPassword.open("password.txt", ios::app);

  if (generatedPassword.is_open())
  {
    cout << "Generated Random password: ";
    for (int i = 0; i < n; i++)
    {
      listPass[i] = alphanum[rand() % string_length];
      tempPass << listPass[i];
    }

    cout << tempPass.str();

    generatedPassword << "Generated Password: " << tempPass.str() << " | "
                      << "Panjang Password: " << n << " | " << times
                      << "\n\n";
    generatedPassword.close();
  }
}