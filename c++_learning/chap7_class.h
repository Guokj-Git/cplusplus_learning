//类的基本思想：数据抽象Data Abstraction和封装Encapsulation。数据抽象是一种依赖于接口Interface和实现Implementation分离的技术。
	//注意数据结构与数据抽象的区别

//7.1 定义抽象数据类型

struct Sales_data{
	//关于Sales_data对象的操作
	std::string isbn() const { return bookNo; }//1)隐式形参：指向调用该函数的对象，但在类中不明示。
											   //	return bookNo 相当于 return this->bookNo, this 为隐式形参。
											   //2)常量成员函数：在参数列表后添加const, 表示将隐式形参声明为指向常量的指针，
											   //	因而isbn()不能改变调用它的对象的内容。
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
	//数据成员
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
//在类外部定义成员函数
double Sales_data::avg_price() const{
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}
Sales_data& Sales_data::combine(const Sales_data &rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}
//Sales_data的非成员函数
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data);
