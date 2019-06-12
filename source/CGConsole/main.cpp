#include <QCoreApplication>
#include "algorithm.h"

extern string filename, imageSaveAddress;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout<< "Please input instruction file path:" << endl;
    cout<< ">>";
    cin>> filename;
    cout<< "Please input image saving address:" << endl;
    cout<< ">>";
    cin>> imageSaveAddress;
    paintevent();
    return 0;
}
