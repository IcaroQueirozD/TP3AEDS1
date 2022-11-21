#include <iostream>
#include "Queue.hpp"
#include <ctime>
#include <iomanip>
#include <windows.h>

using namespace std;

void CreateEmptyQueue(QueueType *queue)  //Criação de uma fila vazia.
{
    queue->start = NULL;
    queue->end = NULL;
    queue->size = 0;
}

bool VerifyEmptyQueue(QueueType *queue) //Verifica se a fila está vazia.
{
    return (queue->start == NULL);
}

int Size(QueueType *queue) //Retorna o tamanho da fila.
{
    return queue->size;
}

void QueueDoctor(QueueType *queue, Doctor item) //Enfileira os médicos.
{
    Point new_item = new ElementType;

    new_item->d_item = item;
    new_item->next = NULL;

    if (VerifyEmptyQueue(queue))
    {
        queue->start = new_item;
    }
    else
    {
        queue->end->next = new_item;
    }

    queue->end = new_item;
    queue->size++;
}

void InsertDoctor(QueueType *queue, Doctor *item) //Insere os médicos pré-definidos na fila.
{
    Doctor doctors;
    doctors.docname="Apollo";
    doctors.occ="Pathologist";
    doctors.crm="23465";
    QueueDoctor(queue,doctors);
    doctors.docname="Asclepius";
    doctors.occ="Cardiologist";
    doctors.crm="98465";
    QueueDoctor(queue,doctors);
    doctors.docname="Chiron";
    doctors.occ="Gastroenterologist";
    doctors.crm="11265";
    QueueDoctor(queue,doctors);
    doctors.docname="Darrhon";
    doctors.occ="Pulmonologist";
    doctors.crm="98666";
    QueueDoctor(queue,doctors);
    doctors.docname="Panacea";
    doctors.occ="General practitioner";
    doctors.crm="44552";
    QueueDoctor(queue,doctors);
}
void QueuePatient(QueueType *queue, Patient item) //Enfileira of pacientes.
{
    Point new_item = new ElementType;
    new_item->p_item = item;
    new_item->next = NULL;
    if (VerifyEmptyQueue(queue))
    {
        queue->start = new_item;
    }
    else
    {
        queue->end->next = new_item;
    }

    queue->end = new_item;
    queue->size++;
}

void InsertPatientFirst(QueueType *queue, Patient patient) //Usado para auxiliar no ordenamento das prioridades.
{
    Point aux = new ElementType;
    aux->p_item = patient;
    aux->next = NULL;

    if (VerifyEmptyQueue(queue))
    {
        queue->start = aux;
        queue->end = queue->start;
    }
    else
    {
        aux->next = queue->start;
        queue->start = aux;
    }
    queue->size++;
}

void InsertAfterElement(Point previous, Point new_item, QueueType *queue) //Usado para inserir um item com maior prioridade na frente da fila.
{
    new_item->next = previous->next;
    previous->next = new_item;
    queue->size++;
}

void QueuePriority(QueueType *queue, Patient patient) //Enfileira os pacientes de acordo com a prioridade.
{
    
    if (VerifyEmptyQueue(queue))
    {
        InsertPatientFirst(queue, patient); //Caso a fila estiver vazia, adiciona o novo item na fila.
        return;
    }

    
    if (patient.priority < queue->start->p_item.priority)
    {
        InsertPatientFirst(queue, patient);
        return;
    }

    Point previous = queue->start;
    Point current = previous->next;
    Point new_item = new ElementType;
    new_item->p_item = patient;
    new_item->next = NULL;

    // Insere o novo item após a maior prioridade na fila.
    while (current != NULL)
    {
        if (new_item->p_item.priority < current->p_item.priority)
        {
            InsertAfterElement(previous, new_item, queue);
            return;
        }
        previous = current;
        current = current->next;
    }
    InsertAfterElement(previous, new_item, queue);
    queue->end = new_item;
}


void UnqueuePatient(QueueType *queue, Patient *item) //Desenfilera um paciente.
{
    if (VerifyEmptyQueue(queue))
    {
        cout << "queue vazia!" << endl;
        return;
    }
    Point aux = queue->start;

    *item = aux->p_item;
    queue->start = aux->next;
    delete aux;
    
}

void PrintDoctors(QueueType *queue) //Imprime a lista de médicos.
{
    Point aux = queue->start;
    while (aux != NULL)
    {

        cout << "\nName: " << aux->d_item.docname;
        cout << "\nOccupation: " << aux->d_item.occ;
        cout << "\nCRM: " << aux->d_item.crm;
        cout << "\nAvailable(0-NO, 1-YES): " << aux->d_item.availability
             << endl;
        aux = aux->next;
    }
    cout << endl;
}
void PrintPatients(QueueType *queue) //Imprime a lista de pacientes.
{

    if (VerifyEmptyQueue(queue))
    {
        cout << "There are no patients in the registry!" << endl;
        return;
    }
    Point aux = queue->start;
    while (aux != NULL)
    {
        cout << "\nName: " << aux->p_item.name;
        cout << "\nAddress: " << aux->p_item.address;
        cout << "\nAge: " << aux->p_item.age;
        cout << "\nSex: " << aux->p_item.sex;
        cout << "\nPriority: " << aux->p_item.priority;
        cout << "\nwas checked or treated: 0-NO 1-YES " << aux->p_item.treated;
        if (aux->p_item.treated == 1)
        {
            cout << "\nTreatment/check time: " << aux->p_item.time
                 << endl;
        }
        cout << "\nTime of Arrival: " << ctime(&aux->p_item.arrival);

        aux = aux->next;
    }
    cout << endl;
}

