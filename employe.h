typedef struct employe//定义员工数据结构体
{
	int iNum;
	char cName[9];
	char cSex[3];
	int iAge;
	char cEdu[5];//学历
	int iSalary;//工资
	char cAdress[20];
	char iPhoneNum[12];
	struct employe *next;
}EMP;

void Interface();
void menu();
EMP *Input(EMP *q);
void Save(EMP *head);
void Display();
void Inquire();
void Delete();
void Change();
EMP *CreateLink();
