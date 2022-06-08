#include<stdio.h>
#pragma warning(disable : 4996)

struct process
{
	int Name, Burst, Waiting, Turnaround, Start, Finish;
};

void Input(process a[], int &n, int &QT)
{
	printf("Moi nhap so luong process: ");
	scanf("%d", &n);
	printf("Moi nhap quantum time: ");
	scanf("%d", &QT);
	for (int i = 0; i < n; ++i)
	{
		printf("Moi nhap ten tien trinh và burst time cua tien trinh thu %d:", i + 1);
		scanf("%d%d", &a[i].Name, &a[i].Burst);
		a[i].Start = -1;
		a[i].Finish = 0;
		a[i].Turnaround = 0;
		a[i].Waiting = 0;
	}
}

void RR(process a[], int n, int qt, int &Twaiting, int &TTurnaround)
{
	int CopyBurst[10];
	int count = 0;
	int lc=0;
	int flag = 0;
	int time = 0;
	int take = 0;
	int set = -1;
	for (int i = 0; i < n; ++i)
		CopyBurst[i] = a[i].Burst;
	printf("So do Grantt chart: \n0");
	while (count != n)
	{
		if (a[lc].Burst != 0)
		{
			take = 1;
			if (a[lc].Start == -1)
				a[lc].Start = time;
			if (a[lc].Burst <= qt)
			{
				time += a[lc].Burst;
				a[lc].Burst = 0;
				flag = 1;
			}
			else
			{
				time += qt;
				a[lc].Burst -= qt;
			}
		}
		if (take == 1)
		{
			take = 0;
			if (set == lc)
				printf(" - %d", time);
			else
				printf(" - P%d - %d", a[lc].Name, time);
		}
		if (a[lc].Burst == 0 && flag == 1)
		{
			flag = 0;
			count++;
			a[lc].Waiting = time - CopyBurst[lc];
			a[lc].Turnaround = time;
			a[lc].Finish = time;
		}
		++lc;
		if (lc == n)
		{
			lc = 0;
		}
		
	}
	for (int i = 0; i < n; ++i)
	{
		a[i].Burst = CopyBurst[i];
		Twaiting += a[i].Waiting;
		TTurnaround += a[i].Turnaround;
	}
	
}

void Output(process a[], int n, int Twaiting, int TTurnaround)
{
	printf("\nPname\tStart\tStop");
	for (int i = 0; i < n; ++i)
	{
		printf("\n%d\t%d\t%d", a[i].Name, a[i].Start, a[i].Finish);
	}
	float arvw = (float)Twaiting / n;
	float arvt = (float)TTurnaround / n;
	printf("\nAverage waiting time: %f", arvw);
	printf("\nAverage turnaroundtime: %f", arvt);
}

int main()
{
	process a[10];
	int n;
	int QT;
	int Twaiting = 0;
	int TTurnaround = 0;
	Input(a, n, QT);
	RR(a, n, QT, Twaiting, TTurnaround);
	Output(a, n, Twaiting, TTurnaround);
}