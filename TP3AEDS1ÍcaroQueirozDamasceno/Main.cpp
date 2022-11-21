#include <iostream>
#include <windows.h>
#include <ctime>
#include <windows.h>
#include "Queue.cpp"
#include "Queue.hpp"

using namespace std;

void menu1()
{
  system("cls");
  cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n"; // Menu principal.
  cout << "▓                           ▓\n";
  cout << "▓    MORIOH-CHO HOSPITAL    ▓\n";
  cout << "▓                           ▓\n";
  cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n";
  cout << "\n1. Hospital Registry.\n";
  cout << "2. Register a new patient.\n";
  cout << "3. Start a treatment or chekup.\n";
  cout << "0. Exit.\n\n";
}

void update(QueueType *patients, QueueType *trtdpatients, QueueType *doctors, QueueType *avdoctors);  

int main()
{
  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_UTF8);

  int choice1; //Declaração de variáveis, filas e seus itens.
  char choice2, choice3;
  QueueType doctors, avdoctors, patients, trtdpatients, queue;
  Patient patient;
  Doctor doctor;

  CreateEmptyQueue(&doctors);
  CreateEmptyQueue(&avdoctors);  //Criação das filas utilizadas no trabalho.
  CreateEmptyQueue(&patients);
  CreateEmptyQueue(&trtdpatients);
  CreateEmptyQueue(&queue);
  InsertDoctor(&doctors, &doctor); //Pré-definição dos médicos.
  

  do
  {
    menu1();
    cin >> choice1; //Escolha de opções no menu.
    switch (choice1)
    {
    case 1:
    {
      system("cls"); 
      cout << "Amount of registered patients: " << Size(&patients) << "\n";
      cout << "Amount of treated/checked patients: " << Size(&trtdpatients) << "\n";  //Impressão dos itens das filas e seus tamanhos.
      cout << "Amount of available doctors: " << Size(&avdoctors) << "\n";
      cout << "List of patients: \n";
      PrintPatients(&trtdpatients);
      PrintPatients(&patients);

      cout << "List of doctors: \n";
      PrintDoctors(&doctors);
      system("pause");
      break;
    }
    case 2:
    {
      char returnq, vet[18];
      int value;
      do
      {
        system("cls");
        returnq = Questionnaire();  //Início da triagem a partir de uma função.
        AddPatient(&patient, returnq);
        QueuePatient(&patients, patient);  //Inserção do paciente na fila.
        cout << "Questionnaire Finished.\n";
        cout << "Do you wish to register another patient? (Y=Yes N=No)\n"; //Input do usuário caso ele queira registrar mais pacientes.
        cin >> choice2;
      } while (choice2 != 'N');

      system("pause");
      break;
    }
    case 3:
    {
      if (Size(&patients) == 0)  //Início do atendimento dos pacientes.
      {
        cout << "There are no patients to treat.\n";
      }
      else
      {

        update(&patients, &trtdpatients, &doctors, &avdoctors); //As filas são atualizadas.

        cout << "Do you wish to update?\n";
        cin >> choice3;

        while (choice3 == 's')
        {
          if (Size(&trtdpatients) == Size(&patients))
          {
            cout << "All patients were treated.\n";
            break;
          }
          else
          {
            update(&patients, &trtdpatients, &doctors, &avdoctors);
            cout << "Do you wish to update?\n";
            cin >> choice3;
          }
          break;
        }
      }
    }
    }
  } while (choice1 != 0);

  cout << endl;
  return 0;
}