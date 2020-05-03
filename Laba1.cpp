#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <direct.h>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <string>


using namespace std;

int getValueInt(string msg);
float getValueFloat(string msg);
bool getValueBool(string msg);
string getValueString(string msg, int minSize);

/// <summary>
/// Базовый класс описывающий абстрактную модель инструмента
/// </summary>
class Instrument {
private:
    //Номер инструмента
    int _id = 0;
    //Название инструмента
    string _name;
    //Цена инструмента
    float _price;
    //Цвет инструмента
    string _color;
public:
    static string type;
    Instrument();
    Instrument(int id, string name, float price, string color);

    int getId();
    string getName();
    float getPrice();
    string getColor();

    void setId(int id);
    void setName(string name);
    void setPrice(float price);
    void setColor(string color);

    void Print();
};
string Instrument::type = "1";
/// <summary>
/// Класс описывающий модель струнного инструмента
/// </summary>
class StringInstrument: public Instrument
{
private:
    //Количество струн
    int _stringCount = 0;
    //Материал струн
    string _stringMaterial = "";

public:
    //Код типа струнного инструмента
    static string type;
    StringInstrument();
    StringInstrument(Instrument inst, int stringCount, string stringMaterial);
    void Print();

    int getStringCount();
    void setStringCount(int stringCount);

    string getStringMaterial();
    void setStringMaterial(string stringMaterial);

};
string StringInstrument::type = Instrument::type + "1";
/// <summary>
/// Класс описывающий модель клавишного инструмента
/// </summary>
class KeysInstrument : public Instrument
{
private:
    //Количество клавиш
    int _keyCount = 0;
    //Молоточковая механика
    bool _hammerMechanics = false;

    //Количество тембров
    int _voiceCount = false;


public:
    static string type;
    KeysInstrument();
    KeysInstrument(Instrument inst, int keyCount, bool hammerMechanics, int voiceCount);
    void Print();

    int getKeyCount();
    void setKeyCount(int keyCount);

    bool getHammerMechanics();
    void setHammerMechanics(bool hammerMechanics);

    int getVoiceCount();
    void setVoiceCount(int voiceCount);

};
string KeysInstrument::type = Instrument::type + "2";
/// <summary>
/// Класс описывающий модель струнного акустического инструмента
/// </summary>
class AcousticStringInstrument : public StringInstrument
{
private:
    //Мензура(мм)
    int _mensura = 0;
    //Колки(открытые/закрытые)
    bool _tuningPeg = false;
    
public:
    static string type;
    AcousticStringInstrument();
    AcousticStringInstrument(StringInstrument inst, int mensura, bool tuningPeg);

    void setMensura(int mensura);
    int getMensura();

    void setTuningPeg(bool tuningPeg);
    bool getTuningPeg();

    void Print();

};
string AcousticStringInstrument::type = StringInstrument::type + "1";
/// <summary>
/// Класс описывающий модель струнного электроинструмента
/// </summary>
class ElectroStringInstrument : public StringInstrument
{
private:
    int _countVolumeController = 0;
    int _countToneController = 0;

public:
    static string type;
    ElectroStringInstrument();
    ElectroStringInstrument(StringInstrument  inst, int countVolumeController, int countToneController);

    void setCountVolumeController(int count);
    int getCountVolumeController();

    void setCountToneController(int count);
    int getCountToneController();

    void Print();

};
string ElectroStringInstrument::type = StringInstrument::type + "2";
class Shop
{
private:
    string _shopName;
    string _acousticStringInstrumentPath;
    string _keysInstrumentPath;
    string _electroStringInstrumentPath;

    void SaveAcousticStringInstrument();
    void SaveElectroStringInstrument();
    void SaveKeysInstrument();

    void LoadKeysInstrument();
    void LoadAcousticStringInstrument();
    void LoadElectroStringInstrument();

public:
    Shop(string name);
    //Вектор указателей на объект класса Instrument
    vector<Instrument*> instrumentVector;
    //Вектор указателей на объект класса StringInstrument
    vector<StringInstrument*> stringInstrumentVector;
    //Вектор указателей на объект класса KeysInstrument
    vector<KeysInstrument*> keysInstrumentVector;
    //Вектор указателей на объект класса AcousticInstrument
    vector<AcousticStringInstrument*> acousticStringInstrumentVector;
    //Вектор указателей на объект класса AcousticInstrument
    vector<ElectroStringInstrument*> electroStringInstrumentVector;
    template<class T>
    void operator+=(T* instrument);
    void Print();
    
