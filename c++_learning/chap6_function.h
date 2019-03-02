//6.2 parameter

//指针形参与引用形参

	int reset(int *j) { //指针形参
		return 1;
		}
	
	int reset(int &i) { //引用形参
		return 2;
	}

//数组形参

	void twodimension_matrix1(int (*matrix) [10]) {}
	void towdimention_matrix2(int matrix[][10]) {}

//6.3return函数与返回值
	//返回过程类似于初始化变量
	//在含有return语句的循环后也应该有一条return语句。

	int(*func1(int i))[10]{ int matrix[10]; return &matrix; } //返回数组指针的函数
	auto func2(int i)->int(*)[10] { int matrix[10]; return &matrix; } //尾置返回类型
	int matrix[10];
		decltype(matrix) *func3(int i) { int matrix[10]; return &matrix; }

//6.4函数重载
	//重载的函数需要在形参数量或类型上有所不同
	//由于传入函数的形参不受顶层const影响

//6.5默认实参
	void func(int i = 45, double j = 55, char k = ' ') {}
	

void chap6()
{
	//6.2
	int i = 0;
	std::cout << reset(i) << std::endl;
	std::cout << reset(&i) << std::endl;

	//6.5
	func(21);//相当于func(21,55.' ');
}