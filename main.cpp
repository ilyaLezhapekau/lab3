#include <Windows.h>
#include <iostream>


using namespace std;

int value1 = 0, value2 = 0, value3 = 0;
volatile int n;
HANDLE hTh1, hTh2, hTh3;

void Thread_1(){

    while (true) {
        value1++;
        Sleep(200);
    }
}

void Thread_2(){

    while (true) {
        value2++;
        Sleep(600);
    }
}

void Thread_3(){
    while (true) {
        value3++;
        Sleep(400);
    }
}

int main()
{
    int threads_number = 3, max, close1 = 0, close2 = 0, close3 = 0;
    HANDLE hThreadManager;
    DWORD IDThread1, IDThread2, IDThread3, IDThreadManager;



    if ((hTh1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_1, NULL, 0, &IDThread1)) == NULL)
    {
        int error = GetLastError();
        cerr << "There is an error while hTh1 thread creating: " << error << endl;
        return error;
    }

    if ((hTh2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_2, NULL, 0, &IDThread2)) == NULL)
    {
        int error = GetLastError();
        cerr << "There is an error while hTh2 thread creating: " << error << endl;
        return error;
    }

    if ((hTh3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_3, NULL, 0, &IDThread3)) == NULL)
    {
        int error = GetLastError();
        cerr << "There is an error while hTh3 thread creating: " << error << endl;
        return error;
    }

    char resp;
    do {
        cout << "'q' Terminate threads" << endl;
        cout << "'w' Write keys" << endl;
        cin >> resp;
        cin.ignore(32767, '\n');
        cin.clear();
        system("cls");

        switch (resp) {
            case 'w':
                cout << "value1 = " << value1 << endl;
                cout << "value2 = " << value2 << endl;
                cout << "value3 = " << value3 << endl;
                break;
            default:
                break;
        }
        if (value1 * value3 == 5000){
            cout << "value[1] = " << value1 << endl;
            cout << "value[3] = " << value3 << endl;
            TerminateThread(hTh2, 0);
            cout << "thread_hTh2 was terminated" << endl;
            CloseHandle(hTh2);
            TerminateThread(hTh1, 0);
            TerminateThread(hTh3, 0);
            CloseHandle(hTh1);
            CloseHandle(hTh3);

            return 0;
        }
        if (value1 * value3 > 5000)
        {
            cout << "thread_hTh2 is not working" << endl;
            TerminateThread(hTh2, 0);
            CloseHandle(hTh2);

        }
//
        CloseHandle(hTh1);
//      CloseHandle(hTh2);
        CloseHandle(hTh3);

    } while (resp != 'q');

    return 0;
}