    void PrintKeysInstrument();
    void PrintAcousticStringInstrument();
    void PrintElectroStringInstrument();

    void Save();
    void Load();

    void RemoveInstrumentId(int id);

    KeysInstrument* promtAddKeysInstrument();
    AcousticStringInstrument* promtAddAcousticStringInstrument();
    ElectroStringInstrument* promtAddElectroStringInstrument();


};

int printFrame1();
int printInstrumentChoice();

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Shop shop = Shop("Магазин");

    shop.Load();
    

    while (true)
    {
        int mode = printFrame1();

        switch (mode)
        {
        case 0:
            shop.Save();
            return 0;
            break;
        case 1:
            system("cls");
            shop.Print();
            system("pause");
            break;
        case 2:
            system("cls");
            shop.PrintKeysInstrument();
            system("pause");
            break;
        case 3:
            system("cls");
            shop.PrintAcousticStringInstrument();
            system("pause");
            break;
        case 4:
            system("cls");
            shop.PrintElectroStringInstrument();
            system("pause");
            break;
        case 5:
            system("cls");
            int inst;
            inst = printInstrumentChoice();
            switch (inst)
            {
            case 0:
                break;
            case 1:
                shop += shop.promtAddKeysInstrument();
                system("pause");
                break;
            case 2:
                shop += shop.promtAddAcousticStringInstrument();
                system("pause");
                break;
            case 3:
                shop += shop.promtAddElectroStringInstrument();
                system("pause");
                break;
            default:
                break;
            }
            break;
        case 6:
            system("cls");
            shop.RemoveInstrumentId(getValueInt("ID инструмента для удаления"));
            system("pause");
            break;
        default:
            break;
        }
    }
    




    shop.Save();


    
}
/// <summary>Функция запроса целочисленного значения от пользователя</summary>
/// <param name="msg">Сообщение запроса</param>
int getValueInt(string msg)
{
    while (true)
    {
        cout << msg << ":";
        int a;
        cin >> a;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
        }
        else return a;
    }
}
/// <summary>Функция запроса вещественного значения от пользователя</summary>
/// <param name="msg">Сообщение запроса</param>
float getValueFloat(string msg)
{
    for (;;)
    {
        cout << msg << ":";
        float a;
        cin >> a;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
        }
        else return a;
    }
}
bool getValueBool(string msg)
{
    int temp = -1;
    while (!(temp == 1 || temp == 0))	temp = getValueInt(msg);
    return static_cast<bool>(temp);;
}
string getValueString(string msg, int minSize)
{
    string temp = "";
    while (temp == "" || temp.length() < minSize)
    {
        cout << msg << ":";
        //cin >> temp;
        cin.ignore(32767, '\n');
        getline(cin, temp);
        //cin.ignore(32767, '\n');
    }
    for (auto& it : temp)
    {
        if (it == ' ') it = '_';
    }
    return temp;
}
int printFrame1()
{
    system("cls");
    cout << "1.Вывести все инструменты" << endl;
    cout << "2.Вывести клавишные инструменты" << endl;
    cout << "3.Вывести акустические гитары" << endl;
    cout << "4.Вывести электрогитары" << endl;
    cout << "5.Добавить инструмент" << endl;
    cout << "6.Удалить инструмент" << endl;
    cout << "0.Выход" << endl;
    int mode = - 1;
    while (mode < 0 || mode > 6)mode = getValueInt("Выберите вариант");
    return mode;
}
int printInstrumentChoice()
{
    system("cls");
    cout << "1.Клавишные" << endl;
    cout << "2.Акустические гитары" << endl;
    cout << "3.Электрогитары" << endl;
    cout << "0.Назад" << endl;

    int mode = -1;
    while (mode < 0 || mode > 3)mode = getValueInt("Выберите вариант");
    return mode;
}
/// <summary>
///Конструктор по умолчанию базового класса Instrument
///</summary>
Instrument::Instrument()
{
    setId(0);
    setName("None");
    setPrice(0.00f);
    setColor("None");
}
/// <summary>Конструктор базового класса Instrument</summary>
/// <param name="name">Название инструмента</param>
/// <param name="price">Цена инструмента</param>
/// <param name="color">Цвет инструмента</param>
Instrument::Instrument(int id, string name, float price, string color)
{
    setId(id);
    setName(name);
    setPrice(price);
    setColor(color);
}
/// <summary>
/// Метод возвращающий номер инструмента
///  </summary>
int Instrument::getId()
{
    return _id;
}
/// <summary>
/// Метод устанавливающий номер инструмента
///  </summary>
/// <param name="id">Номер инструмента</param>
void Instrument::setId(int id)
{
    _id = id;
}
/// <summary>
/// Метод возвращающий название инструмента
/// </summary>
string Instrument::getName()
{
    return _name;
}
/// <summary>
/// Метод возвращающий стоимость инструмента
/// </summary>
float Instrument::getPrice()
{
    return _price;
}
/// <summary>
/// Метод возвращающий цвет инструмента
/// </summary>
string Instrument::getColor()
{
    return _color;
}
/// <summary>Метод устанавливающий название инструмента</summary>
/// <param name="name">Название инструмента</param>
void Instrument::setName(string name)
{
    _name = name;
}
/// <summary>Метод устанавливающий стоимость инструмента</summary>
/// <param name="name">Стоимость инструмента</param>
void Instrument::setPrice(float price)
{
    if (price >= 0) _price = price;
    else _price = 0.00f;
}
/// <summary>Метод устанавливающий цвет инструмента</summary>
/// <param name="name">Цвет инструмента</param>
void Instrument::setColor(string color)
{
    _color = color;
}
/// <summary>
/// Метод вывода информации об инструменте на экран
/// </summary>
void Instrument::Print()
{
    if (type == "1")
    {
        cout << "ID -> " << getId() << endl;
        string temp_name = getName();
        for (auto &it : temp_name)
        {
            if (it == '_')it = ' ';
        }
        cout << "Название -> " << temp_name << endl;
        cout << "Цена -> " << fixed << setprecision(2) << getPrice() << " руб." << endl;
        string temp_color = getColor();
        for (auto& it : temp_color)
        {
            if (it == '_')it = ' ';
        }
        cout << "Цвет -> " << temp_color << endl;
    }
}
/// <summary>
///Конструктор по умолчанию класса StringInstrument
///</summary>
StringInstrument::StringInstrument()
{
    setStringCount(0);
    setStringMaterial("None");
}
/// <summary>
/// Класс описывающий модель струнного инструмента StringInstrument наследуемого от базового класса Instrument
/// </summary>
/// <param name="inst"> Экземпляр класса-родителя Instrument </param>
/// <param name="stringCount"> Количество струн инструмента </param>
/// <param name="stringMaterial"> Материал струн инструмента </param>
StringInstrument::StringInstrument(Instrument inst, int stringCount, string stringMaterial) :Instrument(inst)
{
    setStringCount(stringCount);
    setStringMaterial(stringMaterial);
};
/// <summary>
/// Метод вывода информации о струнном инструменте на экран
/// </summary>
void StringInstrument::Print()
{
    if (type == "11")
    {
        Instrument::Print();
        cout << "Кол-во струн -> " << getStringCount() << " шт." << endl;
        string temp_stringMaterial = getStringMaterial();
        for (auto& it : temp_stringMaterial)
        {
            if (it == '_')it = ' ';
        }
        cout << "Материал струн -> " << temp_stringMaterial << endl;
    }
}
/// <summary>
/// Метод возвращающий количество струн
/// </summary>
int StringInstrument::getStringCount()
{
    return _stringCount;
}
/// <summary>
/// Метод устанавливающий количество струн
/// </summary>
void StringInstrument::setStringCount(int stringCount)
{
    _stringCount = stringCount;
}
/// <summary>
/// Метод возвращающий материал струн
/// </summary>
string StringInstrument::getStringMaterial()
{
    return _stringMaterial;
}
/// <summary>
/// Метод устанавливающий материал струн
/// </summary>
void StringInstrument::setStringMaterial(string stringMaterial)
{
    _stringMaterial = stringMaterial;
}
/// <summary>
///Конструктор по умолчанию класса KeysInstrument
///</summary>
KeysInstrument::KeysInstrument()
{
}
/// <summary>
/// Класс описывающий модель ударного инструмента KeyInstrument наследуемого от базового класса Instrument
/// </summary>
/// <param name="inst"> Экземпляр класса-родителя Instrument </param>
/// <param name="keyCount"> Количество клавиш инструмента </param>
/// <param name="hammerMechanics"> Наличие молоточковой механики> </param>
/// <param name="voiceCount"> Количество тембров инструмента> </param>
KeysInstrument::KeysInstrument(Instrument inst, int keyCount, bool hammerMechanics, int voiceCount) :Instrument(inst)
{
    setKeyCount(keyCount);
    setHammerMechanics(hammerMechanics);
    setVoiceCount(voiceCount);
}
/// <summary>
/// Метод вывода информации о клавишном инструменте на экран
/// </summary>
void KeysInstrument::Print()
{
    if(type == "12")
    { 
        Instrument::Print();
        cout << "Кол-во клавиш -> " << getKeyCount() << " шт." << endl;
        if(getHammerMechanics())cout << "Молоточковая механика -> Есть" << endl;
        else cout << "Молоточковая механика -> Нет" << endl;
        cout << "Кол-во тембров -> " << getVoiceCount() << endl;
        cout << "-----------------------------------------------------------------" << endl;
    }
}
/// <summary>
/// Метод возвращающий количество клавиш инструмента
/// </summary>
int KeysInstrument::getKeyCount()
{
    return _keyCount;
}
/// <summary>
/// Метод устанавливающий количество клавиш инструмента
/// </summary>
/// <param name="keyCount"> Количество клавиш инструмента </param>
void KeysInstrument::setKeyCount(int keyCount)
{
    _keyCount = keyCount;
}
/// <summary>
/// Метод возвращающий наличие молоточковой механики инструмента
/// </summary>
bool KeysInstrument::getHammerMechanics()
{
    return _hammerMechanics;
}
/// <summary>
/// Метод устанавливающий наличие молоточковой механики инструмента
/// </summary>
/// <param name="hammerMechanics"> Наличие молоточковой механики </param>
void KeysInstrument::setHammerMechanics(bool hammerMechanics)
{
    _hammerMechanics = hammerMechanics;
}
/// <summary>
/// Метод возвращающий количество тембров инструмента
/// </summary>
int KeysInstrument::getVoiceCount()
{
    return _voiceCount;
}
/// <summary>
/// Метод устанавливающий количество тембров инструмента
/// </summary>
/// <param name="voiceCount"> Количество тембров </param>
/// <return> Kopa </return>
void KeysInstrument::setVoiceCount(int voiceCount)
{
    _voiceCount = voiceCount;
}
/// <summary>
///Конструктор по умолчанию класса AcousticStringInstrument
///</summary>
AcousticStringInstrument::AcousticStringInstrument()
{
}
/// <summary>
/// Класс описывающий модель акустического струнного инструмента AcousticStringInstrument наследуемого от класса StringInstrument
/// </summary>
/// <param name="inst"> Экземпляр класса-родителя Instrument </param>
/// <param name="mensura"> Размер мензуры(мм) </param>
/// <param name="tuningPeg"> Колки инструмента(true открытые | false - закрытые) </param>
AcousticStringInstrument::AcousticStringInstrument(StringInstrument inst, int mensura, bool tuningPeg) :StringInstrument(inst)
{
    setMensura(mensura);
    setTuningPeg(tuningPeg);
}
/// <summary>
/// Метод устанавливающий размер мензуры инструмента
/// </summary>
/// <param name="mensura"> Размер мензуры(мм) </param>
void AcousticStringInstrument::setMensura(int mensura)
{
    if (mensura < 1)
    {
        _mensura = 1;
    }
    else
    {
        _mensura = mensura;
    }
}
/// <summary>
/// Метод возвращающий размер мензуры инструмента в мм.
/// </summary>
int AcousticStringInstrument::getMensura()
{
    return _mensura;
}
/// <summary>
/// Метод устанавливающий тип колок инструмента(открытые/закрытые)
/// </summary>
/// <param name="mensura"> Колки инструмента(true открытые | false - закрытые) </param>
void AcousticStringInstrument::setTuningPeg(bool tuningPeg)
{
    _tuningPeg = tuningPeg;
}
/// <summary>
/// Метод возвращающий тип колок инструмента(открытые/закрытые)
/// </summary>
bool AcousticStringInstrument::getTuningPeg()
{
    return _tuningPeg;
}
/// <summary>
/// Метод вывода информации о акустическом струнном инструменте
/// </summary>
void AcousticStringInstrument::Print()
{
    if (type == "111") 
    {
        StringInstrument::Print();
        cout << "Мензура -> " << getMensura() << " мм." << endl;
        if (getTuningPeg())cout << "Колки -> Открытые" << endl;
        else cout << "Колки -> Закрытые" << endl;
        cout << "-----------------------------------------------------------------" << endl;
    }
}
/// <summary>
/// Перегруженный оператор += добавляющий инструмент в магазин
/// </summary>
/// <param name="instrument"> Экземпляр класса Instrument или его потомков </param>
template<class T>
/// <summary>
/// <param name="T"> Экземпляр класса Instrument или его потомков </param>
/// </summary>
void Shop::operator+=(T* instrument)
{
    if (instrument->type == "1") instrumentVector.push_back(instrument);
    else if (instrument->type == "11") stringInstrumentVector.push_back((StringInstrument*)instrument);
    else if (instrument->type == "12") keysInstrumentVector.push_back((KeysInstrument*)instrument);
    else if (instrument->type == "111")  acousticStringInstrumentVector.push_back((AcousticStringInstrument*)instrument);
    else if (instrument->type == "112")  electroStringInstrumentVector.push_back((ElectroStringInstrument*)instrument);
}
Shop::Shop(string name)
{
    _shopName = name;
    char buff[100];
    char* temp = _getcwd(buff, sizeof(buff));
    _acousticStringInstrumentPath = buff;
    _acousticStringInstrumentPath += "\\acousticStringInstruments.txt";
    for (size_t i = 0; i < _acousticStringInstrumentPath.size(); i++)
    {
        if (_acousticStringInstrumentPath[i] == '\\')
        {
            _acousticStringInstrumentPath.insert(i, "\\");
            i++;
        }
    }
    buff[0] = '\0';
    temp = _getcwd(buff, sizeof(buff));
    _electroStringInstrumentPath = buff;
    _electroStringInstrumentPath += "\\electroStringInstrument.txt";
    for (size_t i = 0; i < _electroStringInstrumentPath.size(); i++)
    {
        if (_electroStringInstrumentPath[i] == '\\')
        {
            _electroStringInstrumentPath.insert(i, "\\");
            i++;
        }
    }
    buff[0] = '\0';
    temp = _getcwd(buff, sizeof(buff));
    _keysInstrumentPath = buff;
    _keysInstrumentPath += "\\keysInstruments.txt";
    for (size_t i = 0; i < _keysInstrumentPath.size(); i++)
    {
        if (_keysInstrumentPath[i] == '\\')
        {
            _keysInstrumentPath.insert(i, "\\");
            i++;
        }
    }

}
/// <summary>
/// Метод вывода всех инструментов на экран
/// </summary>
void Shop::Print()
{
    if (instrumentVector.size() != 0)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||Инструменты|||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        for (auto it : instrumentVector)
        {
            it->Print();
        }
    }
    if (keysInstrumentVector.size() != 0)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||Клавишные нструменты||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        for (auto it : keysInstrumentVector)
        {
            it->Print();
        }
    }
    if (stringInstrumentVector.size() != 0)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||Струнные нструменты|||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        for (auto it : stringInstrumentVector)
        {
            it->Print();
        }
    }
    if (acousticStringInstrumentVector.size() != 0)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "||||||||||||||||||||||||Акустические нструменты||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        for (auto it : acousticStringInstrumentVector)
        {
            it->Print();
        }
    }
    if (electroStringInstrumentVector.size() != 0)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "||||||||||||||||||||||||||Электроинструменты|||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        for (auto it : electroStringInstrumentVector)
        {
            it->Print();
        }
    }
}
void Shop::PrintKeysInstrument()
{
    if (keysInstrumentVector.size() != 0)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||Клавишные нструменты||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        for (auto it : keysInstrumentVector)
        {
            it->Print();
        }
    }
}
void Shop::PrintAcousticStringInstrument()
{
    if (acousticStringInstrumentVector.size() != 0)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "||||||||||||||||||||||||Акустические нструменты||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        for (auto it : acousticStringInstrumentVector)
        {
            it->Print();
        }
    }
}
void Shop::PrintElectroStringInstrument()
{
    if (electroStringInstrumentVector.size() != 0)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "||||||||||||||||||||||||||Электроинструменты|||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        for (auto it : electroStringInstrumentVector)
        {
            it->Print();
        }
    }
}
void Shop::Save()
{
    SaveAcousticStringInstrument();
    SaveElectroStringInstrument();
    SaveKeysInstrument();
}
void Shop::Load()
{
    LoadAcousticStringInstrument();
    LoadElectroStringInstrument();
    LoadKeysInstrument();
}
void Shop::RemoveInstrumentId(int id)
{
    bool once = true;
    for (int i = 0; i < keysInstrumentVector.size(); i++)
    {
        if (keysInstrumentVector[i]->getId() == id)
        {
            if(once)cout << "Удалено:" << endl;
            keysInstrumentVector[i]->Print();
            keysInstrumentVector.erase(keysInstrumentVector.begin() + i);
            i = 0;
            once = false;
        }
    }
    for (int i = 0; i < acousticStringInstrumentVector.size(); i++)
    {
        if (acousticStringInstrumentVector[i]->getId() == id)
        {
            if (once)cout << "Удалено:" << endl;
            acousticStringInstrumentVector[i]->Print();
            acousticStringInstrumentVector.erase(acousticStringInstrumentVector.begin() + i);
            i = 0;
            once = false;
        }
    }

    for (int i = 0; i < electroStringInstrumentVector.size(); i++)
    {
        if (electroStringInstrumentVector[i]->getId() == id)
        {
            if (once)cout << "Удалено:" << endl;
            cout << "Удалено:" << endl;
            electroStringInstrumentVector[i]->Print();
            electroStringInstrumentVector.erase(electroStringInstrumentVector.begin() + i);
            i = 0;
            once = false;
        }
    }
    if (once)cout << "Инструментов с таким ID не найдено" << endl;
}
KeysInstrument* Shop::promtAddKeysInstrument()
{
    int id = 0;
    string name = "";
    float price = 0;
    string color = "";
    int keyCount = 0;
    bool hammerMechanics;
    int voiceCount;

    id = getValueInt("ID инструмента");
    name = getValueString("Название инструмента", 4);
    price = getValueFloat("Стоимость инструмента");
    color = getValueString("Цвет инструмента", 3);
    keyCount = getValueInt("Количество струн");
    hammerMechanics = getValueBool("Молоточковая механика(1 - есть/ 0 - нет)");
    voiceCount = getValueInt("Количество тембров");

    return new KeysInstrument(Instrument(id, name, price, color), keyCount, hammerMechanics, voiceCount);
}
AcousticStringInstrument* Shop::promtAddAcousticStringInstrument()
{
    int id = 0;
    string name = "";
    float price = 0;
    string color = "";
    int stringCount = 0;
    string stringMaterial = "None";
    int mensura = 0;
    bool tuningPeg = false;

    id = getValueInt("ID инструмента");
    name = getValueString("Название инструмента", 4);
    price = getValueFloat("Стоимость инструмента");
    color = getValueString("Цвет инструмента", 3);
    stringCount = getValueInt("Количество струн");
    stringMaterial = getValueString("Материал струн", 4);
    do { mensura = getValueInt("Размер мензуры(мм)"); } while (mensura < 10);
    tuningPeg = getValueBool("Колки(0 - закрытые| 1 - открытые");

    return new AcousticStringInstrument(StringInstrument(Instrument(id, name, price, color), stringCount, stringMaterial), mensura, tuningPeg);
}
ElectroStringInstrument* Shop::promtAddElectroStringInstrument()
{
    int id = 0;
    string name = "";
    float price = 0;
    string color = "";
    int stringCount = 0;
    string stringMaterial = "None";
    int countVolumeController;
    int countToneController;

    id = getValueInt("ID инструмента");
    name = getValueString("Название инструмента", 4);
    price = getValueFloat("Стоимость инструмента");
    color = getValueString("Цвет инструмента", 3);
    stringCount = getValueInt("Количество струн");
    stringMaterial = getValueString("Материал струн", 4);
    countVolumeController = getValueInt("Регуляторов громкости");
    countToneController = getValueInt("Регуляторов тона");

    return new ElectroStringInstrument(StringInstrument(Instrument(id, name, price, color), stringCount, stringMaterial), countVolumeController, countToneController);
}
void Shop::SaveAcousticStringInstrument()
{
    std::ofstream fp;
    fp.open(_acousticStringInstrumentPath, std::ios_base::trunc | std::ios::out);
    for (size_t i = 0; i < Shop::acousticStringInstrumentVector.size(); i++)
    {
        fp << acousticStringInstrumentVector.at(i)->getId();
        fp << " ";
        fp << acousticStringInstrumentVector.at(i)->getName();
        fp << " ";
        fp << acousticStringInstrumentVector.at(i)->getPrice();
        fp << " ";
        fp << acousticStringInstrumentVector.at(i)->getColor();
        fp << " ";
        fp << acousticStringInstrumentVector.at(i)->getStringCount();
        fp << " ";
        fp << acousticStringInstrumentVector.at(i)->getStringMaterial();
        fp << " ";
        fp << acousticStringInstrumentVector.at(i)->getMensura();
        fp << " ";
        fp << acousticStringInstrumentVector.at(i)->getTuningPeg();
        
        if (i != acousticStringInstrumentVector.size()-1)
        {
            fp << std::endl;
        }        
    }
}
void Shop::SaveElectroStringInstrument()
{
    std::ofstream fp;
    fp.open(_electroStringInstrumentPath, std::ios_base::trunc | std::ios::out);
    for (size_t i = 0; i < Shop::electroStringInstrumentVector.size(); i++)
    {
        fp << electroStringInstrumentVector.at(i)->getId();
        fp << " ";
        fp << electroStringInstrumentVector.at(i)->getName();
        fp << " ";
        fp << electroStringInstrumentVector.at(i)->getPrice();
        fp << " ";
        fp << electroStringInstrumentVector.at(i)->getColor();
        fp << " ";
        fp << electroStringInstrumentVector.at(i)->getStringCount();
        fp << " ";
        fp << electroStringInstrumentVector.at(i)->getStringMaterial();
        fp << " ";
        fp << electroStringInstrumentVector.at(i)->getCountVolumeController();
        fp << " ";
        fp << electroStringInstrumentVector.at(i)->getCountToneController();
        
        if (i != electroStringInstrumentVector.size() - 1)
        {
            fp << std::endl;
        }
        
    }
}
void Shop::SaveKeysInstrument()
{
    std::ofstream fp;
    fp.open(_keysInstrumentPath, std::ios_base::trunc | std::ios::out);
    for (size_t i = 0; i < keysInstrumentVector.size(); i++)
    {
        fp << keysInstrumentVector.at(i)->getId();
        fp << " ";
        fp << keysInstrumentVector.at(i)->getName();
        fp << " ";
        fp << keysInstrumentVector.at(i)->getPrice();
        fp << " ";
        fp << keysInstrumentVector.at(i)->getColor();
        fp << " ";
        fp << keysInstrumentVector.at(i)->getKeyCount();
        fp << " ";
        fp << keysInstrumentVector.at(i)->getHammerMechanics();
        fp << " ";
        fp << keysInstrumentVector.at(i)->getVoiceCount();
        
        if (i != keysInstrumentVector.size() - 1)
        {
            fp << std::endl;
        }
        else
        {
            return;
        }
    }
}
void Shop::LoadKeysInstrument()
{
    keysInstrumentVector.clear();

    int id = 0;
    string name = "None";
    float price = 0;
    string color = "None";
    int keyCount = 0;
    bool hammerMechanics;
    int voiceCount;

    ifstream fp;
    
    fp.open(_keysInstrumentPath);

    while (!fp.eof())
    {
        fp >> id;
        fp >> name;
        fp >> price;
        fp >> color;
        fp >> keyCount;
        fp >> hammerMechanics;
        fp >> voiceCount;
        auto temp = new KeysInstrument(Instrument(id, name, price, color), keyCount, hammerMechanics, voiceCount);
        keysInstrumentVector.push_back(temp);
    }
    fp.close();
    
}
void Shop::LoadAcousticStringInstrument()
{
    acousticStringInstrumentVector.clear();

    int id = 0;
    string name = "None";
    float price = 0;
    string color = "None";
    int stringCount = 0;
    string stringMaterial = "None";
    int mensura = 0;
    bool tuningPeg = false;

    ifstream fp;

    fp.open(_acousticStringInstrumentPath);
    
    while (!fp.eof())
    {
        fp >> id;
        fp >> name;
        fp >> price;
        fp >> color;
        fp >> stringCount;
        fp >> stringMaterial;
        fp >> mensura;
        fp >> tuningPeg;

        auto temp = new AcousticStringInstrument(StringInstrument(Instrument(id, name, price, color), stringCount, stringMaterial), mensura, tuningPeg);

        acousticStringInstrumentVector.push_back(temp);
    }
    fp.close();
}
void Shop::LoadElectroStringInstrument()
{
    electroStringInstrumentVector.clear();

    int id = 0;
    string name = "None";
    float price = 0;
    string color = "None";
    int stringCount = 0;
    string stringMaterial = "None";
    int countVolumeController;
    int countToneController;

    ifstream fp;

    fp.open(_electroStringInstrumentPath);

    while (!fp.eof())
    {
        fp >> id;
        fp >> name;
        fp >> price;
        fp >> color;
        fp >> stringCount;
        fp >> stringMaterial;
        fp >> countVolumeController;
        fp >> countToneController;

        auto temp = new ElectroStringInstrument(StringInstrument(Instrument(id, name, price, color), stringCount, stringMaterial), countVolumeController, countToneController);

        electroStringInstrumentVector.push_back(temp);
    }
    fp.close();
}
/// <summary>
///Конструктор по умолчанию класса ElectroStringInstrument
///</summary>
ElectroStringInstrument::ElectroStringInstrument()
{
}
/// <summary>
/// Класс описывающий модель электрического струнного инструмента ElectroStringInstrument наследуемого от класса StringInstrument
/// </summary>
/// <param name="inst"> Экземпляр класса-родителя Instrument </param>
/// <param name="countVolumeController"> Количество регуляторов громкости </param>
/// <param name="countToneController"> Количество регуляторов тона </param>
ElectroStringInstrument::ElectroStringInstrument(StringInstrument inst, int countVolumeController, int countToneController) :StringInstrument(inst)
{
    setCountVolumeController(countVolumeController);
    setCountToneController(countToneController);
}
/// <summary>
/// Метод устанавливающий количество регуляторов громкости
/// </summary>
/// <param name="count"> Количество регуляторов громкости </param>
void ElectroStringInstrument::setCountVolumeController(int count)
{
    if (count <= 0)
    {
        _countVolumeController = 1;
    }
    else
    {
        _countVolumeController = count;
    }
    
}
/// <summary>
/// Метод возвращающий количество регуляторов громкости
/// </summary>
int ElectroStringInstrument::getCountVolumeController()
{
    return _countVolumeController;
}
/// <summary>
/// Метод устанавливающий количество регуляторов тона
/// </summary>
/// <param name="count"> Количество регуляторов тона </param>
void ElectroStringInstrument::setCountToneController(int count)
{
    if (count <= 0)
    {
        _countToneController = 1;
    }
    else
    {
        _countToneController = count;
    }
}
/// <summary>
/// Метод возвращающий количество регуляторов тона
/// </summary>
int ElectroStringInstrument::getCountToneController()
{
    return _countToneController;
}
/// <summary>
/// Метод вывода информации о электрическом струнном инструменте
/// </summary>
void ElectroStringInstrument::Print()
{

    if (type == "112")
    {
        StringInstrument::Print();
        cout << "Регуляторов громкости -> " << getCountVolumeController() << " шт." << endl;
        cout << "Регуляторов тона -> " << getCountToneController() << endl;
        cout << "-----------------------------------------------------------------" << endl;
    }
}
