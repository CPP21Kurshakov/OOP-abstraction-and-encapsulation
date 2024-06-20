#include <iostream>
#include <string>
#include <fstream>



class Addresses
{
private:
    std::string city;
    std::string street;
    int house = 0;
    int apartment = 0;

public:
    Addresses(const std::string& cit, const std::string& strt, int hs, int aptt) :
        city(cit), street(strt), house(hs), apartment(aptt) {}

    std::string getAddressString() const
    {
        return city + ", " + street + ", " + std::to_string(house) + ", " + std::to_string(apartment);
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    std::string city, street, line;
    int house, apartment;
    int countAddr = 0;

    std::ifstream file_In("in.txt");
    if (!file_In.is_open())
    {
        std::cerr << "Ошибка открытия файла. Проверьте указанный путь к файлу." << std::endl;
        return 1;
    }

    std::cout << "========= in.txt =========" << std::endl;
    std::cout << std::endl;

    while (std::getline(file_In, line))
    {
        std::cout << line << std::endl;
    }

    file_In.clear();
    file_In.seekg(0);

    file_In >> countAddr;

    Addresses** addresses = new Addresses * [countAddr];

    for (int i = 0; i < countAddr; ++i)
    {
        file_In >> city >> street >> house >> apartment;

        if (city.empty() || street.empty() || house <= 0 || apartment <= 0)
        {
            std::cerr << "Ошибка: нельзя создавать пустые адреса!!!" << std::endl;
            return 1;
        }

        addresses[i] = new Addresses(city, street, house, apartment);
    }

    file_In.close();

    Addresses* temp = addresses[0];
    addresses[0] = addresses[countAddr - 1];
    addresses[countAddr - 1] = temp;

    std::ofstream file_Out("out.txt");
    if (!file_Out.is_open())
    {
        std::cerr << "Ошибка открытия файла. Проверьте указанный путь к файлу." << std::endl;
        return 1;
    }

    std::cout << std::endl;
    std::cout << "======== out.txt ========" << std::endl;
    std::cout << std::endl;
    std::cout << countAddr << std::endl;

    file_Out << countAddr << std::endl;
    for (int i = 0; i < countAddr; ++i)
    {
        file_Out << addresses[i]->getAddressString() << std::endl;
        std::cout << addresses[i]->getAddressString() << std::endl;
    }

    file_Out.close();

    for (int i = 0; i < countAddr; ++i)
    {
        delete addresses[i];
    }
    delete[] addresses;

    return 0;
}
