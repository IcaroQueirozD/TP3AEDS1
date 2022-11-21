#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <ctime>



typedef struct Patient //Struct representante das informações do paciente.
{
    std::string name;
    std::string sex;
    std::string address;
    int priority;
    int age;
    bool treated = false;
    char answers[18];
    time_t arrival;
    time_t exit;
    double time;
    
} Patient;

typedef struct Doctor //Struct representante das informações do médico.
{
    std::string docname;
    std::string occ;
    std::string crm;
    bool availability = true;
    Patient patient;
    
} Doctor;


typedef struct ElementType *Point;


typedef struct ElementType
{
    Patient p_item;
    Doctor d_item;
    Point next;

} ElementType;


typedef struct QueueType //Struct que define a fila.
{
    Point start, end;
    int size;

} QueueType;

typedef struct hosp 
{
    Doctor doctors[5];
    int treatments;
    QueueType queue;
    
} hosp;

void CreateEmptyQueue(QueueType *queue);
bool VerifyEmptyQueue(QueueType *queue);
int Size(QueueType *queue);
void InsertDoctor(QueueType *queue, Doctor *item);
void QueueDoctor(QueueType *queue, Doctor item);
void QueuePatient(QueueType *queue, Patient item);
void InsertPatientFirst(QueueType *queue, Patient patient);
void InsertAfterElement(Point previous, Point new_item, QueueType *queue);
void QueuePriority(QueueType *queue, Patient patient);
void UnqueuePatient(QueueType *queue, Patient *item);
void PrintDoctors(QueueType *queue);
void PrintPatients(QueueType *queue);
int Questionnaire();
void AddPatient(Patient *Item, int returnq);
void update(QueueType *patients, QueueType *trtdpatients, QueueType *doctors, QueueType *avdoctors);

#endif