//6.2 parameter

//ָ���β��������β�

	int reset(int *j) { //ָ���β�
		return 1;
		}
	
	int reset(int &i) { //�����β�
		return 2;
	}

//�����β�

	void twodimension_matrix1(int (*matrix) [10]) {}
	void towdimention_matrix2(int matrix[][10]) {}

//6.3return�����뷵��ֵ
	//���ع��������ڳ�ʼ������
	//�ں���return����ѭ����ҲӦ����һ��return��䡣

	int(*func1(int i))[10]{ int matrix[10]; return &matrix; } //��������ָ��ĺ���
	auto func2(int i)->int(*)[10] { int matrix[10]; return &matrix; } //β�÷�������
	int matrix[10];
		decltype(matrix) *func3(int i) { int matrix[10]; return &matrix; }

//6.4��������
	//���صĺ�����Ҫ���β�������������������ͬ
	//���ڴ��뺯�����ββ��ܶ���constӰ��

//6.5Ĭ��ʵ��
	void func(int i = 45, double j = 55, char k = ' ') {}
	

void chap6()
{
	//6.2
	int i = 0;
	std::cout << reset(i) << std::endl;
	std::cout << reset(&i) << std::endl;

	//6.5
	func(21);//�൱��func(21,55.' ');
}