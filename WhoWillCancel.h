#pragma once

class cancel {
public:
	//cancel index
	int index;

	//ȸ����ȣ(���� id)
	int cNum;

	//ȸ���̸�
	char cName[10];

	//� �޼� ���� ù-��/ù-��
	double achieve;

	//���� (�����ֱٿ��-���ʵ����)
	int ingDay;

	//����� ����/����� : ���� ���� ���ֿ�
	double realDay;

	//�ܿ��� (��ǰ��*1/2 > (��ǰ�� ���ҽñ�-���ó�¥) ) > 0 : ���� ������
	int resDay;

};

class find {
public:
	int originIndex;
	int sum;
};

// 1. �ܿ��� ���� ������ ��� ������� cancel ����Ʈ�� ����
// 2. ����/����� �������� �⼮�� ���� => ���� � 0�ΰ�� ����
// 3. �⼮�� ���� ��� �� � �޼� ���� �������
//// 4. ���ٸ� PT���� or ������ ȸ������ üũ