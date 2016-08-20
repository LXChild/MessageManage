#include"employe.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/******************************************************���˵�*************************************************/
void menu()
{
	int SelectNum;
	EMP *head,*p,*q;
	head = NULL;
	p = NULL;
	q = NULL;
	printf("\n\n\n\t\t\t1.ְ����Ϣ���\n");
	printf("\t\t\t2.ְ����Ϣ���\n");
	printf("\t\t\t3.ְ����Ϣ��ѯ\n");
	printf("\t\t\t4.ְ����Ϣɾ��\n");
	printf("\t\t\t5.ְ����Ϣ�޸�\n");
	printf("\t\t\t6.�˳�����ϵͳ\n");
	
	printf("\t\t\t���������ѡ��: ");
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
		printf("ллʹ�ã��ټ���\n");
		system("pause");
		exit(0);
	default:
		system("cls");
		printf("\a������������������!!!\n\n\n");	
		system("pause");
		menu();
	}
	return;
}
/************************************************************����**************************************************/
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
/***************************************************��������*********************************************/
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
	printf("������Ҫ��ӵ�ְԱ�������� \n");
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
/***************************************************************����***********************************************/
EMP *Input(EMP *q)
{
		printf("�������Ա�����ţ�\n");
		scanf("%d",&q->iNum);
		printf("�������Ա��������\n");
		scanf("%s",q->cName);
		printf("�������Ա���Ա�\n");
		scanf("%s",q->cSex);
		printf("�������Ա�����䣺\n");
		scanf("%d",&q->iAge);
		printf("�������Ա��ѧ����\n");
		scanf("%s",q->cEdu);
		printf("�������Ա�����ʣ�\n");
		scanf("%d",&q->iSalary);
		printf("�������Ա����ַ: \n");
		scanf("%s",q->cAdress);
		printf("�������Ա���绰��\n");
		scanf("%s",&q->iPhoneNum);
		return q;
}
/**********************************************��������*******************************************/
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
	printf("����ɹ�\n");
	fclose(fp);
	return;
}
/*********************************************��ʾ**************************************************/
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
			printf("\a��ȡ���ݳ�������");
			system("pause");
			exit(1);
		}
		null = 0;
		printf("%d\t%s\t%s\t%d\t%s\t%d\t%s\t%s\n",p->iNum,p->cName,p->cSex,p->iAge,p->cEdu,p->iSalary,p->cAdress,p->iPhoneNum);
		p = p->next;
	}
	if(null)
	{
		printf("����Ϊ�գ�����\a\n");
		exit(0);
	}
	system("pause");
	fclose(fp);
	return;
}
/*********************************************************��ѯ*************************************************/
void Inquire()
{
	EMP *head,*p,*q;
	char cName[20];
	FILE *fp;
	system("cls");
	printf("��������Ҫ���ҵ�ְ��������\n");
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
			printf("\a��ȡ���ݳ�������");
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
/*****************************************************ɾ��**********************************************************/
void Delete()
{
	FILE *fp;
	EMP *head,*p,*q;
	char cName[20];
	fp = fopen("EmployeData.dat","rb+");
	printf("������Ҫɾ����ְ��������\n");
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
	printf("ɾ���ɹ�������\n");
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
	printf("������Ҫ�޸ĵ�ְ��������\n");
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
	printf("������Ҫ�޸ĵ���Ŀ��\n");
	printf("1.ְ����\n2.����\n3.�Ա�\n4.����\n5.ѧ��\n6.����\n7.סַ\n8.�绰\n");
	scanf("%d",&iItem);
	printf("�����������ݣ�\n");
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
		printf("������󣡣���\n");
		system("pause");
		exit(0);
		break;
	}
	Save(head);
	fclose(fp);
	return ;
}
