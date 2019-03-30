//类的基本思想：数据抽象Data Abstraction和封装Encapsulation。数据抽象是一种依赖于接口Interface和实现Implementation分离的技术。
	//注意数据结构与数据抽象的区别

//7.1 定义抽象数据类型

struct Sales_data{ //使用class或struct的唯一区别：第一个访问说明符出现前，class中出现的成员都是private的，struct则为public。
	//添加友元（friend），以令在类外定义的函数可以使用private数据成员
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::ostream &print(std::ostream&, const Sales_data&);
	friend std::istream &read(std::istream&, Sales_data&);
	
public: //访问说明符。下面的成员可在全程序范围访问。
	//构造函数
	Sales_data() = default; //相当于合成默认构造函数（前提需要为内置类型的数据成员提供初始值）
	Sales_data(const std::string &s) :bookNo(s) {} //构造函数的初始值列表（当有数据成员未出现在括号内时，其将自动以合成默认构造函数代替）
	Sales_data(const std::string &s, unsigned n, double p) :
	bookNo(s), units_sold(n), revenue(p*n) {}
	Sales_data(std::istream&);
	//关于Sales_data对象的操作
	std::string isbn() const { return bookNo; } //1)隐式形参：指向调用该函数的对象，但在类中不明示。
												//	return bookNo 相当于 return this->bookNo, this 为隐式形参。
												//2)常量成员函数：在参数列表后添加const, 表示将隐式形参声明为指向常量的指针，
												//	因而isbn()不能改变调用它的对象的内容。
	Sales_data& combine(const Sales_data&);
private: //访问说明符。下面的成员尽可被类的成员函数访问，不能被使用该类的代码访问。
		 //访问说明符可在类内出现多次。
	double avg_price() const;
	//数据成员
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;

};

//在类外定义构造函数
Sales_data::Sales_data(std::istream& is) {
	read(is, *this);
}

//在类外部定义成员函数
double Sales_data::avg_price() const{
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}
Sales_data& Sales_data::combine(const Sales_data &rhs) { //combine rhs with the item who call the function
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

//Sales_data的非成员函数
Sales_data add(const Sales_data &lhs, const Sales_data &rhs) { //combine lhs and rhs, then return the conjunction of them
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}
std::ostream &print(std::ostream &os, const Sales_data &item) { //print the item to cout
	os << item.isbn() << " " << item.units_sold << " "
		<< item.revenue << " " << item.avg_price();
	return os;
}
std::istream &read(std::istream &is, Sales_data &item) { //read the item from cin
	double price = 0.0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price*item.units_sold;
	return is;
}

class Screen {
public:
	typedef std::string::size_type pos;
	Screen() = default;
	Screen(pos ht, pos wd, char c) : height(ht), width(wd), 
		contents(ht*wd, c) { }
	char get()const { return contents[cursor]; }
	inline char get(pos ht, pos wd)const;	//显式内联：可在类内声明处使用，
	Screen &move(pos r, pos c);				//也可在函数的定义处使用
	void some_member()const;
private:
	mutable size_t access_ctr;	//可变数据成员（mutable data member）：任何成员函数，包括const函数在内均可改变它的值
	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;
};

void Screen::some_member()const {
	++access_ctr;
}

inline Screen &Screen::move(pos r, pos c) {
	pos row = r*width;
	cursor = row + c;
	return *this;
}

char Screen::get(pos r, pos c)const {
	pos row = r*width;
	return contents[row + c];
}

class Window_mgr{
private:
	std::vector<Screen> screens{ Screen(24,80,' ') };
};

void chap7()
{
	//书店程序: 输入isbn，数量，单本价格，统计各类图书数据
	Sales_data total;
	if (read(std::cin, total)) {
		Sales_data trans;
		while (read(std::cin, trans)) {
			if (total.isbn() == trans.isbn())
				total=add(total, trans);
			else {
				print(std::cout, total) << std::endl;
				total = trans;
			}
		}
		print(std::cout, total) << std::endl;
	}
	else {
		std::cerr << "no data" << std::endl;
	}
}