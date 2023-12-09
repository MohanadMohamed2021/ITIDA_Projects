#include <QCoreApplication>
#include <QString>
#include <QTextStream>
#include <map>
#include <vector>
#include <QFile>
#include "qtextensions.h"
/************************Define counters**************************/
qint32 count_happy = 0;
qint32 count_sad = 0;
qint32 count_angry = 0;
qint32 count_calm = 0;
qint32 count_excited = 0;
qint32 count_bored = 0;

/************************Define enum**************************/
enum emotion
{
    happy,
    sad,
    angry,
    calm,
    excited,
    bored,
    wrong
};

/************************Define stdin & stdout**************************/
QTextStream qin(stdin);
QTextStream qout(stdout);

/************************Define map**************************/
std::map<emotion, std::vector<QString>> m;

/************************Define prototype of function**************************/
void Init_vector(std::vector<QString> &v, QString file_path);
void Display_vector(std::vector<QString> &v);
emotion Get_opposite_emotion(QString str);
void Quote_function(emotion emo, qint32 &counter);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /************************Define all files**************************/
    QString happy_file = "/home/mohanad/QT_Quote/happy.txt";
    QString sad_file = "/home/mohanad/QT_Quote/sad.txt";
    QString angry_file = "/home/mohanad/QT_Quote/angry.txt";
    QString calm_file = "/home/mohanad/QT_Quote/calm.txt";
    QString excited_file = "/home/mohanad/QT_Quote/excited.txt";
    QString bored_file = "/home/mohanad/QT_Quote/bored.txt";

    /************************Define all vectors**************************/
    std::vector<QString> happy_vector;
    std::vector<QString> sad_vector;
    std::vector<QString> angry_vector;
    std::vector<QString> calm_vector;
    std::vector<QString> excited_vector;
    std::vector<QString> bored_vector;

    /************************Init all vectors**************************/
    Init_vector(happy_vector, happy_file);
    Init_vector(sad_vector, sad_file);
    Init_vector(angry_vector, angry_file);
    Init_vector(calm_vector, calm_file);
    Init_vector(excited_vector, excited_file);
    Init_vector(bored_vector, bored_file);

    /************************Init map**************************/
    m.insert({emotion::happy, happy_vector});
    m.insert({emotion::sad, sad_vector});
    m.insert({emotion::angry, angry_vector});
    m.insert({emotion::calm, calm_vector});
    m.insert({emotion::excited, excited_vector});
    m.insert({emotion::bored, bored_vector});

    /************************handle project**************************/
    while (true)
    {
        qout << "enter emotion [happy,sad,angry,calm,excited,bored]" << Qt::endl;
        QString user_emotion = qin.readLine();
        system("clear");
        emotion real_emotion = Get_opposite_emotion(user_emotion);
        switch (real_emotion)
        {
        case emotion::happy:
        {
            Quote_function(emotion::happy, count_happy);
            break;
        }
        case emotion::sad:
        {
            Quote_function(emotion::sad, count_sad);
            break;
        }
        case emotion::angry:
        {
            Quote_function(emotion::angry, count_angry);
            break;
        }
        case emotion::calm:
        {
            Quote_function(emotion::calm, count_calm);
            break;
        }
        case emotion::excited:
        {
            Quote_function(emotion::excited, count_excited);
            break;
        }
        case emotion::bored:
        {
            Quote_function(emotion::bored, count_bored);
            break;
        }
        case emotion::wrong:
        {
            qout << "wrong emotion try again" << Qt::endl;
        }
        }
    }

    return a.exec();
}

void Init_vector(std::vector<QString> &v, QString file_path)
{
    QFile file(file_path);
    file.open(QFile::ReadOnly);
    QTextStream s(&file);
    while (!s.atEnd())
    {
        QString temp = s.readLine();
        v.push_back(temp);
    }
    file.close();
}

void Display_vector(std::vector<QString> &v)
{
    for (qint32 i = 0; i < v.size(); i++)
    {
        qout << v[i] << Qt::endl;
    }
}

emotion Get_opposite_emotion(QString str)
{
    if (str == "happy")
    {
        return emotion::sad;
    }
    else if (str == "sad")
    {
        return emotion::happy;
    }
    else if (str == "angry")
    {
        return emotion::calm;
    }
    else if (str == "calm")
    {
        return emotion::angry;
    }
    else if (str == "excited")
    {
        return emotion::bored;
    }
    else if (str == "bored")
    {
        return emotion::excited;
    }
    else
    {
        return emotion::wrong;
    }
}

void Quote_function(emotion emo, qint32 &counter)
{
    auto vec = m[emo];
    qout << vec[counter] << Qt::endl;
    if (counter == 6)
    {
        counter = 0;
    }
    else
    {
        counter++;
    }
}
