#include "database.h"

#include "QFileInfo"
#include "QDir"

bool Database::readStudentData(QString inPath,Student *setStudent)
{
    QFile file(inPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
    file.close();

    setStudent->name = obj["name"].toString();
    setStudent->id = QFileInfo(inPath).baseName();
    QJsonArray examArray = obj["data"].toArray();
    for(unsigned int i1=0;i1<examArray.count();i1++)
    {
        Exam newExam;
        QJsonArray subjectArray = examArray[i1].toArray();
        for(unsigned int i2=0;i2<subjectArray.count();i2++)
        {

            Subject newSub(
                subjectArray[i2][0].toInt(),
                subjectArray[i2][1].toInt(),
                subjectArray[i2][2].toDouble(),
                subjectArray[i2][3].toDouble());
            newExam.subjects.push_back(newSub);
        }
        setStudent->exams.push_back(newExam);
    }
    return true;
}

bool Database::readBasicData()
{
    QFile file(QDir::cleanPath(path+"/basic.json"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
    file.close();

    QJsonArray array1 = obj["subjects"].toArray();
    subjects.clear();
    subjects.shrink_to_fit();
    for(char i1=0;i1<array1.count();i1++)
    {
        subjects<<array1[i1].toString();
    }

    QJsonArray array2 = obj["exams"].toArray();
    exams.clear();
    exams.shrink_to_fit();
    for(char i1=0;i1<array2.count();i1++)
    {
        exams<<array2[i1].toString();
    }
    return true;
}

bool Database::writeStudentData(Student *setStudent)
{
    QFile file(QDir::cleanPath(path+"/students_data/"+setStudent->id+".json"));
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    QJsonObject root;
    root.insert("name",setStudent->name);

    QJsonArray examArray;
    for(unsigned int i1=0;i1<setStudent->exams.size();i1++)
    {
        QJsonArray subjectArray;
        for(unsigned int i2=0;i2<setStudent->exams[i1].subjects.size();i2++)
        {
            QJsonArray singleSubjectArray;
            singleSubjectArray.append(setStudent->exams[i1].subjects[i2].goalRank);
            singleSubjectArray.append(setStudent->exams[i1].subjects[i2].realRank);
            singleSubjectArray.append(setStudent->exams[i1].subjects[i2].toGoalScore());
            singleSubjectArray.append(setStudent->exams[i1].subjects[i2].toRealScore());
            subjectArray.append(singleSubjectArray);
        }
        examArray.append(subjectArray);
    }
    root.insert("data",examArray);

    QJsonDocument doc ;
    doc.setObject(root);
    file.write(doc.toJson());
    file.close();

    return true;
}

bool Database::writeBasic()
{
    QFile file(QDir::cleanPath(path+"/basic.json"));
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    QJsonObject root;
    root.insert("subjects",QJsonArray::fromStringList(subjects));
    root.insert("exams",QJsonArray::fromStringList(exams));

    QJsonDocument doc ;
    doc.setObject(root);
    file.write(doc.toJson());
    file.close();

    return true;
}

bool Database::readAll()
{
    if(!readBasicData())
        return false;

    QDir dataDir(QDir::cleanPath(path+"/students_data/"));
    QStringList studentList = dataDir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    students.clear();
    students.shrink_to_fit();
    for(int i1=0;i1<studentList.count();i1++)
    {
        Student stu;
        if(!readStudentData(QDir::cleanPath(path+"/students_data/"+studentList[i1]),&stu))
            return false;
        students.push_back(stu);
    }

    return true;
}

bool Database::writeAll()
{
    writeBasic();
    for(unsigned int i1=0;i1<students.size();i1++)
    {
        if(!writeStudentData(&students[i1]))
            return false;
    }

    return true;
}

void Database::f_dataChanged(int stu,int exam,int sub,Subject newData)
{
    students[stu].exams[exam].subjects[sub].goalRank = newData.goalRank;
    students[stu].exams[exam].subjects[sub].realRank = newData.realRank;
    students[stu].exams[exam].subjects[sub].goalScore = newData.goalScore;
    students[stu].exams[exam].subjects[sub].realScore = newData.realScore;
}

void Database::deleteStudent(QString id)
{
    for(unsigned int i=0;i<students.size();i++)
    {
        if(students[i].id==id)
        {
            students.erase(students.begin()+i);
            break;
        }
    }
}

void Database::deleteExam(QString name)
{
    unsigned int index = 0;
    for(;index<exams.count();index++)
    {
        if(exams[index]==name)
        {
            exams.erase(exams.begin()+index);
            break;
        }
    }
    for(unsigned int i1=0;i1<students.size();i1++)
    {
        students[i1].exams.erase(students[i1].exams.begin()+index);
    }
}

void Database::deleteSubject(QString name)
{
    unsigned int index = 0;
    for(;index<subjects.count();index++)
    {
        if(subjects[index]==name)
        {
            subjects.erase(subjects.begin()+index);
            break;
        }
    }
    for(unsigned int i1=0;i1<students.size();i1++)
    {
        for(unsigned int i2=0;i2<exams.size();i2++)
        {
            students[i1].exams[i2].subjects.erase(students[i1].exams[i2].subjects.begin()+index);
        }
    }
}

Database::Database(QString setPath)
{
    path = setPath;
}

Database::Database()
{
    path = "";
}