int Questionnaire() //Questionário da triagem.
{
    char ans[18];
    Patient patients;
    QueueType queue;


    cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n";
    cout << "▓                           ▓\n";
    cout << "▓       QUESTIONNAIRE       ▓\n";
    cout << "▓                           ▓\n";
    cout << "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n";

    cout << "1: Compromised Airways?\n";
    cout << "2: Trouble Breathing?\n";
    cout << "3: Shock?\n";
    cout << "4: Not responding to stimuli?\n";
    cout << "5: Convulsing?\n";
    cout << "6: Severe Pain?\n";
    cout << "7: Large uncontrollable hemorrhage?\n";
    cout << "8: Alteration in consciousness?\n";
    cout << "9: Temperature above 39°C?\n";
    cout << "10: Severe Head Trauma?\n";
    cout << "11: Moderate Pain?\n";
    cout << "12: Small uncontrollable hemorrhage?\n";
    cout << "13: Continuous Vomiting?\n";
    cout << "14: Temperature between 38°C  and 39°C?\n";
    cout << "15: Elderly or Pregnant?\n";
    cout << "16: Mild Pain?\n";
    cout << "17: Nausea?\n";
    cout << "18: Temperature between 37°C e 38°C?\n";

    cout << "Do you have any of the aforementioned symptoms?\n\n";
    for (int i = 1; i <= 5; i++)
    { 
        cout << "Answer " << i<<": ";
        cin >> ans[i];
        if (ans[i] == 'S' || ans[i] == 's')
        {
            return i;
        }
    }
    for (int i = 6; i < 18; i++)
    { 
        cout << "Answer " << i<<": ";
        cin >> ans[i];
    }
    cout << "Order of Answers \n ";
    for (int i = 0; i < 18; i++)
    {
        cout << ans[i] << " ";
    }
    for (int i = 6; i < 18; i++)
    {
        if (ans[i] == 'S')
        {
            return i;
        }
    }
    system("PAUSE");
    system("cls");
}

void AddPatient(Patient *Item, int returnq) //Define o tempo de acordo com a prioridade do paciente em segundos.
{
    int priority;
    double treattime;
    if (returnq <= 5)
    {
        priority = 1;
        treattime = 5; 
    }
    else if (returnq > 5 && returnq < 11)
    {
        priority = 2;
        treattime = 4; 
    }
    else if (returnq > 11 && returnq < 16)
    {
        priority = 3;
        treattime = 3; 
    }
    else if (returnq > 16 && returnq < 18)
    {
        priority = 4;
        treattime = 2; 
    }
    else
    {
        priority = 5;
        treattime = 1; 
    }
    cout << "\n";
    cout << "***********************************\n";
    cout << "        PATIENT REGISTRATION       \n";  //Regitra as informações pessoais do paciente.
    cout << "***********************************\n\n";
    cin.ignore();

    cout << "Name: ";
    cin>>Item->name;
    cout << "Address: ";
    cin>>Item->address;
    cout << "Age: ";
    cin>>Item->age;
    cout << "Sex: ";
    cin>>Item->sex;
    Item->priority = priority;
    Item->arrival = time(NULL);
    Item->time = treattime;
}

void update(QueueType *patients, QueueType *trtdpatients, QueueType *doctors, QueueType *avdoctors) //Atualiza a fila.
{

    Point aux = patients->start;
    Point aux2 = doctors->start;
    aux2->d_item.availability = true;

    for (int i = 0; i < doctors->size; i++)
    {

        aux->p_item.exit = time(NULL);
        aux->p_item.time = aux->p_item.exit - aux->p_item.arrival;

        cout << "Patient    " << aux->p_item.name << " was treated or checked in: " << aux->p_item.time << "   seconds."
             << "  by doctor  " << aux2->d_item.docname << "\n";

        cout << "Patient treated succesfully!\n";
        aux->p_item.treated = true;
        aux2->d_item.availability = false;

        if (aux->p_item.treated == true)
        {
            QueuePriority(trtdpatients, aux->p_item);
            UnqueuePatient(patients, &aux->p_item);
        }
        if (patients->size == trtdpatients->size)
        {
            if (aux2->d_item.availability == true)
            {

                QueueDoctor(avdoctors, aux2->d_item);
            }

            break; 
        }
        aux2 = aux2->next;
        aux = aux->next;
        Sleep(1000);
    }
}