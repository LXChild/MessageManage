#include"employe.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/******************************************************主菜单*************************************************/
void menu()
{
	int SelectNum;
	EMP *head,*p,*q;
	head = NULL;
	p = NULL;
	q = NULL;
	printf("\n\n\n\t\t\t1.职工信息添加\n");
	printf("\t\t\t2.职工信息浏览\n");
	printf("\t\t\t3.职工信息查询\n");
	printf("\t\t\t4.职工信息删除\n");
	printf("\t\t\t5.职工信息修改\n");
	printf("\t\t\t6.退出管理系统\n");
	
	printf("\t\t\t请输入你的选择: ");
	scanf("%d",&SelectNum);

	switch(SelectNum)
	{
	case 1:
		head = CreateLink();
		Save(head);
		menu();
		break;
	case 2:
		Display();
		system("cls");
		menu();
		break;		
	case 3:
		Inquire();
		system("cls");
		menu();
		break;
	case 4:
		Delete();
		system("cls");
		menu();
		break;
	case 5:
		Change();
		system("cls");
		menu();
		break;
	case 6:
		system("cls");
		printf("谢谢使用，再见！\n");
		system("pause");
		exit(0);
	default:
		system("cls");
		printf("\a输入有误，请重新输入!!!\n\n\n");	
		system("pause");
		menu();
	}
	return;
}
/************************************************************界面**************************************************/
void Interface()
{
	char data;
	FILE *fp;

	system("cls");
	if((fp = fopen("interface.txt","r")) == NULL)
	{
		printf("\aERROR opening file\n");
		exit(1);
	}	

	while((data = fgetc(fp)) != EOF)
	{
		putchar(data);
	}
	fclose(fp);

	return;
}
/***************************************************创建链表*********************************************/
EMP *CreateLink()
{
	int n,i,temp;
	EMP *head,*p,*q;
	FILE *fp;

	head = (EMP *)malloc(sizeof(EMP));
	p = (EMP *)malloc(sizeof(EMP));
	head = p;

	system("cls");
	fp = fopen("EmployeData.dat","ab+");

	fseek(fp,0,2);
	temp = ftell(fp);
	fseek(fp,0,0);
	while(temp > ftell(fp))
	{
		q = (EMP *)malloc(sizeof(EMP));
		p->next = q;
		fread(q,sizeof(EMP),1,fp);
		p = q;
		q = q->next;
		p->next = NULL;
	}
	printf("请输入要添加的职员的人数： \n");
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		q = (EMP *)malloc(sizeof(EMP));
		p->next = q;
		Input(q);
		p = q;
		q =q->next;
		p->next = NULL;
	}
	
	fclose(fp);
	return head;
}
/***************************************************************输入***********************************************/
EMP *Input(EMP *q)
{
		printf("请输入该员工工号：\n");
		scanf("%d",&q->iNum);
		printf("请输入该员工姓名：\n");
		scanf("%s",q->cName);
		printf("请输入该员工性别：\n");
		scanf("%s",q->cSex);
		printf("请输入该员工年龄：\n");
		scanf("%d",&q->iAge);
		printf("请输入该员工学历：\n");
		scanf("%s",q->cEdu);
		printf("请输入该员工工资：\n");
		scanf("%d",&q->iSalary);
		printf("请输入该员工地址: \n");
		scanf("%s",q->cAdress);
		printf("请输入该员工电话：\n");
		scanf("%s",&q->iPhoneNum);
		return q;
}
/**********************************************保存数据*******************************************/
void Save(EMP *head)
{
	FILE *fp;
	EMP *p;
	p = head->next;
	fp = fopen("EmployeData.dat","wb+");
	while(p != NULL)
	{
		fwrite(p,sizeof(EMP),1,fp);
		p = p->next;
	}
	printf("保存成功\n");
	fclose(fp);
	return;
}
/*********************************************显示**************************************************/
void Display()
{
	EMP *head,*p;
	FILE *fp;
	int temp,null = 1;
	system("cls");
	if((fp = fopen("EmployeData.dat","rb+")) == NULL)
	{
		printf("ERROR opening file\n");
		system("pause");				
		exit(1);
	}
	head = (EMP *)malloc(sizeof(EMP));
	p = head->next;
	fseek(fp,0,2);
	temp = ftell(fp);
	fseek(fp,0,0);
	while(temp > ftell(fp))
	{
		p = (EMP *)malloc(sizeof(EMP));
		if(fread(p,sizeof(EMP),1,fp) != 1)
		{
			printf("\a读取数据出错！！！");
			system("pause");
			exit(1);
		}
		null = 0;
		printf("%d\t%s\t%s\t%d\t%s\t%d\t%s\t%s\n",p->iNum,p->cName,p->cSex,p->iAge,p->cEdu,p->iSalary,p->cAdress,p->iPhoneNum);
		p = p->next;
	}
	if(null)
	{
		printf("数据为空！！！\a\n");
		exit(0);
	}
	system("pause");
	fclose(fp);
	return;
}
/*********************************************************查询*************************************************/
void Inquire()
{
	EMP *head,*p,*q;
	char cName[20];
	FILE *fp;
	system("cls");
	printf("请输入你要查找的职工姓名：\n");
	scanf("%s",cName);

	head = (EMP *)malloc(sizeof(EMP));
	p = (EMP *)malloc(sizeof(EMP));
	head = p;
	fp = fopen("EmployeData.dat","rb+");
	while(!feof(fp))
	{
		q = (EMP *)malloc(sizeof(EMP));
		p->next = q;
		
		if(fread(q,sizeof(EMP),1,fp) != 1)
		{
			printf("\a读取数据出错！！！");
			system("pause");
			exit(1);
		}
		if(strcmp(cName,q->cName) == 0)
		{
			system("cls");
			printf("%d\t%s\t%s\t%d\t%s\t%d\t%s\t%s\n",q->iNum,q->cName,q->cSex,q->iAge,q->cEdu,q->iSalary,q->cAdress,q->iPhoneNum);
			break;
		}
		else
		{
			p = q;
			q = q->next;		
			p->next = NULL;
		}
	}
	system("pause");
	fclose(fp);
	return;
}
/*****************************************************删除**********************************************************/
void Delete()
{
	FILE *fp;
	EMP *head,*p,*q;
	char cName[20];
	fp = fopen("EmployeData.dat","rb+");
	printf("请输入要删除的职工姓名：\n");
	scanf("%s",cName);
	head = (EMP *)malloc(sizeof(EMP));
	p = (EMP *)malloc(sizeof(EMP));
	head = p;
	while(!feof(fp))
	{
		q = (EMP *)malloc(sizeof(EMP));
		p->next = q;
		fread(q,sizeof(EMP),1,fp);
		if(strcmp(cName,q->cName) == 0)
		{
			system("cls");
			printf("%d\t%s\t%s\t%d\t%s\t%d\t%s\t%s\n",q->iNum,q->cName,q->cSex,q->iAge,q->cEdu,q->iSalary,q->cAdress,q->iPhoneNum);
			break;
		}
		else
		{
			p = q;
			q = q->next;
			p->next = NULL;
		}
	}
	p->next = p->next->next;
	free(q);
	Save(head);
	printf("删除成功！！！\n");
	fclose(fp);
	system("pause");

	return;
}
void Change()
{
	FILE *fp;
	EMP *head,*p,*q;
	char cName[20];
	int iItem;
	fp = fopen("EmployeData.dat","rb+");
	system("cls");
	printf("请输入要修改的职工姓名：\n");
	scanf("%s",cName);
	head = (EMP *)malloc(sizeof(EMP));
	p = (EMP *)malloc(sizeof(EMP));
	head = p;
	while(!feof(fp))
	{
		q = (EMP *)malloc(sizeof(EMP));
		p->next = q;
		fread(q,sizeof(EMP),1,fp);
		if(strcmp(cName,q->cName) == 0)
		{
			system("cls");
			printf("%d\t%s\t%s\t%d\t%s\t%d\t%s\t%s\n",q->iNum,q->cName,q->cSex,q->iAge,q->cEdu,q->iSalary,q->cAdress,q->iPhoneNum);
			break;
		}
		else
		{
			p = q;
			q = q->next;
			p->next = NULL;
		}
	}
	printf("请输入要修改的项目：\n");
	printf("1.职工号\n2.姓名\n3.性别\n4.年龄\n5.学历\n6.工资\n7.住址\n8.电话\n");
	scanf("%d",&iItem);
	printf("请输入新数据：\n");
	switch(iItem)
	{
	case 1:
		scanf("%d",q->iNum);
		break;
	case 2:
		scanf("%s",q->cName);
		break;
	case 3:
		scanf("%s",q->cSex);
		break;
	case 4:
		scanf("%d",q->iAge);
		break;
	case 5:
		scanf("%s",q->cEdu);
		break;
	case 6:
		scanf("%d",q->iSalary);
		break;
	case 7:
		scanf("%s",q->cAdress);
		break;
	case 8:
		scanf("%d",q->iPhoneNum);
		break;
	default:
		printf("输入错误！！！\n");
		system("pause");
		exit(0);
		break;
	}
	Save(head);
	fclose(fp);
	return ;
}
