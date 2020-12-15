//Фомин Иван БПИ 197 Вариант 1

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int counter = 0; // Считает количество клиентов за сегодня
int queueLength = 0; // Считает количество клиентов в очереди
bool IsBarberBusy = false; // Определяет занят ли парикмахер
thread th;

/// <summary>
/// Посетитель идет в кресло
/// </summary>
void GoArmchair()
{
        cout << "ID потока = " << this_thread::get_id() << "\tКлиент идет в кресло" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
}

/// <summary>
/// Парикмахер выполняет свою работу
/// </summary>
void DoWork()
{
    IsBarberBusy = true;
    GoArmchair();
    cout << "ID потока = " << this_thread::get_id() << "\tПарикмахер делает свою работу" << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "ID потока = " << this_thread::get_id() << "\tПарикмахер проважает клиента" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    if (queueLength == 0)
    {
        IsBarberBusy = false;
    }
    else
    {
        queueLength--;
        DoWork();
    }
}
/// <summary>
/// Метод добавляет клиента в очередь
/// </summary>
void Wait()
{
    cout << "ID потока = " << this_thread::get_id() << "\tКлиент ожидает своей очереди" << endl;
    queueLength++;
}


int main()
{
    string a;
    setlocale(LC_ALL, "ru");
    for (size_t i = 0; i < 11; i++)
    {
        if (i == 10)
        {
            cout << "Клиенты на сегодня закончились, дождитесь пока парикмахер дострижет оставшихся и закройте парикмахерскую." << endl;
            while (IsBarberBusy == true) // Дожидаемся, пока парикмахер дострижет клиентов
            {

            }
            return 0;
        }
        cout <<"Введите что - нибудь, что бы призвать новых клиентов" << endl;
        cin >> a;
        cout << "ID потока = " << this_thread::get_id() << "\tПришел новый клиент под номером " << counter + 1 << endl;
        counter++;
        if (IsBarberBusy)
        {
            Wait();
        }
        else
        {
            thread th(DoWork);
            th.detach();
        }
    }

    return 0;
}


